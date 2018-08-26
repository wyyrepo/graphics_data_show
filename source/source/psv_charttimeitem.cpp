#include "psv_charttimeitem.h"

PSV_ChartTimeItem::PSV_ChartTimeItem(const QMap<int, QVariant> &param, QGraphicsItem *parent)
    : PSV_ChartItem(param,parent)
{
    m_max_x = QTime(23,59,59);
    m_min_x = QTime(0,0,0);

    m_axisParam_left.m_isShow = true;
    m_axisParam_down.m_isShow = true;
    createAxisi();
    m_isCurrentMessHidden = false;
}

PSV_ChartTimeItem::~PSV_ChartTimeItem()
{
    //
}

int PSV_ChartTimeItem::type() const
{
    return PSV::chartTimeItem;
}

PSV::DATATYPE PSV_ChartTimeItem::dataType()
{
    return PSV::E_DATATYPE_TIME;
}

void PSV_ChartTimeItem::setPrivateItemNull()
{
    return;
}

void PSV_ChartTimeItem::afterUpdateItem()
{
    updateForDouble();
}

bool PSV_ChartTimeItem::addCurve(const QMap<QTime, double> &data, const PSV_CurveParam &curveParam)
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
    QMapIterator<QTime,double> iter(data);
    PSV_CurveInfo curveInfo(curveName);
    curveInfo.m_axisType = curveParam.m_axisType;
    setCurrentAxisType(curveInfo.m_axisType);
    curveInfo.m_curveType = curveParam.m_curveType;

    //==================================
    double sum = 0.0;
    double max_y = 0.0;
    double min_y = 0.0;
    QTime max_y_pointX;
    QTime min_y_pointX;

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
        }
        int sec = QTime(0,0,0).secsTo(iter.key());
        curveData.insert(sec,iter.value());
    }
    if(*m_isFisrtCurve_curP)
    {
        *m_max_y_curP = max_y;
        *m_min_y_curP = min_y;
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
 //======================================
    double avg_y = sum / data.count();
    QStringList textList;
    int dml = decimal();
    textList.append(QString("%1:").arg(curveName));
    textList.append(QString(" %1:(%2,%3)").arg(QString::fromLocal8Bit("最大值")).arg(max_y_pointX.toString("hh:mm:ss")).arg(QString::number(max_y,'f',dml)));
    textList.append(QString(" %1:(%2,%3)").arg(QString::fromLocal8Bit("最小值")).arg(min_y_pointX.toString("hh:mm:ss")).arg(QString::number(min_y,'f',dml)));
    textList.append(QString(" %1:%2").arg(QString::fromLocal8Bit("平均值")).arg(QString::number(avg_y,'f',dml)));

    QString staHtmText = PSV_Public::getStaText(textList/*,m_staFont*/);
    curveInfo.m_staHtmText = staHtmText;
    curveInfo.m_staText = textList.join("");
    //======================================
    curveInfo.m_curveDataMap = curveData;
    m_curveDataMap.insert(curveName,curveInfo);
    if(curveParam.m_isUpdate)
    {
        refreshItem();
    }
    return true;
}

QString PSV_ChartTimeItem::getToolTipText(const double x, const double y)
{
    return QString("value = %1\n时间:%2").arg(QString::number(y,'f',decimal()))
            .arg(getTipDataTextX(x));
}

QString PSV_ChartTimeItem::getTipDataTextX(const double dataX)
{
    QString xText = m_min_time.addSecs((int)dataX).toString("hh:mm:ss");
    return xText;
}
