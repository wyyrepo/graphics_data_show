#include <QGraphicsScene>
#include "psv_tablewidgetitem.h"

PSV_TableWidgetItem::PSV_TableWidgetItem()
{
    //
}

PSV_TableWidgetItem::~PSV_TableWidgetItem()
{
    //
}

void PSV_TableWidgetItem::advance(int phase)
{
    if(phase)
    {
        this->widget()->setGeometry(0,0,(int)(scene()->width()),(int)(scene()->height()));
    }
}
