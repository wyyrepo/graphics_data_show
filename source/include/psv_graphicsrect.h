#ifndef PSV_GRAPHICSRECT_H
#define PSV_GRAPHICSRECT_H
#include <QGraphicsRectItem>

class PSV_GraphicsRect : public QGraphicsRectItem
{
//    Q_OBJECT

public:
//    PSV_GraphicsRect(QGraphicsItem * parent = 0);
    PSV_GraphicsRect ( QGraphicsItem * parent = 0 );
    PSV_GraphicsRect ( const QRectF & rect, QGraphicsItem * parent = 0 );
    PSV_GraphicsRect ( qreal x, qreal y, qreal width, qreal height, QGraphicsItem * parent = 0 );

    ~PSV_GraphicsRect();

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    //
};

#endif // PSV_GRAPHICSRECT_H
