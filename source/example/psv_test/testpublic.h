#ifndef TESTPUBLIC_H
#define TESTPUBLIC_H
#include <QMap>
#include <QTime>
#include <QDate>
#include <QDateTime>
#include <QColor>
#include <QPair>

class TestPublic
{

public:
    TestPublic();
    ~TestPublic();

    static QMap<double,double> mapDoubleDouble(const int count,bool isRand = true);
    static QMap<QString,double> mapStringDouble(const int count,const double dx,bool isRand = true);
    static QMap<QString,QStringList> mapStringStringList(const int count,const int length =  5,int maxValue = 1000);
    static QList<QPair<QString,QList<double> > > listPairStringListDouble(const int count,const int length =  5,const double dx = 0,int maxValue = 1000);

    //====================
    static QMap<QTime,double> mapTimeDouble(const int secs,bool isRand = true);
    static QMap<QDateTime,double> mapDateTimeDouble(const int secs,bool isRand = true);
    static QMap<QDate,double> mapDateDouble(const int days,bool isRand = true);
    static QList<QString> listString(const int count,const QString &frefix = "test");
    static QList<double> listDoulbe(const int count,bool isRand = true);
    static QList<QColor> listColor(const int count);
    static QMap<double,double> mapDoubleDoubleSin(const double begin,const double end,const double dx,const double interval);
};

#endif // TESTPUBLIC_H
