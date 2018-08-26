#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItem>

#include "psv_graphicsscene.h"

PSV_GraphicsScene::PSV_GraphicsScene(const QRectF &sceneRect, QObject *parent)
    : QGraphicsScene(sceneRect, parent)
{
    //
}

PSV_GraphicsScene::PSV_GraphicsScene(QObject *parent) : QGraphicsScene(parent)
{
    //
}

PSV_GraphicsScene::PSV_GraphicsScene(qreal x, qreal y, qreal width, qreal height, QObject *parent)
    : QGraphicsScene(x, y, width, height, parent)
{
    //
}

PSV_GraphicsScene::~PSV_GraphicsScene()
{
    //
}

void PSV_GraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
//    QGraphicsItem *item = this->itemAt(event->scenePos());
//    if(item != NULL)
//    {
//        item->setSelected(true);
//    }
    return QGraphicsScene::mousePressEvent(event);
}

void PSV_GraphicsScene::refreshItems()
{
    this->advance();
}
