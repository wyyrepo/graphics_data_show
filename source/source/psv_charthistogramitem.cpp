#include <QPen>
#include <math.h>
#include "psv_histogramitem.h"
#include "psv_charthistogramitem.h"
#include "psv_axisleftitem.h"
#include "psv_axisdownitem.h"

PSV_ChartHistogramItem::PSV_ChartHistogramItem(const QMap<int, QVariant> &param, QGraphicsItem *parent)
    : PSV_ChartItem(param,parent)
    , m_isSameColor(false)
    , m_isSingle(true)
    , m_isStacked(false)
//    , m_valueHidden(false)
    , m_isContinue(false)
    , m_itemWidth(50.0)
    , m_itemGapWidth(15.0)
    , m_itemWidthRatio(0.8)
    , m_originHeight(0)
    , m_obliqueAngle(45)
    , m_cosLength(m_itemWidth / 3)    
    , m_dataCount(1)
    , m_dataStruct(PSV::realNumber)
    , m_sameColor(Qt::darkCyan)
{
    initParam();

    m_axisParam_left.m_isShow = true;
    m_axisParam_down.m_isShow = true;
//    m_axisParam_up.m_isShow = true;
//    m_axisParam_right.m_isShow = true;
    m_axisParam_down.m_hasArrow = false;
    m_axisParam_down.m_isCenter = true;
    m_axisParam_down.m_isShow = true;
    createAxisi();
}

PSV_ChartHistogramItem::~PSV_ChartHistogramItem()
{
    //
}

int PSV_ChartHistogramItem::type() const
{
    return PSV::chartHistogramItem;
}

PSV::DATATYPE PSV_ChartHistogramItem::dataType()
{
    return PSV::E_DATATYPE_LIST;
}

void PSV_ChartHistogramItem::setPrivateItemNull()
{
    return;
}

void PSV_ChartHistogramItem::beforeUpdateItem()
{
    double flag = 1;
    if(!(m_isStacked  || m_isSingle) && m_dataCount > 0)
    {
        flag = m_dataCount * 0.7;
    }
    QRectF m_rect = getBoundingRect();
//    m_valueFont.setPointSizeF(PSV_Public::getMinLenght(m_rect) * 0.04 / flag);
//    m_titleFont.setPointSizeF(PSV_Public::getMinLenght(m_rect) * 0.05);

    double tempLength = m_rect.width() / (m_axisParam_down.m_list.count() > 1 ? m_axisParam_down.m_list.count() : 1) * 0.5;
    m_margin_up = tan(m_obliqueAngle / 180 * PSV_PI) * tempLength;
    m_margin_right = tempLength;
    adjusetMargin();
    updateChartRect();

    m_isContinue = true;
    if(m_dataCount <= 0)
    {
        m_isContinue = false;
        return;
    }
    int count = m_axisParam_down.m_list.count();
    if(count <= 0)
    {
        count = 1;
        m_itemWidth = m_chartRect.width() / count * m_itemWidthRatio;
        m_itemGapWidth = m_chartRect.width() / count - m_itemWidth;
        m_cosLength = 5;
    }
    else
    {
        m_itemWidth = m_chartRect.width() / count * m_itemWidthRatio;
        m_itemGapWidth = m_chartRect.width() / count - m_itemWidth;
        if(m_isStacked  || m_isSingle)
        {
            m_cosLength = m_itemWidth / 3;
        }
        else
        {
            m_cosLength = m_itemWidth / 3 / m_dataCount;
        }
    }

}

