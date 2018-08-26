#ifndef PSV_GRAPHICSVIEW_H
#define PSV_GRAPHICSVIEW_H
#include <QGraphicsView>
#include "psvlib.h"

class PSVLIB_API PSV_GraphicsView : public QGraphicsView
{
    Q_OBJECT

public:
    PSV_GraphicsView(QWidget *parent = 0);
    PSV_GraphicsView(QGraphicsScene *scene, QWidget *parent = 0);
    ~PSV_GraphicsView();

protected:
    virtual void wheelEvent(QWheelEvent *event);
    virtual void resizeEvent(QResizeEvent *event);

//private:
    //
};

#endif // PSV_GRAPHICSVIEW_H
