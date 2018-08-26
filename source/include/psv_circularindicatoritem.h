#ifndef PSV_CIRCULARINDICATORITEM_H
#define PSV_CIRCULARINDICATORITEM_H
#include <QGraphicsItemGroup>
#include <QTimeLine>
#include <QGraphicsItemAnimation>
#include "psv_item.h"

/*!
  \class PSV_CircularIndicatorItem
  \brief 圆形指示器,参考liudianwu的http://www.qtcn.org/bbs/read-htm-tid-46807.html
  \author miaozhengwei QQ：393758926
  \version 1.0.1
  \date 2014-03-10 修改
*/
class PSVLIB_API PSV_CircularIndicatorItem : public PSV_Item
{
public:
    PSV_CircularIndicatorItem(const QMap<int, QVariant> &param, QGraphicsItem * parent = 0 );
    ~PSV_CircularIndicatorItem();
    void setValue(qreal value);
    virtual int type () const;

private:
    virtual void updateItem();
    virtual void setItemNull();

    void drawOuterCircle(int zValue);
    void drawInnerCircle(int zValue);
    void drawMark(int zValue);
    void drawCoverCircle(int zValue);
    void drawColorPie(int zValue);
    void drawIndicator(int zValue);
    void drawCoverBall(int zValue);
    void drawTextRect(int zValue);

    void initVariables();

private:
    double m_max;
    double m_min;
    double m_value;
    double m_indicatorWidthRatio;
    double m_innerRadiusRatio;

    double m_coverCircleRadiusRatio;
    double m_colorCircleRadiusRatio;
    double m_coverBallRadiusRatio;

    int m_numTicks;
//    int m_indicatorWidth;
    qreal m_currentValue;

    qreal m_outerRadius;
//    qreal m_innerRadius;
//    qreal m_coverCircleRadius;
//    qreal m_colorCircleRadius;
//    qreal m_coverBallRadius;

    QGraphicsSimpleTextItem *m_textItem;
    QGraphicsPolygonItem *m_polygonItem;

    QTimeLine *m_timeLine;
    QGraphicsItemAnimation *m_animation;

    QMap<double,QColor> m_levelInfos;
    //==================================
    QFont m_markFont;
    QFont m_valueFont;
    //==============================

};
#endif // PSV_CIRCULARINDICATORITEM_H
