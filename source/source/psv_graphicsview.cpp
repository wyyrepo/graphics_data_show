#include <QWheelEvent>
#include "psv_public.h"
#include "psv_graphicsview.h"

PSV_GraphicsView::PSV_GraphicsView(QWidget *parent) : QGraphicsView(parent)
{
    //
}

PSV_GraphicsView::PSV_GraphicsView(QGraphicsScene *scene, QWidget *parent) : QGraphicsView(scene, parent)
{
    //
}

PSV_GraphicsView::~PSV_GraphicsView()
{
    //
}

void PSV_GraphicsView::wheelEvent(QWheelEvent *event)
{
    int delta = event->delta();
    double scale_x = 1.0;
    double scale_y = 1.0;
    if(delta >0 )
    {
        scale_x = 1.25;
        scale_y = 1.25;
    }
    else if(delta < 0)
    {
        scale_x = 1 / 1.25;
        scale_y = 1 / 1.25;
    }
    else
    {
        //
    }
    this->scale(scale_x, scale_y);
}

void PSV_GraphicsView::resizeEvent(QResizeEvent *event)
{
    PSV_NOUSED(event);
    if(scene())
    {
        scene()->setSceneRect(this->rect());
        scene()->advance();

    }
}
