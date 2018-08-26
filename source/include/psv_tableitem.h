#ifndef PSV_TABLEITEM_H
#define PSV_TABLEITEM_H
#include <QGraphicsItemGroup>
#include "psv_item.h"

/*!
  \class PSV_TableItem
  \brief ¶þÎ¬±í
  \author miaozhengwei QQ£º393758926
  \version 1.0.1
  \date 2014-03-10 ÐÞ¸Ä
*/
class PSVLIB_API PSV_TableItem : public PSV_Item
{
public:
    PSV_TableItem(const QMap<int, QVariant> &param, QGraphicsItem * parent = 0 );
    ~PSV_TableItem();
    virtual int type () const;
    bool setTableData(const QMap<QString, QStringList> &dataMap);
    void setDataColor(const QMap<QString, QColor> &dataColor);
    void setDataColor(const QString &colName,const QColor &colColor);
    void setTableTile(const QString& title);

protected:
    void initVariables(/*const QMap<PSV::PARAM_EKY, QVariant> &param*/);
    void updateItem();
    void updateTitle();
    virtual void setItemNull();

private:
    int m_maxRow;

//    QRectF m_rect;
    qreal m_lineWidth;

    QString m_titleText;

    QColor m_lineColor;
    QColor m_titleColor;
//    QColor m_defautColor;
    QGraphicsTextItem *m_titleItem;
    QFont m_titleFont;
    QFont m_defautFont;
    QMap<QString, QStringList> m_data;
    QMap<QString, QColor> m_dataColor;
    QMap<QString, QColor> m_vHeaderColor;
    QMap<QString, QFont> m_dataFont;
    QMap<QString, QFont> m_vHeaderFont;
    QMap<QString, QString> m_dataMaxLenght;
};

#endif // PSV_TABLEITEM_H
