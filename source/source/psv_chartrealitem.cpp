//#include <QEvent>
#include "psv_chartrealitem.h"

PSV_ChartRealItem::PSV_ChartRealItem(const QMap<int, QVariant> &param, QGraphicsItem *parent)
    : PSV_ChartItem(param,parent)
{
    m_axisParam_left.m_isShow = true;
    m_axisParam_down.m_isShow = true;
    m_axisParam_up.m_isShow = false;
    m_axisParam_right.m_isShow = true;
    createAxisi();
    m_isCurrentMessHidden = false;
}

PSV_ChartRealItem::~PSV_ChartRealItem()
{
    //
}

int PSV_ChartRealItem::type() const
{
    return PSV::chartRealItem;
}

PSV::DATATYPE PSV_ChartRealItem::dataType()
{
    return PSV::E_DATATYPE_DOUBLE;
}

void PSV_ChartRealItem::setPrivateItemNull()
{
    return;
}

void PSV_ChartRealItem::afterUpdateItem()
{
    updateForDouble();
}

bool PSV_ChartRealItem::addCurve(const QMap<double, double> &data, const PSV_CurveParam &curveParam)
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
    QMapIterator<double,double> iter(data);
    PSV_CurveInfo curveInfo(curveName);
    curveInfo.m_axisType = curveParam.m_axisType;
    setCurrentAxisType(curveInfo.m_axisType);
    curveInfo.m_curveType = curveParam.m_curveType;
    double sum = 0.0;
    double max_y = 0.0;
    double min_y = 0.0;
//    double max_y_pointX = 0.0;
//    double min_y_pointX = 0.0;

    double max_x = 0.0;
    double min_x = 0.0;
    bool isFisrt = true;
    while(iter.hasNext())
    {
        iter.next();
        double value = iter.value();
        if(isFisrt)
        {
            isFisrt = false;
            max_y = value;
            min_y = value;
            sum = value;
            max_x = iter.key();
            min_x = iter.key();
//            max_y_pointX = iter.key();
//            min_y_pointX = iter.key();
        }
        else
        {
            sum += value;
            if(max_y < value)
            {
                max_y = value;
//                max_y_pointX = iter.key();
            }
            if(min_y > value)
            {
                min_y = value;
//                min_y_pointX = iter.key();
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
    }
    if(*m_isFisrtCurve_curP)
    {
        *m_max_y_curP = max_y;
        *m_min_y_curP = min_y;
        if(m_isFisrtCurve_left && m_isFisrtCurve_right)
        {
            m_rangeX.first = min_x;
            m_rangeX.second = max_x;
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
    if(m_rangeX.first > min_x)
    {
        m_rangeX.first = min_x;
    }
    if(m_rangeX.second < max_x)
    {
        m_rangeX.second = max_x;
    }
    m_max_x = m_rangeX.second;
    m_min_x = m_rangeX.first;
    double avg_y = sum / data.count();
    QStringList textList;
    int dml = decimal();
    textList.append(QString("%1:").arg(curveName));
    textList.append(QString(" %1:%2").arg(QString::fromLocal8Bit("最大值")).arg(QString::number(max_y,'f',dml)));
    textList.append(QString(" %1:%2").arg(QString::fromLocal8Bit("最小值")).arg(QString::number(min_y,'f',dml)));
    textList.append(QString(" %1:%2").arg(QString::fromLocal8Bit("平均值")).arg(QString::number(avg_y,'f',dml)));

    QString staHtmText = PSV_Public::getStaText(textList/*,m_staFont*/);
    curveInfo.m_staHtmText = staHtmText;
    curveInfo.m_staText = textList.join("");
    curveInfo.m_curveDataMap = data;
    m_curveDataMap.insert(curveName,curveInfo);
    if(curveParam.m_isUpdate)
    {
        refreshItem();
    }
    return true;
}

bool PSV_ChartRealItem::addCurve(const QMap<int, double> &data, const PSV_CurveParam &curveParam)
{
    QMap<double,double> tempData;
    QMapIterator<int,double> iter(data);
    while(iter.hasNext())
    {
        iter.next();
        tempData.insert(iter.key(),iter.value());
    }
    return addCurve(tempData,curveParam);
}

QString PSV_ChartRealItem::getToolTipText(const double x, const double y)
{
    return QObject::tr("y = %1\nx = %2").arg(QString::number(y,'f',decimal())).arg(x);
}
