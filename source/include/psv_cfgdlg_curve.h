#ifndef PSV_CURVEDLG_H
#define PSV_CURVEDLG_H

#include <QDialog>
#include "psv_define.h"

namespace Ui {
class PSV_CfgDlg_Curve;
}

class PSV_CfgDlg_Curve : public QDialog
{
    Q_OBJECT

public:
    PSV_CfgDlg_Curve(PSV_CurveInfo& curveInfo,QWidget* parent = 0,Qt::WindowFlags f = 0);
    ~PSV_CfgDlg_Curve();

private:
    void init();
    QPixmap getPixmap(const QSize& size,int index,bool isRect = false);
void setColor(QPushButton* button,const QColor& color);
private slots:
    void onBtnOkClicked();
    void updataColor();

private:
    PSV_CurveInfo& m_curveInfo;
    Ui::PSV_CfgDlg_Curve* ui;
};

#endif // PSV_CURVEDLG_H
