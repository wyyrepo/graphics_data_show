#include "psv_item_p.h"


PSV_Item_Private::PSV_Item_Private()
{

}

PSV_Item_Private::PSV_Item_Private(const QMap<int, QVariant> &param)
    :m_param(param)
{
    //
}

PSV_Item_Private::~PSV_Item_Private()
{

}

//QColor PSV_Item_Private::getDefaultColor(const QColor &color)
//{
//    return m_param.value(PSV::defaultColor,color).value<QColor>();
//}

//QRectF PSV_Item_Private::getBoundingRect(const QRectF &rect)
//{
//    return m_param.value(PSV::boundingRect,rect).toRectF();
//}

//int PSV_Item_Private::getMargin(int margin)
//{
//    return m_param.value(PSV::boundingRect,margin).toInt();
//}

void PSV_Item_Private::setData(int role, const QVariant &value)
{
    m_param.insert(role,value);
}

QVariant PSV_Item_Private::getData(int role, const QVariant &defaultValue)
{
    return m_param.value(role,defaultValue);
}

void PSV_Item_Private::setParam(const QMap<int, QVariant> &param)
{
    m_param = param;
}

QMap<int, QVariant> PSV_Item_Private::getParam()
{
    return m_param;
}
