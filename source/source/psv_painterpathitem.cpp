#include "psv_painterpathitem.h"
#include <QPen>
#include <QColor>
#include <QGraphicsItemAnimation>
#include <QTimeLine>

PSV_PainterPathItem::PSV_PainterPathItem(const QPainterPath &painterPath, QGraphicsItem *parent)
    :PSV_Item(parent)
    ,m_startRatio(0.0001)
    ,m_updateInterval(40)
    ,m_arrowsLength(5)
    ,m_animationLength(3)
    ,m_loopCount(0)
    ,m_polygon_item(NULL)
    ,m_animation(NULL)
    ,m_timeLine(NULL)
    ,m_arrowsColor(QColor(Qt::red))
    ,m_isStart(false)
    ,m_isShowArrows(false)
{
    m_polygon = createDefautArrows(m_arrowsLength);
    m_painterPath = painterPath;
    updateItem();
//    m_isAdvancetable = true;//根据advance自动 刷新
}

PSV_PainterPathItem::~PSV_PainterPathItem()
{
    deleteAnimation();
}

int PSV_PainterPathItem::type() const
{
    return PSV::painterPathItem;
}

QRectF PSV_PainterPathItem::boundingRect() const
{
    return m_painterPath.boundingRect();
}

void PSV_PainterPathItem::setItemNull()
{
    m_polygon_item = NULL;
    deleteAnimation();
}

void PSV_PainterPathItem::deleteAnimation()
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

void PSV_PainterPathItem::startAnimation()
{
    m_isStart = true;
    if(m_timeLine != NULL)
    {
        m_timeLine->start();
    }
    else
    {
        if(m_isAutoUpdate)
        {
            refreshItem();
        }
    }
}

void PSV_PainterPathItem::stopAnimation()
{
    m_isStart = false;
    if(m_timeLine != NULL)
    {
        m_timeLine->stop();
    }
    else
    {
        if(m_isAutoUpdate)
        {
            refreshItem();
        }
    }
}

void PSV_PainterPathItem::setPath(const QPainterPath &path)
{
    m_painterPath = path;
    if(m_isAutoUpdate)
    {
        refreshItem();
    }
}

void PSV_PainterPathItem::setArrowsPolygon(const QPolygonF &polygon)
{
    m_polygon = polygon;
    if(m_isAutoUpdate)
    {
        refreshItem();
    }
}

void PSV_PainterPathItem::setArrowsColor(const QColor &color)
{
    m_arrowsColor = color;
    if(m_isAutoUpdate)
    {
        refreshItem();
    }
}

void PSV_PainterPathItem::setArrowsLength(const int length)
{
    if(m_painterPath.length() < length)
    {
        m_arrowsLength = length;
        m_polygon = createDefautArrows(m_arrowsLength);
        if(m_isAutoUpdate)
        {
            refreshItem();
        }
    }
}

void PSV_PainterPathItem::showArrows()
{
    m_isShowArrows = true;
    if(m_isAutoUpdate)
    {
        refreshItem();
    }
}

void PSV_PainterPathItem::hidArrows()
{
    m_isShowArrows = false;
    if(m_isAutoUpdate)
    {
        refreshItem();
    }
}

QPolygonF PSV_PainterPathItem::createDefautArrows(const int length)
{
    QPolygonF polygon;
    QPointF point = m_painterPath.pointAtPercent(0);
    polygon.append(point+QPointF(0,-length));
    polygon.append(point+QPointF(0,length));
    polygon.append(point+QPointF(3 * length,0));
    polygon.append(point+QPointF(0,-length));
    return polygon;
}

void PSV_PainterPathItem::updateItem()
{
    {
        QGraphicsPathItem *item = new QGraphicsPathItem(this);
        item->setPath(m_painterPath);
    }

    if(m_isShowArrows)
    {
        m_timeLine = new QTimeLine;
        m_timeLine->setLoopCount(m_loopCount);
        m_animation = getItemAnimation(m_painterPath,m_timeLine,m_animationLength,40);
        if(m_animation != NULL)
        {
            {
                QPen pen(m_arrowsColor);
                m_polygon_item = new QGraphicsPolygonItem(m_polygon,this);
                if(!m_painterPath.isEmpty())
                {
                    QLineF line(m_painterPath.pointAtPercent(0),m_painterPath.pointAtPercent(m_startRatio));
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
                    m_polygon_item->setRotation(-line.angle());
#else
                    m_polygon_item->rotate(-line.angle());
#endif
                }
                m_polygon_item->setBrush(QBrush(m_arrowsColor));
                m_polygon_item->setZValue(2);
                m_polygon_item->setPen(pen);
                m_polygon_item->setPos(m_painterPath.pointAtPercent(0));
                m_animation->setItem(m_polygon_item);
            }
            if(m_isStart)
            {
                m_timeLine->start();
            }
        }
    }
    //===========================
    {
        QGraphicsRectItem *item = new QGraphicsRectItem(getBoundingRect(),this);
        QPen pen;
        QColor color(Qt::red);
        pen.setColor(color);
        item->setPen(pen);
    }
}

QGraphicsItemAnimation* PSV_PainterPathItem::getItemAnimation(const QPainterPath &path, QTimeLine *timeLine, const int intervalLen, const int updateInterval)
{
    if( timeLine == NULL )
        return NULL;

    if( path.isEmpty() )
    {
        return NULL;
    }
    qreal length = path.length();
    if(qAbs(length) < PSV_ZEOR)
    {
        return NULL;
    }
    if(updateInterval >= 1000 || updateInterval <= 0)
    {
        return NULL;
    }
    if( intervalLen <= 0 )
        return NULL;
    int count = (int)(length / intervalLen);
    if( count <= 0 )
        return NULL;

    int durMs = /*1.0 * */(int)(length / intervalLen * updateInterval);
    if( durMs <= 0 )
        return NULL;
    int duration = qMax(timeLine->duration(), durMs);
    if(duration > 0)
    {
        timeLine->setDuration( duration );
    }
    int interval = timeLine->updateInterval();
    timeLine->setFrameRange( 0, duration /  interval);

    QGraphicsItemAnimation* animation = new QGraphicsItemAnimation();
    animation->setTimeLine( timeLine );
    QPointF previous = path.pointAtPercent(0);


    qreal preAngle = 0;
    {//0000
        QPointF point = path.pointAtPercent(m_startRatio);
        QLineF startL(previous, previous+QPointF(10,0));
        QLineF endL(previous, point);
        qreal angle = startL.angle(endL);
        if(qAbs(angle) < 0.001)
        {
            animation->setRotationAt( 0 , 0 );
        }
        else
        {
            if( point.y() > previous.y() )
                animation->setRotationAt( 0 , angle );
            else
                animation->setRotationAt( 0 , 360 - angle );
        }
        previous = point;
        animation->setPosAt(0,previous);
        preAngle = angle;
    }
    for(int i = 1; i < count; ++i)
    {
        qreal step = ( i * 1.0 ) / count;
        QPointF point = path.pointAtPercent(step);
        //        if( autoRotate )
        {
            QLineF startL(previous, previous+QPointF(10,0));
            QLineF endL(previous, point);
            qreal angle = startL.angle(endL);
            if(qAbs(angle) < 0.001)
            {
                animation->setRotationAt( step , 0 );
            }
            else
            {
                if(point.y() > previous.y())
                {
                    animation->setRotationAt( step , angle );
                    preAngle = angle;
                }
                else
                {
                    animation->setRotationAt( step , 360 - angle );
                    preAngle = angle;
                }
            }
            previous = point;
        }
        animation->setPosAt( step, point );
    }
    return animation;
}
