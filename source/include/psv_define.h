#ifndef PSV_DEFINE_H
#define PSV_DEFINE_H
#include <Qt>
#include <QFont>
#include <QColor>
#include <QPolygonF>
#include "psv_public.h"

class PSVLIB_API PSV_ItemPointParam
{
public:
    PSV_ItemPointParam();
    PSV_ItemPointParam(double dx,double dy,double dw,double dh);
    PSV_ItemPointParam(const PSV_ItemPointParam &ohter);
    PSV_ItemPointParam &operator=(const PSV_ItemPointParam &ohter);
    ~PSV_ItemPointParam();

public:
    double m_dx;
    double m_dy;
    double m_dw;
    double m_dh;
};

//======================================
class PSVLIB_API PSV_Param_Axis
{
public:
    PSV_Param_Axis(double max, double min, int height, Qt::Orientation orientation = Qt::Vertical, const QFont &font = QFont(), int graduatedBarLenth =  5);
    PSV_Param_Axis(const PSV_Param_Axis &src);
    PSV_Param_Axis &operator=(const PSV_Param_Axis &src);
    ~PSV_Param_Axis();

public:
    double m_max;
    double m_min;
    qreal m_height;
    qreal m_graduatedBarLength;
    qreal m_graduatedBarwidth;
    qreal m_lineWidth;
    Qt::Orientation m_orientation;
    QFont m_font;
    QColor m_lineColor;
    QColor m_labelColor;
    QColor m_graduatedBarColor;
};

//=============================================================================================

class PSVLIB_API /*PSVLIB_API*/ PSV_CurveInfo
{
public:
    PSV_CurveInfo();
    PSV_CurveInfo(const QString &curveName);
    PSV_CurveInfo(const PSV_CurveInfo &src);
    PSV_CurveInfo &operator=(const PSV_CurveInfo &src);
    ~PSV_CurveInfo();

public:
    int m_decimal;
    int m_pointSize;
    int m_lineWidth;
    //============================
    PSV::CURVETYPE m_curveType;
    PSV::AXISTTYPE m_axisType;
    PSV::DATATYPE m_dataType;
    //============================    
    QString m_curveName;
    QString m_staText;
    QString m_staHtmText;
    bool m_isModified;
    bool m_isHidden;
    QColor m_pointColor;
    QColor m_lineColor;
    QPolygonF m_polygon;

    QMap<double, double> m_curveDataMap; //存储曲线数据
    QMap<double, double> m_curveDetailDataMap; //存储曲线数据,更加密集的数据，曲线类型为：SMOOTH可用

//    PSV_CurveAttribute m_curveAttribute;
    //======================
};

class PSVLIB_API /*PSVLIB_API*/ PSV_CurveParam
{
public:
    PSV_CurveParam(PSV::CURVETYPE curveType,PSV::AXISTTYPE axisType,bool isReplace,bool isUpdate,const QString &curveName);
    PSV_CurveParam(const QString &curveName);
    PSV_CurveParam(const PSV_CurveParam &src);
    PSV_CurveParam &operator=(const PSV_CurveParam &src);
    ~PSV_CurveParam();

public:
    PSV::CURVETYPE m_curveType;
    PSV::AXISTTYPE m_axisType;
    bool m_isReplace;
    bool m_isUpdate;
    QString m_curveName;
};

//class PSVLIB_API PSV_CurveAttribute
//{
//public:
//    PSV_CurveAttribute();
//    PSV_CurveAttribute(const int pointSize,const int lineWidth,const QColor &pointColor,const QColor &lineColor);
//    PSV_CurveAttribute(const PSV_CurveAttribute &src);
//    PSV_CurveAttribute &operator=(const PSV_CurveAttribute &src);
//    ~PSV_CurveAttribute();

//public:
//    int m_pointSize;
//    int m_lineWidth;
//    QColor m_pointColor;
//    QColor m_lineColor;
//};

typedef struct lastpointinfo
{
    bool isUpdate;
    double newData;
    double curve_time;
    QString curveName;

} LASTPOINTINFO;

QDataStream &operator<<(QDataStream &out,const QMap<QString,PSV_CurveInfo> &dataMap);
QDataStream &operator>>(QDataStream &out,QMap<QString,PSV_CurveInfo> &dataMap);

QDataStream &operator<<(QDataStream &out,PSV::CURVETYPE curveType);
QDataStream &operator>>(QDataStream &out,PSV::CURVETYPE &curveType);

QDataStream &operator<<(QDataStream &out,PSV::DATATYPE dataType);
QDataStream &operator>>(QDataStream &out,PSV::DATATYPE &dataType);

QDataStream &operator<<(QDataStream &out,PSV::AXISTTYPE axisType);
QDataStream &operator>>(QDataStream &out,PSV::AXISTTYPE &axisType);

#endif // PSV_DEFINE_H
