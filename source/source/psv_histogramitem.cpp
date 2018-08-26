#include <QBrush>
#include <QPen>
#include <math.h>
#include "psv_histogramitem.h"

PSV_HistogramItem::PSV_HistogramItem(const QMap<int, QVariant> &param, QGraphicsItem *parent)
    : PSV_Item(param,parent)
    , m_obliqueAngle(60)
    , m_cosLength(cos(m_obliqueAngle) * getBoundingRect().width() / 3)
    , m_dimension(3)
    , m_isCuboid(true)
    , m_color(QColor(Qt::darkCyan))
{
    initVariables();
    updateItem();
}

PSV_HistogramItem::~PSV_HistogramItem()
{
    //
}

void PSV_HistogramItem::initVariables()
{
//    if(d->m_param.contains(PSV::boundingRect))
//    {
//        m_rect = d->m_param.value(PSV::boundingRect).toRectF();
//    }
//    if(d->m_param.contains(PSV::toolTip))
//    {
        setToolTip(getData(PSV::toolTip,"").toString());
//    }
//    if(d->m_param.contains(PSV::obliqueAngle))
    {
        m_obliqueAngle = getData(PSV::obliqueAngle,60).toDouble();
    }
//    if(d->m_param.contains(PSV::cosLength))
    {
        m_cosLength = getData(PSV::cosLength,cos(m_obliqueAngle) * getBoundingRect().width() / 3).toDouble();
    }
//    if(d->m_param.contains(PSV::isCuboid))
    {
        m_isCuboid = getData(PSV::isCuboid,true).toBool();
    }
//    if(d->m_param.contains(PSV::dimension))
    {
        int tempValue = getData(PSV::dimension,3).toInt();
        if(tempValue == 2 || tempValue == 3)
        {
            m_dimension = tempValue;
        }
    }

    if(d->m_param.contains(PSV::color))
    {
        m_color = getData(PSV::color,QColor(Qt::darkCyan)).value<QColor>();
    }

    if(d->m_param.contains(PSV::upPhaseBrush))
    {
        m_upPhaseBrush = d->m_param.value(PSV::upPhaseBrush).value<QBrush>();
    }
    else
    {
        m_upPhaseBrush = QBrush(QBrush(m_color.lighter(150)));
    }

    if(d->m_param.contains(PSV::frontPhaseBrush))
    {
        m_frontPhaseBrush = d->m_param.value(PSV::frontPhaseBrush).value<QBrush>();
    }
    else
    {
        m_frontPhaseBrush = QBrush(QBrush(m_color.darker(100)));
    }
    if(d->m_param.contains(PSV::sidePhaseBrush))
    {
        m_sidePhaseBrush = d->m_param.value(PSV::sidePhaseBrush).value<QBrush>();
    }
    else
    {
        m_sidePhaseBrush = QBrush(m_color.darker(200));
    }
}

int PSV_HistogramItem::type() const
{
    return PSV::cuboidItem;
}

void PSV_HistogramItem::updateItem()
{
    QRectF m_rect = getBoundingRect();
    {
        QPolygonF polygonF_front;
        polygonF_front.append(m_rect.topLeft());
        polygonF_front.append(m_rect.topRight());
        polygonF_front.append(m_rect.bottomRight());
        polygonF_front.append(m_rect.bottomLeft());
        QGraphicsPolygonItem* item = new QGraphicsPolygonItem(this);
        item->setBrush(m_frontPhaseBrush);
        item->setPen(QPen(m_frontPhaseBrush.color()));
        item->setPolygon(polygonF_front);
    }
    double dy = tan(m_obliqueAngle / 180 * PSV_PI) * m_cosLength;
    if(m_dimension == 2)
    {
        dy = 0.0;
    }
    if(m_isCuboid)
    {
        {
            QPolygonF polygonF_side;
            polygonF_side.append(m_rect.bottomRight());
            polygonF_side.append(m_rect.topRight());
            polygonF_side.append(QPointF(m_rect.right() + m_cosLength, m_rect.top() - dy));
            polygonF_side.append(QPointF(m_rect.right() + m_cosLength, m_rect.bottom() - dy));

            QGraphicsPolygonItem* item = new QGraphicsPolygonItem(this);
            item->setBrush(m_sidePhaseBrush);
            item->setPen(QPen(m_frontPhaseBrush.color()));
            item->setPolygon(polygonF_side);
        }
        {
            QPolygonF polygonF_up;
            polygonF_up.append(m_rect.topRight());
            polygonF_up.append(m_rect.topLeft());
            polygonF_up.append(QPointF(m_rect.left()+ m_cosLength, m_rect.top() - dy));
            polygonF_up.append(QPointF(m_rect.right()+ m_cosLength, m_rect.top() - dy));

            QGraphicsPolygonItem* item = new QGraphicsPolygonItem(this);
            item->setBrush(m_upPhaseBrush);
            item->setPen(QPen(m_frontPhaseBrush.color()));
            item->setPolygon(polygonF_up);
        }
    }
    else
    {
        QRectF rectF(m_rect.x(),m_rect.y() - dy,m_rect.width(),2 * dy);
        QGraphicsEllipseItem* item = new QGraphicsEllipseItem(rectF,this);
        item->setBrush(m_upPhaseBrush);
        item->setPen(QPen(m_frontPhaseBrush.color()));
        item->setZValue(2);
    }
}

void PSV_HistogramItem::setItemNull()
{
    return;
}
