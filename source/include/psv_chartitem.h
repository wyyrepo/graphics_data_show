#ifndef PSV_CHARTITEM_H
#define PSV_CHARTITEM_H

#include "psv_item.h"
#include "psv_define.h"
#include "psv_axisitem.h"
#include "psv_cfgdlg_item.h"

class PSV_AxisLeftItem;
class PSV_AxisRightItem;
class PSV_AxisUpItem;
class PSV_AxisDownItem;

/*!
  \class PSV_ChartItem
  \brief 二维图的基类
  \author miaozhengwei QQ：393758926
  \version 1.0.1
  \date 2014-03-10 修改
*/

class PSVLIB_API PSV_ChartItem : public PSV_Item
{

public:
    PSV_ChartItem(const QMap<int, QVariant> &param, QGraphicsItem * parent = 0 );
    virtual ~PSV_ChartItem();

//    void clearAllCurve(void); //清除所有曲线
    void clearCurve(const QString& curveName);//清除曲线
    void setTitleText(const QString& text);
    void setTitleFont(const QFont& font);
    void setTitleColor(const QColor& color);
//    virtual void setData(int role, const QVariant &value, bool isUpdate);

protected:
    virtual void afterUpdateItem() = 0;
    virtual PSV::DATATYPE dataType() = 0;
    virtual void setPrivateItemNull() = 0;
    virtual void beforeUpdateItem()/* = 0*/;//暂时不需要全部实现

//    virtual void initVariables();
    virtual void updateItem();
    virtual void setItemNull();
    virtual void showMenu();

    virtual QPainterPath shape() const;
    virtual QString getToolTipText(const double x,const double y);
    virtual QString getCurrentHtmMes(const double x);
    virtual QString getTipDataTextX(const double dataX);//子类有待实现

    //=====================================================
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    //=====================================================
    bool sceneEventFilter(QGraphicsItem *watched, QEvent *event);
    //=====================================================

    void createLeftAxisi(const PSV_AxisItemParam& axisParam);
    void createRightAxisi(const PSV_AxisItemParam& axisParam);
    void createUpAxisi(const PSV_AxisItemParam& axisParam);
    void createDownAxisi(const PSV_AxisItemParam& axisParam);
    void createAxisi();

    void createHVLine();
    void updateForDouble();

    double getAxisY(float dataY,int adjust = 0) const; //获取数据dataY的Y轴坐标
    virtual double getAxisX(double dataX,int adjust = 0); //获取数据dataX的X轴坐标
//    double getAxisPointDataY(float pointY) const; //计算当前Y坐标对应的数据
    virtual double getAxisPointDataX(float pointX) const; //计算当前X坐标对应的数据

    bool addEllipseItem( PSV_CurveInfo &curveInfo); //载入选择点
    bool addCurveItem( PSV_CurveInfo &curveInfo); //载入曲线
    void setCurrentAxisType(PSV::AXISTTYPE axisType);
    void updateAxisRange(PSV::AXISTTYPE axisType);

    void createTitle(const QString& text);
    void adjustTitlePos();
    void updateChartRect();
    bool isChartRectPoint(const QPointF& point);
    bool adjusetMargin();

    //=======attr
    QString titleText();
    QFont titleFont();
    QColor titleColor();
    QFont staFont();
    bool isStaHidden();
    int decimal();


private:
    void initParam();
    void updateCurrentMes(const QPointF& point);
    void hideCurrentMesItems();
    void showCurrentMesItems();

protected slots:
//    void test();

protected:
//    enum LISTTYPE { E_LEFT = 20001, E_RIGHT, E_UP, E_DOWN};
    enum { EV_FIRST = 20001, EV_MID, EV_LAST};
    enum { E_CURVE_NAME = 10001, E_ITEM_TYPE,E_CURVE_TIME, E_PREVIOUS_TIME, E_NEXT_TIME, E_POINT_TYPE, E_AXIS_X,E_LABLE_TYPE};
//    bool m_isStaHidden;
    bool m_isCurrentMessHidden;
    bool m_isFisrtCurve_left;
    bool m_isFisrtCurve_right;
    bool *m_isFisrtCurve_curP;

    int m_curveZValue;
//    int m_radius; //选择点的半径
//    int m_decimal; //精度

    double m_max_y_left;
    double m_min_y_left;
    double m_max_y_right;
    double m_min_y_right;
    double *m_max_y_curP;
    double *m_min_y_curP;

    qreal m_margin_up;
    qreal m_margin_down;
    qreal m_margin_left;
    qreal m_margin_right;
    qreal m_margin_total_up;
    qreal m_margin_total_down;
    qreal m_margin_total_left;
    qreal m_margin_total_right;
    qreal m_staMaxWidth;

//    QColor m_titleColor;
//    QString m_titleText;

    QVariant m_max_x;
    QVariant m_min_x;

    QRectF m_chartRect;
    QGraphicsTextItem *m_titleItem;
    QGraphicsTextItem *m_currentMesItem;
    PSV_AxisLeftItem *m_leftAxisItem;
    PSV_AxisRightItem *m_rightAxisItem;
    PSV_AxisUpItem *m_upAxisItem;
    PSV_AxisDownItem *m_downAxisItem;
    QGraphicsLineItem *m_vLineItem;
    QGraphicsLineItem *m_hLineItem;
    QGraphicsRectItem *m_boundingItem;

    QPair<double,double> m_rangeX;
    PSV_AxisItemParam m_axisParam_left;
    PSV_AxisItemParam m_axisParam_right;
    PSV_AxisItemParam m_axisParam_up;
    PSV_AxisItemParam m_axisParam_down;    
    QPointF m_staStartPoint;
    QMap<QString,PSV_CurveInfo> m_curveDataMap;
//    QFont m_titleFont;
//    QFont m_staFont;
};
#endif // PSV_CHARTITEM_H
