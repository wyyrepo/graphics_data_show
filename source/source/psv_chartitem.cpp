#include <QPainter>
#include <QMenu>
#include <QAction>
#include <QGraphicsSceneMouseEvent>
#include "psv_chartitem.h"
#include "psv_axisleftitem.h"
#include "psv_axisrightitem.h"
#include "psv_axisupitem.h"
#include "psv_axisdownitem.h"
#include "psv_cfgdlg_curve.h"

PSV_ChartItem::PSV_ChartItem(const QMap<int, QVariant> &param, QGraphicsItem *parent)
    : PSV_Item(param,parent)
//    , m_isStaHidden(false)
    , m_isCurrentMessHidden(true)
    , m_isFisrtCurve_left(true)
    , m_isFisrtCurve_right(true)
    , m_isFisrtCurve_curP(&m_isFisrtCurve_left)
    , m_curveZValue(1)
    , m_max_y_left(10)
    , m_min_y_left(0)
    , m_max_y_right(1)
    , m_min_y_right(-1)
    , m_max_y_curP(&m_max_y_left)
    , m_min_y_curP(&m_min_y_left)
    , m_margin_up(15)
    , m_margin_down(0)
    , m_margin_left(5)
    , m_margin_right(20)
    , m_margin_total_up(50)
    , m_margin_total_down(80)
    , m_margin_total_left(50)
    , m_margin_total_right(80)
    , m_staMaxWidth(0)
    , m_max_x(100.0)
    , m_min_x(0.0)

    , m_titleItem(NULL)
    , m_currentMesItem(NULL)
    , m_leftAxisItem(NULL)
    , m_rightAxisItem(NULL)
    , m_upAxisItem(NULL)
    , m_downAxisItem(NULL)
    , m_vLineItem(NULL)
    , m_hLineItem(NULL)
    , m_boundingItem(NULL)

{
    initParam();
    m_isAdvancetable = true;//根据advance自动 刷新
    //====================
    setAcceptHoverEvents(true);
}

PSV_ChartItem::~PSV_ChartItem()
{
    //
}


void PSV_ChartItem::initParam()
{
    addDefaultParam(PSV::titleColor,QColor(Qt::blue));
    QFont font;
    font.setPointSize(18);
    font.setBold(true);
    addDefaultParam(PSV::titleFont,font);
    QFont staFont;
    staFont.setPointSize(3);
    staFont.setBold(false);
    addDefaultParam(PSV::staFont,staFont);
    addDefaultParam(PSV::titleText,"");
    addDefaultParam(PSV::isStaHidden,false);
    addDefaultParam(PSV::decimal,3);
    m_curveZValue = 1;
    m_max_y_left = 10;
    m_min_y_left = 0;
    m_max_y_right = 1;
    m_min_y_right = -1;
    //        m_max_y_curP(&m_max_y_left;
    //        m_min_y_curP(&m_min_y_left;
    m_margin_up = 15;
    m_margin_down = 0;
    m_margin_left = 5;
    m_margin_right = 20;
    m_margin_total_up = 50;
    m_margin_total_down = 80;
    m_margin_total_left = 50;
    m_margin_total_right = 80;
    m_staMaxWidth = 0;
    updateChartRect();
}

QPainterPath PSV_ChartItem::shape() const
{
    QPainterPath path;
    path.addRect(boundingRect());
    return path;
}

//void PSV_ChartItem::initVariables()
//{
//    if(m_param.contains(PSV::titleFont))
//    {
//        m_titleFont = m_param.value(PSV::titleFont).value<QFont>();
//    }
//    if(m_param.contains(PSV::titleColor))
//    {
//        m_titleColor = m_param.value(PSV::titleColor).value<QColor>();
//    }
//    if(m_param.contains(PSV::titleText))
//    {
//        m_titleText = m_param.value(PSV::titleText).toString();
//    }

//    if(m_param.contains(PSV::margin_up))
//    {
//        m_margin_total_up = m_param.value(PSV::margin_up).toDouble();
//    }
//    if(m_param.contains(PSV::margin_down))
//    {
//        m_margin_total_down = m_param.value(PSV::margin_down).toDouble();
//    }
//    if(m_param.contains(PSV::margin_left))
//    {
//        m_margin_total_left = m_param.value(PSV::margin_left).toDouble();
//    }
//    if(m_param.contains(PSV::margin_right))
//    {
//        m_margin_total_right = m_param.value(PSV::margin_right).toDouble();
//    }
//    updateChartRect();
//}

