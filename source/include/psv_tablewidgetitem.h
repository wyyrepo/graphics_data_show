#ifndef PSV_TABLEWIDGETITEM_H
#define PSV_TABLEWIDGETITEM_H
#include <QGraphicsProxyWidget>
#include <QTableWidget>
#include "psv_item.h"

/*!
  \class PSV_TableWidgetItem
  \brief 基于QTableWidget的二维表
  \author miaozhengwei QQ：393758926
  \version 1.0.1
  \date 2014-03-10 修改
*/
class PSVLIB_API PSV_TableWidgetItem : public QGraphicsProxyWidget
{
public:
    PSV_TableWidgetItem();
    ~PSV_TableWidgetItem();

    void advance(int phase);

private:
    QTableWidget *m_tableWidget;
};

#endif // PSV_TABLEWIDGETITEM_H
