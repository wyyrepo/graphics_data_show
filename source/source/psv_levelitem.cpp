#include <QPen>
#include "psv_levelitem.h"

PSV_LevelItem::PSV_LevelItem(const QMap<int, QVariant> &param, QGraphicsItem *parent)
    : PSV_Item(param,parent)
    , m_rootId(-1)
{
    m_dw = 80;
    m_dh = 80;
    m_isAdvancetable = true;//根据advance自动 刷新
}

PSV_LevelItem::~PSV_LevelItem()
{
    //
}


int PSV_LevelItem::type() const
{
    return PSV::levelItem;
}

void PSV_LevelItem::setItemNull()
{
    //
}


void PSV_LevelItem::updateItem()
{
//    QGraphicsRectItem *rectItem = new QGraphicsRectItem(m_rect,this);
    QRectF m_rect = getBoundingRect();
    paintLine(QPointF(m_rect.center().x(),m_rect.top()),m_data.value(m_rootId));
}

bool PSV_LevelItem::setDataStuct(const QMap<int, ITEM_STRUCT> &dataMap)
{
    m_data = dataMap;
    updateUnitChildCount(dataMap);
    return true;
}

void PSV_LevelItem::updateUnitChildCount(const QMap<int, ITEM_STRUCT> &dataMap)
{
    QMap<int, ITEM_STRUCT> tempDataMap;
    QMapIterator<int,ITEM_STRUCT> iter(dataMap);
    int tempCount = 0;
    while(iter.hasNext())
    {
        iter.next();
        int count = 0;
        ITEM_STRUCT item = iter.value();
        unitChildCount(item,count);
        item.unitChildCount = count;
        if(tempCount < count)
        {
            m_rootId = iter.key();
            tempCount = count;
        }
//        PSV_Public::printMes(QString("id = %1,count = %2").arg(iter.key()).arg(count));
        tempDataMap.insert(iter.key(),item);
    }
    m_data = tempDataMap;
}

void PSV_LevelItem::unitChildCount(const ITEM_STRUCT &item, int &count)
{
    if(item.childList.count() <= 0)
    {
        count++;
        return;
    }
    else
    {
        foreach(int id,item.childList)
        {
            if(m_data.contains(id))
            {
                unitChildCount(m_data.value(id),count);
            }
        }
    }
}

void PSV_LevelItem::paintLine(const QPointF point, const ITEM_STRUCT &item)
{
    QLineF line(point.x() - 0.5 * item.unitChildCount * m_dw
                ,point.y()
                ,point.x() + 0.5 * item.unitChildCount * m_dw
                ,point.y());
    if(item.childList.count() > 0)
    {
        {//头
            ITEM_STRUCT tempItem = m_data.value(item.childList.at(0));

            line.setP1(QPointF(line.x1() + 0.5 * tempItem.unitChildCount * m_dw,line.y1()));
        }
        {//尾
            ITEM_STRUCT tempItem = m_data.value(item.childList.at(item.childList.count() - 1));
                line.setP2(QPointF(line.x2() - 0.5 * tempItem.unitChildCount * m_dw,line.y2()));
        }
        QGraphicsLineItem* lineItem = new QGraphicsLineItem(line,this);
        QPen pen;
        pen.setColor(QColor(Qt::red));
        lineItem->setPen(pen);
        double dx = 0.0;
        double tempY = line.y1()+m_dh;
        for(int i = 0; i < item.childList.count(); ++i)
        {
            ITEM_STRUCT tempItem = m_data.value(item.childList.at(i));
            if(i != 0)
            {
                int tempCount = 1 > tempItem.unitChildCount ? 1 : tempItem.unitChildCount;
                dx += 0.5 * tempCount * m_dw;
            }
            double tempX = line.x1() + dx;
            paintLine(QPointF(tempX,tempY),tempItem);

            QLineF tempLine(tempX,point.y(),tempX,tempY);
            QGraphicsLineItem* lineItem = new QGraphicsLineItem(tempLine,this);
            PSV_NOUSED(lineItem);

            int tempCount = 1 > tempItem.unitChildCount ? 1 : tempItem.unitChildCount;
            dx += 0.5 * tempCount * m_dw;
        }
    }
    else
    {
        QRectF rect(line.x1()+20,line.y1(),line.length()-40,2 * m_dh);
        QGraphicsRectItem *rectItem = new QGraphicsRectItem(rect,this);
        PSV_NOUSED(rectItem);
    }
}
