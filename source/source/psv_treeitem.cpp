#include <QPen>
#include <QColor>
#include "psv_treeitem.h"

PSV_TreeItemData::PSV_TreeItemData(PSV_TreeItemData *parent)
    : m_isModified(true)
    , m_leafCount(0)
    , m_level(0)
    , m_depth(0.0)
    , m_distance(1.0)
    , m_parent(parent)
{
}

PSV_TreeItemData::~PSV_TreeItemData()
{
    //
}

void PSV_TreeItemData::setDistance(qreal distance)
{
    if(distance >= 0)
    {
        m_distance = distance;
        m_isModified = true;
    }
}

void PSV_TreeItemData::setParent(PSV_TreeItemData *parent)
{
    if(m_parent != NULL)
    {
        m_parent->removeChild(this);
    }
    m_parent = parent;
    if(parent != NULL)
    {
        parent->addChild(this);
    }
    m_isModified = true;
}

void PSV_TreeItemData::addChild(PSV_TreeItemData *child)
{
    if(child != NULL && !m_children.contains(child))
    {
        m_children.append(child);
        m_isModified = true;
    }
}

void PSV_TreeItemData::removeChild(PSV_TreeItemData *child)
{
    if(m_children.contains(child))
    {
        m_children.removeAll(child);
        m_isModified = true;
        child->setParent(NULL);
    }
}

QString PSV_TreeItemData::text()
{
    return m_data.value(Qt::DisplayRole).toString();
}

void PSV_TreeItemData::setText(const QString &text)
{
    m_data.insert(Qt::DisplayRole,text);
}

QList<PSV_TreeItemData*> PSV_TreeItemData::children()
{
    return m_children;
}

int PSV_TreeItemData::leafCount()
{
    if(m_isModified)
    {
        updateTreeMes();
    }
    return m_leafCount;
}

int PSV_TreeItemData::level()
{
    if(m_isModified)
    {
        updateTreeMes();
    }
    return m_level;
}

qreal PSV_TreeItemData::depth()
{
    if(m_isModified)
    {
        updateTreeMes();
    }
    return m_depth;
}

qreal PSV_TreeItemData::distance() const
{
    return m_distance;
}

void PSV_TreeItemData::updateTreeMes()
{
    int leafCount = 0;
    int level = 0;
    qreal depth = 0;
    calculateTreeMes(leafCount,level,depth);
}

void PSV_TreeItemData::calculateTreeMes(int &leafCount, int &level, qreal &depth)
{
    m_isModified = false;
    if(m_children.count() <= 0)
    {
        m_leafCount = 1;
        m_depth = 0;
        m_level = 1;

        leafCount += 1;
        depth += m_distance;
        level += 1;
    }
    else
    {
        double maxDepth = 0;
        int maxLevel = 0;
        m_leafCount = 0;
        for(int i = 0; i < m_children.count(); ++i)
        {
            int tempLeafCount = 0;
            int tempLevel = 0;
            qreal tempDepth = m_children.at(i)->m_distance;
            m_children.at(i)->calculateTreeMes(tempLeafCount,tempLevel,tempDepth);
            if(maxDepth < tempDepth)
            {
                maxDepth = tempDepth;
            }
            leafCount += tempLeafCount;
            m_leafCount += tempLeafCount;
            if(maxLevel < tempLevel)
            {
                maxLevel = tempLevel;
            }
//            level += tempLevel;
        }
        depth += maxDepth;
        level += maxLevel;
        m_depth = maxDepth;
        m_level = maxLevel;
    }
//    PSV_Public::printMes(text(),"text");
//    PSV_Public::printMes(m_depth,"m_depth");
//    PSV_Public::printMes(m_level,"m_level");
//    PSV_Public::printMes(m_leafCount,"m_leafCount");
//    PSV_Public::printMes(m_distance,"m_distance");
}

PSV_TreeItemData* PSV_TreeItemData::parent()
{
    return m_parent;
}

void PSV_TreeItemData::setModified(bool isModified)
{
    m_isModified = isModified;
}

//=================================================
PSV_TreeItem::PSV_TreeItem(const QMap<int, QVariant> &param, PSV_TreeItemData *itemData, QGraphicsItem *parent)
//    : PSV_Item(param,parent)
    : PSV_ChartItem(param,parent)
    , m_itemData(itemData)
    , m_dw(0)
    , m_dhRatio(0)
{
    setAcceptHoverEvents(false);
    m_axisParam_left.m_isShow = true;
    createAxisi();
}

