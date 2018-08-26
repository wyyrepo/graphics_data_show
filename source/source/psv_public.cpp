#include <QColor>
#include <QTime>
#include <QFont>
#include <QDebug>
#include <math.h>
#include <QLine>
#include <QRect>
#include "psv_public.h"

PSV_Public::PSV_Public()
{
    //
}

PSV_Public::~PSV_Public()
{
    //
}

void PSV_Public::printMes(const QVariant &mes, const QString &frefix)
{    
    QString message;
    int type = mes.type();
    switch(type)
    {
    case QVariant::Bool :
        message = mes.toBool() ? "true":"false";
        break;
    case QVariant::Color :
    {
        QColor color = mes.value<QColor>();
        message = QObject::tr("colorname:%1,r=%2,g=%3,b=%4")
                .arg(color.name())
                .arg(color.red())
                .arg(color.green())
                .arg(color.blue());
    }
        break;
    case QVariant::Date:
        message = mes.toDate().toString("yyyy-MM-dd");
        break;
    case QVariant::DateTime:
        message = mes.toDateTime().toString("yyyy-MM-dd hh:mm:ss");
        break;
    case QVariant::Double:
        message = QString::number(mes.toDouble());
        break;
    case QVariant::UInt:
    case QVariant::Int:
        message = QString::number(mes.toInt());
        break;
    case QVariant::ULongLong:
    case QVariant::LongLong:
        message = QString::number(mes.toLongLong());
        break;
    case QVariant::Line:
    {
        QLine line = mes.toLine();
        message = QObject::tr("Line x1=%1,y1=%2,x2=%3,y2=%4")
                .arg(line.x1()).arg(line.y1()).arg(line.x2()).arg(line.y2());
    }
        break;
    case QVariant::LineF:
    {
        QLineF lineF = mes.toLineF();
        message = QObject::tr("LineF x1=%1,y1=%2,x2=%3,y2=%4")
                .arg(lineF.x1()).arg(lineF.y1()).arg(lineF.x2()).arg(lineF.y2());
    }
        break;
    case QVariant::Point:
    {
        QPoint point = mes.toPoint();
        message = QObject::tr("point x=%1,y=%2")
                .arg(point.x()).arg(point.y());
    }
        break;
    case QVariant::PointF:
    {
        QPointF pointF = mes.toPointF();
        message = QObject::tr("pointF x=%1,y=%2")
                .arg(pointF.x()).arg(pointF.y());
    }
        break;
    case QVariant::Rect:
    {
        QRect rect = mes.toRect();
        message = QObject::tr("rect x=%1,y=%2,width=%3,height=%4")
                .arg(rect.x()).arg(rect.y()).arg(rect.width()).arg(rect.height());
    }
        break;
    case QVariant::RectF:
    {
        QRectF rectF = mes.toRect();
        message = QObject::tr("rectF x=%1,y=%2,width=%3,height=%4")
                .arg(rectF.x()).arg(rectF.y()).arg(rectF.width()).arg(rectF.height());
    }
        break;

    default:
        message = QObject::tr("type = %1,<%2>").arg(type).arg(mes.toString());
        break;
    }
    QString outMes = QObject::tr("%1 %2").arg(frefix).arg(message);

    qDebug()<<QObject::tr("PSV_LIB:<%1>%2").arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")).arg(outMes);
}

int  PSV_Public::getNumTicks(double& max, double& min, int minimumNumTicks)
{
    if( minimumNumTicks <= 0 )
        minimumNumTicks = 4;

    if( max <= min )
        return minimumNumTicks;

    double grossStep = (max - min) / minimumNumTicks;
    double step = pow(10.0, floor(log10(grossStep)));
    if (5 * step < grossStep)
    {
        step *= 5;
    }
    else if (2 * step < grossStep)
    {
        step *= 2;
    }
    int ticks = int(ceil(max / step) - floor(min / step));
    if (ticks < minimumNumTicks)
        ticks = minimumNumTicks;
    min = floor(min / step) * step;
    max = ceil(max / step) * step;
    return ticks;
}

