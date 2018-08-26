#include <QPen>
#include "psv_axisrightitem.h"

PSV_AxisRightItem::PSV_AxisRightItem(const QMap<int, QVariant> &param, QGraphicsItem *parent)
    : PSV_AxisItem(param, parent)
{
    updateItem();
}

PSV_AxisRightItem::PSV_AxisRightItem(const QMap<int, QVariant> &param, const QStringList &list, QGraphicsItem *parent)
    : PSV_AxisItem(param, list, parent)
{
    updateItem();
}

PSV_AxisRightItem::~PSV_AxisRightItem()
{
    //
}

int PSV_AxisRightItem::type () const
{
    return PSV::axisRightItem;
}

void PSV_AxisRightItem::updateItem()
{
    PSV_Public::getLabels(m_maxValue, m_minValue,m_range, m_labelList);
    QPen linePen(QBrush(m_lineColor), m_lineWidth);
    QPen barPen(QBrush(m_markColor), m_markWidth);
    QRectF m_rect = getBoundingRect();
    {
        QGraphicsLineItem* lineItem = new QGraphicsLineItem(this);
        lineItem->setPen(linePen);
        lineItem->setLine(m_rect.left(), m_rect.y() - 2 * m_arrowsLength
                          , m_rect.left(), m_rect.bottom());
        lineItem->setZValue(1);

        QGraphicsLineItem* arrowsItem_left = new QGraphicsLineItem(this);
        arrowsItem_left->setPen(linePen);
        arrowsItem_left->setLine(m_rect.left(), m_rect.y()- 2 * m_arrowsLength
                                 , m_rect.left()- 0.5 * m_arrowsLength, m_rect.y() - m_arrowsLength);
        arrowsItem_left->setZValue(1);

        QGraphicsLineItem* arrowsItem_right = new QGraphicsLineItem(this);
        arrowsItem_right->setPen(linePen);
        arrowsItem_right->setLine(m_rect.left(), m_rect.y() - 2 * m_arrowsLength
                                  , m_rect.left() + 0.5 * m_arrowsLength, m_rect.y() - m_arrowsLength);
        arrowsItem_right->setZValue(1);
    }
    int count = m_labelList.count();
    if(count <= 1)
    {
        return;
    }
    m_markPointList.clear();
    double dy = m_rect.height() / (count - 1);
    bool isRatote = false;
    qreal maxHeight = 0.0;;
    qreal maxWidth = 0.0;;
    for(int index = 0; index < count; ++index)
    {
        QPair<QVariant, QString> labelPair = m_labelList.at(index);
        qreal y = m_rect.bottom() - index * dy;
        QGraphicsTextItem *textItem = new QGraphicsTextItem(labelPair.second, this);
        textItem->setDefaultTextColor(getDefaultColor());
        textItem->setFont(m_markFont);
        qreal height = textItem->boundingRect().height();
        qreal width = textItem->boundingRect().width();
        if(index == 0)
        {
            if(height > dy && width <= dy)
            {
                //                isRotate = true;//左右不需要旋转
                maxHeight = width;
                maxWidth = height;
            }
            else
            {
                maxHeight = height;
                maxWidth = width;
            }
        }

        if(isRatote)
        {
#if QT_VERSION > QT_VERSION_CHECK(4, 6, 0)
            textItem->setRotation(90);
#else
            textItem->rotate(90);
#endif
            textItem->setPos(m_rect.left() + m_markLength + height, y - 0.5 * height);
            if(maxHeight < width)
            {
                maxHeight = width;
            }
            if(maxWidth < height)
            {
                maxWidth = height;
            }
        }
        else
        {
            textItem->setPos(m_rect.left() + m_markLength, y - 0.5 * height);
            if(maxHeight < height)
            {
                maxHeight = height;
            }
            if(maxWidth < width)
            {
                maxWidth = width;
            }
        }
        QGraphicsLineItem *lineItem = new QGraphicsLineItem(this);
        lineItem->setPen(barPen);
        if(index != 0 && index != count -1)
        {
            lineItem->setLine(m_rect.left(), y - 0.5 * barPen.width(), m_rect.left() + m_markLength, y - 0.5 * barPen.width());
        }
        else
        {
            lineItem->setLine(m_rect.left(), y, m_rect.left() + m_markLength, y);
        }
        m_markPointList.append(QPointF(m_rect.left(), y - 0.5 * barPen.width()));
    }
    //=================
    m_validRect =  QRectF(m_rect.x()
                          ,m_rect.y() - 0.5 * maxHeight
                          ,m_markLength + maxWidth
                          ,m_rect.height() + maxHeight);
//    QGraphicsRectItem *item = new QGraphicsRectItem(m_validRect,this);
}
