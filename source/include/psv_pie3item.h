#ifndef PSV_3PIEITEM_H
#define PSV_3PIEITEM_H
#include <QGraphicsItem>
#include "psv_item.h"

/*!
  \class PSV_Pie3Item
  \brief ÈýÎ¬Æ´Í¼
  \author miaozhengwei QQ£º393758926
  \version 1.0.1
  \date 2014-03-10 ÐÞ¸Ä
*/
class PSVLIB_API PSV_Pie3Item : public PSV_Item
{
public:
    PSV_Pie3Item(const QMap<int, QVariant> &param, QGraphicsItem * parent = 0 );
    ~PSV_Pie3Item();

    virtual int type () const;
    void setChartData(const QMap<QString, double>& data);
    void hideLabel();
    void showLabel();

protected:
    void initVariables(/*const QMap<PSV::PARAM_EKY, QVariant> &param*/);
    void updateItem();
    virtual void setItemNull();
    void adjustChartRect();

protected:
    bool m_isShowLabel;
    qreal m_startAngle;
    qreal m_heigthRatio;
    double m_sum;
    QRectF m_chartRect;
    QFont m_labelFont;
    QMap<QString, double> m_data;
};
#endif // PSV_3PIEITEM_H
