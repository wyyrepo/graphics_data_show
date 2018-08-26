#ifndef PSV_AXISUPITEM_H
#define PSV_AXISUPITEM_H

#include "psv_axisitem.h"

/*!
  \class PSV_AxisUpItem
  \brief ÉÏ×ø±êÖá
  \author miaozhengwei QQ£º393758926
  \version 1.0.1
  \date 2014-03-10 ÐÞ¸Ä
*/
class PSVLIB_API PSV_AxisUpItem : public PSV_AxisItem
{
public:
    PSV_AxisUpItem(const QMap<int, QVariant> &param, QGraphicsItem * parent = 0 );
    PSV_AxisUpItem(const QMap<int, QVariant> &param,const QStringList &list, QGraphicsItem * parent = 0 );
    ~PSV_AxisUpItem();
    virtual int type () const;

protected:
    void updateItem();
};

#endif // PSV_AXISUPITEM_H
