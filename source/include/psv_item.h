#ifndef PSV_ITEM_H
#define PSV_ITEM_H
#include <QGraphicsItem>
#include <QGraphicsObject>
#include "psv_public.h"
#include "psv_define.h"
#include "psv_item_p.h"

class PSV_Item_Private;

class PSVLIB_API PSV_Item : public QGraphicsObject
{
    Q_OBJECT

public:
    PSV_Item(QGraphicsItem * parent = 0 );
    PSV_Item(const QMap<int, QVariant> &param, QGraphicsItem * parent = 0 );
    ~PSV_Item();

    virtual int type ()  const = 0;
    virtual QRectF boundingRect() const;
    virtual QPainterPath shape() const;
    virtual void refreshItem();
    void beginSet();
    void endSet();
    QMap<int, QVariant> getParam();
    void setParam(const QMap<int, QVariant>& param);
    void setData(int role,const QVariant& value,bool isUpdate = false);
    QVariant  getData(int role,const QVariant& defaultValue) const;
    bool isSetable(int role);

protected:
    virtual void updateItem() = 0;
    virtual void setItemNull() = 0;
    virtual PSV_Item* getInstance()/* = 0*/;//Òª´¿Ðéº¯Êý
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    virtual void advance(int phase);
    bool clearAll();
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void showMenu();
    void showPropertyDlg();
    //===============================
    void addProperty(int role);
    QColor getDefaultColor()const;
    QRectF getBoundingRect()const ;
    int getMargin()const;
    void addDefaultParam(int role,const QVariant& v);
    void addUnsetParam(int role);
    void deleteUnsetParam(int role);

private:
    void initParam();
    void adjustPointParam();
    void refreshRect();

protected slots:
    void onShowPropertyDlg();

protected:
    bool m_isBeginSet;
    bool m_isAutoUpdate;
    bool m_isAdvancetable;
    QPainterPath m_painterPath;
    PSV_ItemPointParam m_itemPointParam;
    PSV_Item_Private *d;
};

#endif // PSV_ITEM_H
