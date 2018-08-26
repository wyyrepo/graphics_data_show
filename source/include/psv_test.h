#ifndef PSV_TEST_H
#define PSV_TEST_H
#include <QApplication>
#include <QTextCodec>
//#include <QObject>
#include <math.h>
#include <QStyleOption>
//#include <QStyle>
//#include "dialog_test.h"
#include <QGraphicsItemGroup>
#include <math.h>
#include <QGraphicsView>
#include "dialog_test.h"

#define PI 3.141592653589793

QRectF createRect(const QPointF &center,qreal width,qreal height);
QGraphicsItemGroup * createSubstation(double basekV,bool isPonePlant,const QPointF& point);
bool calcLinkLinePosition(const QRectF &rectFrom
                          ,const QRectF &rectTo
                          ,double begeinHeight
                          ,bool fromPowerPlant
                          ,bool toPowerPlant
                          ,QPointF &pointFrom
                          ,QPointF &pointTo);
QGraphicsPathItem* createLine(QGraphicsItem* fromSubstation
                              , bool fromPowerPlant
                              , QGraphicsItem* toSubstation
                              , bool toPowerPlant
                              , QList<QGraphicsPathItem*>& parallelingLines);
void PSV_TEST_line(PSV_GraphicsView *view);

#endif // PSV_TEST_H
