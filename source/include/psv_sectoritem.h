#ifndef PSV_SECTORITEM_H
#define PSV_SECTORITEM_H
#include <QGraphicsItem>
#include "psv_item.h"

/*!
  \class PSV_SectorItem
  \brief 三维拼图的一片
  \author miaozhengwei QQ：393758926
  \version 1.0.1
  \date 2014-03-10 修改
*/
class PSVLIB_API PSV_SectorItem : public PSV_Item
{
public:
    PSV_SectorItem(const QMap<int, QVariant> &param, QGraphicsItem * parent = 0 );
    ~PSV_SectorItem();
    virtual int type () const;
//    QRectF boundingRect() const;
//    QPainterPath shape() const;

protected:
    void initVariables(/*const QMap<PSV::PARAM_EKY, QVariant> &param*/);
    void updateItem();
    void setItemNull();

    void hoverEnterEvent ( QGraphicsSceneHoverEvent * event ) ;
    void hoverLeaveEvent ( QGraphicsSceneHoverEvent * event ) ;
    void paint ( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0 ) ;

private:
//    QRectF m_rect;
    qreal m_height;
    qreal m_startAngle;
    qreal m_angle;
    QColor m_color;
    int m_factor;
    double m_dx;
    double m_dy;
//    QPainterPath m_painterPath;//TTTTTTTTTT
};

#endif // PSV_SECTORITEM_H
