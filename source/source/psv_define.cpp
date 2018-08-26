#include <QFont>
#include "psv_define.h"
#include <QDataStream>
PSV_ItemPointParam::PSV_ItemPointParam()
    : m_dx(0.1)
    , m_dy(0.1)
    , m_dw(0.8)
    , m_dh(0.8)

{
    //
}

PSV_ItemPointParam::PSV_ItemPointParam(double dx, double dy, double dw, double dh)
    : m_dx(dx)
    , m_dy(dy)
    , m_dw(dw)
    , m_dh(dh)
{

}

PSV_ItemPointParam::PSV_ItemPointParam(const PSV_ItemPointParam &ohter)
    : m_dx(ohter.m_dx)
    , m_dy(ohter.m_dy)
    , m_dw(ohter.m_dw)
    , m_dh(ohter.m_dh)
{
}

PSV_ItemPointParam::~PSV_ItemPointParam()
{
    //
}

PSV_ItemPointParam& PSV_ItemPointParam::operator =(const PSV_ItemPointParam& ohter)
{
    if(this != &ohter)
    {
        m_dx = ohter.m_dx;
        m_dy = ohter.m_dy;
        m_dw = ohter.m_dw;
        m_dh = ohter.m_dh;
    }
    return *this;
}

//===========================================
int psv_global_index = 0;

PSV_Param_Axis::PSV_Param_Axis(double max, double min, int height, Qt::Orientation orientation, const QFont &font, int graduatedBarLenth)
    : m_max(max)
    , m_min(min)
    , m_height(height)
    , m_graduatedBarLength(graduatedBarLenth)
    , m_graduatedBarwidth(1.5)
    , m_lineWidth(1.5)
    , m_orientation(orientation)
    , m_font(font)
    , m_lineColor(Qt::black)
    , m_labelColor(Qt::black)
    , m_graduatedBarColor(Qt::black)
{
    //
}

PSV_Param_Axis::PSV_Param_Axis(const PSV_Param_Axis &src)
    : m_max(src.m_max)
    , m_min(src.m_min)
    , m_height(src.m_height)
    , m_graduatedBarLength(src.m_graduatedBarLength)
    , m_graduatedBarwidth(src.m_graduatedBarwidth)
    , m_lineWidth(src.m_lineWidth)
    , m_orientation(src.m_orientation)
    , m_font(src.m_font)
    , m_lineColor(src.m_lineColor)
    , m_labelColor(src.m_labelColor)
    , m_graduatedBarColor(src.m_graduatedBarColor)
{

}

PSV_Param_Axis::~PSV_Param_Axis()
{
    //
}

PSV_Param_Axis& PSV_Param_Axis::operator =(const PSV_Param_Axis& src)
{
    if(this != &src)
    {
        m_max = src.m_max;
        m_min = src.m_min;
        m_height = src.m_height;
        m_graduatedBarLength = src.m_graduatedBarLength;
        m_graduatedBarwidth = src.m_graduatedBarwidth;
        m_lineWidth = src.m_lineWidth;
        m_orientation = src.m_orientation;
        m_font = src.m_font;
        m_lineColor = src.m_lineColor;
        m_labelColor = src.m_labelColor;
        m_graduatedBarColor = src.m_graduatedBarColor;
    }
    return *this;
}

//===============================================================================
PSV_CurveInfo::PSV_CurveInfo()
    : m_decimal(3)
    , m_pointSize(2)
    , m_lineWidth(2)
    , m_curveType(PSV::E_CURVE_LINE)
    , m_axisType(PSV::E_AXIS_LEFT)
    , m_dataType(PSV::E_DATATYPE_UNKOWN)
    , m_curveName(QString("default_%1").arg(psv_global_index))
    , m_staText("")
    , m_staHtmText("")
    , m_isModified(false)
    , m_isHidden(false)
    , m_pointColor(Qt::black)
    , m_lineColor(Qt::black)
{
    QColor color = PSV_Public::getColor(psv_global_index);
    m_pointColor = color;
    m_lineColor = color;
    psv_global_index++;
}

PSV_CurveInfo::PSV_CurveInfo(const QString &curveName)
    : m_decimal(3)
    , m_pointSize(2)
    , m_lineWidth(2)
    , m_curveType(PSV::E_CURVE_LINE)
    , m_axisType(PSV::E_AXIS_LEFT)
    , m_dataType(PSV::E_DATATYPE_UNKOWN)
    , m_curveName(curveName)
    , m_staText("")
    , m_staHtmText("")
    , m_isModified(false)
    , m_isHidden(false)
    , m_pointColor(Qt::black)
    , m_lineColor(Qt::black)
{
    QColor color = PSV_Public::getColor(psv_global_index);
    m_pointColor = color;
    m_lineColor = color;
    psv_global_index++;
}