void PSV_ChartItem::createDownAxisi(const PSV_AxisItemParam &axisParam)
{
    QMap<int, QVariant> param;
    QRectF boundingRect = QRectF(m_chartRect.x()
                                 ,m_chartRect.bottom()
                                 ,m_chartRect.width()
                                 ,m_margin_total_down);
    param.insert(PSV::boundingRect,boundingRect);
    QFont markFont;
    markFont.setPointSizeF(PSV_Public::getMinLenght(getBoundingRect()) * axisParam.m_fontRatio * 0.03);
    param.insert(PSV::markFont,markFont);
    param.insert(PSV::hasArrow,axisParam.m_hasArrow);
    param.insert(PSV::maxValue,m_max_x);
    param.insert(PSV::minValue,m_min_x);
    param.insert(PSV::isCenter,axisParam.m_isCenter);
    if(axisParam.m_list.count() > 0)
    {
        m_downAxisItem = new PSV_AxisDownItem(param,axisParam.m_list,this);
    }
    else
    {
        m_downAxisItem = new PSV_AxisDownItem(param,this);
    }
    m_downAxisItem->getRange(m_max_x,m_min_x,m_rangeX);
}

void PSV_ChartItem::createUpAxisi(const PSV_AxisItemParam &axisParam)
{
    QMap<int, QVariant> param;
    QRectF m_rect = getBoundingRect();
    QRectF boundingRect = QRectF(m_chartRect.x(),m_rect.top()
                                 ,m_chartRect.width(),m_margin_total_up);
    param.insert(PSV::boundingRect,boundingRect);
    QFont markFont;
    markFont.setPointSizeF(PSV_Public::getMinLenght(m_rect) * axisParam.m_fontRatio * 0.03);
    param.insert(PSV::markFont,markFont);

    param.insert(PSV::hasArrow,axisParam.m_hasArrow);
    param.insert(PSV::maxValue,m_max_x);
    param.insert(PSV::minValue,m_min_x);
    if(axisParam.m_list.count() > 0)
    {
        m_upAxisItem = new PSV_AxisUpItem(param,axisParam.m_list,this);
        param.insert(PSV::isCenter,axisParam.m_isCenter);
    }
    else
    {
        m_upAxisItem = new PSV_AxisUpItem(param,this);
    }
    m_upAxisItem->getRange(m_max_x,m_min_x,m_rangeX);
}

void PSV_ChartItem::createLeftAxisi(const PSV_AxisItemParam &axisParam)
{
    QMap<int, QVariant> param;
    QRectF m_rect = getBoundingRect();
    QRectF boundingRect = QRectF(m_rect.left(),m_chartRect.top()
                                 ,m_margin_total_left, m_chartRect.height());
    param.insert(PSV::boundingRect,boundingRect);
    QFont markFont;
    markFont.setPointSizeF(PSV_Public::getMinLenght(m_rect) * axisParam.m_fontRatio * 0.03);
    param.insert(PSV::markFont,markFont);

    param.insert(PSV::hasArrow,axisParam.m_hasArrow);
    param.insert(PSV::maxValue,m_max_y_left);
    param.insert(PSV::minValue,m_min_y_left);
    if(axisParam.m_list.count() > 0)
    {
        m_leftAxisItem = new PSV_AxisLeftItem(param,axisParam.m_list,this);
        param.insert(PSV::isCenter,axisParam.m_isCenter);
    }
    else
    {
        m_leftAxisItem = new PSV_AxisLeftItem(param,this);
    }
    QVariant max;
    QVariant min;
    m_leftAxisItem->getRange(max,min);
    m_max_y_left = max.toDouble();
    m_min_y_left = min.toDouble();
}

void PSV_ChartItem::createRightAxisi(const PSV_AxisItemParam &axisParam)
{
    QMap<int, QVariant> param;
    QRectF m_rect = getBoundingRect();
    QRectF boundingRect = QRectF(m_chartRect.right(), m_chartRect.top()
                                 ,m_margin_total_right, m_chartRect.height());
    param.insert(PSV::boundingRect,boundingRect);
    QFont markFont;
    markFont.setPointSizeF(PSV_Public::getMinLenght(m_rect) * axisParam.m_fontRatio * 0.03);
    param.insert(PSV::markFont,markFont);


    param.insert(PSV::hasArrow,axisParam.m_hasArrow);
    param.insert(PSV::maxValue,m_max_y_right);
    param.insert(PSV::minValue,m_min_y_right);
    if(axisParam.m_list.count() > 0)
    {
        m_rightAxisItem = new PSV_AxisRightItem(param,axisParam.m_list,this);
        param.insert(PSV::isCenter,axisParam.m_isCenter);
    }
    else
    {
        m_rightAxisItem = new PSV_AxisRightItem(param,this);
    }

    QVariant max;
    QVariant min;
    m_rightAxisItem->getRange(max,min);
    m_max_y_right = max.toDouble();
    m_min_y_right = min.toDouble();
}

void PSV_ChartItem::beforeUpdateItem()
{
    adjusetMargin();
    updateChartRect();
}