QColor PSV_Public::getColor(int index)
{
    switch(index)
    {
    case 0:
        return QColor(255, 0, 0, 255);
        break;
    case 1:
        return QColor(0, 255, 0, 255);
        break;
    case 2:
        return QColor(0, 0, 255, 255);
        break;
    case 3:
        return QColor(125, 0, 0, 255);
        break;
    case 4:
        return QColor(0, 125, 0, 255);
        break;
    case 5:
        return QColor(0, 0, 123, 255);
        break;
    default:
        //        qsrand(index * QTime::currentTime().second());
        //        return QColor(qrand()%256, qrand()%256, qrand()%256);
        break;
    }
    int d1 = 11;
    int d2 = 44;
    int d3 = 77;
    int red = 210;
    int blue = 30;
    int green = 88;
    index += 15;
    if(index % 3 == 0)
    {
        return QColor((index*d1 + red) % 256,(index*d2 + blue) % 256,(index*d3 + green) % 256);
    }
    else if(index % 3 == 1)
    {
        return QColor((index*d2 + red) % 256,(index*d3 + blue) % 256,(index*d1 + green) % 256);
    }
    else
    {
        return QColor((index*d3 + red) % 256,(index*d1 + blue) % 256,(index*d2 + green) % 256);
    }
}

void PSV_Public::adjustRange(double &max, double &min)
{
    if(qAbs(max - min) < PSV_ZEOR)
    {
        if(qAbs(min) > PSV_ZEOR)
        {
            double flag = min > 0 ? 0.01 : -0.01;
            min = min - flag * min;
            max = max + flag * max;
        }
        else
        {
            min = -1;
            max = 1;
        }
        return;
    }
    if(max < min)
    {
        qSwap(max, min);
    }
}

bool PSV_Public::getDateLabels(QDate &maxDate, QDate &minDate, QList<QPair<QVariant, QString> > &labelList)
{
    labelList.clear();
    int maxNum = 31;
    int days = minDate.daysTo(maxDate);
    if(days < 0)
    {
        days = -days;
        qSwap(maxDate, minDate);
    }
    int min_year = minDate.year();
    int min_month = minDate.month();
    int max_year = maxDate.year();
    int max_month = maxDate.month();
    QDate beginDate = QDate(1970, 1, 1);
    QString dateFormat = "";
    if(days <= maxNum)
    {
        if(min_year == max_year)
        {
            dateFormat = QString::fromLocal8Bit("MM月dd日");
        }
        else
        {
            dateFormat = QString::fromLocal8Bit("yyyy年MM月dd日");
        }
        int min_days = beginDate.daysTo(minDate);
        int max_days = beginDate.daysTo(maxDate);
        if(min_days >= max_days)
        {
            max_days = max_days + 1;
            min_days = min_days - 1;
        }
        for(int i = min_days; i <= max_days; ++i)
        {
            QDate tempDate = beginDate.addDays(i);
            labelList.append(QPair<QVariant, QString>(tempDate, tempDate.toString(dateFormat)));
        }
        //        m_min_x = min_days;
        //        m_max_x = max_days;
    }
    else
    {
        int interval = 1;
        dateFormat = QString::fromLocal8Bit("yyyy年MM月");
        int years = max_year - min_year;
        if(years <= 1)
        {
            interval = 1;
        }
        else if( years <= 2)
        {
            interval = 2;
        }
        else if(years <= 3)
        {
            interval = 3;
        }
        else if(years <= 5)
        {
            interval = 6;
        }
        else
        {
            dateFormat = QString::fromLocal8Bit("yyyy年");
            interval = 12;
        }
        int tempMonth = 1;
        int beginMonth =1;
        do
        {
            beginMonth = tempMonth;
            tempMonth += interval;
        }while(tempMonth <= min_month);
        min_month = beginMonth;
        QDate minDate = QDate(min_year, min_month, 1);
        QDate maxDate = QDate(max_year, max_month, 1).addMonths(1).addDays(-1);
        QDate tempDate = minDate;
        labelList.append(QPair<QVariant, QString>(tempDate, tempDate.toString(dateFormat)));
        do
        {
            tempDate = tempDate.addMonths(interval);
            labelList.append(QPair<QVariant, QString>(tempDate, tempDate.toString(dateFormat)));
        }while(maxDate.daysTo(tempDate) <= 0);

    }
    if(labelList.count() >= 2)
    {
        minDate = labelList.at(0).first.toDate();
        maxDate = labelList.at(labelList.count() - 1).first.toDate().addDays(-1);
        return true;
    }
    return false;
}

bool PSV_Public::getTimeLabels(QTime &maxTime, QTime &minTime, QList<QPair<QVariant, QString> > &labelList)
{
    labelList.clear();
    for(int i = 0; i <= 24; ++i)
    {
        if(i != 24)
        {
            labelList.append(QPair<QVariant, QString> (QTime(i, 0, 0), QObject::tr("%1").arg(QTime(i, 0, 0).toString("hh"))));
        }
        else
        {
            labelList.append(QPair<QVariant, QString> (QTime(23, 59, 59), QObject::tr("24")));
        }
    }
    minTime = QTime(0, 0, 0);
    maxTime = QTime(23, 59, 59);
    return true;
}

