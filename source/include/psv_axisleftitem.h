#ifndef PSV_AXISLEFTITEM_H
#define PSV_AXISLEFTITEM_H
#include "psv_axisitem.h"

/*!
  \class PSV_AxisLeftItem
  \brief ×ó×ø±êÖá
  \author miaozhengwei QQ£º393758926
  \version 1.0.1
  \date 2014-03-10 ÐÞ¸Ä
*/

class PSVLIB_API PSV_AxisLeftItem : public PSV_AxisItem
{
public:
    PSV_AxisLeftItem(const QMap<int, QVariant> &param, QGraphicsItem * parent = 0 );
    PSV_AxisLeftItem(const QMap<int, QVariant> &param,const QStringList &list, QGraphicsItem * parent = 0 );
    ~PSV_AxisLeftItem();
    virtual int type () const;

protected:
    void updateItem();
};

#endif // PSV_AXISLEFTITEM_H
