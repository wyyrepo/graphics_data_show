#ifndef PSV_PUBLIC_H
#define PSV_PUBLIC_H
#include <Qt>
#include <QVariant>
#include <QDateTime>
#include <QColor>
#include "psvlib.h"

#define PSV_ZEOR 1.0E-16
#define PSV_PI 3.1415926
#define PSV_PROPERTY "PSV_ROLE"
#define PSV_NOUSED(var) (void)var

const QDateTime PSV_BEGIN_DATETIME = QDateTime(QDate(1990,1,1),QTime(0,0,0));

class QColor;
namespace PSV
{
enum DATA_STRUCT{
    realNumber = 3001, 
    positiveNumber, 
    negativeNumber
};

enum ITEM_TYPE{
    psvItem = Qt::UserRole + 1//父对象
    , axisItem//父类
    , axisUpItem
    , axisDownItem
    , axisLeftItem
    , axisRightItem
    , axisListItem
    , crcularIndicatorItem
    , cuboidItem
    , histogramItem
    , tableItem
    , sectorItem
    , chartItem//父类
    , chartTimeItem
    , chartDateTimeItem
    , chartRealItem
    , chartHistogramItem
    , chartAreaItem
    , painterPathItem
    , chartBarItem
    , verticalIndicatorItem
    , treeItem
    , levelItem
    , buttonItem
    , ellipseItem
    , staLabelItem
};

enum ATTRIBUTE_ROLE{
    //========================int
   lineWidth = 1001
    , margin
    , margin_up
    , margin_down
    , margin_left
    , margin_right
    , obliqueAngle//斜角
    , cosLength//余弦长度
    , markLength//标轴刻度长度
    , markWidth//标轴刻度线的宽度
    , arrowsLength//坐标轴箭头的长度
    , dimension//维数
    , decimal//精度
    , height
    , startAngle
    , angle

    //========================color
    , color
    , defaultColor
    , lineColor//
    , valueColor
    , dataColor
    , markColor//标轴刻度颜色
    , titleColor
    , vHeaderColor
    , hHeaderColor
    , sameColor
    //========================double
    , value//
    , maxValue//
    , minValue//
    , data//
    , dx
    , dy
    , dw
    , dh
    //========================font
    , font//
    , valueFont
    , staFont//
    , dataFont
    , markFont//标轴刻度font
    , titleFont
    //========================rect
    , boundingRect//
    //========================brush
    , upPhaseBrush//上面
    , sidePhaseBrush//侧面
    , frontPhaseBrush//正面
    //========================string
    , titleText
    //========================bool
    , hasArrow
    , isSameColor
    , isCuboid//是否为长方体
    , isCenter
    , isStaHidden//是否隐藏统计信息
    , isLineHidden//是否隐藏 直方图的折线
    , isValueHidden//是否隐藏 直方图的数值
    //========================
    , pieItem
    , pie3Item
    , factor//darker
    , toolTip
    , levelInfos
    , indicatorWidthRatio
};

enum ROLE_DATA_TYPE
{
    ROLE_TYPE_INT
    ,ROLE_TYPE_STRING
    ,ROLE_TYPE_COLOR
    ,ROLE_TYPE_FONT
    ,ROLE_TYPE_BOOL
    ,ROLE_TYPE_RECTF
    ,ROLE_TYPE_DOUBLE
};

enum DATA_TYPE
{
    dataDouble
    ,dataTime
};
//===================================================================
/*!< \brief 曲线显示风格枚举常量
*/
enum CURVETYPE{
    E_CURVE_LINE = 1001 /*!< 折线曲线 */
    , E_CURVE_PARELLEL /*!< 平直曲线 */
    , E_CURVE_SMOOTH /*!< 光滑曲线 */
    , E_CURVE_UNKOWN /*!< 未知类型 */
};

/*!< \brief X坐标轴数据类型枚举常量
*/
enum DATATYPE{
    E_DATATYPE_TIME = 2001 /*!< QTime */
    , E_DATATYPE_DATE /*!< QDate */
    , E_DATATYPE_DOUBLE /*!< double */
    , E_DATATYPE_STRING /*!< QString */
    , E_DATATYPE_DATETIME /*!< QDateTime */
    , E_DATATYPE_LIST /*!< QList */
    , E_DATATYPE_UNKOWN /*!< 未知类型，用于初始化 */
};

enum AXISTTYPE{
    E_AXIS_LEFT = 3001,
    E_AXIS_RIGHT,
    E_AXIS_DOWN,
    E_AXIS_UP
};
//===================================================================
struct ROLE_DATA{
    int role;
    QString name;
    int type;
};
}

class PSVLIB_API PSV_Public
{
public:
    PSV_Public();
    ~PSV_Public();
    static void printMes(const QVariant &mes,const QString &frefix = "");
    static int getNumTicks(double& max, double& min, int minimumNumTicks = 4); //获取适当的刻度数
    static QColor getColor(int index = -1);
    static QColor getHistogramColor(int index,const QList<QColor> &colorList,bool isSameColor = false,const QColor &sameColor = QColor(Qt::black));
    static void adjustRange(double &max, double &min);
    static bool getLabels(QVariant &maxValue, QVariant &minValue, QPair<double,double> &range, QList<QPair<QVariant, QString> > &labelList);
    static double getListValue(const QList<double> &valueList,const bool isStacked,bool &isNonnegative);
//    static QString getStaText(const QStringList &textList,const QFont &font,QList<QColor> colorList = QList<QColor>());
    static QString getStaText(const QStringList &textList,QList<QColor> colorList = QList<QColor>());
    static double getMaxLenght(const QRectF& rect);
    static double getMinLenght(const QRectF& rect);

    static PSV::ROLE_DATA getRoleData(int role);


protected:
    static bool getDateLabels(QDate &maxDate, QDate &minDate, QList<QPair<QVariant, QString> > &labelList);
    static bool getTimeLabels(QTime &maxTime, QTime &minTime, QList<QPair<QVariant, QString> > &labelList);
    static bool getDateTimeLabels(QDateTime &maxTime, QDateTime &minTime, QList<QPair<QVariant, QString> > &labelList);
};

#endif // PSV_PUBLIC_H