bool PSV_Public::getDateTimeLabels(QDateTime &maxDateTime, QDateTime &minDateTime, QList<QPair<QVariant, QString> > &labelList)
{
    labelList.clear();
    QString dateFormat;
    int maxNum = 31;
    int days = minDateTime.daysTo(maxDateTime);
    int min_year = minDateTime.date().year();
    int min_month = minDateTime.date().month();
    int min_hour = minDateTime.time().hour();

    int max_year = maxDateTime.date().year();
    int max_month = maxDateTime.date().month();
    int max_hour = maxDateTime.time().hour();
    int hours = 24 * days + max_hour - min_hour;
    bool isDays = false;
    if(days < 2)
    {
        if(minDateTime.date() == maxDateTime.date())
        {
            dateFormat = QString::fromLocal8Bit("hh时");
            QDate tempDate = minDateTime.date();
            for(int i = 0; i < 24; ++i)
            {
                QDateTime tempDateTime = QDateTime(tempDate,QTime(i,0,0));
                labelList.append(QPair<QVariant,QString>(tempDateTime,tempDateTime.toString(dateFormat)));
            }
            QDateTime tempDateTime = QDateTime(tempDate,QTime(23,59,59));
            labelList.append(QPair<QVariant,QString>(tempDateTime,QString::fromLocal8Bit("24时")));
        }
        else
        {
            dateFormat = QString::fromLocal8Bit("MM月dd日 hh时");
            int interval = 1;
            if(hours <= 12)
            {
                interval = 1;
            }
            else
            {
                interval = 2;
            }
            int tempHour = 0;
            int beginHour = 0;
            do
            {
                beginHour = tempHour ;
                tempHour  += interval;
            }while(tempHour <= min_hour );
            min_hour = beginHour;
            QDateTime tempDateTime = QDateTime(minDateTime.date(),QTime(min_hour,0,0));
            labelList.append(QPair<QVariant,QString>(tempDateTime,tempDateTime.toString(dateFormat)));
            do
            {
                tempDateTime = tempDateTime.addSecs(3600 * interval);
                labelList.append(QPair<QVariant,QString>(tempDateTime,tempDateTime.toString(dateFormat)));
            }while(maxDateTime.secsTo(tempDateTime) <= 0);
        }
    }
    else if(days <= maxNum)
    {
        if(min_year == max_year)
        {
            dateFormat = QString::fromLocal8Bit("MM月dd日");
        }
        else
        {
            dateFormat = QString::fromLocal8Bit("yyyy年MM月dd日");
        }
        int flag = 0;
        if(QTime(0,0,0).secsTo(minDateTime.time()) > 0)
        {
            flag = -1;
        }
        int min_days = PSV_BEGIN_DATETIME.daysTo(QDateTime(minDateTime.date().addDays(flag),QTime(0,0,0)));
        flag = 0;
        if(QTime(0,0,0).secsTo(maxDateTime.time()) > 0)
        {
            flag = 1;
        }
        int max_days = PSV_BEGIN_DATETIME.daysTo(QDateTime(maxDateTime.date().addDays(flag),QTime(0,0,0)));

        if(min_days >= max_days)
        {
            max_days = max_days + 1;
            min_days = min_days - 1;
        }
        for(int i = min_days; i <= max_days; ++i)
        {
            QDateTime tempDateTime = PSV_BEGIN_DATETIME.addDays(i);
            labelList.append(QPair<QVariant,QString>(tempDateTime,tempDateTime.toString(dateFormat)));
        }
        //        m_min_x = 86400 * min_days;
        //        m_max_x = 86400 * max_days;
    }
    else
    {
        int interval = 1;
        isDays = true;
        dateFormat = QString::fromLocal8Bit("yyyy年MM月");
        int years = max_year - min_year;
        if(years <= 1)
        {
            interval = 1;
        }
        else if( years <= 2)
        {
            interval = 2;
        }
        else if(years <= 3)
        {
            interval = 3;
        }
        else if(years <= 5)
        {
            interval = 6;
        }
        else
        {
            dateFormat = QString::fromLocal8Bit("yyyy年");
            interval = 12;
        }
        int tempMonth = 1;
        int beginMonth =1;
        do
        {
            beginMonth = tempMonth;
            tempMonth += interval;
        }while(tempMonth <= min_month);
        min_month = beginMonth;
        QDate minDate = QDate(min_year,min_month,1);
        QDate maxDate = QDate(max_year,max_month,1).addMonths(1).addDays(-1);
        QDate tempDate = minDate;
        QDateTime tempDateTime = QDateTime(tempDate,QTime(0,0,0));
        labelList.append(QPair<QVariant,QString>(tempDateTime,tempDateTime.toString(dateFormat)));
        do
        {
            if(isDays)
            {
                tempDate = tempDate.addYears(1);
            }
            else
            {
                tempDate = tempDate.addMonths(interval);
            }
            tempDateTime = QDateTime(tempDate,QTime(0,0,0));
            labelList.append(QPair<QVariant,QString>(tempDateTime,tempDateTime.toString(dateFormat)));
        }while(maxDate > tempDate);
    }
    if(labelList.count() >= 2)
    {
        minDateTime = labelList.at(0).first.toDateTime();
        if(isDays)
        {
            QDateTime tempDateTime = labelList.at(labelList.count() - 1).first.toDateTime().addDays(-1);
            maxDateTime = qMax(tempDateTime,maxDateTime);
        }
        else
        {
            maxDateTime = labelList.at(labelList.count() - 1).first.toDateTime();
        }
    }
    else
    {
        //        emit somethingMessage(tr("TTTTTTTT:901"));
    }
    return true;
}