void PSV_ChartItem::updateItem()
{
    m_curveZValue = 1;
//    QRectF m_rect = getBoundingRect();

//    m_staFont.setPointSizeF(m_rect.height() * 0.008);
//    m_titleFont.setPointSizeF(m_rect.height() * 0.038);
    beforeUpdateItem();
    if(!m_chartRect.isValid())
    {
        return;
    }
    m_staStartPoint = m_chartRect.bottomLeft();
    createAxisi();
    createTitle(getData(PSV::titleText,"").toString());

    if(m_axisParam_left.m_isShow)
    {
        m_staStartPoint.setX(m_leftAxisItem->validRect().right());
    }
    if(m_axisParam_down.m_isShow)
    {
        m_staStartPoint.setY(m_downAxisItem->validRect().bottom() + getData(PSV::margin,3).toInt());
    }
    createHVLine();
    afterUpdateItem();
}

void PSV_ChartItem::updateForDouble()
{
    QMapIterator<QString,PSV_CurveInfo> iter(m_curveDataMap);
    qreal posY = m_staStartPoint.y();
    qreal posX = m_staStartPoint.x();
    while(iter.hasNext())
    {
        iter.next();
        PSV_CurveInfo curveInfo = iter.value();
        updateAxisRange(curveInfo.m_axisType);
        addCurveItem(curveInfo);
        addEllipseItem(curveInfo);
        if(!isStaHidden())
        {
            QGraphicsTextItem *textItem = new QGraphicsTextItem(this);
            textItem->setData(E_ITEM_TYPE,PSV::staLabelItem);
            textItem->setData(E_CURVE_NAME,curveInfo.m_curveName);
            textItem->setFlags(QGraphicsItem::ItemIsSelectable);
            textItem->installSceneEventFilter(this);

            textItem->setDefaultTextColor(getDefaultColor());
            textItem->setFont(staFont());
            textItem->setHtml(curveInfo.m_staHtmText);
            double textHeight = textItem->boundingRect().height();
            int staMaxHeight = (int)textHeight* 6 / 10;
            textItem->setPos(posX + textItem->boundingRect().height(),posY);

            QPixmap pixmap(staMaxHeight,staMaxHeight);
            pixmap.fill();
            QPen pen(curveInfo.m_lineColor);
            pen.setWidth(3);
            QPainter painter(&pixmap);
            painter.setPen(pen);
            if(!curveInfo.m_isHidden)
            {
                QBrush brush(curveInfo.m_lineColor);
                painter.setBrush(brush);
            }
            painter.drawRect(0, 0, pixmap.height(), pixmap.height());
            QGraphicsPixmapItem* pixmapItem = new QGraphicsPixmapItem(pixmap,this);
            pixmapItem->setPixmap(pixmap);
            pixmapItem->setPos(posX,posY + textHeight * 2 / 10);
            pixmapItem->setData(E_ITEM_TYPE,PSV::staLabelItem);
            pixmapItem->setData(E_CURVE_NAME,curveInfo.m_curveName);
            pixmapItem->setFlags(QGraphicsItem::ItemIsSelectable);
            pixmapItem->installSceneEventFilter(this);
            if(posX + 2 * m_staMaxWidth > m_chartRect.right())
            {
                posX = m_staStartPoint.x();
                posY += textItem->boundingRect().height() + getData(PSV::margin,3).toInt();
            }
            else
            {
                posX += m_staMaxWidth;
            }
        }
    }
    //TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
    //    QGraphicsRectItem *item = new QGraphicsRectItem(m_rect,this);//TTTTTTTTTTTTTTT
    //    item->setPen(QPen(QColor(Qt::red)));//TTTTTTTTTTTTTTT
    //TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
}

QString PSV_ChartItem::getToolTipText(const double x, const double y)
{
    PSV_NOUSED(x);
    PSV_NOUSED(y);
    return "";
}

QString PSV_ChartItem::getCurrentHtmMes(const double x)
{
    QString str;
    double dataX = getAxisPointDataX(x);
    PSV::DATATYPE tempType = dataType();
    if(tempType == PSV::E_DATATYPE_TIME
            || tempType == PSV::E_DATATYPE_DATE
            || tempType == PSV::E_DATATYPE_DOUBLE
            || tempType == PSV::E_DATATYPE_DATETIME)
    {
        QMapIterator<QString, PSV_CurveInfo > iter(m_curveDataMap);
        while(iter.hasNext())
        {
            iter.next();
            PSV_CurveInfo curveInfo = iter.value();
            if(curveInfo.m_isHidden)
            {
                continue;
            }
            //暂时不支持曲线            QMap<double, double> tempValue = curveInfo.m_curveDetailDataMap;
            QMap<double, double> tempValue = curveInfo.m_curveDataMap;
            QString curveName = curveInfo.m_curveName;
            //            if(m_hideCurveNameList.contains(curveName))
            //            {
            //                continue;
            //            }
            QString corStr = curveInfo.m_lineColor.name();
            double dataY = 0.0;
            QMapIterator<double, double>  iter_data(tempValue);
            int count = 0;
            bool isFound = false;
            double preX = 0.0;
            double nextX = 0.0;
            double preY = 0.0;
            double nextY = 0.0;
            while(iter_data.hasNext())
            {
                iter_data.next();
                if(qAbs(dataX - iter_data.key()) < PSV_ZEOR)
                {
                    dataY = iter_data.value();
                    isFound  = true;
                    count = 0;
                    break;
                }
                else if(dataX > iter_data.key())
                {
                    preX = iter_data.key();
                    preY = iter_data.value();
                    count++;
                }
                else
                {
                    nextX = iter_data.key();
                    nextY = iter_data.value();
                    if(count > 0)
                    {
                        isFound  = true;
                    }
                    break;
                }
            }
            if(isFound)
            {
                if(count != 0)
                {
                    if(curveInfo.m_curveType == PSV::E_CURVE_PARELLEL)
                    {
                        dataY = preY;
                    }
                    else
                    {
                        dataY = (nextY - preY) * (dataX - preX) / (nextX - preX) + preY;
                    }
                }
                str.append(QString("<b><font size= 8 color = %1>%2:%3</font><br/></b>")
                           .arg(corStr)
                           .arg(curveName)
                           .arg(QString::number(dataY,'f',decimal())));
            }
            else
            {
//                PSV_Public::printMes(QString("NOT fount = %1").arg(iter.key()));
            }
            //
        }
    }
    if(!str.isEmpty())
    {
        QString xStr = getTipDataTextX(dataX);
        return QString("<b><font size= 8 color = Black>%1</font></b><br/>%2").arg(xStr).arg(str);
    }
    return str;
}

