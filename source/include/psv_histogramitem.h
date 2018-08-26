#ifndef PSV_HISTOGRAMITEM_H
#define PSV_HISTOGRAMITEM_H

#include <QBrush>
#include "psv_item.h"

class PSVLIB_API PSV_HistogramItem : public PSV_Item
{
public:
    PSV_HistogramItem(const QMap<int, QVariant> &param, QGraphicsItem * parent = 0 );
    ~PSV_HistogramItem();
    virtual int type () const;

private:
    void initVariables();
    void updateItem();
    virtual void setItemNull();

private:
//    QRectF m_rect;
    qreal m_obliqueAngle;//–±Ω«
    qreal m_cosLength;//”‡œ“≥§∂»
    int m_dimension;//Œ¨ ˝
    bool m_isCuboid;
    QColor m_color;

    QBrush m_upPhaseBrush;
    QBrush m_frontPhaseBrush;
    QBrush m_sidePhaseBrush;
};
#endif // PSV_HISTOGRAMITEM_H
