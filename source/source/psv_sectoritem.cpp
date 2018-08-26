#include <QPen>
#include <QBrush>
#include <QPainter>
#include <QEvent>
#include <QGraphicsSceneDragDropEvent>
#include <math.h>
#include "psv_sectoritem.h"

PSV_SectorItem::PSV_SectorItem(const QMap<int, QVariant> &param, QGraphicsItem *parent)
    : PSV_Item(param,parent)
    , m_height(30)
    , m_startAngle(270)
    , m_angle(40)
    , m_color(QColor(qrand()%255, qrand()%255, qrand()%255))
    , m_factor(200)
    , m_dx(0.0)
    , m_dy(0.0)
{
    initVariables();
    updateItem();
    setAcceptHoverEvents(true);
}

PSV_SectorItem::~PSV_SectorItem()
{
    //
}

int PSV_SectorItem::type() const
{
    return PSV::sectorItem;
}

void PSV_SectorItem::initVariables(/*const QMap<PSV::PARAM_EKY, QVariant> &d->m_param*/)
{
//    if(d->m_param.contains(PSV::boundingRect))
//    {
//        m_rect = d->m_param.value(PSV::boundingRect).toRectF();
//    }
    if(d->m_param.contains(PSV::toolTip))
    {
        setToolTip(d->m_param.value(PSV::toolTip).toString());
    }
    if(d->m_param.contains(PSV::height))
    {
        m_height = d->m_param.value(PSV::height).toDouble();
    }
    if(d->m_param.contains(PSV::startAngle))
    {
        m_startAngle = d->m_param.value(PSV::startAngle).toDouble();
    }
    if(d->m_param.contains(PSV::angle))
    {
        m_angle = d->m_param.value(PSV::angle).toDouble();
    }
    if(d->m_param.contains(PSV::color))
    {
        m_color = d->m_param.value(PSV::color).value<QColor>();
    }
    if(d->m_param.contains(PSV::factor))
    {
        m_factor = d->m_param.value(PSV::factor).toInt();
    }
}

void PSV_SectorItem::updateItem()
{
    QRectF m_rect = getBoundingRect();
    QRectF rect_up(m_rect.x(), m_rect.y(), m_rect.width(), m_rect.height());
    QRectF rect_down(m_rect.x(), m_rect.y() + m_height, m_rect.width(), m_rect.height());
    while(m_startAngle > 360)
    {
        m_startAngle -= 360;
    }

    double dx_e_up = rect_up.width() * 0.5 * cos((m_startAngle + m_angle)* PSV_PI / 180);
    double dy_e_up = rect_up.height() * 0.5 * sin((m_startAngle + m_angle)* PSV_PI / 180);
    double dx_e_down = rect_down.width() * 0.5 * cos((m_startAngle + m_angle)* PSV_PI / 180);
    double dy_e_down = rect_down.height() * 0.5 * sin((m_startAngle + m_angle)* PSV_PI / 180);

    double dx_s_up = rect_up.width() * 0.5 * cos(m_startAngle * PSV_PI / 180);
    double dy_s_up = rect_up.height() * 0.5 * sin(m_startAngle * PSV_PI / 180);
    double dx_s_down = rect_down.width() * 0.5 * cos(m_startAngle * PSV_PI / 180);
    double dy_s_down = rect_down.height() * 0.5 * sin(m_startAngle * PSV_PI / 180);
    QPointF pointS_U(rect_up.center().x() + dx_s_up, rect_up.center().y() - dy_s_up);
    QPointF pointS_D(rect_down.center().x() + dx_s_down, rect_down.center().y() - dy_s_down);
    QPointF pointE_U(rect_up.center().x() + dx_e_up, rect_up.center().y() - dy_e_up);
    QPointF pointE_D(rect_down.center().x() + dx_e_down, rect_down.center().y() - dy_e_down);

    /*double*/ m_dx = 0.1 * rect_up.width() * 0.5 * cos((m_startAngle + 0.5 * m_angle)* PSV_PI / 180);
    /*double*/ m_dy = -0.1 * rect_up.height() * 0.5 * sin((m_startAngle + 0.5 * m_angle)* PSV_PI / 180);

    QPen pen(m_color.dark(m_factor));
    {
        QGraphicsEllipseItem *item = new QGraphicsEllipseItem(rect_up, this);
        item->setStartAngle((int)(m_startAngle * 16));
        item->setSpanAngle((int)(m_angle * 16));
        QBrush brush(m_color);
        item->setBrush(brush);
        item->setPen(pen);
        item->setZValue(4);
        m_painterPath.moveTo(rect_up.center());
        m_painterPath.arcTo(rect_up, m_startAngle, m_angle);
    }

    {//item2
        QGraphicsEllipseItem *item = new QGraphicsEllipseItem(rect_down, this);
        item->setStartAngle((int)(m_startAngle * 16));
        item->setSpanAngle((int)(m_angle * 16));
        QBrush brush(m_color.dark(m_factor));
        item->setBrush(brush);
        item->setPen(pen);
    }
    int zValue_s = 1;
    int zValue_e = 2;
    if((m_startAngle >= 0 && m_startAngle<= 90) || (m_startAngle >= 270 && m_startAngle<= 360))
    {
        zValue_s = 2;
        zValue_e = 1;
    }
    {//²àÃæs
        QPolygonF polygon;
        polygon.append(QPointF(pointS_U));
        polygon.append(QPointF(pointS_D));
        polygon.append(rect_down.center());
        polygon.append(rect_up.center());
        polygon.append(QPointF(pointS_U));
        QGraphicsPolygonItem *item = new QGraphicsPolygonItem(polygon, this);
        item->setBrush(QBrush(m_color.dark(m_factor)));
        item->setPen(pen);
        item->setZValue(zValue_s);
    }
    {//²àÃæe
        QPolygonF polygon;
        polygon.append(QPointF(pointE_U));
        polygon.append(QPointF(pointE_D));
        polygon.append(rect_down.center());
        polygon.append(rect_up.center());
        polygon.append(QPointF(pointE_U));

        QGraphicsPolygonItem *item = new QGraphicsPolygonItem(polygon, this);
        item->setBrush(QBrush(m_color.dark(m_factor)));
        item->setPen(pen);
        item->setZValue(zValue_e);
    }
}

void PSV_SectorItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    PSV_NOUSED(event);
    this->moveBy(m_dx, m_dy);
}

void PSV_SectorItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    PSV_NOUSED(event);
    this->moveBy(-m_dx, -m_dy);
}

void PSV_SectorItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    PSV_NOUSED(option);
    PSV_NOUSED(widget);
    painter->drawPath(m_painterPath);
}

void PSV_SectorItem::setItemNull()
{
    return;
}