void PSV_ChartHistogramItem::afterUpdateItem()
{
    //================================================================
    QList<QPointF> pointList;
    pointList = m_leftAxisItem->getMarkPointList();
    if(m_dataStruct == PSV::positiveNumber)
    {
        m_originHeight = m_chartRect.bottom();
    }
    else if(m_dataStruct ==  PSV::negativeNumber)
    {
        m_originHeight = m_chartRect.top();
    }
    else
    {
        m_originHeight = m_chartRect.bottom() - (0.0 - m_min_y_left) / (m_max_y_left - m_min_y_left) * m_chartRect.height();
    }
    //================================================================
    if(!m_isContinue)
    {
        return;
    }    
    //================================================================
    {//圆点
        QPen pen;
        pen.setWidthF(1.0);
        pen.setStyle(Qt::DashDotLine);
        pen.setColor(Qt::white);
        for(int i = 0; i < pointList.count();++i)
        {
            QPointF point1 = pointList.at(i);
            QPointF point2 = QPointF(point1.x() + m_cosLength, point1.y() - tan(m_obliqueAngle / 180 * PSV_PI) * m_cosLength);
            QPointF point3 = QPointF(point1.x() + m_chartRect.width() + m_cosLength, point2.y());
            QGraphicsPathItem* item = new QGraphicsPathItem(this);
            QPainterPath path;
            path.moveTo(point1);
            path.lineTo(point2);
            path.lineTo(point3);
            item->setPath(path);
            item->setPen(pen);
            item->setZValue(-10);
            item->setAcceptedMouseButtons(0);
            item->setAcceptHoverEvents(false);
        }
        QColor color(222, 222, 222, 50);
        QRectF rect(m_chartRect.left(), m_originHeight, m_chartRect.width(), 5);

        QMap<int, QVariant> param;
        param.insert(PSV::boundingRect,rect);
        param.insert(PSV::color,color);
        param.insert(PSV::obliqueAngle,m_obliqueAngle);
        param.insert(PSV::cosLength,m_cosLength);
        PSV_HistogramItem *item = new PSV_HistogramItem(param,this);
        item->setAcceptedMouseButtons(0);
        item->setAcceptHoverEvents(false);
//        PSV_NOUSED(item);
    }

    double x = m_chartRect.x();
    bool valueHidden = getData(PSV::isValueHidden,true).toBool();
    QFont valueFont = getData(PSV::valueFont,QFont()).value<QFont>();
    QColor textColor = getData(PSV::valueColor,getDefaultColor()).value<QColor>();
    if(m_isSingle)
    {
        for(int k = 0; k < m_singleDataListPair.count(); ++k)
        {
            QPair<QString, double > dataPair = m_singleDataListPair.at(k);
            int index = k;
            QRectF rectF;
            QPointF textPos;
            QRectF boundingRect(0,0,0,0);
            QGraphicsTextItem* textItem = NULL;
            if(!valueHidden)
            {
                textItem = new QGraphicsTextItem(QString::number(dataPair.second), this);
                textItem->setDefaultTextColor(textColor);
                textItem->setFont(valueFont);
                textItem->setZValue(2);
                textItem->setAcceptedMouseButtons(0);
                textItem->setAcceptHoverEvents(false);
                boundingRect = textItem->boundingRect();
            }
            getItemsPos(index, boundingRect, dataPair.second, textPos, rectF);
            if(!valueHidden)
            {
                textItem->moveBy(textPos.x(), textPos.y());
            }
            QColor color = PSV_Public::getHistogramColor(index,m_colorList,m_isSameColor,m_sameColor);
            QMap<int, QVariant> param;
            param.insert(PSV::boundingRect,rectF);
            param.insert(PSV::color,color);
            param.insert(PSV::obliqueAngle,m_obliqueAngle);
            param.insert(PSV::cosLength,m_cosLength);
            PSV_HistogramItem *item = new PSV_HistogramItem(param,this);
            item->setAcceptedMouseButtons(0);
            item->setAcceptHoverEvents(false);
            PSV_NOUSED(item);
        }
    }
    else
    {
        int zvalue = 0;
        for(int k = 0; k < m_dataListPair.count(); ++k)
        {
            QPair<QString, QList<double> > dataPair = m_dataListPair.at(k);
            QList<double> valueList = dataPair.second;
            int valueCount = valueList.count();
            if(valueCount != m_dataCount)
            {
                continue;
            }
            int count = m_dataCount;
            if(m_isStacked)
            {
                count = 1;
            }
            qreal singleItemWidth = m_itemWidth / count;
            qreal singleItemGapWidth = m_itemGapWidth / (count + 1);
            double y = m_originHeight;
            double height = 0;
            for(int i = 0; i < m_dataCount; ++i)
            {
                QRectF rectF;
                double value = valueList.at(i);
                qreal curHeight =  qAbs(value - m_min_y_left) / (m_max_y_left - m_min_y_left) * m_chartRect.height();
                height = curHeight;
                rectF = QRectF(x + singleItemGapWidth,y - height,singleItemWidth,curHeight);

                if(!valueHidden && value > PSV_ZEOR)
                {
                    QString text = QString::number(value);
                    QGraphicsTextItem *textItem = new QGraphicsTextItem(text, this);
                    textItem->setDefaultTextColor(textColor);
                    textItem->setAcceptedMouseButtons(0);
                    textItem->setAcceptHoverEvents(false);
                    textItem->setFont(valueFont);
                    textItem->setPos(rectF.x() + 0.5 * (rectF.width() - textItem->boundingRect().width())
                                     ,rectF.top() + 0.5 * (rectF.height() - textItem->boundingRect().height()));
                    textItem->setZValue(m_dataCount * m_axisParam_down.m_list.count() + 2);
                }
                QColor color = PSV_Public::getHistogramColor(i,m_colorList,m_isSameColor,m_sameColor);
                QMap<int, QVariant> param;
                param.insert(PSV::boundingRect,rectF);
                param.insert(PSV::color,color);
                param.insert(PSV::obliqueAngle,m_obliqueAngle);
                param.insert(PSV::cosLength,m_cosLength);
                PSV_HistogramItem *item = new PSV_HistogramItem(param,this);
                item->setAcceptedMouseButtons(0);
                item->setAcceptHoverEvents(false);
                if(!m_isStacked)
                {
                    item->setZValue(k);
                    x += singleItemWidth + singleItemGapWidth;
                }
                else
                {
                    item->setZValue(zvalue++);
                    y -= height;
                }
            }
            if(m_isStacked)
            {
                x += m_itemWidth + m_itemGapWidth;
            }
            else
            {
                x += singleItemGapWidth;
            }
        }
    }
    //================================================
    if(!getData(PSV::isLineHidden,false).toBool())
    {
        QMapIterator<QString,PSV_CurveInfo> iter(m_curveDataMap);
        while(iter.hasNext())
        {
            iter.next();
            PSV_CurveInfo curveInfo = iter.value();
            updateAxisRange(curveInfo.m_axisType);
            addCurveItem(curveInfo);
            addEllipseItem(curveInfo);
        }
    }
    //================================================
}

