#include <QPixmap>
#include <QPainter>
#include <QColorDialog>
#include "psv_cfgdlg_curve.h"
#include "ui_psv_cfgdlg_curve.h"


PSV_CfgDlg_Curve::PSV_CfgDlg_Curve(PSV_CurveInfo &curveInfo, QWidget *parent, Qt::WindowFlags f)
    :QDialog(parent,f)
    ,m_curveInfo(curveInfo)
{
    ui = new Ui::PSV_CfgDlg_Curve;
    ui->setupUi(this);
    this->setWindowFlags(this->windowFlags()
                         | Qt::WindowCloseButtonHint
                         | Qt::WindowMinimizeButtonHint
                         | Qt::WindowMaximizeButtonHint);
//    this->setWindowTitle(tr("±à¼­ÇúÏßÊôÐÔ"));
    this->layout()->setSizeConstraint(QLayout::SetFixedSize);
    init();
    connect(ui->btn_ok,SIGNAL(clicked()),this,SLOT(onBtnOkClicked()));
    connect(ui->btn_cancel,SIGNAL(clicked()),this,SLOT(close()));
    connect(ui->btn_line,SIGNAL(clicked()),this,SLOT(updataColor()));
    connect(ui->btn_point,SIGNAL(clicked()),this,SLOT(updataColor()));
}

PSV_CfgDlg_Curve::~PSV_CfgDlg_Curve()
{
    delete ui;
    ui = NULL;
}

void PSV_CfgDlg_Curve::init()
{
    QSize size(200,23);
    ui->cbox_line->setIconSize(size);
    for(int i = 1; i <= 10; ++i)
    {
        ui->cbox_point->addItem(QIcon(getPixmap(QSize(20,20),i,false)),QString::number(i),i);
        ui->cbox_line->addItem(QIcon(getPixmap(size,i,true)),"",i);
    }
    int index = ui->cbox_point->findData(m_curveInfo.m_pointSize);
    if(index >= 0)
    {
        ui->cbox_point->setCurrentIndex(index);
    }
    else
    {
        int i = 11;
        ui->cbox_point->addItem(QIcon(getPixmap(QSize(20,20),i,false)),QString::number(i),m_curveInfo.m_pointSize);
        index = ui->cbox_point->findData(m_curveInfo.m_pointSize);
        ui->cbox_point->setCurrentIndex(index);
    }

    index = ui->cbox_line->findData(m_curveInfo.m_lineWidth);
    if(index >= 0)
    {
        ui->cbox_line->setCurrentIndex(index);
    }
    else
    {
        int i = 11;
        ui->cbox_line->addItem(QIcon(getPixmap(size,i,true)),"",m_curveInfo.m_lineWidth);
        index = ui->cbox_line->findData(m_curveInfo.m_lineWidth);
        ui->cbox_line->setCurrentIndex(index);
    }
    ui->lineEdit->setText(m_curveInfo.m_curveName);

    setColor(ui->btn_line,m_curveInfo.m_lineColor);
    setColor(ui->btn_point,m_curveInfo.m_pointColor);

    if(m_curveInfo.m_curveType == PSV::E_CURVE_LINE)
    {
        ui->rbtn_line->setChecked(true);
    }
    else if(m_curveInfo.m_curveType == PSV::E_CURVE_PARELLEL)
    {
        ui->rbtn_parellel->setChecked(true);
    }
}

QPixmap PSV_CfgDlg_Curve::getPixmap(const QSize &size, int index, bool isRect)
{
    QPixmap pixmap(size);
    pixmap.fill();
    QPainter painter(&pixmap);
    QBrush brush(Qt::black);
    painter.setBrush(brush);
    if(isRect)
    {
        painter.drawRect(0,pixmap.height() / 2 - index,pixmap.width(),2*index);
    }
    else
    {
        painter.drawEllipse(pixmap.width() / 2 - index,pixmap.height() / 2 - index,2*index,2*index);
    }
    return pixmap;
}

void PSV_CfgDlg_Curve::onBtnOkClicked()
{
    int index = ui->cbox_point->currentIndex();
    m_curveInfo.m_pointSize = ui->cbox_point->itemData(index).toInt();
    index = ui->cbox_line->currentIndex();
    m_curveInfo.m_lineWidth = ui->cbox_line->itemData(index).toInt();
    if(ui->rbtn_line->isChecked())
    {
        m_curveInfo.m_curveType = PSV::E_CURVE_LINE;
    }
    else if(ui->rbtn_parellel->isChecked())
    {
        m_curveInfo.m_curveType = PSV::E_CURVE_PARELLEL;
    }

    m_curveInfo.m_lineColor = ui->btn_line->palette().color(QPalette::Button);
    m_curveInfo.m_pointColor = ui->btn_point->palette().color(QPalette::Button);

    this->accept();
}

void PSV_CfgDlg_Curve::setColor(QPushButton *button, const QColor &color)
{
    if(button == NULL)
    {
        return;
    }
    QPalette pal = button->palette();
    pal.setColor(QPalette::Button,color);
    button->setPalette(pal);
    button->setAutoFillBackground(true);
    button->setFlat(true);
}

void PSV_CfgDlg_Curve::updataColor()
{
     QPushButton* pushButton = qobject_cast<QPushButton *> (sender());
//     QString objectName = pushButton->objectName();
     if(pushButton != NULL)
     {
         QColor color = pushButton->palette().color(QPalette::Button);
         bool ok = false;
         QRgb rgba = QColorDialog::getRgba(color.rgba(),&ok,this);
         QColor newColor = QColor::fromRgba(rgba);
         if(newColor != color && ok)
         {
             QPalette pal = pushButton->palette();
             pal.setColor(QPalette::Button,newColor);
             pushButton->setPalette(pal);
         }
     }
}
