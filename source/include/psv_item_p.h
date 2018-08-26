#ifndef PSV_ITEM_P_H
#define PSV_ITEM_P_H
#include <QString>
#include <QMap>
#include <QVariant>
#include "psv_define.h"

class PSV_Item_Private
{
protected:
    PSV_Item_Private();
    PSV_Item_Private(const QMap<int,QVariant>& param);
    ~PSV_Item_Private();

public:
//    QColor getDefaultColor(const QColor& color = QColor(Qt::black));
//    QRectF getBoundingRect(const QRectF& rect = QRectF(0,0,600,400));
//    int getMargin(int margin = 3);
    void  setData(int role,const QVariant& value);
    QVariant  getData(int role,const QVariant& defaultValue);
    void setParam(const QMap<int, QVariant>& param);
    QMap<int, QVariant> getParam();

public:
    QMap<int,QVariant> m_param;
    QList<int> m_propertyList;
    QList<int> m_unsetPropertyList;
    friend class PSV_Item;
};

#endif // PSV_ITEM_P_H
