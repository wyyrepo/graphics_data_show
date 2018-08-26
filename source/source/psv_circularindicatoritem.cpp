#include <QRadialGradient>
#include <QGraphicsEllipseItem>
#include <QGraphicsTextItem>
#include <QPen>
#include <QFont>
#include <QTime>
#include "psv_circularindicatoritem.h"

PSV_CircularIndicatorItem::PSV_CircularIndicatorItem(const QMap<int, QVariant> &param
                                                     , QGraphicsItem *parent)
    : PSV_Item(param,parent)
    , m_max(100.0)
    , m_min(0.0)
    , m_value(m_min)
    , m_indicatorWidthRatio(0.05)
    , m_innerRadiusRatio(0.875)
    , m_coverCircleRadiusRatio(0.5)
    , m_colorCircleRadiusRatio(0.625)
    , m_coverBallRadiusRatio(0.125)
    , m_numTicks(100)
    , m_currentValue(0.0)
    , m_textItem(NULL)
    , m_polygonItem(NULL)
    , m_timeLine(NULL)
    , m_animation(NULL)
{    
    if(m_timeLine == NULL)
    {
        m_timeLine = new QTimeLine(50000);
        m_timeLine->setFrameRange(0, 500);
    }
    m_markFont.setPointSize(16);
    m_valueFont.setPointSize(22);
    initVariables();
    updateItem();
    m_isAdvancetable = true;//根据advance自动 刷新
}

PSV_CircularIndicatorItem::~PSV_CircularIndicatorItem()
{
    //
}

int PSV_CircularIndicatorItem::type() const
{
    return PSV::crcularIndicatorItem;
}

void PSV_CircularIndicatorItem::initVariables(/*const QMap<PSV::PARAM_EKY, QVariant> &d->m_param.*/)
{

//    if(d->m_param.contains(PSV::boundingRect))
//    {
//        QVariant vaiant = d->m_param.value(PSV::boundingRect);
//        m_rect = vaiant.toRectF();
//    }
    if(d->m_param.contains(PSV::toolTip))
    {
        setToolTip(d->m_param.value(PSV::toolTip).toString());
    }
    if(d->m_param.contains(PSV::maxValue))
    {
        m_max = d->m_param.value(PSV::maxValue).toDouble();
    }
    if(d->m_param.contains(PSV::minValue))
    {
        m_min = d->m_param.value(PSV::minValue).toDouble();
    }
    if(d->m_param.contains(PSV::indicatorWidthRatio))
    {
        m_indicatorWidthRatio = d->m_param.value(PSV::indicatorWidthRatio).toDouble();
    }

    PSV_Public::adjustRange(m_max,m_min);

    if(d->m_param.contains(PSV::levelInfos))
    {
        QMap<QString, QVariant> temp_data = d->m_param.value(PSV::levelInfos).toMap();
        QMapIterator<QString, QVariant> iter(temp_data);
        while(iter.hasNext())
        {
            iter.next();
            m_levelInfos.insert(iter.key().toDouble(),iter.value().value<QColor>());
        }
    }
    else
    {
        m_levelInfos.insert(0.6,QColor(Qt::green));
        m_levelInfos.insert(0.8,QColor(Qt::yellow));
        m_levelInfos.insert(1,QColor(Qt::red));
    }
    QRectF m_rect = getBoundingRect();

    m_outerRadius = m_rect.width() > m_rect.height() ? m_rect.height() / 2: m_rect.width() / 2;
    //    m_innerRadius=m_outerRadius/8*7;
    //    m_coverCircleRadius=m_outerRadius/8*4;
    //    m_colorCircleRadius=m_outerRadius/8*5;
    if(d->m_param.contains(PSV::value))
    {
        m_value = d->m_param.value(PSV::value).toDouble();
    }
    if(m_value > m_max || m_value < m_min)
    {
        m_value = m_min;
    }
    m_currentValue = m_value;

    if(d->m_param.contains(PSV::font))
    {
        m_markFont = d->m_param.value(PSV::font).value<QFont>();
    }
}

void PSV_CircularIndicatorItem::updateItem()
{
    QRectF m_rect = getBoundingRect();

    m_outerRadius = PSV_Public::getMinLenght(m_rect) * 0.5;
    m_markFont.setPointSizeF(PSV_Public::getMinLenght(m_rect) * 0.03);
    m_valueFont.setPointSizeF(PSV_Public::getMinLenght(m_rect) * 0.04);
    int zValue = 0;
    drawOuterCircle(zValue++);
    drawInnerCircle(zValue++);
    drawColorPie(zValue++);
    drawCoverCircle(zValue++);
    drawMark(zValue++);
    drawIndicator(zValue++);
    drawCoverBall(zValue++);
    drawTextRect(zValue++);
    //=====================================
}

