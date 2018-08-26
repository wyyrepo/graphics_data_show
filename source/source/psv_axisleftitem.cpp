#include <QPen>
#include "psv_axisleftitem.h"

PSV_AxisLeftItem::PSV_AxisLeftItem(const QMap<int, QVariant> &param, QGraphicsItem *parent)
    : PSV_AxisItem(param, parent)
{
    updateItem();
}

PSV_AxisLeftItem::PSV_AxisLeftItem(const QMap<int, QVariant> &param, const QStringList &list, QGraphicsItem *parent)
    : PSV_AxisItem(param, list, parent)
{
    updateItem();
}

PSV_AxisLeftItem::~PSV_AxisLeftItem()
{
    //
}

int PSV_AxisLeftItem::type () const
{
    return PSV::axisLeftItem;
}

void PSV_AxisLeftItem::updateItem()
{
    updateLabels();
//    QPen linePen(QBrush(QColor(Qt::white)), m_lineWidth);
    QPen linePen(QBrush(m_lineColor), m_lineWidth);
    QPen barPen(QBrush(m_markColor), m_markWidth);
    QRectF m_rect = getBoundingRect();
    {
        QGraphicsLineItem* lineItem = new QGraphicsLineItem(this);
        lineItem->setPen(linePen);
        lineItem->setLine(m_rect.right(), m_rect.y() - 2 * m_arrowsLength
                          , m_rect.right(), m_rect.bottom());
        lineItem->setZValue(1);

        QGraphicsLineItem* arrowsItem_left = new QGraphicsLineItem(this);
        arrowsItem_left->setPen(linePen);
        arrowsItem_left->setLine(m_rect.right(), m_rect.y()- 2 * m_arrowsLength
                                 , m_rect.right() - 0.5 * m_arrowsLength, m_rect.y() - m_arrowsLength);
        arrowsItem_left->setZValue(1);

        QGraphicsLineItem* arrowsItem_right = new QGraphicsLineItem(this);
        arrowsItem_right->setPen(linePen);
        arrowsItem_right->setLine(m_rect.right(), m_rect.y() - 2 * m_arrowsLength
                                  , m_rect.right() + 0.5 * m_arrowsLength, m_rect.y() - m_arrowsLength);
        arrowsItem_right->setZValue(1);
    }
    int count = m_labelList.count();
    if(count <= 1)
    {
        return;
    }

    double dx = 0.0;
    double dy = 0.0;
    if(m_isCenter && m_isList)
    {
        dy = -0.5 * m_rect.height() / count;
    }
    else
    {
        count--;
    }

    m_markPointList.clear();
    double oneSpace = m_rect.height() / count;
    bool isRotate = false;
    qreal maxHeight = 0.0;
    qreal maxWidth = 0.0;
    if(m_isCenter && m_isList)
    {
        count = m_labelList.count() + 1;
    }
    else
    {
        count = m_labelList.count();
    }

    for(int index = 0; index < m_labelList.count(); ++index)
    {
        QPair<QVariant, QString> labelPair = m_labelList.at(index);
        qreal y = m_rect.bottom() - index * oneSpace;
        QGraphicsTextItem *textItem = new QGraphicsTextItem(labelPair.second, this);
        textItem->setDefaultTextColor(getDefaultColor());
        textItem->setFont(m_markFont);
        qreal height = textItem->boundingRect().height();
        qreal width = textItem->boundingRect().width();
        if(index == 0)
        {
            if(height > oneSpace && width <= oneSpace)
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

        if(isRotate)
        {
#if QT_VERSION > QT_VERSION_CHECK(4, 6, 0)
            textItem->setRotation(90);
#else
            textItem->rotate(90);
#endif

            textItem->setPos(m_rect.right() - m_markLength, y - 0.5 * height);
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
            textItem->setPos(m_rect.right() - width - m_markLength, y - 0.5 * height);
            if(maxHeight < height)
            {
                maxHeight = height;
            }
            if(maxWidth < width)
            {
                maxWidth = width;
            }
        }
        textItem->moveBy(dx,dy);
        QGraphicsLineItem *lineItem = new QGraphicsLineItem(this);
        lineItem->setPen(barPen);
        if(index != 0 && index != count -1)
        {
            lineItem->setLine(m_rect.right(), y - 0.5 * barPen.width(), m_rect.right() - m_markLength, y - 0.5 * barPen.width());
        }
        else
        {
            lineItem->setLine(m_rect.right(), y, m_rect.right() - m_markLength, y);
        }
        m_markPointList.append(QPointF(m_rect.right(), y - 0.5 * barPen.width()));
    }
    //=================
    m_validRect =  QRectF(m_rect.right() - maxWidth - m_markLength
                          ,m_rect.y() - 0.5 * maxHeight
                          ,m_markLength + maxWidth
                          ,m_rect.height() + maxHeight);
//    QGraphicsRectItem *item = new QGraphicsRectItem(m_validRect,this);
}
