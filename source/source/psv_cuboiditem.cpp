#include <QBrush>
#include <QPen>
#include <math.h>
#include "psv_cuboiditem.h"

PSV_CuboidItem::PSV_CuboidItem(const QRectF &rect, const QColor &color, qreal obliqueAngle, qreal cosLength, QGraphicsItem *parent)
    : QGraphicsItemGroup(parent)
    , m_rect(rect)
    , m_obliqueAngle(obliqueAngle)
    , m_cosLength(cosLength)
    , m_dimension(3)
    , m_isCuboid(true)
{
//    if(m_cosLength <= 0)
//    {
//        m_cosLength = cos(m_obliqueAngle / 180 * PSV_PI) * m_rect.width() / 3;
//    }
    m_upPhaseBrush = QBrush(QBrush(color.lighter(150)));
    m_frontPhaseBrush = QBrush(QBrush(color.darker(100)));
    m_sidePhaseBrush = QBrush(color.darker(200));
    updateItem();
}

PSV_CuboidItem::PSV_CuboidItem(const QMap<PSV::PARAM_EKY, QVariant> &param, QGraphicsItem *parent)
    : QGraphicsItemGroup(parent)
    , m_rect(0, 0, 30, 60)
    , m_obliqueAngle(60)
    , m_cosLength(cos(m_obliqueAngle) * m_rect.width() / 3)
    , m_dimension(3)
    , m_isCuboid(true)
{
    QColor color = PSV_Public::getColor();
    m_upPhaseBrush = QBrush(QBrush(color.lighter(150)));
    m_frontPhaseBrush = QBrush(QBrush(color.darker(100)));
    m_sidePhaseBrush = QBrush(color.darker(200));

    initVariables(param);
    updateItem();
}

PSV_CuboidItem::~PSV_CuboidItem()
{
    //
}

void PSV_CuboidItem::initVariables(const QMap<PSV::PARAM_EKY, QVariant> &param)
{
    if(param.contains(PSV::boundingRect))
    {
        m_rect = param.value(PSV::boundingRect).toRectF();
    }
    if(param.contains(PSV::toolTip))
    {
        setToolTip(param.value(PSV::toolTip).toString());
    }
    if(param.contains(PSV::obliqueAngle))
    {
        m_obliqueAngle = param.value(PSV::obliqueAngle).toDouble();
    }
    if(param.contains(PSV::cosLength))
    {
        m_cosLength = param.value(PSV::cosLength).toDouble();
    }
    if(param.contains(PSV::isCuboid))
    {
        m_isCuboid = param.value(PSV::isCuboid).toBool();
    }
    if(param.contains(PSV::dimension))
    {
        int tempValue = param.value(PSV::dimension).toInt();
        if(tempValue == 2 || tempValue == 3)
        {
            m_dimension = tempValue;
        }
    }

    if(param.contains(PSV::upPhaseBrush))
    {
        m_upPhaseBrush = param.value(PSV::upPhaseBrush).value<QBrush>();
    }

    if(param.contains(PSV::frontPhaseBrush))
    {
        m_frontPhaseBrush = param.value(PSV::frontPhaseBrush).value<QBrush>();
    }

    if(param.contains(PSV::sidePhaseBrush))
    {
        m_sidePhaseBrush = param.value(PSV::sidePhaseBrush).value<QBrush>();
    }

}

int PSV_CuboidItem::type() const
{
    return PSV::cuboidItem;
}

void PSV_CuboidItem::updateItem()
{
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
            //        addToGroup(item);
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