bool PSV_Public::getLabels(QVariant &maxValue, QVariant &minValue, QPair<double, double> &range, QList<QPair<QVariant, QString> > &labelList)
{
    if(maxValue.type() != minValue.type())
    {
        return false;
    }
    QVariant::Type type = maxValue.type();
    switch(type)
    {
    case QVariant::Double:
    case QVariant::Int:
    case QVariant::UInt:
    {
        double max = maxValue.toDouble();
        double min = minValue.toDouble();
        int numTick = getNumTicks(max, min);
        if(numTick <= 0)
        {
            return false;
        }
        adjustRange(max, min);
        labelList.clear();
        for(int i = 0; i <= numTick; ++i)
        {
            double value = min + 1.0 * (max - min) * i / numTick;
            QString str = QObject::tr("%1").arg(value);
            labelList.append(QPair<QVariant, QString>(value, str));
        }
        maxValue = max;
        minValue = min;
        range = QPair<double,double>(min,max);
        return true;
    }
        break;
    case QVariant::Date:
    {
        QDate maxDate = maxValue.toDate();
        QDate minDate = minValue.toDate();
        bool isOk = getDateLabels(maxDate, minDate, labelList);
        maxValue = maxDate;
        minValue = minDate;
        range = QPair<double,double>(0.0, 1.0 * minDate.daysTo(maxDate));
        return isOk;
    }
        break;
    case QVariant::Time:
    {
        QTime maxTime = maxValue.toTime();
        QTime minTime = minValue.toTime();
        bool isOk = getTimeLabels(maxTime, minTime, labelList);
        maxValue = maxTime;
        minValue = minTime;
        range = QPair<double,double>(0.0, 86400.0/*1.0 * minTime.secsTo(maxTime)*/);
        return isOk;
    }
        break;
    case QVariant::DateTime:
    {
        QDateTime maxTime = maxValue.toDateTime();
        QDateTime minTime = minValue.toDateTime();
        //        PSV_Public::printMes(maxTime,"1maxTime");
        //        PSV_Public::printMes(minTime,"1minTime");
        bool isOk = getDateTimeLabels(maxTime, minTime, labelList);
        maxValue = maxTime;
        minValue = minTime;
        //        PSV_Public::printMes(maxTime,"2maxTime");
        //        PSV_Public::printMes(minTime,"2minTime");

        range = QPair<double,double>(PSV_BEGIN_DATETIME.secsTo(minValue.toDateTime()),PSV_BEGIN_DATETIME.secsTo(maxValue.toDateTime()));
        return isOk;
    }
        break;
    default:
        break;
    }
    return false;
}

double PSV_Public::getListValue(const QList<double> &valueList,const bool isStacted, bool &isNonnegative)
{
    isNonnegative = true;
    double sum = 0.0;
    double max = 0.0;
    for(int i = 0; i < valueList.count(); ++i)
    {
        double value = valueList.at(i);
        sum += value;
        if(i == 0)
        {
            max = value;
        }
        else
        {
            if(max < value)
            {
                max = value;
            }
        }
        if(value < 0)
        {
            isNonnegative = false;
        }
    }
    if(isStacted)
    {
        return sum;
    }
    return max;
}