PSV_CurveInfo::PSV_CurveInfo(const PSV_CurveInfo &rhs)
    :m_decimal(rhs.m_decimal)
    , m_pointSize(rhs.m_pointSize)
    , m_lineWidth(rhs.m_lineWidth)
    , m_curveType(rhs.m_curveType)
    , m_axisType(rhs.m_axisType)
    , m_dataType(rhs.m_dataType)
    , m_curveName(rhs.m_curveName)
    , m_staText(rhs.m_staText)
    , m_staHtmText(rhs.m_staHtmText)
    , m_isModified(rhs.m_isModified)
    , m_isHidden(rhs.m_isHidden)
    , m_pointColor(rhs.m_pointColor)
    , m_lineColor(rhs.m_lineColor)
    , m_polygon(rhs.m_polygon)
    , m_curveDataMap(rhs.m_curveDataMap)
    , m_curveDetailDataMap(rhs.m_curveDetailDataMap)
{
    //
}

PSV_CurveInfo& PSV_CurveInfo::operator =(const PSV_CurveInfo& rhs)
{
    if( this != &rhs)
    {
        m_decimal = rhs.m_decimal;
        m_pointSize = rhs.m_pointSize;
        m_lineWidth = rhs.m_lineWidth;
        m_curveType = rhs.m_curveType;
        m_axisType = rhs.m_axisType;
        m_dataType = rhs.m_dataType;
        m_curveName = rhs.m_curveName;
        m_staText = rhs.m_staText;
        m_staHtmText = rhs.m_staHtmText;
        m_isModified = rhs.m_isModified;
        m_isHidden = rhs.m_isHidden;
        m_pointColor = rhs.m_pointColor;
        m_lineColor = rhs.m_lineColor;
        m_polygon = rhs.m_polygon;
        m_curveDataMap = rhs.m_curveDataMap;
        m_curveDetailDataMap = rhs.m_curveDetailDataMap;
    }
    return *this;
}

PSV_CurveInfo ::~PSV_CurveInfo()
{

}

PSV_CurveParam::PSV_CurveParam(PSV::CURVETYPE curveType, PSV::AXISTTYPE axisType, bool isReplace, bool isUpdate, const QString &curveName)
    : m_curveType(curveType)
    , m_axisType(axisType)
    , m_isReplace(isReplace)
    , m_isUpdate(isUpdate)
    , m_curveName(curveName)
{
    //
}

PSV_CurveParam::PSV_CurveParam(const QString &curveName)
    : m_curveType(PSV::E_CURVE_LINE)
    , m_axisType(PSV::E_AXIS_LEFT)
    , m_isReplace(false)
    , m_isUpdate(true)
    , m_curveName(curveName)
{
}

PSV_CurveParam::PSV_CurveParam(const PSV_CurveParam &rhs)
    : m_curveType(rhs.m_curveType)
    , m_axisType(rhs.m_axisType)
    , m_isReplace(rhs.m_isReplace)
    , m_isUpdate(rhs.m_isUpdate)
    , m_curveName(rhs.m_curveName)
{

}

PSV_CurveParam& PSV_CurveParam::operator =(const PSV_CurveParam& rhs)
{
    if(this != &rhs)
    {
        m_curveType = rhs.m_curveType;
        m_axisType = rhs.m_axisType;
        m_isReplace = rhs.m_isReplace;
        m_isUpdate = rhs.m_isUpdate;
        m_curveName = rhs.m_curveName;
    }
    return *this;
}

PSV_CurveParam::~PSV_CurveParam()
{
    //
}

QDataStream &operator<<(QDataStream &out,const QMap<QString,PSV_CurveInfo> &dataMap)
{
    QMapIterator<QString,PSV_CurveInfo> iter(dataMap);
    int count = dataMap.count();
    out<<count;
    while(iter.hasNext())
    {
        iter.next();
        out<<iter.value().m_axisType;
        out<<iter.value().m_curveDataMap;
        out<<iter.value().m_curveDetailDataMap;
        out<<iter.value().m_curveName;
        out<<iter.value().m_curveType;
        out<<iter.value().m_dataType;
        out<<iter.value().m_decimal;
        out<<iter.value().m_isModified;
        out<<iter.value().m_isHidden;
        out<<iter.value().m_lineColor;
        out<<iter.value().m_lineWidth;
        out<<iter.value().m_pointColor;
        out<<iter.value().m_pointSize;
    }
    return out;
}

