/*!
  \class PSV_AxisItemParam
  \brief 坐标轴设置参数
  \author miaozhengwei QQ：393758926
  \version 1.0.1
  \date 2014-03-10 修改
*/


#ifndef PSV_AXISITEM_H
#define PSV_AXISITEM_H
#include <QFont>
#include "psv_define.h"
#include "psv_item.h"

class PSVLIB_API PSV_AxisItemParam
{
public:
    PSV_AxisItemParam();
    PSV_AxisItemParam(const PSV_AxisItemParam& other);
    ~PSV_AxisItemParam();
    PSV_AxisItemParam& operator=(const PSV_AxisItemParam& ohter);

public:
    bool m_isCenter;
    bool m_hasArrow;
    bool m_isShow;
    qreal m_fontRatio;
    QStringList m_list;
};

/*!
  \class PSV_AxisItem
  \brief 坐标轴基类
  \author miaozhengwei QQ：393758926
  \version 1.0.1
  \date 2014-03-10 修改
*/
class PSVLIB_API PSV_AxisItem : public PSV_Item
{
public:
    PSV_AxisItem(const QMap<int, QVariant> &param, QGraphicsItem * parent = 0 );
    PSV_AxisItem(const QMap<int, QVariant> &param,const QStringList &list, QGraphicsItem * parent = 0 );
    ~PSV_AxisItem();
    QList<QPointF> getMarkPointList();
    void getRange(QVariant &max, QVariant &min,QPair<double,double> &range);
    void getRange(QVariant &max, QVariant &min);
    void setRange(QVariant &max, QVariant &min,QPair<double,double> &range);
    void setRange(QVariant &max, QVariant &min);

    void setMarkWidth(const qreal width);
    QRectF validRect();
    void setList(const QStringList& list);

protected:
    virtual void initVariables();
    virtual void updateItem();
    virtual void setItemNull();
    void updateLabels();

protected:
    bool m_hasArrow;
    bool m_isList;
    bool m_isCenter;

    QVariant m_maxValue;
    QVariant m_minValue;

    int m_numTicks;

    qreal m_lineWidth;
    qreal m_markWidth;
    qreal m_markLength;
    qreal m_arrowsLength;

    QColor m_lineColor;
    QColor m_markColor;

    QFont m_markFont;
    QList<QPair<QVariant, QString> > m_labelList;
    QStringList m_list;
    QList<QPointF> m_markPointList;

    QPair<double,double> m_range;
    QRectF m_validRect;
};

#endif // PSV_AXISITEM_H
