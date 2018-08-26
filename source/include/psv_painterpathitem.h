#ifndef PSV_PAINTERPATHITEM_H
#define PSV_PAINTERPATHITEM_H

#include <QGraphicsItemAnimation>
#include <QTimeLine>
#include "psv_item.h"

/*!
  \class PSV_PainterPathItem
  \brief 路径图，小三角沿着定义的路径移动
  \author miaozhengwei QQ：393758926
  \version 1.0.1
  \date 2014-03-10 修改
*/
class PSVLIB_API PSV_PainterPathItem : public PSV_Item
{
public:
    PSV_PainterPathItem(const QPainterPath& painterPath,QGraphicsItem * parent = 0 );
    ~PSV_PainterPathItem();

    virtual int type () const;
    virtual QRectF boundingRect() const;
    virtual void setItemNull();
    void startAnimation();
    void stopAnimation();
    void setPath(const QPainterPath &path);
    void setLoopCount(const int loopCount);
    void setArrowsColor(const QColor &color);
    void setArrowsPolygon(const QPolygonF &polygon);
    void setArrowsLength(const int length);
    void showArrows();
    void hidArrows();

protected:
    QGraphicsItemAnimation* getItemAnimation(const QPainterPath &path,QTimeLine *timeLine,const int intervalLen = 4,const int updateInterval = 40);
    virtual void updateItem();
    void deleteAnimation();
    QPolygonF createDefautArrows(const int length);

private:
    qreal m_startRatio;
    int m_updateInterval;
    int m_arrowsLength;
    int m_animationLength;
    int m_loopCount;
    QGraphicsPolygonItem *m_polygon_item;
    QGraphicsItemAnimation* m_animation;
    QTimeLine *m_timeLine;
    QColor m_arrowsColor;
    bool m_isStart;
    bool m_isShowArrows;
    QPolygonF m_polygon;
};


#endif // PSV_PAINTERPATHITEM_H
