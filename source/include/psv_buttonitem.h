#ifndef PSV_BUTTONITEM_H
#define PSV_BUTTONITEM_H
#include "psv_item.h"

/*!
  \class PSV_ButtonItem
  \brief 圆形状态,可用于信号量的显示
  \author miaozhengwei QQ：393758926
  \version 1.0.1
  \date 2014-03-10 修改
*/
class PSVLIB_API PSV_ButtonItem : public PSV_Item
{
public:
    PSV_ButtonItem(const QMap<int, QVariant> &param, QGraphicsItem * parent = 0 );
    ~PSV_ButtonItem();
    virtual int type () const;
    void setCurrentState(int state);
    void setStateColor(int state,const QColor &color,const QString& tip = "");

private:
    void updateItem();
    virtual void setItemNull();

private:
    int m_currentState;
    QMap<int,QPair<QColor,QString> >m_dataMap;
};

#endif // PSV_BUTTONITEM_H