QDataStream &operator>>(QDataStream &out,QMap<QString,PSV_CurveInfo> &dataMap)
{
    int count;
    out>>count;
    if(out.status() != QDataStream::Ok)
    {
        return out;
    }
    dataMap.clear();
    for(int i = 0; i < count; ++i)
    {
        PSV_CurveInfo curveInfo;
        out>>curveInfo.m_axisType;
        if(out.status() != QDataStream::Ok)
        {
            return out;
        }
        out>>curveInfo.m_curveDataMap;
        if(out.status() != QDataStream::Ok)
        {
            return out;
        }
        out>>curveInfo.m_curveDetailDataMap;
        if(out.status() != QDataStream::Ok)
        {
            return out;
        }
        out>>curveInfo.m_curveName;
        if(out.status() != QDataStream::Ok)
        {
            return out;
        }
        out>>curveInfo.m_curveType;
        if(out.status() != QDataStream::Ok)
        {
            return out;
        }
        out>>curveInfo.m_dataType;
        if(out.status() != QDataStream::Ok)
        {
            return out;
        }
        out>>curveInfo.m_decimal;
        if(out.status() != QDataStream::Ok)
        {
            return out;
        }
        out>>curveInfo.m_isModified;
        if(out.status() != QDataStream::Ok)
        {
            return out;
        }
        out>>curveInfo.m_isHidden;
        if(out.status() != QDataStream::Ok)
        {
            return out;
        }
        out>>curveInfo.m_lineColor;
        if(out.status() != QDataStream::Ok)
        {
            return out;
        }
        out>>curveInfo.m_lineWidth;
        if(out.status() != QDataStream::Ok)
        {
            return out;
        }
        out>>curveInfo.m_pointColor;
        if(out.status() != QDataStream::Ok)
        {
            return out;
        }
        out>>curveInfo.m_pointSize;
        if(out.status() != QDataStream::Ok)
        {
            return out;
        }
        dataMap.insert(curveInfo.m_curveName,curveInfo);
    }
    return out;
}

QDataStream &operator<<(QDataStream &out,PSV::CURVETYPE curveType)
{
    int type = 0;
    switch(curveType)
    {
    case PSV::E_CURVE_LINE:
        type = 1;
        break;
    case PSV::E_CURVE_PARELLEL:
        type = 2;
        break;
    case PSV::E_CURVE_SMOOTH:
        type = 3;
        break;
    default:
        type = 1;
        break;
    }
    out<<type;
    return out;
}

QDataStream &operator>>(QDataStream &out,PSV::CURVETYPE &curveType)
{
    int type = 0;
    out>>type;
    if(out.status() != QDataStream::Ok)
    {
        return out;
    }
    switch(type)
    {
    case 1:
        curveType = PSV::E_CURVE_LINE;
        break;
    case 2:
        curveType = PSV::E_CURVE_PARELLEL;
        break;
    case 3:
        curveType = PSV::E_CURVE_SMOOTH;
        break;
    default:
        curveType = PSV::E_CURVE_LINE;
        break;
    }
    return out;
}

QDataStream &operator<<(QDataStream &out,PSV::DATATYPE dataType)
{
    int type = 0;
    switch(dataType)
    {
    case PSV::E_DATATYPE_DATE:
        type = 1;
        break;
    case PSV::E_DATATYPE_DATETIME:
        type = 2;
        break;
    case PSV::E_DATATYPE_DOUBLE:
        type = 3;
        break;
    case PSV::E_DATATYPE_LIST:
        type = 4;
        break;
    case PSV::E_DATATYPE_STRING:
        type = 5;
        break;
    case PSV::E_DATATYPE_TIME:
        type = 6;
        break;
    default:
        type = 7;
        break;
    }
    out<<type;
    return out;
}

QDataStream &operator>>(QDataStream &out,PSV::DATATYPE &dataType)
{
    int type = 0;
    out>>type;
    if(out.status() != QDataStream::Ok)
    {
        return out;
    }
    switch(type)
    {
    case 1:
        dataType = PSV::E_DATATYPE_DATE;
        break;
    case 2:
        dataType = PSV::E_DATATYPE_DATETIME;
        break;
    case 3:
        dataType = PSV::E_DATATYPE_DOUBLE;
        break;
    case 4:
        dataType = PSV::E_DATATYPE_LIST;
        break;
    case 5:
        dataType = PSV::E_DATATYPE_STRING;
        break;
    case 6:
        dataType = PSV::E_DATATYPE_TIME;
        break;
    default:
        dataType = PSV::E_DATATYPE_UNKOWN;
        break;
    }
    return out;
}

QDataStream &operator<<(QDataStream &out,PSV::AXISTTYPE axisType)
{
    int type = 0;
    switch(axisType)
    {
    case PSV::E_AXIS_RIGHT:
        type = 1;
        break;
    default:
        type = 2;
        break;
    }
    out<<type;
    return out;
}

QDataStream &operator>>(QDataStream &out,PSV::AXISTTYPE &axisType)
{
    int type = 0;
    out>>type;
    if(out.status() != QDataStream::Ok)
    {
        return out;
    }
    switch(type)
    {
    case 1:
        axisType = PSV::E_AXIS_RIGHT;
        break;
    default:
        axisType = PSV::E_AXIS_LEFT;
        break;
    }
    return out;
}
//===========================================================
