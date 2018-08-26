#ifndef PSV_TREEITEM_H
#define PSV_TREEITEM_H
#include "psv_item.h"
#include "psv_chartitem.h"

class PSVLIB_API PSV_TreeItemData
{
public:
    PSV_TreeItemData(PSV_TreeItemData* parent = 0);
    ~PSV_TreeItemData();
    void setParent(PSV_TreeItemData* parent);
    void removeChild(PSV_TreeItemData* child);
    void setText(const QString& text);
    int leafCount();
    int level();
    qreal depth();
    qreal distance() const;
    QList<PSV_TreeItemData*> children();
    QString text();

    void setDistance(qreal distance);
    PSV_TreeItemData* parent();

private:
    void addChild(PSV_TreeItemData* child);
    void calculateTreeMes(int& leafCount,int& level,qreal& depth);
    void updateTreeMes();
    void setModified(bool isModified);

private:
    bool m_isModified;
    int m_leafCount;
    int m_level;
    qreal m_depth;//最远的子节点距离
    qreal m_distance;//父节点的距离
    PSV_TreeItemData* m_parent;
    QList<PSV_TreeItemData*> m_children;
    QMap<int,QVariant> m_data;
};

//=================================================
class PSVLIB_API PSV_TreeItem : public PSV_ChartItem/*PSV_Item*/
{

public:
    PSV_TreeItem(const QMap<int, QVariant> &param,PSV_TreeItemData* itemData = 0, QGraphicsItem * parent = 0 );
    ~PSV_TreeItem();
    virtual int type () const;

protected:
    void beforeUpdateItem();
    virtual PSV::DATATYPE dataType();
    void afterUpdateItem();
    virtual void setPrivateItemNull();
    void paintLine(const QLineF& parentVLine,PSV_TreeItemData* itemData);

private:
//    QRectF m_chartRect;
    PSV_TreeItemData* m_itemData;
    qreal m_dw;
    qreal m_dhRatio;
};
#endif // PSV_TREEITEM_H
