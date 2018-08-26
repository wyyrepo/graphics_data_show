#include <QBrush>
#include <QPen>
#include "psv_chartareaitem.h"

extern int psv_global_index;

PSV_ChartAreaItem::PSV_ChartAreaItem(const QMap<int, QVariant> &param, QGraphicsItem *parent)
    : PSV_ChartItem(param,parent)
    , m_dataCount(0)
{
    //==============================
    m_axisParam_left.m_isShow = true;
    m_axisParam_down.m_isShow = true;
//    m_axisParam_up.m_isShow = true;
//    m_axisParam_right.m_isShow = true;
    createAxisi();
    psv_global_index = 3;
    addUnsetParam(PSV::isStaHidden);
}

PSV_ChartAreaItem::~PSV_ChartAreaItem()
{
    //
}

//
int PSV_ChartAreaItem::type() const
{
    return PSV::chartAreaItem;
}

PSV::DATATYPE PSV_ChartAreaItem::dataType()
{
    return PSV::E_DATATYPE_LIST;
}

void PSV_ChartAreaItem::setPrivateItemNull()
{
    return;
}

void PSV_ChartAreaItem::afterUpdateItem()
{
    int count = m_dataListPair.count();
    for(int i = 0; i < m_dataCount; ++i)
    {
        PSV_CurveInfo curveInfo;
        QMap<double, double> curveDataMap;
        for(int j = 0; j < count; ++j)
        {
            QPair<QString, QList<double> > pairData = m_dataListPair.at(j);
            QList<double> doubleList = pairData.second;
            curveDataMap.insert(j,doubleList.at(i));
        }
        QColor color;
        if(m_colorList.count() - 1 < i)
        {
            color = PSV_Public::getHistogramColor(i,m_colorList);
            m_colorList.append(color);
        }
        else
        {
            color = m_colorList.at(i);
        }
        curveInfo.m_curveDataMap = curveDataMap;
        curveInfo.m_pointColor = QColor(Qt::white).light();
//        curveInfo.m_lineColor;
        curveInfo.m_lineColor = color;
        addCurveItem(curveInfo);
        addEllipseItem(curveInfo);
        ///==============
        color.setAlpha(160);
        QGraphicsPolygonItem *item = new QGraphicsPolygonItem(curveInfo.m_polygon,this);
        item->setBrush(QBrush(color));
        item->setZValue(m_curveZValue-2);
//        item->setPen(QPen(QColor(Qt::green)));
        item->setPen(QPen(Qt::NoPen));
    }
}

//PSV_Item* PSV_ChartAreaItem::getInstance()
//{
//    return this;
//}

bool PSV_ChartAreaItem::addCurve(const QList<QPair<QString, QList<double> > > dataList, QList<QColor> &colorList, bool isMandated)
{
    if(!isMandated && m_dataListPair.count() > 0)
    {
        return false;
    }

    QStringList tempList;
    bool isFisrt = true;
    double max = 0.0;
    double min = 0.0;
    int dataCount = -1;

    for(int i = 0; i < dataList.count(); ++i)
    {
        QPair<QString, QList<double> > dataPair = dataList.at(i);
        QList<double> valueList = dataPair.second;
        bool isnonegative = true;
        double value = PSV_Public::getListValue(valueList,false,isnonegative);
        if(!isnonegative)
        {
            return false;
        }
        tempList.append(dataPair.first);
        if(isFisrt)
        {
            max = value;
            min = value;
            isFisrt = false;
            dataCount = valueList.count();
        }
        else
        {
            if(dataCount != valueList.count())
            {
                return false;
            }
        }
        //===================
        if(max < value)
        {
            max = value;
        }
        if(min > value)
        {
            min = value;
        }
    }

    if(dataCount <= 0)
    {
        return false;
    }
    m_dataCount = dataCount;
    m_isFisrtCurve_left = false;
    m_dataListPair = dataList;
    m_colorList = colorList;
    m_axisParam_down.m_list = tempList;
    m_max_y_left = max;
    m_min_y_left = 0;
    return true;
}

QString PSV_ChartAreaItem::getToolTipText(const double /*x*/, const double y)
{
    return QObject::tr("value = %1").arg(QString::number(y,'f',decimal()));
}

//void PSV_ChartAreaItem::showPropertyDlg()
//{
//    QMap<int,QVariant> param = this->getParam();
////    PSV_ChartAreaItem* item = new PSV_ChartAreaItem(this->getParam());
//    PSV_CfgDlg_Item dlg(*this);
//    if(dlg.exec() != QDialog::Accepted)
//    {
//        this->setParam(param);
//        this->refreshItem();
//    }
//}

//==================================
