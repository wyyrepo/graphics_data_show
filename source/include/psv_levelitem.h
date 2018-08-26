#ifndef PSV_LEVELITEM_H
#define PSV_LEVELITEM_H
#include "psv_item.h"

struct ITEM_STRUCT
{
    int id;
    QString text;
    QList<int> childList;
    bool isUnit;
    int unitChildCount;
};

/*!
  \class PSV_LevelItem
  \brief ²ã´ÎÍ¼
  \author miaozhengwei QQ£º393758926
  \version 1.0.1
  \date 2014-03-10 ÐÞ¸Ä
*/

class PSVLIB_API PSV_LevelItem : public PSV_Item
{
public:
    PSV_LevelItem(const QMap<int, QVariant> &param, QGraphicsItem * parent = 0);
    ~PSV_LevelItem();
    int type() const;
    bool setDataStuct(const QMap<int,ITEM_STRUCT> &dataMap);
    void unitChildCount(const ITEM_STRUCT &item,int &count);

protected:
    virtual void updateItem();
    virtual void setItemNull();
    void updateUnitChildCount(const QMap<int,ITEM_STRUCT> &dataMap);
    void paintLine(const QPointF point,const ITEM_STRUCT &item);

private:
    QMap<int,ITEM_STRUCT> m_data;
    int m_rootId;
    qreal m_dw;
    qreal m_dh;
};

#endif // PSV_LEVELITEM_H
