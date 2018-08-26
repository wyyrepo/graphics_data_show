#ifndef PSV_VERTICALINDICATORITEM_H
#define PSV_VERTICALINDICATORITEM_H

#include <QFont>
#include <QGraphicsItemAnimation>
#include <QTimeLine>
#include "psv_item.h"

/*!
  \class PSV_VerticalIndicatorItem
  \brief 垂直指示器
  \author miaozhengwei QQ：393758926
  \version 1.0.1
  \date 2014-03-10 修改
*/
class PSVLIB_API PSV_VerticalIndicatorItem : public PSV_Item
{
public:
    PSV_VerticalIndicatorItem(const QMap<int, QVariant> &param, QGraphicsItem * parent = 0 );
    ~PSV_VerticalIndicatorItem();
    void setValue(const double value);
    void setAlign(const bool isAlignLeft);
    int type() const;

private:
    void drawBackground();
    void drawMark();
    void drawUnderRect();

    void setItemNull();
    void updateItem();
    void adjustRect();
    void adjustMarkTextWidth();
    void deleteAnimation();
    void adjustValueItem(const double value);

private:
    bool m_isAlignLeft;
    int m_zValue;
    int m_min;
    int m_max;

    QColor m_valueColor;
    QColor m_markColor;
    QColor m_markTextColor;
    QColor m_indicatorColor;

    qreal m_currentValue;
    qreal m_margin_up_ratio;
    qreal m_margin_down_ratio;
    qreal m_margin_left_ratio;
    qreal m_margin_right_ratio;

    qreal m_marginVRatio;
    qreal m_marginHRatio;
    qreal m_markLength;

    qreal m_prevDy;
    qreal m_prevScaleY;
    qreal m_markTextWidth;

    qreal m_valueHeight;

    QGraphicsRectItem *m_upRectItem;
    QGraphicsTextItem *m_valueItem;
    QGraphicsItemAnimation* m_animation;
    QTimeLine *m_timeLine;

    QFont m_markFont;
    QFont m_valueFont;

    QRectF  m_underRect;
    QRectF  m_upRect;
    QRectF  m_markRect;
};

#endif // PSV_VERTICALINDICATORITEM_H
