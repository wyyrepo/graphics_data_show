#include <QBrush>
#include <QPen>
#include <QFontMetrics>
#include<math.h>
#include "psv_pie3item.h"
#include "psv_sectoritem.h"
#include <QGraphicsSceneDragDropEvent>

PSV_Pie3Item::PSV_Pie3Item(const QMap<int, QVariant> &param, QGraphicsItem *parent)
    : PSV_Item(param,parent)
    , m_isShowLabel(true)
    , m_startAngle(90)
    , m_heigthRatio(0.2)
    , m_sum(0)
{
    initVariables();
    updateItem();
    //=======================
    QRectF m_rect = getBoundingRect();
    m_painterPath.moveTo(m_rect.center());
    m_painterPath.addRect(m_rect);
    m_isAdvancetable = true;//根据advance自动 刷新
}

PSV_Pie3Item::~PSV_Pie3Item()
{
    //
}

void PSV_Pie3Item::setItemNull()
{
    //
}

void PSV_Pie3Item::initVariables(/*const QMap<PSV::PARAM_EKY, QVariant> &d->m_param*/)
{
//    if(d->m_param.contains(PSV::boundingRect))
//    {
//        m_rect = d->m_param.value(PSV::boundingRect).toRectF();
//    }
    if(d->m_param.contains(PSV::toolTip))
    {
        setToolTip(d->m_param.value(PSV::toolTip).toString());
    }
    if(d->m_param.contains(PSV::data))
    {
        QMap<QString, QVariant> tempData = d->m_param.value(PSV::data).toMap();
        QMapIterator<QString, QVariant> iter(tempData);
        while(iter.hasNext())
        {
            iter.next();
            double value = iter.value().toDouble();
            if(value < 0)
            {
                m_data.clear();
                return;
            }
            else
            {
                m_data.insert(iter.key(), value);
                m_sum += value;
            }
        }
    }
}

int PSV_Pie3Item::type() const
{
    return PSV::pie3Item;
}


void PSV_Pie3Item::adjustChartRect()
{
    QRectF m_rect = getBoundingRect();
    if(m_isShowLabel)
    {
        QString maxLengStr;
        QMap<QString, double>::const_iterator iter = m_data.constBegin();
        while(iter != m_data.constEnd())
        {
            if(maxLengStr.toLocal8Bit().length() < iter.key().toLocal8Bit().length())
            {
                maxLengStr = iter.key();
            }
            ++iter;
        }
        QFontMetrics fontMetrics(m_labelFont);
        int width = fontMetrics.boundingRect(maxLengStr).width();
        int height = fontMetrics.boundingRect(maxLengStr).height();
        m_chartRect = QRectF(m_rect.x(),m_rect.y()
                             ,m_rect.width() - width - height,m_rect.height());
//        PSV_Public::printMes(width,"width");
    }
    else
    {
        m_chartRect = m_rect;
    }
}

void PSV_Pie3Item::updateItem()
{
    int count = m_data.count();
    if(count <= 0)
    {
        PSV_Public::printMes(QString("warring:数据个数为<%1>").arg(count),"PSV_Pie3Item");
        return;
    }
    if(m_sum <= 0)
    {
        PSV_Public::printMes(QString("warring:数据总和<%1>").arg(m_sum),"PSV_Pie3Item");
        return;
    }
    QRectF m_rect = getBoundingRect();

    m_labelFont.setPointSizeF(m_rect.width() * m_rect.height() * 0.000042);
    adjustChartRect();

    QMapIterator<QString, double> iter(m_data);
    int index = 0;
    qreal startAngle = m_startAngle;
    QMap<int, QVariant> param;
    param.insert(PSV::boundingRect, m_chartRect);
    param.insert(PSV::height, m_heigthRatio * qMin(m_chartRect.width(),m_chartRect.height()));
    param.insert(PSV::factor, 200);
    int zValue = 0;
    double dh = m_chartRect.height() / count;
    double curY = m_chartRect.top();
    while(iter.hasNext())
    {
        iter.next();
        QColor color = PSV_Public::getColor(index);
        qreal angle = iter.value() / m_sum * 360;
        param.insert(PSV::startAngle, startAngle);
        param.insert(PSV::angle, angle);
        param.insert(PSV::color, color);
        param.insert(PSV::toolTip, iter.key());

        PSV_SectorItem *item = new PSV_SectorItem(param, this);
        if((startAngle >= 0 && startAngle<= 90) || (startAngle >= 270 && startAngle<= 360))
        {
            zValue--;
        }
        else
        {
            zValue++;
        }
        item->setZValue(zValue);
        startAngle += angle;
        while(startAngle > 360)
        {
            startAngle -= 360;
        }
        if(m_isShowLabel)
        {
            QGraphicsTextItem* textItem = new QGraphicsTextItem(this);
            textItem->setDefaultTextColor(getDefaultColor());
            textItem->setPlainText(iter.key());
            textItem->setFont(m_labelFont);
            double height = textItem->boundingRect().height() * 0.8;
            QRectF rect = QRectF(m_chartRect.right() + height
                                ,curY + 0.5 * dh - 0.5 * height
                                ,height,height);
            textItem->setPos(rect.right(),rect.y() - height * 0.1);
            QGraphicsRectItem* rectItem = new QGraphicsRectItem(rect,this);
            QBrush brush(color);
            QPen pen(color);
            rectItem->setPen(pen);
            rectItem->setBrush(brush);
            curY += dh;
        }
        index++;
    }    
}

void PSV_Pie3Item::setChartData(const QMap<QString, double> &data)
{
    m_data = data;
    QMapIterator<QString, double> iter(m_data);
    m_sum = 0;
    while(iter.hasNext())
    {
        iter.next();
        double value = iter.value();
        if(value < 0)
        {
            m_data.clear();
            PSV_Public::printMes(QString("圆饼数据不能为负数<%1,%2>")
                                 .arg(iter.key())
                                 .arg(iter.value())
                                 ,"warning");
            return;
        }
        else
        {
            m_sum += value;
        }
    }
    refreshItem();
}

void PSV_Pie3Item::hideLabel()
{
    if(m_isShowLabel)
    {
        m_isShowLabel = false;
        refreshItem();
    }
}

void PSV_Pie3Item::showLabel()
{
    if(!m_isShowLabel)
    {
        m_isShowLabel = true;
        refreshItem();
    }
}
