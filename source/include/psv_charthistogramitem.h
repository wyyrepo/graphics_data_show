#ifndef PSV_CHARTHISTOGRAMITEM_H
#define PSV_CHARTHISTOGRAMITEM_H
#include "psv_chartitem.h"

/*!
  \class PSV_ChartHistogramItem
  \brief 柱状图
  \author miaozhengwei QQ：393758926
  \version 1.0.1
  \date 2014-03-10 修改
*/
class PSVLIB_API PSV_ChartHistogramItem : public PSV_ChartItem
{
public:
    PSV_ChartHistogramItem(const QMap<int, QVariant> &param, QGraphicsItem * parent = 0 );
    ~PSV_ChartHistogramItem();
    virtual int type () const;

    bool addHistogram(const QMap<QString,double> &data,QList<QColor> &colorList,bool isMandated = false);
    bool addHistogram(const QList<QPair<QString,double> > dataList,QList<QColor> &colorList,bool isMandated = false);
    bool addCurve(const QMap<QString,double> &data,const PSV_CurveParam &curveParam);

    bool addHistogram(const QList<QPair<QString,QList<double> > > dataList
                      ,QList<QColor> &colorList
                      ,bool isStacked = false,bool isMandated = false);
    void setList(const QStringList &list);
//    void setValueHidden(bool hidden);

protected:
    PSV::DATATYPE dataType();
    virtual void setPrivateItemNull();
    void beforeUpdateItem();
    virtual void afterUpdateItem();
    virtual PSV_Item* getInstance(){return this;}
    void initParam();
    QString getToolTipText(const double x, const double y);
    virtual double getAxisX(double dataX,int adjust = 0);
    virtual double getAxisPointDataX(float pointX) const; //计算当前X坐标对应的数据
    void getItemsPos(int index, const QRectF &text, double value, QPointF &textPos, QRectF &rectF);

protected:
    bool m_isSameColor;
    bool m_isSingle;
    bool m_isStacked;
//    bool m_valueHidden;
    bool m_isContinue;
    qreal m_itemWidth;
    qreal m_itemGapWidth;
    qreal m_itemWidthRatio;
    qreal m_originHeight;
    qreal m_obliqueAngle;//斜角
    qreal m_cosLength;//余弦长度
    int m_dataCount;
    PSV::DATA_STRUCT m_dataStruct;
    QColor m_sameColor;
//    QFont m_valueFont;
    QList<QPair<QString, double > > m_singleDataListPair;//单个
    QList<QPair<QString, QList<double> > > m_dataListPair;//多个
    QList<QColor> m_colorList;
};

#endif // PSV_CHARTHISTOGRAMITEM_H
