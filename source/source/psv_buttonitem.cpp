#include <QLinearGradient>
#include <QPen>
#include <QColor>
#include "psv_buttonitem.h"

PSV_ButtonItem::PSV_ButtonItem(const QMap<int, QVariant> &param, QGraphicsItem *parent)
    : PSV_Item(param,parent)
    , m_currentState(0)
{
    //
}

PSV_ButtonItem::~PSV_ButtonItem()
{
    //
}

int PSV_ButtonItem::type() const
{
    return PSV::buttonItem;
}

void PSV_ButtonItem::setItemNull()
{
    //
}

void PSV_ButtonItem::updateItem()
{
    QRectF boundingRect = getBoundingRect();
    QPointF center = boundingRect.center();
    qreal max = qMax(boundingRect.width(),boundingRect.height());
    QPen pen(Qt::NoPen);
    int zValue = 0;
    {
        QLinearGradient lg1(center.x(),boundingRect.top(),center.x(),boundingRect.bottom());
        lg1.setColorAt(0, QColor(255, 255, 255));
        lg1.setColorAt(1, QColor(166, 166, 166));
        QGraphicsEllipseItem *item =new QGraphicsEllipseItem(boundingRect,this);
        item->setZValue(zValue++);
        item->setBrush(lg1);
        item->setPen(pen);
    }
    {
//        QLinearGradient lg1(center.x(),m_rect.top(),center.x(),m_rect.bottom());
//        lg1.setColorAt(0, QColor(255, 255, 255));
//        lg1.setColorAt(1, QColor(166, 166, 166));
        qreal rate = 0.90;
        QRectF rect(center.x() - boundingRect.width() * rate * 0.5
                    ,center.y() - boundingRect.height() * rate * 0.5
                    ,rate * boundingRect.width(),boundingRect.height() * rate);
        QGraphicsEllipseItem *item =new QGraphicsEllipseItem(rect,this);
        item->setZValue(zValue++);
        QColor color(Qt::darkGray);
        QBrush brush(color);
        item->setBrush(brush);
        item->setPen(pen);
    }
    {
        QColor color(Qt::green);
        QString tip = color.name();
        if(m_dataMap.contains(m_currentState))
        {
            QPair<QColor,QString> pair = m_dataMap.value(m_currentState);
            color = pair.first;
            tip = pair.second;
        }
        QRadialGradient rg(center.x(),center.y(),max * 0.5);
        rg.setColorAt(0, color.light(100));
//        rg.setColorAt(0.6, color);
        rg.setColorAt(1, color.dark());
        qreal rate = 0.85;
        QRectF rect(center.x() - boundingRect.width() * rate * 0.5
                    ,center.y() - boundingRect.height() * rate * 0.5
                    ,rate * boundingRect.width(),boundingRect.height() * rate);
        QGraphicsEllipseItem *item =new QGraphicsEllipseItem(rect,this);
        item->setZValue(zValue++);
        item->setPen(pen);
        item->setBrush(rg);
        item->setToolTip(tip);
    }
}

void PSV_ButtonItem::setCurrentState(int state)
{
    if(m_currentState != state)
    {
        m_currentState = state;
        refreshItem();
    }
}

void PSV_ButtonItem::setStateColor(int state, const QColor &color, const QString &tip)
{
    m_dataMap.insert(state,QPair<QColor,QString>(color,tip.isEmpty() ? color.name() : tip));
}
