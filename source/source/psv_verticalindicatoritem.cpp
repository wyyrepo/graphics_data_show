#include <QLinearGradient>
#include <math.h>
#include "psv_verticalindicatoritem.h"

//============
#include <QPainter>

PSV_VerticalIndicatorItem::PSV_VerticalIndicatorItem(const QMap<int, QVariant> &param, QGraphicsItem *parent)
    : PSV_Item(param,parent)
    , m_isAlignLeft(true)
    , m_zValue(0)
    , m_min(0)
    , m_max(100)
    //=============QColor
    , m_valueColor(QColor(Qt::green).light())
    , m_markColor(Qt::white)
    , m_markTextColor(Qt::white)
    , m_indicatorColor(Qt::green)
    //=============qreal
    , m_currentValue(m_min)
    , m_margin_up_ratio(0.03)
    , m_margin_down_ratio(0.0)
    , m_margin_left_ratio(0.01)
    , m_margin_right_ratio(0.02)
    , m_marginVRatio(0.01)
    , m_marginHRatio(0.01)
    , m_markLength(3)
    , m_prevDy(0.0)
    , m_prevScaleY(1)
    , m_markTextWidth(0.0)
    , m_valueHeight(0.0)
    //=============pointer
    , m_upRectItem(NULL)
    , m_valueItem(NULL)
    , m_animation(NULL)
    , m_timeLine(NULL)
{
    m_markFont.setPointSize(9);
    m_valueFont.setPointSize(12);
    m_valueFont.setBold(true);
    adjustMarkTextWidth();//自动会调用adjustRect
//adjustRect();
    drawBackground();//目前不支持背景修改,默认 黑色
    drawUnderRect();
    drawMark();
//    setValue(m_currentValue);
    m_isAdvancetable = true;//根据advance自动 刷新
}

PSV_VerticalIndicatorItem::~PSV_VerticalIndicatorItem()
{
    deleteAnimation();
}

int PSV_VerticalIndicatorItem::type() const
{
    return PSV::verticalIndicatorItem;
}

void PSV_VerticalIndicatorItem::deleteAnimation()
{
    if(m_animation != NULL)
    {
        m_animation->deleteLater();
        m_animation = NULL;
    }
    if(m_timeLine != NULL)
    {
        m_timeLine->deleteLater();
        m_timeLine = NULL;
    }
}

void PSV_VerticalIndicatorItem::updateItem()
{
//    m_prevDy = 0;
//    m_prevScaleY = 1;
    m_valueFont.setPointSizeF(getBoundingRect().height() * 0.05);
    adjustMarkTextWidth();//自动会调用adjustRect
//    adjustRect();
    drawBackground();//目前不支持背景修改,默认 黑色
    drawUnderRect();
    drawMark();
}

void PSV_VerticalIndicatorItem::setItemNull()
{
    m_upRectItem = NULL;
    m_valueItem = NULL;
    deleteAnimation();
}

void PSV_VerticalIndicatorItem::adjustMarkTextWidth()
{
    QString maxLenStr;
    for(int i = m_min;i <= m_max; ++i)
    {
        if(i % 10 == 0)
        {
            if(maxLenStr.toLatin1().length() < QString::number(i).toLatin1().length())
            {
                maxLenStr = QString::number(i);
            }
        }
    }
    QGraphicsTextItem tempItem(maxLenStr);
    tempItem.setFont(m_markFont);
    m_markTextWidth = tempItem.boundingRect().width();
    tempItem.setFont(m_valueFont);
    m_valueHeight = tempItem.boundingRect().height();
    //=========================
    adjustRect();
}

