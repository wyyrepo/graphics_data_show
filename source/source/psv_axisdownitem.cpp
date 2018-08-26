#include <QPen>
#include "psv_axisdownitem.h"

PSV_AxisDownItem::PSV_AxisDownItem(const QMap<int, QVariant> &param, QGraphicsItem *parent)
    : PSV_AxisItem(param, parent)
{
    updateItem();
}

PSV_AxisDownItem::PSV_AxisDownItem(const QMap<int, QVariant> &param, const QStringList &list, QGraphicsItem *parent)
    : PSV_AxisItem(param,list, parent)
{    
    updateItem();
}

PSV_AxisDownItem::~PSV_AxisDownItem()
{
    //
}

int PSV_AxisDownItem::type () const
{
    return PSV::axisDownItem;
}

void PSV_AxisDownItem::updateItem()
{
//    m_markFont.setPointSizeF(m_rect.width() * m_rect.height() * 0.0005);
    updateLabels();
    QPen linePen(QBrush(m_lineColor), m_lineWidth);
    QPen barPen(QBrush(m_markColor), m_markWidth);
    QRectF m_rect = getBoundingRect();
    {
        QGraphicsLineItem* lineItem = new QGraphicsLineItem(this);
        lineItem->setPen(linePen);
        lineItem->setLine(m_rect.right() + 2 * m_arrowsLength, m_rect.top()
                          , m_rect.left(), m_rect.top());
        lineItem->setZValue(1);

        QGraphicsLineItem* arrowsItem_up = new QGraphicsLineItem(this);
        arrowsItem_up->setPen(linePen);
        arrowsItem_up->setLine(m_rect.right() + 2 * m_arrowsLength, m_rect.y()
                                 , m_rect.right() + m_arrowsLength, m_rect.y()- 0.5 * m_arrowsLength);
        arrowsItem_up->setZValue(1);

        QGraphicsLineItem* arrowsItem_right = new QGraphicsLineItem(this);
        arrowsItem_right->setPen(linePen);
        arrowsItem_right->setLine(m_rect.right() + 2 * m_arrowsLength, m_rect.y()
                                  , m_rect.right() + m_arrowsLength, m_rect.y() + 0.5 * m_arrowsLength);
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
        dx = 0.5 * m_rect.width() / count;
    }
    else
    {
        count--;
    }

    double oneSpace = m_rect.width() / count;
    m_markPointList.clear();
    bool isRotate = false;
    qreal maxHeight = 0.0;;
    qreal maxWidth = 0.0;;
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
        QGraphicsTextItem* textItem = new QGraphicsTextItem(labelPair.second, this);
        textItem->setDefaultTextColor(getDefaultColor());
        textItem->setFont(m_markFont);
        qreal height = textItem->boundingRect().height();
        qreal width = textItem->boundingRect().width();
        if(index == 0)
        {
            if(width > oneSpace && height < 2*oneSpace)//ÔÝÊ±´¦Àí
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
        qreal y = m_rect.top() + m_markLength;
        if(isRotate)
        {
#if QT_VERSION > QT_VERSION_CHECK(4, 6, 0)
            textItem->setRotation(90);
#else
            textItem->rotate(90);
#endif

            textItem->setPos(x + 0.5 * height, y);
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
            textItem->setPos(x - 0.5 * width, y);
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
            lineItem->setLine(x - 0.5 * barPen.width(), m_rect.top(), x - 0.5 * barPen.width(), m_rect.top() + m_markLength);
        }
        else
        {
            lineItem->setLine(x, m_rect.top(), x, m_rect.top() + m_markLength);
        }
        m_markPointList.append(QPointF(x - 0.5 * barPen.width(), m_rect.top()));
    }
    //=================
    m_validRect =  QRectF(m_rect.x() - 0.5 * maxWidth
                          ,m_rect.y()
                          ,m_rect.width() + maxWidth
                          ,m_markLength + maxHeight);
//    QGraphicsRectItem *item = new QGraphicsRectItem(m_validRect,this);
}

