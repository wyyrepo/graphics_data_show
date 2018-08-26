#ifndef PSV_CHARTREALITEM_H
#define PSV_CHARTREALITEM_H

#include "psv_chartitem.h"

/*!
  \class PSV_ChartRealItem
  \brief X坐标轴数据为<实数>二维坐标图
  \author miaozhengwei QQ：393758926
  \version 1.0.1
  \date 2014-03-10 修改
*/
class PSVLIB_API PSV_ChartRealItem : public PSV_ChartItem
{
public:
    PSV_ChartRealItem(const QMap<int, QVariant> &param, QGraphicsItem * parent = 0 );
    ~PSV_ChartRealItem();
    virtual int type () const;

    bool addCurve(const QMap<double,double> &data,const PSV_CurveParam & curveParam);
    bool addCurve(const QMap<int,double> &data,const PSV_CurveParam & curveParam);

protected:
    PSV::DATATYPE dataType();
    virtual void setPrivateItemNull();
    virtual void afterUpdateItem();
    virtual PSV_Item* getInstance(){return this;}
    QString getToolTipText(const double x, const double y);

protected:
//    double m_min_x;
//    double m_max_x;
};

#endif // PSV_CHARTREALITEM_H
