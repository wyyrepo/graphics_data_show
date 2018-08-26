#include "psv_test.h"

#define PI 3.141592653589793

QRectF createRect(const QPointF &center,qreal width,qreal height)
{
    return QRectF(center.x() - 0.5 * width,center.y() - 0.5 * height,width,height);
}

QGraphicsItemGroup * createSubstation(double basekV,bool isPonePlant,const QPointF& point)
{

    QGraphicsItemGroup *itemGroup = new QGraphicsItemGroup;
    if(isPonePlant)
    {
        qreal height = 30;
        qreal width = 60;
        if(basekV > 100)
        {
            QRectF rect = createRect(point,width,height);
            QGraphicsRectItem *item = new QGraphicsRectItem(rect,itemGroup);
            {
                QPainterPath path(point);
                path.moveTo(point.x() - 0.5 * width,point.y());
                path.arcTo(createRect(QPointF(point.x() - 0.25 * width,point.y()),0.5 * width,height),-180,180);
                path.moveTo(point.x() + 0.5 * width,point.y());
                path.arcTo(createRect(QPointF(point.x() + 0.25 * width,point.y()),0.5 * width,height),0,180);
                QGraphicsPathItem *item = new QGraphicsPathItem(itemGroup);
                item->setPath(path);
            }
        }
        if(basekV > 200)
        {
            QRectF rect = createRect(point,width*1.2,height*1.2);
            QGraphicsRectItem *item = new QGraphicsRectItem(rect,itemGroup);
        }
        if(basekV > 480)
        {
            QRectF rect = createRect(point,width*1.5,height*1.5);
            QGraphicsRectItem *item = new QGraphicsRectItem(rect,itemGroup);
        }
    }
    else
    {
        qreal height = 60;
        qreal width = 60;
        if(basekV > 100)
        {
            QRectF rect = createRect(point,width,height);
            QGraphicsEllipseItem *item = new QGraphicsEllipseItem(rect,itemGroup);
        }
        if(basekV > 200)
        {
            QRectF rect = createRect(point,width*1.2,height*1.2);
            QGraphicsEllipseItem *item = new QGraphicsEllipseItem(rect,itemGroup);
        }
        if(basekV > 480)
        {
            QRectF rect = createRect(point,width*1.5,height*1.5);
            QGraphicsEllipseItem *item = new QGraphicsEllipseItem(rect,itemGroup);
        }
    }
    return itemGroup;
}
QPointF  intersectionPoint(const QRectF &rect,const QLineF &line,bool &isOk)
{
    QPointF point(0,0);
//    QPointF* pointF =;
    isOk = true;
    {
        QLineF rectLine(rect.bottomLeft(),rect.topLeft());
        if(rectLine.intersect(line,&point) == QLineF::BoundedIntersection)
        {
            return point;
        }
    }
    {
        QLineF rectLine(rect.topLeft(),rect.topRight());
        if(rectLine.intersect(line,&point) == QLineF::BoundedIntersection)
        {
            return point;
        }
    }
    {
        QLineF rectLine(rect.topRight(),rect.bottomRight());
        if(rectLine.intersect(line,&point) == QLineF::BoundedIntersection)
        {
            return point;
        }
    }
    {
        QLineF rectLine(rect.bottomRight(),rect.bottomLeft());
        if(rectLine.intersect(line,&point) == QLineF::BoundedIntersection)
        {
            return point;
        }
    }
    isOk = false;
    return point;
}
//QPointF getPosition(const QRectF &rectFrom
//                    , bool fromPowerPlant
//                    ,const QRectF &rectFrom
//                    , bool toPowerPlant
//                    ,qreal height,bool &isOk)
//{
//}

bool calcLinkLinePosition(const QRectF &rectFrom
                          ,const QRectF &rectTo
                          ,double begeinHeight
                          ,bool fromPowerPlant
                          ,bool toPowerPlant
                          ,QPointF &pointFrom
                          ,QPointF &pointTo)
{
    QLineF line(rectFrom.center(),rectTo.center());
    qreal angle = 0.0;
    if(qAbs(line.y1() - line.y2()) > 0.0001)
    {
        angle = line.angle();
    }
    qreal rFrom = qMin(rectFrom.width(),rectFrom.height()) / 2;
    qreal rTo = qMin(rectTo.width(),rectTo.height()) / 2;
    if(qAbs(rFrom) < 0.0001 || qAbs(rTo) < 0.0001)
    {
        return false;
    }
    qreal length = line.length();
    int flag = begeinHeight > 0 ? 1 : -1;
    printf("flag = %d\n",flag);
    if(fromPowerPlant)
    {
        QPointF p2 = line.pointAt(begeinHeight / length);
        QLineF lineFrom(line.p1(),p2);
        lineFrom.setAngle(angle + flag * 90);
        pointFrom = lineFrom.p2();
    }
    else
    {
        qreal tempCos = asin(begeinHeight / rFrom) * 180 / PI;
        qreal tempAngle =-angle - tempCos + 360;
        tempAngle = tempAngle * PI / 180;
        printf("tempAngle = %lf\n",tempAngle);
        pointFrom = QPointF(rFrom * cos(tempAngle),rFrom * sin(tempAngle)) + rectFrom.center();
    }
    if(toPowerPlant)
    {
        QLineF tempLine(line.p2(),line.p1());
        QPointF p2 = tempLine.pointAt(begeinHeight / length);
        QLineF lineFrom(tempLine.p1(),p2);
        lineFrom.setAngle(angle + flag * 90);
        pointTo = lineFrom.p2();
    }
    else
    {
        qreal tempAngle = 180 - angle + asin(begeinHeight / rTo) * 180 / PI;
        tempAngle = tempAngle * PI / 180;
        printf("tempAngle = %lf\n",tempAngle);
        pointTo = QPointF(rTo * cos(tempAngle),rTo * sin(tempAngle)) + rectTo.center();
    }

    if(fromPowerPlant)
    {
        QLineF tempLine(pointFrom,pointTo);
        bool isOk = false;
        QPointF tempPoint = intersectionPoint(rectFrom,tempLine,isOk);
        if(isOk)
        {
            pointFrom = tempPoint;
        }
        else
        {
            return false;
        }
    }

    if(toPowerPlant)
    {
        QLineF tempLine(pointFrom,pointTo);
        bool isOk = false;
        QPointF tempPoint = intersectionPoint(rectTo,tempLine,isOk);
        if(isOk)
        {
            pointTo = tempPoint;
        }
        else
        {
            return false;
        }
    }
        return true;
}

