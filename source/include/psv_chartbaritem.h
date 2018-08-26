#ifndef PSV_CHARTBARITEM_H
#define PSV_CHARTBARITEM_H
#include "psv_chartitem.h"


/*!
  \class PSV_ChartBarItem
  \brief ÌõÐÎÍ¼
  \author miaozhengwei QQ£º393758926
  \version 1.0.1
  \date 2014-03-10 ÐÞ¸Ä
*/
class PSVLIB_API PSV_ChartBarItem : public PSV_ChartItem
{
public:
    PSV_ChartBarItem(const QMap<int, QVariant> &param, QGraphicsItem * parent = 0);
    ~PSV_ChartBarItem();
    bool setChartValue(const QList<QString> &keys,const QList<double> &values
                       ,const QList<QColor> &colorList = QList<QColor>());
    bool setChartValue(const QMap<QString, double> &dataMap);
    virtual int type () const;

protected:
    PSV::DATATYPE dataType();
    virtual void setPrivateItemNull();
    virtual void afterUpdateItem();
    virtual PSV_Item* getInstance(){return this;}

private:
    bool m_isSameColor;

    qreal m_itemWidth;
    qreal m_itemGapWidth;
    qreal m_itemWidthRatio;

    QColor m_sameColor;
    QColor m_valueColor;
    QList<double> m_dataList;
    QList<QColor> m_colorList;
    QFont m_valueFont;
};

#endif // PSV_CHARTBARITEM_H