void PSV_VerticalIndicatorItem::adjustRect()
{
    QRectF m_rect = getBoundingRect();
    qreal dx = 0.0;
    qreal margin_left = m_margin_left_ratio * m_rect.width();
    qreal margin_right = m_margin_right_ratio * m_rect.width();
    qreal margin_up = m_margin_up_ratio * m_rect.height();
    qreal margin_down = m_margin_down_ratio * m_rect.height() + m_valueHeight;
    if(m_isAlignLeft)
    {
        dx = m_rect.width() * m_marginHRatio + m_markLength + m_markTextWidth;
    }
    m_underRect = QRectF(m_rect.x() + margin_left + dx
                         ,m_rect.y() + margin_up
                         ,m_rect.width()-margin_left - margin_right - m_markLength - m_markTextWidth
                         ,m_rect.height() - m_marginVRatio * m_rect.height() - margin_up -margin_down);

    m_upRect = m_underRect;
    qreal markX = m_underRect.right() + m_rect.width() * m_marginHRatio;
    if(m_isAlignLeft)
    {
        markX = m_rect.x() + margin_left;
    }
    m_markRect = QRectF(markX
                        , m_underRect.y()
                        , m_markLength + m_markTextWidth
                        , m_underRect.height());
}

void PSV_VerticalIndicatorItem::setValue(const double value)
{
    if(value < m_min || value > m_max)
    {
        PSV_Public::printMes(QString("warrning:<min %1 max %2> value%3").arg(m_min).arg(m_max).arg(value));
        return;
    }
    if(m_upRectItem != NULL)
    {
        double curScale = 1 - (value - m_min) / (m_max - m_min);
        QPointF point = m_upRectItem->rect().toRect().topLeft();
//        m_upRectItem->resetTransform();
//        m_upRectItem->setPos(0,0);
        double curDy = point.y() * (1 - curScale);
        deleteAnimation();
        if(m_timeLine == NULL)
        {
            m_timeLine = new QTimeLine;
        }
        m_timeLine->setLoopCount(1);
        if(m_animation == NULL)
        {
            m_animation = new QGraphicsItemAnimation();
        }
        m_animation->setTimeLine( m_timeLine );
        int count = 10;
        int updateInterval = 40;
        int durMs = /*1.0 * */count * updateInterval;
        int duration = qMax(m_timeLine->duration(), durMs);
        if(duration > 0)
        {
            m_timeLine->setDuration( duration );
        }
        int interval = m_timeLine->updateInterval();
        m_timeLine->setFrameRange( 0, duration /  interval);
        QPointF itemPos = m_upRectItem->pos();
        m_animation->setScaleAt(0,1,m_prevScaleY);
        m_animation->setPosAt(1,QPointF(itemPos.x(),itemPos.y() - (m_prevDy - curDy)));
//        m_animation->setPosAt(1,QPointF(0,-(m_prevDy - curDy)));
        m_animation->setScaleAt(1,1,curScale);
        m_animation->setItem(m_upRectItem);
        m_timeLine->start();
        m_prevScaleY = curScale;
        m_prevDy = curDy;
    }
    adjustValueItem(value);
    m_currentValue = value;
}

void PSV_VerticalIndicatorItem::adjustValueItem(const double value)
{
    if(m_valueItem == NULL)
    {
        m_valueItem = new QGraphicsTextItem(this);
        m_valueItem->setFont(m_valueFont);
        m_valueItem->setDefaultTextColor(m_valueColor);
        m_valueItem->setZValue(m_zValue);
    }
    m_valueItem->setPlainText(QString::number(value));
    QRectF rect = m_valueItem->boundingRect();
    QPointF pos((m_underRect.left() + m_underRect.right() - rect.width()) * 0.5
                ,m_underRect.bottom()/* + m_marginVRatio * m_rect.height()*/);
    m_valueItem->setPos(pos);
    m_valueItem->update(rect);
//    m_valueItem->update(m_valueItem->boundingRect());
}

void PSV_VerticalIndicatorItem::drawBackground()
{
    QRectF m_rect = getBoundingRect();
    QLinearGradient bgGradient(QPointF(0,0),QPointF(0,m_rect.height()));
    bgGradient.setColorAt(0.0,QColor(30,30,30));
    bgGradient.setColorAt(0.1,QColor(30,30,30));
    bgGradient.setColorAt(0.9,QColor(30,30,30));
    bgGradient.setColorAt(1.0,QColor(30,30,30));
    //=============================
    QGraphicsRectItem *item = new QGraphicsRectItem(m_rect,this);
    item->setPen(Qt::NoPen);
    item->setBrush(bgGradient);
    item->setZValue(m_zValue++);
}

