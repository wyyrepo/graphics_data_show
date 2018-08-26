#include <qmath.h>
#include "testpublic.h"
#include <QObject>
TestPublic::TestPublic()
{
    //
}

TestPublic::~TestPublic()
{
    //
}

QMap<double,double> TestPublic::mapDoubleDouble(const int count, bool isRand)
{
    QMap<double,double> tempData;
    for(int i = 0; i < count; ++i)
    {
        double value = i;
        if(isRand)
        {
            value = qrand() % 1000;
        }
        tempData.insert(i,value);
    }
    return tempData;
}

QMap<QString,double> TestPublic::mapStringDouble(const int count, const double dx, bool isRand)
{
    QMap<QString,double> tempData;
    for(int i = 0; i < count; ++i)
    {
        double value = i;
        if(isRand)
        {
            value = 1.0 * (qrand() % 1000) / 10 - dx;
        }
        tempData.insert(QObject::tr("test_%1").arg(i),value);
    }
    return tempData;
}

QMap<QTime,double> TestPublic::mapTimeDouble(const int secs, bool isRand)
{
    QMap<QTime,double> tempData;
    if(secs <= 0)
    {
        return tempData;
    }
    int curSecs = 0;
    int index  = 1;
    while(curSecs < 86400)
    {
        double value = index;
        if(isRand)
        {
            value = 1.0 * (qrand() % 1000) / 100;
        }
        tempData.insert(QTime(0,0,0).addSecs(curSecs),value);
        curSecs += secs * (qrand() % 300 / 100.0);
    }
    return tempData;
}

QMap<QDateTime,double> TestPublic::mapDateTimeDouble(const int secs, bool isRand)
{
    QMap<QDateTime,double> tempData;
    if(secs <= 0)
    {
        return tempData;
    }
    int curSecs = 0;
    int index  = 1;
    while(curSecs < 86400)
    {
        double value = index;
        if(isRand)
        {
            value = 1.0 * (qrand() % 1000) / 100;
        }
        QDateTime dataTime = QDateTime(QDate(qrand() % 10 + 2000,qrand() % 12 + 1,qrand() % 28 + 1),QTime(0,0,0).addSecs(curSecs));
//        PSV_Public::printMes(dataTime,"dataTime");
        tempData.insert(dataTime,value);
        curSecs += secs;
    }
    return tempData;
}

QMap<QDate,double> TestPublic::mapDateDouble(const int days, bool isRand)
{
    QMap<QDate,double> tempData;
    if(days <= 0)
    {
        return tempData;
    }
    int curSecs = 0;
    int index  = 1;
    while(curSecs < 1000)
    {
        double value = index;
        if(isRand)
        {
            value = 1.0 * (qrand() % 1000) / 100;
        }
        tempData.insert(QDate::currentDate().addDays(curSecs),value);
        curSecs += days;
    }
    return tempData;
}

QMap<QString,QStringList> TestPublic::mapStringStringList(const int count, const int length, int maxValue)
{
    QMap<QString,QStringList> tempData;
    if(maxValue <= 0)
    {
        maxValue = 1000;
    }
    for(int i = 0; i < count; ++i)
    {
        QStringList list;
        for(int j = 0; j < length; ++j)
        {
            list.append(QObject::tr("%1").arg(qrand() % maxValue));
        }
        tempData.insert(QObject::tr("test_%1").arg(i),list);
    }
    return tempData;
}

QList<QPair<QString,QList<double> > > TestPublic::listPairStringListDouble(const int count, const int length, const double dx, int maxValue)
{
    QList<QPair<QString,QList<double> > > tempData;
    if(maxValue <= 0)
    {
        maxValue = 1000;
    }

    for(int i = 0; i < count; ++i)
    {
        QList<double> list;
        for(int j = 0; j < length; ++j)
        {
            list.append(qrand() % maxValue - dx);
        }
        tempData.append(QPair<QString,QList<double> >(QObject::tr("test_%1").arg(i),list));
    }
    return tempData;
}

QList<QString> TestPublic::listString(const int count, const QString &frefix)
{
    QList<QString> tempValue;
    for(int i = 0; i < count;++i)
    {
        tempValue.append(QString("%1%2").arg(frefix).arg(i));
    }
    return tempValue;
}

QList<double> TestPublic::listDoulbe(const int count, bool isRand)
{
    QList<double> tempValue;
    for(int i = 0; i < count;++i)
    {
        if(isRand)
        {
            tempValue.append(qrand() % 1000);
        }
        else
        {
            tempValue.append(i);
        }
    }
    return tempValue;
}

QList<QColor> TestPublic::listColor(const int count)
{
    QList<QColor> tempValue;
    for(int i = 0; i < count;++i)
    {
        tempValue.append(QColor(qrand() % 256,qrand() % 256,qrand() % 256));
    }
    return tempValue;
}

QMap<double,double> TestPublic::mapDoubleDoubleSin(const double begin
                                                   , const double end
                                                   , const double dx
                                                   , const double interval)
{
    QMap<double,double> tempValue;
    if(begin >= end || interval <= 0)
    {
        return tempValue;
    }
    double x = begin;
    while(x < end)
    {
        tempValue.insert(x,sin(x+dx));
        x += interval;
    }
    tempValue.insert(end,sin(end+dx));
    return tempValue;
}