void PSV_CircularIndicatorItem::drawOuterCircle(int zValue)
{
    QRectF m_rect = getBoundingRect();

    QRadialGradient outerGradient(m_rect.center(), m_outerRadius, m_rect.center());
    outerGradient.setColorAt(0.0, QColor(200, 200, 200));
    outerGradient.setColorAt(0.9, QColor(80, 80, 80));
    outerGradient.setColorAt(0.95, QColor(180, 180, 180));
    outerGradient.setColorAt(1.0, QColor(80, 80, 80));
    //==========================
    QPen pen(Qt::NoPen);
    QGraphicsEllipseItem* item = new QGraphicsEllipseItem(this);
    item->setRect(m_rect.center().x() - m_outerRadius, m_rect.center().y() - m_outerRadius, m_outerRadius*2, m_outerRadius*2);
    item->setPen(pen);
    item->setBrush(outerGradient);
    item->setZValue(zValue);
    {//TEST

        QGraphicsRectItem *item = new QGraphicsRectItem(m_rect, this);
        item->setPen(QPen(Qt::blue));
        //        item->setPen();
    }
}

void PSV_CircularIndicatorItem::drawInnerCircle(int zValue)
{
    QRectF m_rect = getBoundingRect();

    qreal innerRadius = m_innerRadiusRatio * m_outerRadius;
    QRadialGradient innerGradient(m_rect.center(), innerRadius, m_rect.center());
    innerGradient.setColorAt(0.0, QColor(130, 130, 130));
    innerGradient.setColorAt(0.7, QColor(130, 130, 130));
    innerGradient.setColorAt(1.0, QColor(80, 80, 80));
    //==
    QPen pen(Qt::NoPen);
    QRectF rect(m_rect.center().x()-innerRadius, m_rect.center().y()-innerRadius, innerRadius*2, innerRadius*2);
    QGraphicsEllipseItem* item = new QGraphicsEllipseItem(rect, this);
    item->setPen(pen);
    item->setBrush(innerGradient);
    item->setZValue(zValue);
}

void PSV_CircularIndicatorItem::drawMark(int zValue)
{
    QRectF boundingRect = getBoundingRect();

    double colorCircleRadius = m_colorCircleRadiusRatio * m_outerRadius;
    double value= m_min;
    double dValue = (m_max - m_min) / m_numTicks;
    QString strValue;
    for(int i=0;i<=m_numTicks;i++)
    {
        QPointF topPot;
        QPointF bottomPot;

        if(i%10==0)
        {
            strValue=QObject::tr("%1").arg(value);
            bottomPot = QPointF(boundingRect.center().x(), boundingRect.center().y() - colorCircleRadius);
            topPot = QPointF(boundingRect.center().x(), boundingRect.center().y() - colorCircleRadius*1.05);
            value+=10 * dValue;
            QGraphicsTextItem* item = new QGraphicsTextItem(strValue, this);
            item->setDefaultTextColor(QColor(Qt::white));
            item->setFont(m_markFont);
            item->setZValue(zValue);
            QRectF rectF = item->boundingRect();
            QPointF movePointF = QPointF(boundingRect.center().x() - 0.5 * rectF.width()
                                         , boundingRect.center().y() - colorCircleRadius*1.05 - rectF.height());
            item->moveBy(movePointF.x(), movePointF.y());
            item->setTransform(QTransform().translate(boundingRect.center().x() - movePointF.x(), boundingRect.center().y() - movePointF.y()).rotate(270 * i / 100-135).translate(-(boundingRect.center().x() - movePointF.x()), -(boundingRect.center().y() - movePointF.y())));
        }
        else if(i%5==0)
        {
            bottomPot = QPointF(boundingRect.center().x(), boundingRect.center().y() - colorCircleRadius);
            topPot = QPointF(boundingRect.center().x(), boundingRect.center().y() - colorCircleRadius*1.03);
        }
        else
        {
            bottomPot = QPointF(boundingRect.center().x(), boundingRect.center().y() - colorCircleRadius);
            topPot = QPointF(boundingRect.center().x(), boundingRect.center().y() - colorCircleRadius*1.01);
        }
        QGraphicsLineItem* item = new QGraphicsLineItem(QLineF(topPot, bottomPot), this);
        item->setPen(QPen(Qt::white));
        item->setZValue(zValue);
        item->setTransform(QTransform().translate(boundingRect.center().x(), boundingRect.center().y()).rotate(270.0 * i / 100-135).translate(-boundingRect.center().x(), -boundingRect.center().y()));
    }
}