QString PSV_Public::getStaText(const QStringList &textList, QList<QColor> colorList)
{
    if(colorList.count() <= 0)
    {
        QColor color(Qt::black);
        colorList.append(color);
        color = QColor(Qt::red);
        colorList.append(color);
        color = QColor(Qt::green);
        colorList.append(color);
        color = QColor(Qt::blue);
        colorList.append(color);
    }
    QString staText;
    int index = 0;
    foreach(QString text,textList)
    {
        QColor color;
        if(index < colorList.count())
        {
            color = colorList.at(index);
        }
        else
        {
            color = getColor();
        }
        //        staText.append(QObject::tr("<b><font size= %1 color = %2>%3</font></b>")
        //                       .arg(font.pointSize())
        //                       .arg(color.name())
        //                       .arg(text));
        staText.append(QObject::tr("<b><font size= %1 color = %2>%3</font></b>")
                       .arg(9)
                       .arg(color.name())
                       .arg(text));
        index++;
    }
    return staText;
}

QColor PSV_Public::getHistogramColor(int index, const QList<QColor> &colorList, bool isSameColor, const QColor &sameColor)
{
    QColor color;
    if(isSameColor)
    {
        color = sameColor;
    }
    else
    {
        if(colorList.count() == 1)
        {
            color = colorList.at(0);
        }
        else if(colorList.count() > index)
        {
            color = colorList.at(index);
        }
        else
        {
            color = PSV_Public::getColor(index+10);
        }
    }
    return color;
}

double PSV_Public::getMaxLenght(const QRectF &rect)
{
    return rect.width() > rect.height() ? rect.width() : rect.height();
}

double PSV_Public::getMinLenght(const QRectF &rect)
{
    return rect.width() < rect.height() ? rect.width() : rect.height();
}

PSV::ROLE_DATA PSV_Public::getRoleData(int role)
{
    PSV::ROLE_DATA d;
    d.role = role;
    d.name = QString("undefined_role%1").arg(role);
    d.type = PSV::ROLE_TYPE_STRING;
    switch (role) {
    case PSV::titleText:
        d.name = QString::fromLocal8Bit("标题内容");
        d.type = PSV::ROLE_TYPE_STRING;
        break;
    case PSV::titleColor:
        d.name = QString::fromLocal8Bit("标题颜色");
        d.type = PSV::ROLE_TYPE_COLOR;
        break;
    case PSV::titleFont:
        d.name = QString::fromLocal8Bit("标题字体");
        d.type = PSV::ROLE_TYPE_FONT;
        break;
    case PSV::decimal:
        d.name = QString::fromLocal8Bit("数据精度");
        d.type = PSV::ROLE_TYPE_INT;
        break;
    case PSV::staFont:
        d.name = QString::fromLocal8Bit("统计字体");
        d.type = PSV::ROLE_TYPE_FONT;
        break;
    case PSV::defaultColor:
        d.name = QString::fromLocal8Bit("默认颜色");
        d.type = PSV::ROLE_TYPE_COLOR;
        break;
    case PSV::isStaHidden:
        d.name = QString::fromLocal8Bit("隐藏统计");
        d.type = PSV::ROLE_TYPE_BOOL;
        break;
    case PSV::margin:
        d.name = QString::fromLocal8Bit("MARGIN");
        d.type = PSV::ROLE_TYPE_INT;
        break;
    case PSV::boundingRect:
        d.name = QString::fromLocal8Bit("轮廓矩形");
        d.type = PSV::ROLE_TYPE_RECTF;
        break;
    case PSV::maxValue:
        d.name = QString::fromLocal8Bit("最大值");
        d.type = PSV::ROLE_TYPE_DOUBLE;
        break;
    case PSV::minValue:
        d.name = QString::fromLocal8Bit("最小值");
        d.type = PSV::ROLE_TYPE_DOUBLE;
        break;
    case PSV::isLineHidden:
        d.name = QString::fromLocal8Bit("隐藏折线");
        d.type = PSV::ROLE_TYPE_BOOL;
        break;
    case PSV::isValueHidden:
        d.name = QString::fromLocal8Bit("隐藏数值");
        d.type = PSV::ROLE_TYPE_BOOL;
        break;
    case PSV::valueFont:
        d.name = QString::fromLocal8Bit("数值字体");
        d.type = PSV::ROLE_TYPE_FONT;
        break;
    case PSV::valueColor:
        d.name = QString::fromLocal8Bit("数值颜色");
        d.type = PSV::ROLE_TYPE_COLOR;
        break;
        //    case PSV::isLineHidden:
        //        d.name = "TTTTT";
        //        d.type = PSV::ROLE_TYPE_TTTTTT;
        //        break;
        //    case PSV::isLineHidden:
        //        d.name = "TTTTT";
        //        d.type = PSV::ROLE_TYPE_TTTTTT;
        //        break;
    default:
        break;
    }
    return d;
}
