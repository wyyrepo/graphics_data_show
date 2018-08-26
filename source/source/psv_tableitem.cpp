#include <QFont>
#include <QPen>
#include "psv_tableitem.h"

PSV_TableItem::PSV_TableItem(const QMap<int, QVariant> &param, QGraphicsItem *parent)
    : PSV_Item(param,parent)
    , m_maxRow(0)
    , m_lineWidth(1)
    , m_titleText("")
    , m_lineColor(Qt::black)
    , m_titleColor(Qt::black)
    , m_titleItem(NULL)
{
    m_titleFont.setBold(true);
    m_titleFont.setPointSize(16);

    m_defautFont.setBold(false);
    m_defautFont.setPixelSize(12);
    initVariables();
    updateItem();
    //====================
    m_isAdvancetable = true;//根据advance自动 刷新
    m_painterPath.addRect(getBoundingRect());
    setAcceptHoverEvents(true);
}

PSV_TableItem::~PSV_TableItem()
{
    //
}

int PSV_TableItem::type() const
{
    return PSV::tableItem;
}

void PSV_TableItem::initVariables(/*const QMap<PSV::PARAM_EKY, QVariant> &d->m_param*/)
{
//    if(d->m_param.contains(PSV::boundingRect))
//    {
//        m_rect = d->m_param.value(PSV::boundingRect).toRectF();
//    }
    if(d->m_param.contains(PSV::toolTip))
    {
        setToolTip(d->m_param.value(PSV::toolTip).toString());
    }
    if(d->m_param.contains(PSV::lineColor))
    {
        m_lineColor = d->m_param.value(PSV::lineColor).value<QColor>();
    }
    if(d->m_param.contains(PSV::lineWidth))
    {
        m_lineWidth = d->m_param.value(PSV::lineWidth).toDouble();
    }
    if(d->m_param.contains(PSV::titleText))
    {
        m_titleText = d->m_param.value(PSV::titleText).toString();
    }
    if(d->m_param.contains(PSV::titleFont))
    {
        m_titleFont = d->m_param.value(PSV::titleFont).value<QFont>();
    }
    if(d->m_param.contains(PSV::titleColor))
    {
        m_titleColor = d->m_param.value(PSV::titleColor).value<QColor>();
    }
    if(d->m_param.contains(PSV::dataFont))
    {
        QMap<QString, QVariant> tempMap = d->m_param.value(PSV::dataFont).toMap();
        QMapIterator<QString, QVariant> iter(tempMap);
        while(iter.hasNext())
        {
            iter.next();
            m_dataFont.insert(iter.key(), iter.value().value<QFont>());
        }
    }
    if(d->m_param.contains(PSV::dataColor))
    {
        QMap<QString, QVariant> tempMap = d->m_param.value(PSV::dataColor).toMap();
        QMapIterator<QString, QVariant> iter(tempMap);
        while(iter.hasNext())
        {
            iter.next();
            m_dataColor.insert(iter.key(), iter.value().value<QColor>());
        }
    }

    if(d->m_param.contains(PSV::vHeaderColor))
    {
        QMap<QString, QVariant> tempMap = d->m_param.value(PSV::vHeaderColor).toMap();
        QMapIterator<QString, QVariant> iter(tempMap);
        while(iter.hasNext())
        {
            iter.next();
            m_vHeaderColor.insert(iter.key(), iter.value().value<QColor>());
        }
    }
}