double PSV_ChartItem::getAxisX(double dataX, int adjust)
{
    double x = m_chartRect.left() - adjust;
    QRectF rect = m_chartRect;
    if(!rect.isValid())
    {
        return x;
    }
    if(m_rangeX.second > m_rangeX.first)
    {
        x = 1.0 * ((dataX - m_rangeX.first) / (m_rangeX.second - m_rangeX.first)) * rect.width() + rect.left() - adjust;
    }
    return x;
}

double PSV_ChartItem::getAxisPointDataX(float pointX) const
{
    double new_data = 1.0 * (m_rangeX.first) + 1.0 * (pointX - m_chartRect.left()) / (m_chartRect.width()) * (m_rangeX.second - m_rangeX.first);  //计算当前鼠标坐标对应的数据
    return new_data;
}

double PSV_ChartItem::getAxisY(float dataY, int adjust) const
{
    double y = m_margin_total_up + getBoundingRect().top();
    QRectF rect = m_chartRect;
    if(!rect.isValid())
    {
        return y;
    }

    if(*m_max_y_curP > *m_min_y_curP)
    {
        y = rect.bottom() - 1.0 * (dataY - *m_min_y_curP) / (*m_max_y_curP - *m_min_y_curP) * rect.height() - adjust;
    }
    else
    {
        PSV_Public::printMes(QString("*m_max_y_curP(%1) <= *m_min_y_curP(%2)")
                             .arg(*m_max_y_curP).arg(*m_min_y_curP));
    }
    return y;
}

bool PSV_ChartItem::addEllipseItem(PSV_CurveInfo &curveInfo)
{
    if(curveInfo.m_isHidden)
    {
        return true;
    }
    setCurrentAxisType(curveInfo.m_axisType);
    QMap<double, double> curveData = curveInfo.m_curveDataMap;
    QMapIterator<double, double> iter(curveData);
    QPolygonF polygon;
    int m_radius = curveInfo.m_pointSize;
    double pointY0 = getAxisY(*m_min_y_curP,m_radius);;
    QPointF fisrtPoint(0,pointY0);
    QString curveName = curveInfo.m_curveName;
    QPen pen(curveInfo.m_pointColor);
    QBrush brush(curveInfo.m_pointColor);
    int count =1;
    double previous_time = 1.0 * qrand();
    QGraphicsEllipseItem* preItem = NULL;
    int index = 1;
    while(iter.hasNext())
    {
        iter.next();
        double x = getAxisX(iter.key(),m_radius);
        double y = getAxisY(iter.value(),m_radius);
        QPointF point(x, y);
        if(index == 1)
        {
            fisrtPoint = QPointF(x + m_radius,pointY0 + m_radius);
            polygon.append(fisrtPoint);
        }
        polygon.append(QPointF(x+m_radius,y+m_radius));
        if(index == curveData.count())
        {
            polygon.append(QPointF(x + m_radius,pointY0 + m_radius));
            polygon.append(fisrtPoint);
        }
        index++;
        QGraphicsEllipseItem *ellipse_item = new QGraphicsEllipseItem(this);
        ellipse_item->setZValue(m_curveZValue);
        ellipse_item->setRect(0,0,2*m_radius,2*m_radius);
        ellipse_item->setPos(point);
        ellipse_item->setFlag(QGraphicsItem::ItemIsSelectable);
        ellipse_item->setPen(pen);
        ellipse_item->setBrush(brush);
        ellipse_item->setData(E_CURVE_NAME,curveName);  //设置属于哪条曲线
        ellipse_item->setData(E_AXIS_X,iter.key());  //设置对应的X坐标轴值
        ellipse_item->setData(E_PREVIOUS_TIME,previous_time);
        ellipse_item->setData(E_NEXT_TIME,previous_time);
        ellipse_item->setData(E_POINT_TYPE,EV_FIRST);
        ellipse_item->setData(E_ITEM_TYPE,PSV::ellipseItem);
        ellipse_item->setToolTip(getToolTipText(iter.key(),iter.value()));
        ellipse_item->installSceneEventFilter(this);
        if(ellipse_item != NULL)
        {
            preItem->setData(E_NEXT_TIME,iter.key());
            if(count == curveData.count() - 1)
            {
                ellipse_item->setData(E_POINT_TYPE,EV_LAST);
            }
            else if(count != 1)
            {
                ellipse_item->setData(E_POINT_TYPE,EV_MID);
            }
        }
        preItem = ellipse_item;
        previous_time = iter.key();
    }
    curveInfo.m_polygon = polygon;
    m_curveZValue++;
    return true;
}