void PSV_ChartHistogramItem::setList(const QStringList &list)
{
    m_downAxisItem->setList(list);
    m_axisParam_down.m_list = list;
}

void PSV_ChartHistogramItem::initParam()
{
    addDefaultParam(PSV::isLineHidden,false);
    addDefaultParam(PSV::isValueHidden,false);
    addDefaultParam(PSV::valueFont,QFont());
    addDefaultParam(PSV::valueColor,getDefaultColor());

    addUnsetParam(PSV::isStaHidden);

//    if(d->m_param.contains(PSV::valueFont))
//    {
//        m_valueFont = d->m_param.value(PSV::valueFont).value<QFont>();
//    }
    if(d->m_param.contains(PSV::isSameColor))
    {
        m_isSameColor = d->m_param.value(PSV::isSameColor).toBool();
    }
    if(d->m_param.contains(PSV::sameColor))
    {
        m_sameColor = d->m_param.value(PSV::sameColor).value<QColor>();
    }
}

bool PSV_ChartHistogramItem::addHistogram(const QMap<QString, double> &data, QList<QColor> &colorList, bool isMandated)
{
    QList<QPair<QString, double > > dataList;
    QMapIterator<QString, double> iter(data);
    while(iter.hasNext())
    {
        iter.next();
        dataList.append(QPair<QString,double >(iter.key(),iter.value()));
    }
    return addHistogram(dataList,colorList,isMandated);
}

