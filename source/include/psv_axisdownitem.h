/*!
  \class PSV_AxisDownItem
  \brief ÏÂ×ø±êÖá
  \author miaozhengwei QQ£º393758926
  \version 1.0.1
  \date 2014-03-10 ÐÞ¸Ä
*/

#ifndef PSV_AXISDOWNITEM_H
#define PSV_AXISDOWNITEM_H
#include "psv_axisitem.h"

class PSVLIB_API PSV_AxisDownItem : public PSV_AxisItem
{
public:
    PSV_AxisDownItem(const QMap<int, QVariant> &param, QGraphicsItem * parent = 0 );
    PSV_AxisDownItem(const QMap<int, QVariant> &param,const QStringList &list, QGraphicsItem * parent = 0 );
    ~PSV_AxisDownItem();
    virtual int type () const;

protected:
    void updateItem();
};
#endif // PSV_AXISDOWNITEM_H