QGraphicsPathItem* createLine(QGraphicsItem* fromSubstation
                              , bool fromPowerPlant
                              , QGraphicsItem* toSubstation
                              , bool toPowerPlant
                              , QList<QGraphicsPathItem*>& parallelingLines)
{
    if(fromSubstation == NULL || toSubstation == NULL)
    {
        return NULL;
    }
    QRectF rectFrom = fromSubstation->boundingRect();
    QRectF rectTo = toSubstation->boundingRect();

    if(rectFrom.center().x() > rectTo.center().x())
    {
        qSwap(rectFrom,rectTo);
        qSwap(fromPowerPlant,toPowerPlant);
    }
    QLineF line(rectFrom.center(),rectTo.center());
    qreal angle = 0.0;
    if(qAbs(line.y1() - line.y2()) > 0.0001)
    {
        angle = line.angle();
    }
    printf("angle = %lf\n",angle);
    qreal rFrom = qMin(rectFrom.width(),rectFrom.height()) / 2;
    qreal rTo = qMin(rectTo.width(),rectTo.height()) / 2;
    if(qAbs(rFrom) < 0.0001 || qAbs(rTo) < 0.0001)
    {
        return NULL;
    }
    int count = parallelingLines.count();
    qreal halfHeight = qMin(rFrom,rTo) / (count + 1) * 0.8;
    qreal begeinHeight = count * halfHeight;
    printf("begeinHeight = %lf\n",begeinHeight);
    for(int i = 0; i < count; ++i)
    {//计算现有的交叉点
        QPointF fromPoint;//待求的交叉点
        QPointF toPoint;//待求的交叉点
        bool isOk = calcLinkLinePosition(rectFrom,rectTo,begeinHeight,fromPowerPlant,toPowerPlant,fromPoint,toPoint);
        if(!isOk)
        {
            return NULL;
        }
//        QGraphicsPathItem* pathItem = parallelingLines.at(i);
//        QPainterPath path = pathItem->path();
//        path.moveTo(fromPoint);
//        path.lineTo(toPoint);
        begeinHeight += -2 * halfHeight;
    }
    //新增的线路
    QPointF fromPoint;//新增的交叉点
    QPointF toPoint;//新增的交叉点
    bool isOk = calcLinkLinePosition(rectFrom,rectTo,begeinHeight,fromPowerPlant,toPowerPlant,fromPoint,toPoint);
    if(!isOk)
    {
        return NULL;
    }
    QGraphicsPathItem *item = new QGraphicsPathItem;
    QPainterPath path;
    path.moveTo(fromPoint);
    path.lineTo(toPoint);
    item->setPath(path);
    item->setPen(QPen(QColor(Qt::red)));//TTTTTTTTTT
    return item;
}


void PSV_TEST_line(PSV_GraphicsView* view)
{
    QList<QGraphicsPathItem*> parallelingLines;

//    PSV_GraphicsView view;
    QGraphicsScene* scene = new QGraphicsScene;
//    scene->addItem(createSubstation(551,true,QPointF(100,100)));

//    QGraphicsItem* fromItem = new QGraphicsEllipseItem(729,122,30,30);
//    QGraphicsItem* fromItem = new QGraphicsRectItem(10,10,50,50);
//    QGraphicsItem* fromItem = new QGraphicsRectItem(10,10,50,50);
//    QGraphicsItem* fromItem = new QGraphicsRectItem(503,226,45,35);
    QGraphicsItem* fromItem = new QGraphicsRectItem(729,122,30,30);
    scene->addItem(fromItem);
//    QGraphicsItem* toItem = new QGraphicsRectItem(50,60,50,50);
    QGraphicsItem* toItem = new QGraphicsEllipseItem(330,38,45,45);
    scene->addItem(toItem);
//    QGraphicsItem *item = createLine(fromItem,true,toItem,true,parallelingLines);
//    QGraphicsItem *item = createLine(fromItem,true,toItem,false,parallelingLines);
//    QGraphicsItem *item = createLine(toItem,true,fromItem,true,parallelingLines);
    QGraphicsItem *item = createLine(fromItem,true,toItem,false,parallelingLines);
//    QGraphicsItem *item = createLine(toItem,false,fromItem,false,parallelingLines);
    if(item == NULL)
    {
        printf("tqredsafadsf\n");
    }
    else
    {
        item->setZValue(1111111111);
        scene->addItem(item);
    }
    {
//        QGraphicsLineItem *item = new QGraphicsLineItem(1,1,111,111);
//        item->setFlags(QGraphicsItem::ItemStacksBehindParent);
//        scene->addItem(item);
//        QPen pen;
//        pen.setWidth(0);
//        item->setPen(pen);
//        printf("item->pen().width()<%d>\n",item->pen().width());
    }
    view->setScene(scene);
    view->setRenderHint(QPainter::Antialiasing);
    view->setDragMode(QGraphicsView::ScrollHandDrag);
//    view->show();
}