bool PSV_ChartHistogramItem::addHistogram(const QList<QPair<QString, double> > dataList, QList<QColor> &colorList, bool isMandated)
{
    if(!isMandated && (m_singleDataListPair.count() > 0 || m_dataListPair.count() > 0))
    {
        return false;
    }
    m_isSingle = true;
    m_isFisrtCurve_left = true;
    m_singleDataListPair.clear();
    m_dataListPair.clear();
    m_colorList = colorList;
    m_axisParam_down.m_list.clear();
    m_dataCount = 1;

    int positiveNumberCount = 0;
    int negativeNumberCount = 0;
    for(int i = 0; i < dataList.count(); ++i)
    {
        QPair<QString, double> dataPair = dataList.at(i);
        double value = dataPair.second;
        m_axisParam_down.m_list.append(dataPair.first);
        m_singleDataListPair.append(QPair<QString,double >(dataPair.first,dataPair.second));
        if(m_isFisrtCurve_left)
        {
            m_max_y_left = value;
            m_min_y_left = value;
            m_isFisrtCurve_left = false;
        }
        //===================
        if(m_max_y_left < value)
        {
            m_max_y_left = value;
        }
        if(m_min_y_left > value)
        {
            m_min_y_left = value;
        }
        if(value > 0)
        {
            positiveNumberCount++;
        }
        if(value < 0)
        {
            negativeNumberCount++;
        }
    }
    if(positiveNumberCount > 0 && negativeNumberCount == 0)
    {
        m_dataStruct = PSV::positiveNumber;
    }
    else if(negativeNumberCount > 0 && positiveNumberCount == 0)
    {
        m_dataStruct = PSV::negativeNumber;
    }
    else
    {
        m_dataStruct = PSV::realNumber;
    }
    return true;
}

bool PSV_ChartHistogramItem::addHistogram(const QList<QPair<QString, QList<double> > > dataList, QList<QColor> &colorList, bool isStacked, bool isMandated)
{
    if(!isMandated && (m_singleDataListPair.count() > 0 || m_dataListPair.count() > 0))
    {
        return false;
    }
    addUnsetParam(PSV::isLineHidden);

    QStringList tempList;
    bool isFisrt = true;
    double max = 0.0;
    double min = 0.0;
    int dataCount = -1;

    for(int i = 0; i < dataList.count(); ++i)
    {
        QPair<QString, QList<double> > dataPair = dataList.at(i);
        QList<double> valueList = dataPair.second;
        bool isnonegative = true;
        double value = PSV_Public::getListValue(valueList,isStacked,isnonegative);
        if(!isnonegative)
        {
            return false;
        }
        tempList.append(dataPair.first);
        if(isFisrt)
        {
            max = value;
            min = value;
            isFisrt = false;
            dataCount = valueList.count();
        }
        else
        {
            if(dataCount != valueList.count())
            {
                return false;
            }
        }
        //===================
        if(max < value)
        {
            max = value;
        }
        if(min > value)
        {
            min = value;
        }
    }

    if(dataCount <= 0)
    {
        return false;
    }
    m_isStacked = isStacked;
    m_dataCount = dataCount;
    m_isSingle = false;
    m_isFisrtCurve_left = false;
    m_singleDataListPair.clear();
    m_dataListPair = dataList;
    m_colorList = colorList;
    m_axisParam_down.m_list = tempList;
    m_dataStruct = PSV::positiveNumber;
    m_max_y_left = max;
//    m_min_y_left = min;
    m_min_y_left = 0;
    return true;
}

void PSV_ChartHistogramItem::getItemsPos(int index, const QRectF &text, double value, QPointF &textPos, QRectF &rectF)
{
    qreal textWidth = text.width();
    qreal textHeight = text.height();
    qreal x = index * (m_itemWidth + m_itemGapWidth) + m_chartRect.x() - 0.5 * m_itemGapWidth;
    qreal textPosX = x + (m_itemWidth - textWidth) / 2 + m_itemGapWidth;
//    qreal height = qAbs(value) / (m_max_y_left - m_min_y_left) * m_chartRect.height();
    double zeroValue = 0.0;
    if(m_dataStruct == PSV::negativeNumber)
    {
        zeroValue = m_max_y_left;
    }
    else if(m_dataStruct == PSV::positiveNumber)
    {
        zeroValue = m_min_y_left;
    }
    else
    {
        zeroValue = 0.0;
    }

    qreal height = qAbs(value - zeroValue) / (m_max_y_left - m_min_y_left) * m_chartRect.height();
    if(m_dataStruct == PSV::negativeNumber)
    {
        textPos = QPointF(textPosX, height + m_chartRect.y());
        rectF = QRectF(x + m_itemGapWidth, m_chartRect.y(), m_itemWidth, height);
    }
    else if(m_dataStruct == PSV::positiveNumber)
    {
        textPos = QPointF(textPosX, m_originHeight - height - textHeight );
        rectF = QRectF(x + m_itemGapWidth, m_originHeight - height, m_itemWidth, height);
    }
    else
    {
        qreal y = 0;
        if(value > 0)
        {
            y = m_originHeight - height;
            textPos = QPointF(textPosX, y - textHeight);
        }
        else
        {
            y = m_originHeight;
            textPos = QPointF(x + (m_itemWidth - textWidth) / 2 + m_itemGapWidth, y + height);
        }
        rectF = QRectF(x + m_itemGapWidth, y, m_itemWidth, height);
    }
}