bool PSV_ChartItem::addCurveItem(PSV_CurveInfo &curveInfo)
{
    if(curveInfo.m_isHidden)
    {
        return true;
    }
    setCurrentAxisType(curveInfo.m_axisType);
    PSV::CURVETYPE curveType = curveInfo.m_curveType;
    QMap<double, double> curve_data = curveInfo.m_curveDataMap;
    QPen pen(curveInfo.m_lineColor);
    pen.setWidth(curveInfo.m_lineWidth);
    QMapIterator<double, double> iter(curve_data);
    QLineF lineF;
    QLineF lineF_V;
    QLineF lineF_H;
    bool is_first = true;
    QMap<double, QGraphicsLineItem *> line_item_map;
    QMap<double, QGraphicsLineItem *> line_V_item_map;
    QMap<double, QGraphicsLineItem *> line_H_item_map;

    while(iter.hasNext())
    {
        iter.next();
        double x = getAxisX(iter.key());//不调整
        double y = getAxisY(iter.value());//不调整
        QPointF point(x,y);
        if(is_first)
        {
            is_first = false;
            if(curveType == PSV::E_CURVE_PARELLEL)
            {
                lineF_H.setP1(point);
            }
            else
            {
                lineF.setP1(point);
            }
        }
        else
        {
            if(curveType == PSV::E_CURVE_PARELLEL)
            {
                QGraphicsLineItem *line_item_H = new QGraphicsLineItem(this);
                line_item_H->setZValue(m_curveZValue);
                lineF_H.setP2(QPointF(x,lineF_H.p1().y()));
                line_item_H->setLine(lineF_H);
                line_item_H->setPen(pen);
                line_H_item_map.insert(iter.key(),line_item_H);
                lineF_V.setP1(QPointF(x,lineF_H.p1().y()));
                lineF_V.setP2(point);
                QGraphicsLineItem *line_item_V = new QGraphicsLineItem(this);
                line_item_V->setZValue(m_curveZValue);
                line_item_V->setLine(lineF_V);
                line_item_V->setPen(pen);
                line_V_item_map.insert(iter.key(),line_item_V);
                lineF_H.setP1(point);
            }
            else
            {
                QGraphicsLineItem *line_item;
                line_item = new QGraphicsLineItem(this);
                line_item->setZValue(m_curveZValue);
                lineF.setP2(point);
                line_item->setLine(lineF);
                line_item->setPen(pen);
                line_item_map.insert(iter.key(),line_item);
                lineF.setP1(lineF.p2());
            }
        }
    }
    m_curveZValue++;
    return true;
}

void PSV_ChartItem::setCurrentAxisType(PSV::AXISTTYPE axisType)
{
    switch(axisType)
    {
    case PSV::E_AXIS_LEFT:
    {
        m_max_y_curP = &m_max_y_left;
        m_min_y_curP = &m_min_y_left;
        m_isFisrtCurve_curP = &m_isFisrtCurve_left;
    }
        break;
    case PSV::E_AXIS_RIGHT:
    {
        m_max_y_curP = &m_max_y_right;
        m_min_y_curP = &m_min_y_right;
        m_isFisrtCurve_curP = &m_isFisrtCurve_right;
    }
        break;
    case PSV::E_AXIS_DOWN:
    {
        //        m_max_y_curP = &m_max_y_right;
        //        m_min_y_curP = &m_min_y_right;
        //        m_numYTick_curP = &m_numYTick_right;
        //        m_isFisrtCurve_curP = &m_isFisrtCurve_right;
    }
        break;
    case PSV::E_AXIS_UP:
    {
        //        m_max_y_curP = &m_max_y_right;
        //        m_min_y_curP = &m_min_y_right;
        //        m_numYTick_curP = &m_numYTick_right;
        //        m_isFisrtCurve_curP = &m_isFisrtCurve_right;
    }
        break;
    default:
    {
        m_max_y_curP = &m_max_y_left;
        m_min_y_curP = &m_min_y_left;
        //        m_numYTick_curP = &m_numYTick_left;
        m_isFisrtCurve_curP = &m_isFisrtCurve_left;
    }
        break;
    }
}

