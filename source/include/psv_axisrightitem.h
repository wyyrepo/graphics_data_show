#ifndef PSV_AXISRIGHTITEM_H
#define PSV_AXISRIGHTITEM_H
#include "psv_axisitem.h"

/*!
  \class PSV_AxisRightItem
  \brief ÓÒ×ø±êÖá
  \author miaozhengwei QQ£º393758926
  \version 1.0.1
  \date 2014-03-10 ÐÞ¸Ä
*/

class PSVLIB_API PSV_AxisRightItem : public PSV_AxisItem
{
public:
    PSV_AxisRightItem(const QMap<int, QVariant> &param, QGraphicsItem * parent = 0 );
    PSV_AxisRightItem(const QMap<int, QVariant> &param,const QStringList &list, QGraphicsItem * parent = 0 );
    ~PSV_AxisRightItem();
    virtual int type () const;

protected:
    void updateItem();
};

#endif // PSV_AXISRIGHTITEM_H
