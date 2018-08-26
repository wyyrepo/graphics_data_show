#include "psv_chartdatetimeitem.h"

PSV_ChartDateTimeItem::PSV_ChartDateTimeItem(const QMap<int, QVariant> &param, QGraphicsItem *parent)
    : PSV_ChartItem(param,parent)
{
    m_beginDateTime = PSV_BEGIN_DATETIME;
    m_min_x = m_beginDateTime;
    m_max_x = QDateTime::currentDateTime();
    m_max_dateTime = m_beginDateTime;
    m_min_dateTime = m_beginDateTime;

    m_axisParam_left.m_isShow = true;
    m_axisParam_down.m_isShow = true;
    createAxisi();
    m_isCurrentMessHidden = false;
}

PSV_ChartDateTimeItem::~PSV_ChartDateTimeItem()
{
    //
}

int PSV_ChartDateTimeItem::type() const
{
    return PSV::chartDateTimeItem;
}

PSV::DATATYPE PSV_ChartDateTimeItem::dataType()
{
    return PSV::E_DATATYPE_DATETIME;
}

void PSV_ChartDateTimeItem::setPrivateItemNull()
{
    return;
}

bool PSV_ChartDateTimeItem::addCurve(const QMap<QDateTime, double> &data
                                     , const PSV_CurveParam &curveParam
                                     , bool isDate)
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
    if(data.count() <= 0)
    {
        PSV_Public::printMes(QString::fromLocal8Bit("warning:数据为空"));
        return false;
    }

    QMap<double,double> curveData;
    QMapIterator<QDateTime,double> iter(data);
    PSV_CurveInfo curveInfo(curveName);
    curveInfo.m_axisType = curveParam.m_axisType;
    setCurrentAxisType(curveInfo.m_axisType);
    curveInfo.m_curveType = curveParam.m_curveType;
    if(isDate)
    {
        curveInfo.m_dataType = PSV::E_DATATYPE_DATE;
    }
    else
    {
        curveInfo.m_dataType = PSV::E_DATATYPE_DATETIME;
    }


    bool isChangedY = false;
    bool isChangedX = false;
    //==========================
    double sum = 0.0;
    double max_y = 0.0;
    double min_y = 0.0;
    QDateTime max_y_pointX = PSV_BEGIN_DATETIME;
    QDateTime min_y_pointX = PSV_BEGIN_DATETIME;

    QDateTime max_x = PSV_BEGIN_DATETIME;
    QDateTime min_x = PSV_BEGIN_DATETIME;

    bool isFisrt = true;

    while(iter.hasNext())
    {
        iter.next();
        if(!iter.key().isValid())
        {
            continue;
        }
        double value = iter.value();
        if(isFisrt)
        {
            isFisrt = false;
            max_y = value;
            min_y = value;
            sum = value;
            max_y_pointX = iter.key();
            min_y_pointX = iter.key();
            max_x = iter.key();
            min_x = iter.key();
        }
        else
        {
            sum += value;
            if(max_y < value)
            {
                max_y = value;
                max_y_pointX = iter.key();
            }
            if(min_y > value)
            {
                min_y = value;
                min_y_pointX = iter.key();
            }
            if(max_x < iter.key())
            {
                max_x = iter.key();
            }
            if(min_x > iter.key())
            {
                min_x = iter.key();
            }
        }
        int sec = m_beginDateTime.secsTo(iter.key());//
        curveData.insert(sec,iter.value());
    }

    if(*m_isFisrtCurve_curP)
    {
        *m_max_y_curP = max_y;
        *m_min_y_curP = min_y;
        if(m_isFisrtCurve_left && m_isFisrtCurve_right)
        {
            m_max_dateTime = max_x;
            m_min_dateTime = min_x;
        }
        *m_isFisrtCurve_curP = false;
    }
    else
    {
        if(*m_max_y_curP < max_y)
        {
            *m_max_y_curP = max_y;
        }
        if(*m_min_y_curP > min_y)
        {
            *m_min_y_curP = min_y;
        }
    }
    if(m_max_dateTime < max_x)
    {
        m_max_dateTime = max_x;
    }
    if(m_min_dateTime > min_x)
    {
        m_min_dateTime = min_x;
    }
//    PSV_Public::printMes(max_y_pointX,"max_y_pointX");
//    PSV_Public::printMes(min_y_pointX,"min_y_pointX");
    m_max_x = m_max_dateTime;
    m_min_x = m_min_dateTime;
//    PSV_Public::printMes(m_max_x,"m_max_x");
//    PSV_Public::printMes(m_min_x,"m_min_x");
    //======================================
    QString dateForm = curveInfo.m_dataType == PSV::E_DATATYPE_DATETIME ? "yyyy-MM-dd hh:mm:ss" : "yyyy-MM-dd";
    double avg_y = sum / data.count();
    QStringList textList;
    int dml = decimal();
    textList.append(QString("%1:").arg(curveName));
    textList.append(QString(" %1:(%2,%3)").arg(QString::fromLocal8Bit("最大值"))
                    .arg(max_y_pointX.toString(dateForm))
                    .arg(QString::number(max_y,'f',dml)));

    textList.append(QString(" %1:(%2,%3)")
                    .arg(QString::fromLocal8Bit("最小值"))
                    .arg(min_y_pointX.toString(dateForm))
                    .arg(QString::number(min_y,'f',dml)));
    textList.append(QString(" %1:%2")
                    .arg(QString::fromLocal8Bit("平均值"))
                    .arg(QString::number(avg_y,'f',dml)));

    QString staHtmText = PSV_Public::getStaText(textList/*,m_staFont*/);
    curveInfo.m_staHtmText = staHtmText;
    curveInfo.m_staText = textList.join("");
    //======================================
    curveInfo.m_curveDataMap = curveData;
    m_curveDataMap.insert(curveName,curveInfo);
    if(curveParam.m_isUpdate)
    {
        if(isChangedY || isChangedX)
        {
//            PSV_Public::printMes("19refreshItem");
            refreshItem();
        }
    }
    return true;
}

bool PSV_ChartDateTimeItem::addCurve(const QMap<QDate, double> &data, const PSV_CurveParam &curveParam)
{
    QMapIterator<QDate, double> iter(data);
    QMap<QDateTime,double> tempData;
    while(iter.hasNext())
    {
        iter.next();
        if(iter.key().isValid())
        {
            tempData.insert(QDateTime(iter.key(),QTime(0,0,0)),iter.value());
        }
    }
    return addCurve(tempData,curveParam,true);
}

QString PSV_ChartDateTimeItem::getToolTipText(const double x, const double y)
{
    return QString("value = %1\n%2").arg(QString::number(y,'f',decimal()))
            .arg(getTipDataTextX(x));
}

void PSV_ChartDateTimeItem::afterUpdateItem()
{
    updateForDouble();
}

QString PSV_ChartDateTimeItem::getTipDataTextX(const double dataX)
{
    QString xText = QString("%1:%2").arg(QString::fromLocal8Bit("日期")).arg(PSV_BEGIN_DATETIME.addSecs((int)dataX).toString("yyyy-MM-dd hh:mm:ss"));
    return xText;
}