void PSV_CircularIndicatorItem::drawCoverBall(int zValue)
{
    QRectF m_rect = getBoundingRect();
    qreal ballRadius=m_outerRadius * m_coverBallRadiusRatio;
    QRadialGradient ballGradient(m_rect.center(), ballRadius, m_rect.center());
    ballGradient.setColorAt(0.0, QColor(140, 140, 140));
    ballGradient.setColorAt(0.7, QColor(140, 140, 140));
    ballGradient.setColorAt(1.0, QColor(60, 60, 60));
    //==================
    QRectF rect(m_rect.center().x()-ballRadius, m_rect.center().y()-ballRadius, ballRadius*2, ballRadius*2);
    QGraphicsEllipseItem* item = new QGraphicsEllipseItem(rect, this);
    item->setPen(QPen(Qt::NoPen));
    item->setBrush(ballGradient);
    item->setZValue(zValue);
}

void PSV_CircularIndicatorItem::drawTextRect(int zValue)
{
    QRectF m_rect = getBoundingRect();
    qreal rectWidth = m_coverCircleRadiusRatio * m_outerRadius / 5;
    QPointF topLeftPot(m_rect.center().x()-1.5*rectWidth, m_rect.center().y()+rectWidth*2);
    QPointF bottomRightPot(topLeftPot.x()+3*rectWidth, topLeftPot.y()+rectWidth*2);
    QRectF textRect(topLeftPot, bottomRightPot);
    qreal fontSize=textRect.height()/2;
    QFont font;
    font.setPointSizeF(fontSize);
    QString strValue;
    strValue=QString("%1").arg(m_value);
    //    {
    //        QGraphicsRectItem *item = new QGraphicsRectItem(this);
    //        item->setRect(textRect);
    //        item->setPen(QPen(Qt::NoPen));
    //        item->setOpacity(0.6);
    //        item->setBrush(QColor(0, 170, 255));
    //        item->setZValue(zValue);
    //    }
    {
        m_textItem = new QGraphicsSimpleTextItem(strValue, this);
        m_textItem->setOpacity(1);
        m_textItem->setFont(m_valueFont);
        m_textItem->setZValue(zValue);
        QPointF pointF = m_textItem->boundingRect().center();
        //        m_textItem->moveBy(textRect.center().x() - pointF.x(), textRect.center().y() - pointF.y());
        m_textItem->moveBy(m_rect.center().x() - pointF.x(), m_rect.center().y() - pointF.y());
    }
}

void PSV_CircularIndicatorItem::drawCoverCircle(int zValue)
{
    QRectF m_rect = getBoundingRect();
    double coverCircleRadius = m_coverCircleRadiusRatio * m_outerRadius;
    QRectF rect(m_rect.center().x()-coverCircleRadius, m_rect.center().y()-coverCircleRadius, coverCircleRadius*2, coverCircleRadius*2);
    QGraphicsEllipseItem* item = new QGraphicsEllipseItem(rect, this);
    item->setPen(QPen(Qt::NoPen));
    item->setBrush(QBrush(QColor(130, 130, 130)));
    item->setZValue(zValue);
}

void PSV_CircularIndicatorItem::drawColorPie(int zValue)
{
    QRectF m_rect = getBoundingRect();
    double colorCircleRadius = m_colorCircleRadiusRatio * m_outerRadius;
    QPointF topLeftPot(m_rect.center().x()-colorCircleRadius, m_rect.center().y()-colorCircleRadius);
    QPointF bottomRightPot(m_rect.center().x()+colorCircleRadius, m_rect.center().y()+colorCircleRadius);
    QRectF colorCircleRect=QRectF(topLeftPot, bottomRightPot);


    QMapIterator<double,QColor> iter(m_levelInfos);

    int startAngle = 225 * 16;
    double dValue = m_max -m_min;
    if(qAbs(dValue) < PSV_ZEOR)
    {
        dValue = 100;
        m_max = 100;
        m_min = 0;
    }
    int spanAngle = 0;
    int topAngle = 0;
    while(iter.hasNext())
    {
        iter.next();
        spanAngle = (int)(16 * 270 * iter.key()) - topAngle;
        topAngle += spanAngle;
        QGraphicsEllipseItem* item = new QGraphicsEllipseItem(this);
        item->setRect(colorCircleRect);
        item->setStartAngle(startAngle - spanAngle);
        item->setSpanAngle(spanAngle);
        item->setPen(QPen(Qt::NoPen));
        item->setBrush(QBrush(iter.value()));
        item->setZValue(zValue);
        startAngle = startAngle - spanAngle;
    }
}