PSV_TreeItem::~PSV_TreeItem()
{
    //
}

int PSV_TreeItem::type() const
{
    return PSV::treeItem;
}

void PSV_TreeItem::setPrivateItemNull()
{
    //
}

PSV::DATATYPE PSV_TreeItem::dataType()
{
    return PSV::E_DATATYPE_UNKOWN;
}

void PSV_TreeItem::beforeUpdateItem()
{
    qreal depth = m_itemData->depth();
    m_max_y_left = depth;
    m_min_y_left = 0;

    adjusetMargin();
    updateChartRect();
    if(m_itemData == NULL)
    {
        return;
    }
    int leafCount = m_itemData->leafCount();
    if(leafCount <= 0)
    {
        return;
    }
    depth = m_max_y_left;
    if(depth <= 0)
    {
        m_dhRatio = 1;
    }
    else
    {
        m_dhRatio = m_chartRect.height() / depth;
    }
    m_dw = m_chartRect.width() / leafCount;
}

void PSV_TreeItem::afterUpdateItem()
{
//    m_dh = 50;
    double depth  = m_itemData->depth();
    PSV_Public::printMes(depth,"depth");
    PSV_Public::printMes(m_max_y_left,"m_max_y_left");
    PSV_Public::printMes(m_dhRatio,"m_dhRatio");

    QPointF point(m_chartRect.center().x(),m_chartRect.top() + (m_max_y_left - depth) * m_dhRatio);
    PSV_Public::printMes(point,"point");
    PSV_Public::printMes(m_chartRect,"m_chartRect");

    paintLine(QLineF(point,point),m_itemData);
}

void PSV_TreeItem::paintLine(const QLineF &parentVLine, PSV_TreeItemData *itemData)
{
    if(itemData == NULL)
    {
        return;
    }
    QPointF point2 = parentVLine.p2();
    QList<PSV_TreeItemData*> children = itemData->children();
    int leafCount = itemData->leafCount();
    int count = children.count();
    QPen pen;
    pen.setColor(QColor(Qt::red));
    QPen pen_vLine;
    pen_vLine.setColor(QColor(Qt::blue));
    QPen pen_hLine;
    QString tempText = itemData->text().trimmed();
    QString text;
    for(int i = 0; i < tempText.length(); ++i)
    {
        text.append(tempText.at(i));
        if(i != tempText.length() - 1)
        {
            text.append("\n");
        }
    }
    QGraphicsItem* nodeItem = new QGraphicsEllipseItem(QRectF(0,0,1,1),this);
    nodeItem->setToolTip(tempText);

    QSizeF size = nodeItem->boundingRect().size();
    nodeItem->setPos(point2.x() - size.width() * 0.5,point2.y() - size.height() * 0.5);
    QRectF rect = QRectF(nodeItem->pos().x(),nodeItem->pos().y(),size.width(),size.height());

//    QGraphicsRectItem* rectItem = new QGraphicsRectItem(rect,this);
//    rectItem->setPen(pen);
    if(parentVLine.length() > PSV_ZEOR)
    {
        QLineF line = parentVLine;
        line.setP2(QPointF(line.x2(),rect.top()));
        QGraphicsLineItem* item = new QGraphicsLineItem(line,this);
        PSV_NOUSED(item);
    }
    if(count > 0)
    {
        QLineF leftHLine(point2.x() - leafCount * 0.5 * m_dw
                      ,point2.y()
                      ,rect.left()
                      ,point2.y());

        QLineF rightHLine(rect.right()
                      ,point2.y()
                      ,point2.x() + leafCount * 0.5 * m_dw
                      ,point2.y());

        double curX1 = leftHLine.x1();
        for(int i = 0; i < count; ++i)
        {
            PSV_TreeItemData* tempItemData = children.at(i);
            int tempLeafCount = tempItemData->leafCount();
            curX1 += tempLeafCount * 0.5 * m_dw;
            if(i == 0)
            {
                leftHLine.setP1(QPointF(curX1,leftHLine.y1()));
            }
            if(i == count - 1)
            {
                rightHLine.setP2(QPointF(curX1,leftHLine.y2()));
            }
            double y1 = point2.y();
            double y2 = point2.y() + tempItemData->distance() * m_dhRatio;
            if(curX1 > rect.left() && curX1 < rect.right())
            {
                y1 = rect.bottom();
            }
            QLineF lineV(curX1,y1,curX1,y2);
            curX1 += tempLeafCount * 0.5 * m_dw;
            paintLine(lineV,tempItemData);
        }
        if(count > 1)
        {
            QGraphicsLineItem* leftHLineItem = new QGraphicsLineItem(leftHLine,this);
            leftHLineItem->setPen(pen_hLine);
            QGraphicsLineItem* rightHLineItem = new QGraphicsLineItem(rightHLine,this);
            rightHLineItem->setPen(pen_hLine);
        }
    }
}