void PSV_VerticalIndicatorItem::drawMark()
{
    //=====================================
    qreal curY = m_markRect.bottom();
    qreal curX2 = m_markRect.left() + m_markLength;
    if(m_isAlignLeft)
    {
        curX2 = m_markRect.right() - m_markLength;
    }
    QPen pen;
    pen.setColor(m_markColor);
    pen.setWidth(1);
    {
        QGraphicsLineItem *item = new QGraphicsLineItem(curX2,m_markRect.top(),curX2,curY,this);
        item->setPen(pen);
        item->setZValue(m_zValue);
    }
    for(int i = m_min;i <= m_max; ++i)
    {
        double ratio = 0.0;
        if(i % 10 == 0)
        {
            QGraphicsTextItem *item = new QGraphicsTextItem(this);
            item->setPlainText(QString::number(i));
            item->setFont(m_markFont);
            QRectF rect = item->boundingRect();
            qreal textDx = 0.0;
            if(m_isAlignLeft)
            {
                textDx = rect.width();
            }
            item->setPos(curX2 - textDx,curY - 0.5 * rect.height());
            item->setZValue(m_zValue);
            item->setDefaultTextColor(m_markTextColor);
        }
        else if(i % 5 == 0)
        {
            ratio = 0.45;
        }
        else
        {
            ratio = 0.7;
        }
        qreal curX1 = m_markRect.left() + ratio * m_markLength;
        if(m_isAlignLeft)
        {
            curX1 = m_markRect.right() - ratio * m_markLength;
        }
        QGraphicsLineItem *item = new QGraphicsLineItem(curX1,curY,curX2,curY,this);
        item->setPen(pen);
        item->setZValue(m_zValue);
        curY -= 1.0 * m_markRect.height() / (m_max - m_min);
    }
}

void PSV_VerticalIndicatorItem::drawUnderRect()
{
    //==============
    {
//        QColor color(Qt::green);
        QLinearGradient rectGradient(m_underRect.topLeft(),m_underRect.topRight());
        rectGradient.setColorAt(0.0,m_indicatorColor);
        rectGradient.setColorAt(0.3,m_indicatorColor.dark(150));
        rectGradient.setColorAt(0.7,m_indicatorColor.dark(150));
        rectGradient.setColorAt(1.0,m_indicatorColor);
        QGraphicsRectItem *item = new QGraphicsRectItem(m_underRect,this);
        item->setPen(Qt::NoPen);
        item->setBrush(rectGradient);
        item->setZValue(m_zValue++);
    }

    {
        if(m_upRectItem == NULL)
        {
            m_upRectItem = new QGraphicsRectItem(m_upRect,this);
            m_upRectItem->resetTransform();
        }

        m_upRectItem->setPen(QPen(QColor(150,150,150)));
        QLinearGradient rectGradient(m_upRect.topLeft(),m_upRect.topRight());
        rectGradient.setColorAt(0.0,QColor(150,150,150));
        rectGradient.setColorAt(0.3,QColor(100,100,100));
        rectGradient.setColorAt(0.7,QColor(100,100,100));
        rectGradient.setColorAt(1.0,QColor(150,150,150));

        m_upRectItem->setBrush(rectGradient);
        m_upRectItem->setZValue(m_zValue++);

        double curScale = 1 - (m_currentValue - m_min) / (m_max - m_min);
        QPointF point = m_upRectItem->rect().toRect().topLeft();
        double curDy = point.y() * (1 - curScale);
        QPointF itemPoint = m_upRectItem->pos();
        QTransform matrix;
        matrix.scale(1,curScale);
        m_upRectItem->setTransform(matrix);
        m_upRectItem->setPos(QPointF(itemPoint.x(),itemPoint.y() - (0 - curDy)));
        m_prevDy = curDy;
        m_prevScaleY = curScale;

        adjustValueItem(m_currentValue);
    }
}

void PSV_VerticalIndicatorItem::setAlign(const bool isAlignLeft)
{
    m_isAlignLeft = isAlignLeft;
    if(m_isAutoUpdate)
    {
        refreshItem();
    }
}
