#include <QPen>
#include "psv_axisupitem.h"

PSV_AxisUpItem::PSV_AxisUpItem(const QMap<int, QVariant> &param, QGraphicsItem *parent)
    : PSV_AxisItem(param, parent)
{
    updateItem();
}

PSV_AxisUpItem::PSV_AxisUpItem(const QMap<int, QVariant> &param, const QStringList &list, QGraphicsItem *parent)
    : PSV_AxisItem(param, list, parent)
{
    updateItem();
}

PSV_AxisUpItem::~PSV_AxisUpItem()
{
    //
}

int PSV_AxisUpItem::type () const
{
    return PSV::axisUpItem;
}

void PSV_AxisUpItem::updateItem()
{
    PSV_Public::getLabels(m_maxValue, m_minValue,m_range, m_labelList);
    QPen linePen(QBrush(m_lineColor), m_lineWidth);
    QPen barPen(QBrush(m_markColor), m_markWidth);
    QRectF m_rect = getBoundingRect();
    {
        QGraphicsLineItem* lineItem = new QGraphicsLineItem(this);
        lineItem->setPen(linePen);
        lineItem->setLine(m_rect.right() + 2 * m_arrowsLength, m_rect.bottom()
                          , m_rect.left(), m_rect.bottom());
        lineItem->setZValue(1);

        QGraphicsLineItem* arrowsItem_up = new QGraphicsLineItem(this);
        arrowsItem_up->setPen(linePen);
        arrowsItem_up->setLine(m_rect.right() + 2 * m_arrowsLength, m_rect.bottom()
                                 , m_rect.right() + m_arrowsLength, m_rect.bottom()- 0.5 * m_arrowsLength);
        arrowsItem_up->setZValue(1);

        QGraphicsLineItem* arrowsItem_right = new QGraphicsLineItem(this);
        arrowsItem_right->setPen(linePen);
        arrowsItem_right->setLine(m_rect.right() + 2 * m_arrowsLength, m_rect.bottom()
                                  , m_rect.right() + m_arrowsLength, m_rect.bottom() + 0.5 * m_arrowsLength);
        arrowsItem_right->setZValue(1);
    }
    int count = m_labelList.count();
    if(count <= 1)
    {
        return;
    }
    m_markPointList.clear();
    double dy = m_rect.width() / (count - 1);
    bool isRotate = false;
    qreal maxHeight = 0.0;;
    qreal maxWidth = 0.0;;
    for(int index = 0; index < count; ++index)
    {
        QPair<QVariant, QString> labelPair = m_labelList.at(index);
        QGraphicsTextItem* textItem = new QGraphicsTextItem(labelPair.second, this);
        textItem->setDefaultTextColor(getDefaultColor());
        textItem->setFont(m_markFont);
        qreal height = textItem->boundingRect().height();
        qreal width = textItem->boundingRect().width();
        if(index == 0)
        {
            if(width > dy && height < 2*dy)//ÔÝÊ±´¦Àí
            {
               isRotate = true;
               maxHeight = width;
               maxWidth = height;
            }
            else
            {
                maxHeight = height;
                maxWidth = width;
            }
        }
        qreal x = m_rect.left() + (index * (m_rect.width())) / (count - 1);
        qreal y = m_rect.bottom() - m_markLength;
        if(isRotate)
        {
#if QT_VERSION > QT_VERSION_CHECK(4, 6, 0)
            textItem->setRotation(90);
#else
            textItem->rotate(90);
#endif
            textItem->setPos(x + 0.5 * height, y - width);
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
            textItem->setPos(x - 0.5 * width, y - height);
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
            lineItem->setLine(x - 0.5 * barPen.width(), m_rect.bottom(), x - 0.5 * barPen.width(), y);
        }
        else
        {
            lineItem->setLine(x, m_rect.bottom(), x, y);
        }
        m_markPointList.append(QPointF(x - 0.5 * barPen.width(), m_rect.bottom()));
    }
    //=================
    m_validRect =  QRectF(m_rect.x() - 0.5 * maxWidth
                          ,m_rect.bottom() - m_markLength - maxHeight
                          ,m_rect.width() + maxWidth
                          ,m_markLength + maxHeight);
}
