#include <QPainter>

#include "psv_graphicsrect.h"

PSV_GraphicsRect::PSV_GraphicsRect(QGraphicsItem *parent) : QGraphicsRectItem(parent)
{
    //
}

PSV_GraphicsRect::PSV_GraphicsRect(const QRectF &rect, QGraphicsItem *parent)
    : QGraphicsRectItem(rect,parent)
{
    //
}

PSV_GraphicsRect::PSV_GraphicsRect(qreal x, qreal y, qreal width, qreal height, QGraphicsItem *parent)
    : QGraphicsRectItem(x,y,width,height,parent)
{
    //
}

PSV_GraphicsRect::~PSV_GraphicsRect()
{
    //
}

void PSV_GraphicsRect::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawLine(QLine(1,1,100,100));
    painter->drawRect(rect());
//    painter->setPen(d->pen);
//    painter->setBrush(d->brush);
//    painter->drawRect(d->rect);
//    if (option->state & QStyle::State_Selected)
//        qt_graphicsItem_highlightSelected(this, painter, option);
}
