#ifndef PSV_CFGDLG_ITEM_H
#define PSV_CFGDLG_ITEM_H
#include <QDialog>
#include <QLineEdit>
#include <QLabel>
#include <QHBoxLayout>
#include <QCheckBox>
#include <QSpinBox>
#include <QCloseEvent>
#include "psv_define.h"
#include "psv_item.h"
#include "psv_graphicsscene.h"

namespace Ui {
class PSV_CfgDlg_Item;
}

class PSV_CfgDlg_Item : public QDialog
{
    Q_OBJECT
public:
    PSV_CfgDlg_Item(PSV_Item& item,QWidget* parent = 0,Qt::WindowFlags f = 0);
    ~PSV_CfgDlg_Item();

private:
    void init();
    bool addItem(int role,const QVariant& value,int row,int col);
    void setColor(QPushButton* button,const QColor& color);
    void updateItem(int role,const QVariant& value);

private slots:
    void onSetFont();
    void onSetColor();
    void onSetText(const QString& text);
    void onSetInt(int value);
    void onSetDouble(double value);
    void onSetBool(bool value);

    void on_btn_save_clicked();

    void on_btn_cancel_clicked();

private:
    Ui::PSV_CfgDlg_Item* ui;
    PSV_Item& m_item;
    bool m_isSave;
    QMap<int,QVariant> m_param;
//    PSV_GraphicsScene m_scene;
};

#endif // PSV_CFGDLG_ITEM_H
