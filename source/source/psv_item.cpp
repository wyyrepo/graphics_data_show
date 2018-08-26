#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include "psv_item.h"
#include "psv_cfgdlg_item.h"

PSV_Item::PSV_Item(QGraphicsItem *parent)
    : QGraphicsObject(parent)
    ,d(new PSV_Item_Private())
{
    initParam();
}

PSV_Item::PSV_Item(const QMap<int, QVariant> &param, QGraphicsItem *parent)
    : QGraphicsObject(parent)
    ,d(new PSV_Item_Private(param))
{
    initParam();
    if(param.contains(PSV::dx))
    {
        m_itemPointParam.m_dx = param.value(PSV::dx).toDouble();
    }
    if(param.contains(PSV::dy))
    {
        m_itemPointParam.m_dy = param.value(PSV::dy).toDouble();
    }
    if(param.contains(PSV::dw))
    {
        m_itemPointParam.m_dw = param.value(PSV::dw).toDouble();
    }
    if(param.contains(PSV::dh))
    {
        m_itemPointParam.m_dh = param.value(PSV::dh).toDouble();
    }
}

PSV_Item::~PSV_Item()
{
    delete d;
    d = NULL;
}

QRectF PSV_Item::boundingRect() const
{
    return getBoundingRect();
}

QPainterPath PSV_Item::shape() const
{
    return m_painterPath;
}

void PSV_Item::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{    
    PSV_NOUSED(painter);
    PSV_NOUSED(option);
    PSV_NOUSED(widget);
    return;
}

void PSV_Item::beginSet()
{
    m_isBeginSet = true;
    m_isAutoUpdate = false;
}

void PSV_Item::endSet()
{
    if(m_isBeginSet)
    {
        if(!m_isAutoUpdate)
        {
            m_isAutoUpdate = true;
            refreshItem();
        }
    }
    else
    {
        PSV_Public::printMes("请设置对应的起始设置标识PSV_Item::beginSet()","warning:警告");
    }
}

QMap<int, QVariant> PSV_Item::getParam()
{
    return d->getParam();
}

void PSV_Item::setParam(const QMap<int, QVariant> &param)
{
    d->setParam(param);
}

void PSV_Item::setData(int role, const QVariant &value, bool isUpdate)
{
   d->setData(role,value);
   if(isUpdate)
   {
       refreshItem();
   }
}

QVariant PSV_Item::getData(int role, const QVariant &defaultValue) const
{
    return d->getData(role,defaultValue);
}

bool PSV_Item::isSetable(int role)
{
    if(d->m_propertyList.contains(role) && (!d->m_unsetPropertyList.contains(role)))
    {
        return true;
    }
    return false;
}

PSV_Item *PSV_Item::getInstance()
{
    return NULL;
}

void PSV_Item::refreshItem()
{
    if(clearAll())
    {
        refreshRect();
        updateItem();
    }
}

bool PSV_Item::clearAll()
{
    QGraphicsScene *scene = this->scene();
    QList<QGraphicsItem*> chirldrenItem = this->childItems();
    if(scene != NULL)
    {
        for(int i = 0; i < chirldrenItem.count(); ++i)
        {
            scene->removeItem(chirldrenItem.at(i));
        }
        setItemNull();//设为NULL
        return true;
    }
    return false;
}

void PSV_Item::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::RightButton)
    {
        showMenu();
    }
    return QGraphicsItem::mousePressEvent(event);
}

void PSV_Item::showMenu()
{
}

void PSV_Item::showPropertyDlg()
{
    PSV_Item* item = getInstance();
    if(item == NULL)
    {
        return;
    }
    QMap<int,QVariant> param = item->getParam();
    PSV_CfgDlg_Item dlg(*item);
    if(dlg.exec() != QDialog::Accepted)
    {
        item->setParam(param);
        item->refreshItem();
    }
    return;
}

void PSV_Item::addProperty(int role)
{
    if(!d->m_propertyList.contains(role))
    {
        d->m_propertyList.append(role);
    }
}

void PSV_Item::onShowPropertyDlg()
{
    showPropertyDlg();
}

void PSV_Item::initParam()
{
    addDefaultParam(PSV::defaultColor,QColor(Qt::black));
    addDefaultParam(PSV::boundingRect,QRectF(0,0,600,400));
    addDefaultParam(PSV::margin,3);
    addUnsetParam(PSV::defaultColor);
    addUnsetParam(PSV::boundingRect);
    m_isBeginSet=false;
    m_isAutoUpdate=true;
    m_isAdvancetable=false;
}

void PSV_Item::advance(int phase)
{
    if(phase != 0 && m_isAdvancetable)
    {
        refreshItem();
    }
}

void PSV_Item::refreshRect()
{
    QGraphicsScene *scene = this->scene();
    if(scene != NULL && m_isAdvancetable)
    {
        adjustPointParam();
        QRectF rect = scene->sceneRect();
        QRectF m_rect = QRectF(rect.x() + m_itemPointParam.m_dx * rect.width()
                        ,rect.y() + m_itemPointParam.m_dy * rect.height()
                        ,m_itemPointParam.m_dw * rect.width()
                        ,m_itemPointParam.m_dh * rect.height());
        d->setData(PSV::boundingRect,m_rect);
    }
}


QColor PSV_Item::getDefaultColor() const
{
    return getData(PSV::defaultColor,QColor(Qt::black)).value<QColor>();
}

QRectF PSV_Item::getBoundingRect() const
{
    return getData(PSV::boundingRect,QRectF(0,0,600,400)).toRectF();
}

int PSV_Item::getMargin() const
{
    return getData(PSV::margin,3).toInt();
}

void PSV_Item::addDefaultParam(int role, const QVariant &v)
{
    addProperty(role);
    if(!d->m_param.contains(role))
    {
        d->setData(role,v);
    }
}

void PSV_Item::addUnsetParam(int role)
{
    if(!d->m_unsetPropertyList.contains(role))
    {
        d->m_unsetPropertyList.append(role);
    }
}

void PSV_Item::deleteUnsetParam(int role)
{
    d->m_unsetPropertyList.removeOne(role);
}

void PSV_Item::adjustPointParam()
{
    if(m_itemPointParam.m_dx < 0 && m_itemPointParam.m_dx > 1)
    {
        m_itemPointParam.m_dx = 0;
    }
    if(m_itemPointParam.m_dy < 0 && m_itemPointParam.m_dy > 1)
    {
        m_itemPointParam.m_dy = 0;
    }
    if(m_itemPointParam.m_dw < 0 && m_itemPointParam.m_dw > 1)
    {
        m_itemPointParam.m_dw = 1;
    }
    if(m_itemPointParam.m_dh < 0 && m_itemPointParam.m_dh > 1)
    {
        m_itemPointParam.m_dh = 1;
    }
}
