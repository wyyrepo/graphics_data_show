#ifndef PSV_CHARTTIMEITEM_H
#define PSV_CHARTTIMEITEM_H
#include <QTime>
#include "psv_chartitem.h"

/*!
  \class PSV_ChartTimeItem
  \brief X坐标轴数据为<Time>二维坐标图
  \author miaozhengwei QQ：393758926
  \version 1.0.1
  \date 2014-03-10 修改
*/
class PSVLIB_API PSV_ChartTimeItem : public PSV_ChartItem
{
public:
    PSV_ChartTimeItem(const QMap<int, QVariant> &param, QGraphicsItem * parent = 0 );
    ~PSV_ChartTimeItem();
    virtual int type () const;

    bool addCurve(const QMap<QTime,double> &data,const PSV_CurveParam & curveParam);

protected:
    PSV::DATATYPE dataType();
    virtual void setPrivateItemNull();
    virtual void afterUpdateItem();
    virtual PSV_Item* getInstance(){return this;}
    QString getToolTipText(const double x, const double y);
    virtual QString getTipDataTextX(const double dataX);//子类有待实现

protected:
    QTime m_min_time;
    QTime m_max_time;
};

#endif // PSV_CHARTTIMEITEM_H
