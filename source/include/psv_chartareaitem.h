#ifndef PSV_CHARTAREAITEM_H
#define PSV_CHARTAREAITEM_H
#include "psv_chartitem.h"

/*!
  \class PSV_ChartAreaItem
  \brief 面积图
  \author miaozhengwei QQ：393758926
  \version 1.0.1
  \date 2014-03-10 修改
*/
class PSVLIB_API PSV_ChartAreaItem : public PSV_ChartItem
{
public:
    PSV_ChartAreaItem(const QMap<int, QVariant> &param, QGraphicsItem * parent = 0);
//    PSV_ChartAreaItem(const PSV_ChartAreaItem &src,QGraphicsItem * parent = 0);
//    PSV_ChartAreaItem &operator=(const PSV_ChartAreaItem &src);

    ~PSV_ChartAreaItem();
    virtual int type () const;
    bool addCurve(const QList<QPair<QString,QList<double> > > dataList
                  ,QList<QColor> &colorList,bool isMandated = false);


protected:
    PSV::DATATYPE dataType();
    virtual void setPrivateItemNull();
    virtual void afterUpdateItem();
    virtual PSV_Item* getInstance(){return this;}
    QString getToolTipText(const double x, const double y);

protected:
    int m_dataCount;
    QList<QPair<QString, QList<double> > > m_dataListPair;//多个
    QList<QColor> m_colorList;
};

#endif // PSV_CHARTAREAITEM_H