void PSV_ChartItem::updateAxisRange(PSV::AXISTTYPE axisType)
{
    switch(axisType)
    {
    case PSV::E_AXIS_RIGHT:
    {
        if(m_rightAxisItem == NULL)
        {
            createRightAxisi(m_axisParam_right);
        }
    }
        break;
    default:
    {
        if(m_leftAxisItem == NULL)
        {
            createLeftAxisi(m_axisParam_left);
        }
    }
        break;
    }
}

/*!
  \brief 清除曲线 \a curveName 以及数据
  \sa ZCurveView::clearAllCurve()
  */
void PSV_ChartItem::clearCurve(const QString &curveName)
{
    if(curveName.isEmpty())
    {
        return;
    }
    if(m_curveDataMap.contains(curveName))
    {
        m_curveDataMap.remove(curveName);
        //        m_staLabelItemMap.remove(curveName);
        //        m_hideCurveNameList.removeOne(curveName);
        //        updataView();
        refreshItem();
    }
}

void PSV_ChartItem::setTitleText(const QString &text)
{
//    m_titleText = text;
    d->setData(PSV::titleText,text);
    if(m_titleItem == NULL)
    {
        createTitle(text);
    }
    else
    {
        m_titleItem->setPlainText(text);
        adjustTitlePos();
    }
}

void PSV_ChartItem::setTitleFont(const QFont &font)
{
//    m_titleFont = font;
    d->setData(PSV::titleFont,font);
    QString titleText = getData(PSV::titleText,"").toString();
    if(m_titleItem == NULL)
    {
        createTitle(titleText);
    }
    else
    {
        m_titleItem->setFont(titleText);
        adjustTitlePos();
    }
}

void PSV_ChartItem::setTitleColor(const QColor &color)
{
//    m_titleColor = color;
    d->setData(PSV::titleColor,color);
    if(m_titleItem == NULL)
    {
        createTitle(getData(PSV::titleText,"").toString());
    }
    else
    {
        m_titleItem->setDefaultTextColor(color);
        adjustTitlePos();
    }
}

//void PSV_ChartItem::setData(int role, const QVariant &value, bool isUpdate)
//{
//    bool isValib = true;
//    if(role == PSV::titleColor && value.type() == QVariant::Color)
//    {
////        m_titleColor = value.value<QColor>();

//    }
//    else if(role == PSV::titleText && (value.type() == QVariant::String || value.type() == QVariant::Char))
//    {
////        m_titleText = value.toString();
//    }
//    else if(role == PSV::titleFont && value.type() == QVariant::Font)
//    {
////        m_titleFont = value.value<QFont>();
//    }
//    else
//    {
//        isValib = false;
//    }
//    if(isValib)
//    {
//        d->setData(role,value);
//    }
//    if(isUpdate && isValib)
//    {
//        refreshItem();
//    }
//}


void PSV_ChartItem::createTitle(const QString &text)
{
    m_titleItem = new QGraphicsTextItem(text,this);
    //    m_titleItem->setHtml(text);//TTTTTTTTTTTTT
    QFont font = titleFont();
    QColor color = titleColor();
    m_titleItem->setFont(font);
    m_titleItem->setDefaultTextColor(color);
    adjustTitlePos();
}

void PSV_ChartItem::adjustTitlePos()
{
    if(m_titleItem == NULL)
    {
        return;
    }
//    qreal margin = getData(PSV::margin).toDouble();
//    PSV_Public::printMes(margin,"margin");

    qreal x = m_chartRect.left() + 0.5 * (m_chartRect.width() - m_titleItem->boundingRect().width());
    qreal dy = 0;
    if(m_upAxisItem != NULL)
    {
        dy += m_upAxisItem->validRect().height();
    }
    qreal y = getBoundingRect().top() + (m_margin_total_up - m_margin_up - getData(PSV::margin,3).toInt() - m_titleItem->boundingRect().height()) * 0.5;
    m_titleItem->setPos(x,y);
}

