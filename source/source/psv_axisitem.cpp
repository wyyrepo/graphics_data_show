#include "psv_axisitem.h"
#include "psv_public.h"

PSV_AxisItem::PSV_AxisItem(const QMap<int, QVariant> &param,QGraphicsItem *parent)
    : PSV_Item(param,parent)
    , m_hasArrow(true)
    , m_isList(false)
    , m_isCenter(false)
    , m_maxValue(10)
    , m_minValue(1)
    , m_numTicks(10)
    , m_lineWidth(1)
    , m_markWidth(1)
    , m_markLength(5)
    , m_arrowsLength(3)
    , m_lineColor(getDefaultColor())
    , m_markColor(getDefaultColor())
{
    m_markFont.setPointSize(12);
    initVariables();    
}

PSV_AxisItem::PSV_AxisItem(const QMap<int, QVariant> &param, const QStringList &list, QGraphicsItem *parent)
    : PSV_Item(param,parent)
    , m_hasArrow(true)
    , m_isList(true)
    , m_isCenter(true)
    , m_maxValue(10)
    , m_minValue(1)
    , m_numTicks(10)
    , m_lineWidth(1)
    , m_markWidth(1)
    , m_markLength(5)
    , m_arrowsLength(3)
    , m_lineColor(getDefaultColor())
    , m_markColor(getDefaultColor())
    , m_list(list)
{
    m_markFont.setPointSize(12);
    initVariables();
}

PSV_AxisItem::~PSV_AxisItem()
{
    //
}

void PSV_AxisItem::initVariables()
{
//    if(d->m_param.contains(PSV::boundingRect))
//    {
//        m_rect = d->m_param.value(PSV::boundingRect).toRectF();
//    }
    if(d->m_param.contains(PSV::toolTip))
    {
        setToolTip(d->m_param.value(PSV::toolTip).toString());
    }
    if(d->m_param.contains(PSV::maxValue))
    {
        m_maxValue = d->m_param.value(PSV::maxValue)/*.toDouble()*/;
    }
    if(d->m_param.contains(PSV::minValue))
    {
        m_minValue = d->m_param.value(PSV::minValue)/*.toDouble()*/;
    }
    if(d->m_param.contains(PSV::lineColor))
    {
        m_lineColor = d->m_param.value(PSV::lineColor).value<QColor>();
    }
    if(d->m_param.contains(PSV::lineWidth))
    {
        m_lineWidth = d->m_param.value(PSV::lineWidth).toDouble();
    }
    if(d->m_param.contains(PSV::markWidth))
    {
        m_markWidth = d->m_param.value(PSV::markWidth).toDouble();
    }
    if(d->m_param.contains(PSV::markColor))
    {
        m_markColor = d->m_param.value(PSV::markColor).value<QColor>();
    }
    if(d->m_param.contains(PSV::markFont))
    {
        m_markFont = d->m_param.value(PSV::markFont).value<QFont>();
    }
    if(d->m_param.contains(PSV::arrowsLength))
    {
        m_arrowsLength = d->m_param.value(PSV::arrowsLength).toDouble();
    }

    if(d->m_param.contains(PSV::isCenter))
    {
        m_isCenter = d->m_param.value(PSV::isCenter).toBool();
    }
    if(d->m_param.contains(PSV::hasArrow))
    {
        m_hasArrow = d->m_param.value(PSV::hasArrow).toBool();
    }
//
    if(!m_hasArrow)
    {
        m_arrowsLength = 0;
    }
    m_validRect = getBoundingRect();
}

//int PSV_AxisItem::type() const
//{
//    return PSV::axisItem;
//}

void PSV_AxisItem::getRange(QVariant &max, QVariant &min, QPair<double, double> &range)
{
    max = m_maxValue;
    min = m_minValue;
    range = m_range;
}

void PSV_AxisItem::getRange(QVariant &max, QVariant &min)
{
    max = m_maxValue;
    min = m_minValue;
}

void PSV_AxisItem::setRange(QVariant &max, QVariant &min, QPair<double, double> &range)
{
    m_maxValue = max;
    m_minValue = min;
    refreshItem();
    getRange(max,min,range);
}

void PSV_AxisItem::setRange(QVariant &max, QVariant &min)
{
    m_maxValue = max;
    m_minValue = min;
    refreshItem();
    QPair<double, double> range(0,0);
    getRange(max,min,range);
}

QList<QPointF> PSV_AxisItem::getMarkPointList()
{
    return m_markPointList;
}

void PSV_AxisItem::updateItem()
{
    return;
}

void PSV_AxisItem::setMarkWidth(const qreal width)
{
    if(width > 0)
    {
        m_markWidth = width;
        refreshItem();
    }
}

QRectF PSV_AxisItem::validRect()
{
    return m_validRect;
}

void PSV_AxisItem::updateLabels()
{
    if(m_isList)
    {
        m_maxValue = m_list.count() - 1;
        m_minValue = 0;
        m_range.first = 0;
        m_range.second = m_list.count() - 1;
        int index  = 0;
        m_labelList.clear();
        foreach(QString label,m_list)
        {
            m_labelList.append(QPair<QVariant, QString>(index,label));
            index++;
        }
    }
    else
    {
        PSV_Public::getLabels(m_maxValue, m_minValue,m_range, m_labelList);
    }
}

void PSV_AxisItem::setList(const QStringList &list)
{
    m_list = list;
    if(m_isList)
    {
        refreshItem();
    }
}

void PSV_AxisItem::setItemNull()
{
    return;
}

//============================================================================
PSV_AxisItemParam::PSV_AxisItemParam()
    : m_isCenter(false)
    , m_hasArrow(true)
    , m_isShow(false)
    , m_fontRatio(1.0)
    , m_list(QStringList())
{
 //
}

PSV_AxisItemParam::PSV_AxisItemParam(const PSV_AxisItemParam &other)
    : m_isCenter(other.m_isCenter)
    , m_hasArrow(other.m_hasArrow)
    , m_isShow(other.m_isShow)
    , m_fontRatio(other.m_fontRatio)
    , m_list(other.m_list)
{
    //
}

PSV_AxisItemParam::~PSV_AxisItemParam()
{
    //
}

PSV_AxisItemParam& PSV_AxisItemParam::operator =(const PSV_AxisItemParam& other)
{
    if(this != &other)
    {
        m_isCenter = other.m_isCenter;
        m_hasArrow = other.m_hasArrow;
        m_isShow = other.m_isShow;
        m_fontRatio = other.m_fontRatio;
        m_list = other.m_list;
    }
    return *this;
}
