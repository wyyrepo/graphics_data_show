#include <QLinearGradient>
#include "psv_chartbaritem.h"

PSV_ChartBarItem::PSV_ChartBarItem(const QMap<int, QVariant> &param, QGraphicsItem *parent)
    : PSV_ChartItem(param,parent)
    , m_isSameColor(false)
    , m_itemWidth(0)
    , m_itemGapWidth(0)
    , m_itemWidthRatio(0.6)
    , m_sameColor(Qt::black)
    , m_valueColor(Qt::blue)
{
    //==============================
    m_axisParam_left.m_isShow = true;
    m_axisParam_up.m_isShow = true;
    createAxisi();
   //==============================
    m_valueFont.setBold(true);
    m_valueFont.setPointSize(12);
    //====================
    setAcceptedMouseButtons(0);
}

PSV_ChartBarItem::~PSV_ChartBarItem()
{
    //
}

int PSV_ChartBarItem::type() const
{
    return PSV::chartBarItem;
}

PSV::DATATYPE PSV_ChartBarItem::dataType()
{
    return PSV::E_DATATYPE_UNKOWN;
}

void PSV_ChartBarItem::setPrivateItemNull()
{
    //
}

void PSV_ChartBarItem::afterUpdateItem()
{
//    createLeftAxisi(m_list,true,false);
//    createUpAxisi();
//    m_axisParam_left.m_list = m_list;
//    createAxisi();

//    createTitle(m_titleText);
    QRectF m_rect = getBoundingRect();
    m_valueFont.setPointSizeF(m_rect.height() * 0.025);

    if(m_axisParam_left.m_list.count() <= 0)
    {
        return;
    }
    //============

    m_itemWidth = m_chartRect.height() / m_axisParam_left.m_list.count() * m_itemWidthRatio;
    m_itemGapWidth = m_chartRect.height() / m_axisParam_left.m_list.count() - m_itemWidth;

//    double height = m_itemWidth - m_itemGapWidth;
    double posY = m_chartRect.bottom() - m_itemGapWidth / 2 - m_itemWidth;
    for(int i = 0; i < m_dataList.count(); ++i)
    {
//        QPair<double,QColor> tempPair = m_dataList.at(i);
        QColor color = m_colorList.at(i);
        double value = m_dataList.at(i);
        double width = (value - m_rangeX.first) / (m_rangeX.second - m_rangeX.first) * m_chartRect.width();
        QRectF rect(m_chartRect.left(),posY,width,m_itemWidth);
        {
            QGraphicsRectItem *item = new QGraphicsRectItem(rect,this);
            QLinearGradient bgGradient(rect.topLeft(),rect.bottomLeft());
            bgGradient.setColorAt(0.0,color);
            bgGradient.setColorAt(0.15,color.light(125));
            bgGradient.setColorAt(0.85,color.light(125));
            bgGradient.setColorAt(1.0,color);
            item->setBrush(bgGradient);
        }
        {
            QGraphicsTextItem *item = new QGraphicsTextItem(QString::number(value),this);
            item->setFont(m_valueFont);
            item->setDefaultTextColor(m_valueColor);
            item->setPos(rect.right(),posY + 0.5 * (m_itemWidth - item->boundingRect().height()));
        }
        posY -= m_itemWidth + m_itemGapWidth;
    }
}

bool PSV_ChartBarItem::setChartValue(const QList<QString> &keys
                                     , const QList<double> &values
                                     , const QList<QColor> &colorList)
{
    if(keys.count() <= 1 || values.count() != keys.count())
    {
        return false;
    }
    m_dataList.clear();
    m_colorList.clear();
    m_axisParam_left.m_list.clear();
    int count = keys.count();
    double min = 0.0;
    double max = 0.0;
    for(int i = 0; i < count; ++i)
    {
        double value = values.at(i);
        if(i == 0)
        {
            min = value;
            max = value;
        }
        else
        {
            if(min > value)
            {
                min = value;
            }
            if(max < value)
            {
                max = value;
            }
        }
        QColor color = PSV_Public::getHistogramColor(i,colorList,m_isSameColor,m_sameColor);
//        m_dataList.append(QPair<double,QColor>(value,color));
        m_dataList.append(value);
        m_colorList.append(color);
        m_axisParam_left.m_list.append(keys.at(i));
    }
    m_min_x = min;
    m_max_x = max;
    refreshItem();
    return true;
}

bool PSV_ChartBarItem::setChartValue(const QMap<QString, double> &dataMap)
{
    int count = dataMap.count();
    if(count <= 1)
    {
        return false;
    }
    double min = 0.0;
    double max = 0.0;
    int index = 0;
    m_dataList.clear();
    m_colorList.clear();
    m_axisParam_left.m_list.clear();
    QMapIterator<QString,double> iter(dataMap);
    while(iter.hasNext())
    {
        iter.next();
        double value = iter.value();
        if(index == 0)
        {
            min = value;
            max = value;
        }
        else
        {
            if(min > value)
            {
                min = value;
            }
            if(max < value)
            {
                max = value;
            }
        }
        QColor color = PSV_Public::getHistogramColor(index,QList<QColor>(),m_isSameColor,m_sameColor);

        m_dataList.append(value);
        m_colorList.append(color);
        m_axisParam_left.m_list.append(iter.key());
        ++index;
    }
    return true;
}