bool PSV_ChartItem::adjusetMargin()
{
//    qreal m_margin = getData(PSV::margin).toDouble();
//    PSV_Public::printMes(m_margin,"margin");
    int m_margin = getData(PSV::margin,3).toInt();
    qreal margin_up = m_margin_up+m_margin;
    qreal margin_down = m_margin_down+m_margin;
    qreal margin_left = m_margin_left+m_margin;
    qreal margin_right = m_margin_right+m_margin;

    if(m_axisParam_left.m_isShow)
    {
        createLeftAxisi(m_axisParam_left);
        margin_left += m_leftAxisItem->validRect().width();
    }
    if(m_axisParam_right.m_isShow)
    {
        createRightAxisi(m_axisParam_right);
        margin_right += m_rightAxisItem->validRect().width();
    }
    if(m_axisParam_up.m_isShow)
    {
        createUpAxisi(m_axisParam_up);
        margin_up += m_upAxisItem->validRect().height();
    }

    if(m_axisParam_down.m_isShow)
    {
        createDownAxisi(m_axisParam_down);
        margin_down += m_downAxisItem->validRect().height();
    }
    QString m_titleText = getData(PSV::titleText,"").toString();
    if(!m_titleText.isEmpty())
    {
        createTitle(m_titleText);
        margin_up += m_titleItem->boundingRect().height();
    }
    if(!isStaHidden() && m_curveDataMap.count() > 0)
    {
        qreal height_max = 0;
        qreal width_max = 0;
        QGraphicsTextItem *textItem = new QGraphicsTextItem(this);
        textItem->setDefaultTextColor(getDefaultColor());
        textItem->setFont(staFont());
        QMapIterator<QString,PSV_CurveInfo> iter(m_curveDataMap);
        while(iter.hasNext())
        {
            iter.next();
            PSV_CurveInfo curveInfo = iter.value();
            textItem->setHtml(curveInfo.m_staHtmText);
            qreal tempWidth = textItem->boundingRect().width();
            qreal tempHeight = textItem->boundingRect().height();
            if(width_max < tempWidth)
            {
                width_max = tempWidth;
            }
            if(height_max < tempHeight)
            {
                height_max = tempHeight;
            }
        }
        width_max += height_max;
        height_max +=  getData(PSV::margin,3).toInt();
        qreal width = getBoundingRect().width() - margin_left - margin_right;
        if(width_max >= width)
        {
            margin_down += m_curveDataMap.count() * height_max;
        }
        else
        {
            int count_row = (int)(width / width_max);
            int dataCount = m_curveDataMap.count();
            if(dataCount % count_row != 0)
            {
                dataCount += count_row;
            }
            int count = dataCount / count_row;
            margin_down += count * height_max;
        }
        m_staMaxWidth = width_max;
    }
    m_margin_total_up = margin_up;
    m_margin_total_down = margin_down;
    m_margin_total_left = margin_left;
    m_margin_total_right = margin_right;
    updateChartRect();
    return clearAll();
}


QString PSV_ChartItem::titleText()
{
    return getData(PSV::titleText,"").toString();
}

QFont PSV_ChartItem::titleFont()
{
    return getData(PSV::titleFont,QFont()).value<QFont>();
}

QColor PSV_ChartItem::titleColor()
{
    return getData(PSV::titleColor,QColor(Qt::blue)).value<QColor>();
}

QFont PSV_ChartItem::staFont()
{
    return getData(PSV::staFont,QFont()).value<QFont>();
}


void PSV_ChartItem::updateChartRect()
{
    QRectF m_rect = getBoundingRect();
    m_chartRect = QRectF(m_rect.x() + m_margin_total_left
                         ,m_rect.y()+m_margin_total_up
                         ,m_rect.width() - m_margin_total_left - m_margin_total_right
                         ,m_rect.height() - m_margin_total_up - m_margin_total_down);
}

void PSV_ChartItem::setItemNull()
{
    m_titleItem = NULL;
    m_leftAxisItem = NULL;
    m_rightAxisItem = NULL;
    m_upAxisItem = NULL;
    m_downAxisItem = NULL;
    //====================
    m_vLineItem = NULL;
    m_hLineItem = NULL;
    m_currentMesItem = NULL;
    //====================
    setPrivateItemNull();
}

void PSV_ChartItem::showMenu()
{
    QMenu contextMenu;
    contextMenu.addAction( QIcon(":/auxlib/images/shu.png"), QString::fromLocal8Bit("属性"), this, SLOT(onShowPropertyDlg()) );
//    contextMenu.addAction( QIcon(":/auxlib/images/data.png"), QString("曲线数据"), NULL, SLOT(showCurveData()) );
//    contextMenu.addAction( QIcon(":/auxlib/images/pdf.png"), QString("导到PDF"), NULL, SLOT(outputToPdf()) );
//    contextMenu.exec( QCursor::pos() );
//    contextMenu.addAction( QIcon(":/auxlib/images/save.png"), QString("保存曲线"), NULL, SLOT(saveCurrentState()) );
//    contextMenu.addAction( QIcon(":/auxlib/images/load.png"), QString("载入曲线"), NULL, SLOT(loadCurve()) );
    contextMenu.exec( QCursor::pos() );
}

void PSV_ChartItem::createAxisi()
{
    if(m_axisParam_left.m_isShow)
    {
        createLeftAxisi(m_axisParam_left);
    }
    if(m_axisParam_right.m_isShow)
    {
        createRightAxisi(m_axisParam_right);
    }
    if(m_axisParam_up.m_isShow)
    {
        createUpAxisi(m_axisParam_up);
    }
    if(m_axisParam_down.m_isShow)
    {
        createDownAxisi(m_axisParam_down);
    }
}