void PSV_CircularIndicatorItem::drawIndicator(int zValue)
{
    QRectF m_rect = getBoundingRect();
    QPointF center(0, 0);
    QPointF topPot(center.x(), center.y() - m_colorCircleRadiusRatio * m_outerRadius/*m_coverBallRadius*/);
    QPointF bottomLeftPot(center.x() - m_outerRadius * m_indicatorWidthRatio, center.y());
    QPointF bottomRightPot(center.x() + m_outerRadius * m_indicatorWidthRatio, center.y());

    QLinearGradient indicatorGradient(topPot, bottomLeftPot);
    indicatorGradient.setColorAt(0.0, QColor(236, 187, 62));
    indicatorGradient.setColorAt(0.5, QColor(220, 147, 0));
    indicatorGradient.setColorAt(1.0, QColor(236, 187, 62));

    QPolygonF polygon;
    polygon.append(topPot);
    polygon.append(bottomLeftPot);
    polygon.append(bottomRightPot);
    //    if(m_polygonItem == NULL)
    {
        QGraphicsLineItem *item = new QGraphicsLineItem(this);
        item->setPos(m_rect.center().x(), m_rect.center().y());
        item->setZValue(zValue);
        m_polygonItem = new QGraphicsPolygonItem(item);
    }
    m_polygonItem->setPolygon(polygon);
    m_polygonItem->setPen(QPen(Qt::NoPen));
    m_polygonItem->setBrush(indicatorGradient);
    m_polygonItem->setZValue(zValue);
    qreal angle = (m_value - m_min) / (m_max - m_min) * 270 - 135;
//    PSV_Public::printMes(angle,"angle");
#if QT_VERSION > QT_VERSION_CHECK(4, 6, 0)
    m_polygonItem->setRotation(angle);
#else
    m_polygonItem->rotate((m_value - m_min) / (m_max - m_min) * 270 - 135);
#endif

}

void PSV_CircularIndicatorItem::setValue(qreal value)
{
    if(value >= m_min && value <= m_max)
    {
        m_currentValue = m_value;
        m_value = value;
//        PSV_Public::printMes(m_currentValue,"m_currentValue");
//        PSV_Public::printMes(m_value,"m_value");

        {
            //原来是垂直的90，先225 - 90 = 135到起始点，再算出对应的角度
            double flag = m_currentValue > m_value ? -1.0:1.0;
            double setpAngle = flag / 100  * 270;
            double startAngle = qAbs(m_currentValue - m_min) / (m_max - m_min) * 270 - 135;
            double endAngle = qAbs(m_value - m_min) / (m_max - m_min) * 270 - 135;
            double currentAngle = startAngle;
            int count = (int)(qAbs(startAngle - endAngle) / qAbs(setpAngle));
            if(m_timeLine != NULL)
            {
                m_timeLine->deleteLater();
            }
            m_timeLine = new QTimeLine(count * 80);
            m_timeLine->setFrameRange(0, count);
            m_timeLine->setUpdateInterval(10);
            if(m_animation != NULL)
            {
                m_animation->deleteLater();
            }
            m_animation = new QGraphicsItemAnimation;
#if QT_VERSION > QT_VERSION_CHECK(4, 6, 0)
            m_polygonItem->setRotation(0.0);
#else
#endif
            m_animation->setItem(m_polygonItem);
            m_animation->setTimeLine(m_timeLine);
            m_animation->setRotationAt(0, currentAngle);

            m_animation->setRotationAt(1, endAngle);
//            PSV_Public::printMes(currentAngle,"currentAngle");
//            PSV_Public::printMes(endAngle,"endAngle");

            m_timeLine->start();
            m_textItem->setText(QObject::tr("%1").arg(m_value));
            m_textItem->update();
            QPointF pointF = m_textItem->boundingRect().center();
            QRectF m_rect = getBoundingRect();
            m_textItem->setPos(m_rect.center().x() - pointF.x(), m_rect.center().y() - pointF.y());
        }
    }
}

void PSV_CircularIndicatorItem::setItemNull()
{
    m_textItem = NULL;
    m_polygonItem = NULL;
    return;
}
