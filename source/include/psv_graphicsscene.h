#ifndef PSV_GRAPHICSSCENE_H
#define PSV_GRAPHICSSCENE_H
#include <QGraphicsScene>
#include "psvlib.h"

class PSVLIB_API PSV_GraphicsScene : public QGraphicsScene
{
    Q_OBJECT

public:
    PSV_GraphicsScene ( QObject * parent = 0 );
    PSV_GraphicsScene ( const QRectF & sceneRect, QObject * parent = 0 );
    PSV_GraphicsScene ( qreal x, qreal y, qreal width, qreal height, QObject * parent = 0 );
    ~PSV_GraphicsScene();
    void refreshItems();

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
    //
};

#endif // PSV_GRAPHICSSCENE_H