void PSV_ChartItem::createHVLine()
{
    QLineF hLine(m_chartRect.left(),m_chartRect.center().y(),m_chartRect.right(),m_chartRect.center().y());
    QLineF vLine(m_chartRect.center().x(),m_chartRect.top(),m_chartRect.center().x(),m_chartRect.bottom());

    m_hLineItem = new QGraphicsLineItem(hLine,this);
    m_vLineItem = new QGraphicsLineItem(vLine,this);
    m_boundingItem = new QGraphicsRectItem(getBoundingRect(),this);
    m_hLineItem->hide();
    m_vLineItem->hide();
    m_boundingItem->hide();
    m_hLineItem->setZValue(10001);
    m_vLineItem->setZValue(10001);
    m_boundingItem->setZValue(10001);

    m_currentMesItem = new QGraphicsTextItem(this);
    //    m_currentMesItem->setFont(m_valueFont);

}

//=============================
//================================
void PSV_ChartItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(isChartRectPoint(event->pos()) && event->button() == Qt::LeftButton)
    {
        if(!m_isCurrentMessHidden)
        {
            showCurrentMesItems();
            updateCurrentMes(event->pos());
        }
        return;
    }
    else
    {
        hideCurrentMesItems();
    }
//    PSV_Public::printMes(event->pos(),"event->pos()");
//    PSV_Public::printMes(m_chartRect,"m_chartRect");
    return PSV_Item::mousePressEvent(event);
}

void PSV_ChartItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
//    PSV_Public::printMes("mouseMoveEvent");
    if(isChartRectPoint(event->pos()))
    {
        if(!m_isCurrentMessHidden)
        {
            updateCurrentMes(event->pos());
        }
    }
    else
    {
        hideCurrentMesItems();
    }
}

void PSV_ChartItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    PSV_NOUSED(event);
    hideCurrentMesItems();
}

void PSV_ChartItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    PSV_NOUSED(event);
    m_boundingItem->setVisible(true);
}

void PSV_ChartItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    PSV_NOUSED(event);
    m_boundingItem->setVisible(false);
}

bool PSV_ChartItem::sceneEventFilter(QGraphicsItem *watched, QEvent *event)
{
    if(event->type() == QEvent::GraphicsSceneMouseDoubleClick)
    {
        if(watched->data(E_ITEM_TYPE).toInt() == PSV::ellipseItem)
        {
//            PSV_Public::printMes("sceneEventFilter");
            QString curveName = watched->data(E_CURVE_NAME).toString();
            if(m_curveDataMap.contains(curveName))
            {
                PSV_CurveInfo& info = m_curveDataMap[curveName];
                PSV_CfgDlg_Curve dlg(info);
                if(dlg.exec() == QDialog::Accepted)
                {
                    event->accept();
                    this->refreshItem();
                    return true;
                }
            }
        }

    }
    else if(event->type() == QEvent::GraphicsSceneMousePress)
    {
        if(watched->data(E_ITEM_TYPE).toInt() == PSV::staLabelItem)
        {
            QString curveName = watched->data(E_CURVE_NAME).toString();
            if(m_curveDataMap.contains(curveName))
            {
                PSV_CurveInfo& info = m_curveDataMap[curveName];
                info.m_isHidden = !info.m_isHidden;
                    event->accept();
                    this->refreshItem();
                    return true;
            }
        }
    }

    return QGraphicsItem::sceneEventFilter(watched,event);
}

bool PSV_ChartItem::isChartRectPoint(const QPointF &point)
{
    return m_chartRect.contains(point);
}

QString PSV_ChartItem::getTipDataTextX(const double dataX)
{
    QString xText = QString::number(dataX,'f',decimal());;
    return xText;
}

void PSV_ChartItem::hideCurrentMesItems()
{
    m_vLineItem->setVisible(false);
    m_hLineItem->setVisible(false);
    m_currentMesItem->setVisible(false);
}

void PSV_ChartItem::showCurrentMesItems()
{
    m_vLineItem->setVisible(true);
    m_hLineItem->setVisible(true);
    m_currentMesItem->setVisible(true);
}

//void PSV_Item::test()
//{
//    PSV_CfgDlg_Item dlg(this->m_param);
//    if(dlg.exec() == QDialog::Accepted)
//    {
//        //
//    }
//}
bool PSV_ChartItem::isStaHidden()
{
    return getData(PSV::isStaHidden,false).toBool();
}

int PSV_ChartItem::decimal()
{
    return getData(PSV::decimal,3).toInt();
}

void PSV_ChartItem::updateCurrentMes(const QPointF &point)
{
    QLineF vLine = m_vLineItem->line();
    vLine.setP1(QPointF(point.x(),vLine.y1()));
    vLine.setP2(QPointF(point.x(),vLine.y2()));
    m_vLineItem->setLine(vLine);

    QLineF hLine = m_hLineItem->line();
    hLine.setP1(QPointF(hLine.x1(),point.y()));
    hLine.setP2(QPointF(hLine.x2(),point.y()));
    m_hLineItem->setLine(hLine);

    m_currentMesItem->setHtml(getCurrentHtmMes(point.x()));
    m_currentMesItem->setPos(point.x(),point.y()+10);
}