bool PSV_ChartHistogramItem::addCurve(const QMap<QString, double> &data, const PSV_CurveParam &curveParam)
{
    QString curveName = curveParam.m_curveName;
    if(curveParam.m_isReplace)
    {
        clearCurve(curveName);
    }
    if(m_curveDataMap.contains(curveName) || curveName.isEmpty())
    {
        return false;
    }
    QStringList tempList = data.keys();
    if(m_axisParam_down.m_list.count() > 0)
    {
    foreach(QString label,tempList)
    {
        if(!m_axisParam_down.m_list.contains(label))
        {
            return false;
        }
    }
    }
    else
    {
        m_axisParam_down.m_list = tempList;
    }

    QMapIterator<QString,double> iter(data);
    QMap<double,double> tempData;
    PSV_CurveInfo curveInfo(curveName);
    curveInfo.m_axisType = PSV::E_AXIS_RIGHT;//强制设为右坐标
    curveInfo.m_curveType = curveParam.m_curveType;
    bool isChangedY = false;
    int index = 0;
    while(iter.hasNext())
    {
        iter.next();
        int tempIndex = m_axisParam_down.m_list.indexOf(iter.key());
        if(tempIndex < 0)
        {
            tempIndex = index;
        }
        tempData.insert(tempIndex,iter.value());
        if(m_isFisrtCurve_right)
        {
            m_max_y_right = iter.value();
            m_min_y_right = iter.value();
            isChangedY = true;
            m_isFisrtCurve_right = false;
        }
        else
        {
            if(m_max_y_right < iter.value())
            {
                m_max_y_right = iter.value();
                isChangedY = true;
            }
            if(m_min_y_right > iter.value())
            {
                m_min_y_right = iter.value();
                isChangedY = true;
            }
        }
        index++;
    }
    curveInfo.m_curveDataMap = tempData;
    m_curveDataMap.insert(curveName,curveInfo);
    if(curveParam.m_isUpdate)
    {
        refreshItem();
    }
    return true;
}

QString PSV_ChartHistogramItem::getToolTipText(const double x, const double y)
{
    int tempX = (int)x;
    QString xStr;
    if(m_axisParam_down.m_list.count() > tempX && tempX >= 0)
    {
        xStr = m_axisParam_down.m_list.at(tempX);
    }
    return QObject::tr("y = %1\n%2").arg(QString::number(y,'f',decimal())).arg(xStr);
}

//void PSV_ChartHistogramItem::setValueHidden(bool hidden)
//{
//    if(m_valueHidden != hidden)
//    {
//        m_valueHidden = hidden;
//        refreshItem();
//    }
//}

double PSV_ChartHistogramItem::getAxisX(double dataX, int adjust)
{
    QRectF rect(m_chartRect.x() + 0.5 * (m_itemWidth+m_itemGapWidth)
                ,m_chartRect.y()
                ,m_chartRect.width() - (m_itemWidth+m_itemGapWidth)
                ,m_chartRect.height());

    double x = rect.left() - adjust;
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

double PSV_ChartHistogramItem::getAxisPointDataX(float pointX) const
{
    QRectF rect(m_chartRect.x() + 0.5 * (m_itemWidth+m_itemGapWidth)
                ,m_chartRect.y()
                ,m_chartRect.width() - (m_itemWidth+m_itemGapWidth)
                ,m_chartRect.height());

    double new_data = 1.0 * (m_rangeX.first) + 1.0 * (pointX - rect.left()) / (rect.width()) * (m_rangeX.second - m_rangeX.first);  //计算当前鼠标坐标对应的数据
    return new_data;
}