//void PSV_TreeItem::paintLine(const QPointF &point, PSV_TreeItemData *itemData)
//{
//    if(itemData == NULL)
//    {
//        return;
//    }
//    QList<PSV_TreeItemData*> children = itemData->children();
//    int leafCount = itemData->leafCount();
//    int count = children.count();
//    QPen pen;
//    pen.setColor(QColor(Qt::red));
//    QPen pen_vLine;
//    pen_vLine.setColor(QColor(Qt::blue));
//    QPen pen_hLine;
//    pen_hLine.setColor(QColor(Qt::yellow));
////    PSV_Public::printMes(itemData->text(),"itemData->text()");
////    PSV_Public::printMes(count,"count");
//    QString tempText = itemData->text().trimmed();
//    QString itemText;
//    for(int i = 0; i < tempText.length(); ++i)
//    {
//        itemText.append(tempText.at(i));
//        if(i != tempText.length() - 1)
//        {
//            itemText.append("\n");
//        }
//    }


//    if(count <= 0)
//    {
//        QGraphicsTextItem* item = new QGraphicsTextItem(itemText,this);
//        QRectF rect = item->boundingRect();
//        item->setPos(point.x() - rect.width() * 0.5,point.y());
//        QGraphicsRectItem* rectItem = new QGraphicsRectItem(QRectF(item->pos().x(),item->pos().y(),rect.width(),rect.height()),this);
//        rectItem->setPen(pen);
//    }
//    else
//    {
//        qreal m_dh = itemData->distance() * m_dhRatio;
//        QGraphicsTextItem* item = new QGraphicsTextItem(itemText,this);
//        QRectF rect = item->boundingRect();
//        item->setPos(point.x() - rect.width() * 0.5,point.y());
//        QGraphicsRectItem* rectItem = new QGraphicsRectItem(QRectF(item->pos().x(),item->pos().y(),rect.width(),rect.height()),this);
//        rectItem->setPen(pen);

//        QLineF lineV1(point.x(),point.y() + rect.height(),point.x(),point.y() + rect.height() + 0.5 * m_dh);
//        QGraphicsLineItem* lineItem1 = new QGraphicsLineItem(lineV1,this);
//        lineItem1->setPen(pen_vLine);


//        QLineF lineH(point.x() - leafCount * 0.5 * m_dw
//                      ,lineV1.y1() + 0.5 * m_dh
//                      ,point.x() + leafCount * 0.5 * m_dw
//                      ,lineV1.y1() + 0.5 * m_dh);

//        double curX1 = lineH.x1();
//        double y1 = lineH.y1();
//        double y2 = lineH.y1() + 0.5 * m_dh;
//        for(int i = 0; i < count; ++i)
//        {
//            PSV_TreeItemData* tempItemData = children.at(i);
//            curX1 += tempItemData->leafCount() * 0.5 * m_dw;
//            if(i == 0)
//            {
//                lineH.setP1(QPointF(curX1,lineH.y1()));
//            }
//            if(i == count - 1)
//            {
//                lineH.setP2(QPointF(curX1,lineH.y2()));
//            }
//            QLineF lineV(curX1,y1,curX1,y2);
//            QGraphicsLineItem* lineItem1 = new QGraphicsLineItem(lineV,this);
//            int tempLeafCount = tempItemData->leafCount();
//            curX1 += tempLeafCount * 0.5 * m_dw;
//            paintLine(lineV.p2(),tempItemData);
//        }
//        QGraphicsLineItem* hLineItem = new QGraphicsLineItem(lineH,this);
//        hLineItem->setPen(pen_hLine);
//    }
//}