void PSV_TableItem::updateItem()
{
    QPen pen(m_lineColor);
    QRectF m_rect = getBoundingRect();
    pen.setWidthF(m_lineWidth);
    {
        QGraphicsRectItem *item = new QGraphicsRectItem(m_rect, this);
        item->setPen(pen);
    }
    m_titleFont.setPointSizeF(m_rect.width() * 0.022);
    qreal currentHeight = m_rect.top();
    if(!m_titleText.isEmpty())
    {
        updateTitle();
        currentHeight += m_titleItem->boundingRect().height();

        QGraphicsLineItem *item = new QGraphicsLineItem(this);
        QLineF line(m_rect.left(), currentHeight, m_rect.right(), currentHeight);
        item->setLine(line);
        item->setPen(pen);
    }

    int count = m_data.count();
    if(count <= 0)
    {
        return;
    }
    m_defautFont.setPointSizeF(m_rect.height() * m_rect.width() / m_maxRow / count * 0.0035);
    QMapIterator<QString, QString> iter_max(m_dataMaxLenght);
    QMap<QString, QGraphicsTextItem*> tempMaxItem;
    QMap<QString, QGraphicsTextItem*> tempHeaderItem;
    QMap<QString, qreal> tempMaxWidth;
    double totalWidth = 0;
    double maxHeight = 0;
    qreal headerHeight = 0;
    while(iter_max.hasNext())
    {
        iter_max.next();
        {
            QGraphicsTextItem *item = new QGraphicsTextItem(iter_max.key(), this);
            QFont font = m_defautFont;
            if(m_vHeaderFont.contains(iter_max.key()))
            {
                font = m_vHeaderFont.value(iter_max.key());
            }
            item->setFont(font);
            QColor color = getDefaultColor();
            if(m_vHeaderColor.contains(iter_max.key()))
            {
                color = m_vHeaderColor.value(iter_max.key());
            }
            item->setDefaultTextColor(color);
            if(item->boundingRect().height() > headerHeight)
            {
                headerHeight = item->boundingRect().height();
            }
            tempHeaderItem.insert(iter_max.key(), item);
        }
        QGraphicsTextItem *item = new QGraphicsTextItem(iter_max.value(), this);
        QFont font = m_defautFont;
        if(m_dataFont.contains(iter_max.key()))
        {
            font = m_dataFont.value(iter_max.key());
        }
        item->setFont(font);
        QColor color = getDefaultColor();
        if(m_dataColor.contains(iter_max.key()))
        {
            color = m_dataColor.value(iter_max.key());
        }
        item->setDefaultTextColor(color);
        tempMaxItem.insert(iter_max.value(), item);
        QRectF rect = item->boundingRect();
        totalWidth += rect.width();
        tempMaxWidth.insert(iter_max.key(), rect.width());
        if(maxHeight < rect.height())
        {
            maxHeight = rect.height();
        }
    }
//    if(m_maxRow <= 0)
//    {
//        m_maxRow = 1;
//    }
    m_maxRow = qMax(1,m_maxRow);
    double dy = (m_rect.bottom() - currentHeight - headerHeight) / m_maxRow;
    if(dy < 0)
    {
        return;
    }
    qreal sx = m_rect.width() / totalWidth;
    QMapIterator<QString, QStringList> iter(m_data);
    int col = 0;
    qreal x = m_rect.left();
    int testCount = 0;
    while(iter.hasNext())
    {
        iter.next();
        QString key = iter.key();
        double dx = tempMaxWidth.value(key) * sx;
        {
            if(tempHeaderItem.contains(iter.key()))
            {
                QGraphicsTextItem *item = tempHeaderItem.value(iter.key());
                item->setPos(x + 0.5 * (dx - item->boundingRect().width())
                             , currentHeight + 0.5 * (headerHeight - item->boundingRect().height()));
            }
        }
        QStringList list = iter.value();
        bool isExist = true;
        QFont font = m_defautFont;
        if(m_dataFont.contains(key))
        {
            font = m_dataFont.value(key);
        }
        QColor color = getDefaultColor();
        if(m_dataColor.contains(key))
        {
            color = m_dataColor.value(key);
        }
        qreal y = currentHeight + headerHeight;
        foreach(QString str, list)
        {
            QGraphicsTextItem *item;
            if(tempMaxItem.contains(str) && isExist)
            {
                isExist = false;
                item = tempMaxItem.value(str);
            }
            else
            {
                item = new QGraphicsTextItem(str, this);
                item->setFont(font);
                item->setDefaultTextColor(color);
                testCount++;
            }
            item->setPos(x + 0.5 * (dx - item->boundingRect().width()), y + 0.5 * (dy - item->boundingRect().height()) );
            y += dy;
        }
        if(col > 0 && col < count)
        {
            QGraphicsLineItem *item = new QGraphicsLineItem(this);
            QLineF line(x, currentHeight, x, m_rect.bottom());
            item->setLine(line);
            item->setPen(pen);
        }
        x += dx;
        col++;
    }
    for(int i = 0; i <= m_maxRow; ++i)
    {
        if(i == 0)
        {
            QGraphicsLineItem *item = new QGraphicsLineItem(this);
            QLineF line(m_rect.left(), currentHeight+headerHeight, m_rect.right(), currentHeight+headerHeight);
            item->setLine(line);
            item->setPen(pen);
            currentHeight += headerHeight;
        }
        else
        {
            QGraphicsLineItem *item = new QGraphicsLineItem(this);
            QLineF line(m_rect.left(), currentHeight, m_rect.right(), currentHeight);
            item->setLine(line);
            item->setPen(pen);
            currentHeight += dy;
        }
    }
}

void PSV_TableItem::updateTitle()
{
    if(m_titleItem == NULL)
    {
        m_titleItem = new QGraphicsTextItem(this);
    }
    m_titleItem->setPlainText(m_titleText);
    m_titleItem->setDefaultTextColor(m_titleColor);
    m_titleItem->setFont(m_titleFont);
    QRectF rect = m_titleItem->boundingRect();
    QRectF m_rect = getBoundingRect();
    m_titleItem->setPos(m_rect.center().x() - 0.5 * rect.width(), m_rect.top());
}

bool PSV_TableItem::setTableData(const QMap<QString, QStringList> &dataMap)
{
    int maxRow = 0;
    QMap<QString, QString> dataMaxLenght;

    QMapIterator<QString, QStringList> iter(dataMap);
    while(iter.hasNext())
    {
        iter.next();
        QStringList list = iter.value();
        if(maxRow < list.count())
        {
            maxRow = list.count();
        }
        int maxLen = 0;
        QString maxStr;
        foreach(QString str, list)
        {
            if(str.toLatin1().length() > maxLen)
            {
                maxLen = str.toLatin1().length();
                maxStr = str;
            }
        }
        dataMaxLenght.insert(iter.key(), maxStr);
    }
    if(maxRow <= 0)
    {
        return false;
    }
    m_maxRow = maxRow;
    m_dataMaxLenght = dataMaxLenght;
    m_data = dataMap;
    refreshItem();
    return true;
}

void PSV_TableItem::setDataColor(const QMap<QString, QColor> &dataColor)
{
    m_dataColor = dataColor;
    refreshItem();
}

void PSV_TableItem::setDataColor(const QString &colName, const QColor &colColor)
{
    if(m_data.contains(colName))
    {
        m_dataColor.insert(colName,colColor);
        refreshItem();
    }
}

void PSV_TableItem::setItemNull()
{
    m_titleItem = NULL;
    return;
}

void PSV_TableItem::setTableTile(const QString &title)
{
    m_titleText = title;
    updateTitle();
}
