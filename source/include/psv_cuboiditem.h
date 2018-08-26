#ifndef PSV_CUBOIDITEM_H
#define PSV_CUBOIDITEM_H
#include <QGraphicsItemGroup>
#include <QBrush>
#include "psv_public.h"

class PSV_CuboidItem : public QGraphicsItemGroup
{
public:
    PSV_CuboidItem(const QRectF &rect, const QColor &color, qreal obliqueAngle = 45, qreal cosLength = -1, QGraphicsItem * parent = 0 );
    PSV_CuboidItem(const QMap<PSV::PARAM_EKY, QVariant> &param, QGraphicsItem * parent = 0 );
    ~PSV_CuboidItem();
    virtual int type () const;

private:
    void initVariables(const QMap<PSV::PARAM_EKY, QVariant> &param);
    void updateItem();

private:
    QRectF m_rect;
    qreal m_obliqueAngle;//–±Ω«
    qreal m_cosLength;//”‡œ“≥§∂»

    QBrush m_upPhaseBrush;
    QBrush m_frontPhaseBrush;
    QBrush m_sidePhaseBrush;
    bool m_isCuboid;
    int m_dimension;//Œ¨ ˝
};

#endif // PSV_CUBOIDITEM_H
