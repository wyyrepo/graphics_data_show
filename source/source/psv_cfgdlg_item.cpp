#include <QColorDialog>
#include <QFontDialog>
#include "psv_cfgdlg_item.h"
#include "ui_psv_cfgdlg_item.h"

PSV_CfgDlg_Item::PSV_CfgDlg_Item(PSV_Item& item
                                 ,QWidget *parent
                                 , Qt::WindowFlags f)
    :QDialog(parent,f)
    ,ui(new Ui::PSV_CfgDlg_Item)
    ,m_item(item)
    ,m_param(item.getParam())
{
    ui->setupUi(this);
    this->setWindowFlags(this->windowFlags()
                         | Qt::WindowCloseButtonHint
                         | Qt::WindowMinimizeButtonHint
                         | Qt::WindowMaximizeButtonHint);
    init();
}

PSV_CfgDlg_Item::~PSV_CfgDlg_Item()
{
    delete ui;
    ui = NULL;
}

void PSV_CfgDlg_Item::init()
{
    QMap<int,QVariant> param = m_item.getParam();
    QMapIterator<int,QVariant> iter(param);
    int row = 0;
    int col = 0;
//    int count = m_param.count();
    int index = 0;
    while(iter.hasNext())
    {
        iter.next();
        if(!m_item.isSetable(iter.key()))
        {
            continue;
        }
        bool ok = addItem(iter.key(),iter.value(),row,2*col);
        if(ok)
        {
            index++;
            row = index / 2;
            col++;
            col %= 2;
        }
    }
}

bool PSV_CfgDlg_Item::addItem(int role
                              ,const QVariant& value
                              ,int row,int col)
{
    PSV::ROLE_DATA d = PSV_Public::getRoleData(role);
    QWidget* widget = NULL;
    QCheckBox* checkBox =NULL;
    QPushButton* pushButton = NULL;
    QLineEdit* lineEdit = NULL;
    QSpinBox* spinBox = NULL;
    QDoubleSpinBox* doubleSpinBox = NULL;
    QString labelText = d.name;

    switch (d.type) {
    case PSV::ROLE_TYPE_BOOL :
        checkBox = new QCheckBox(d.name);
        checkBox->setChecked(value.toBool());
        connect(checkBox,SIGNAL(clicked(bool)),this,SLOT(onSetBool(bool)));
        widget = checkBox;
        labelText = "";
        break;
    case PSV::ROLE_TYPE_COLOR :
        pushButton = new QPushButton;
        setColor(pushButton,value.value<QColor>());
        connect(pushButton,SIGNAL(clicked()),this,SLOT(onSetColor()));
        widget = pushButton;
        break;
    case PSV::ROLE_TYPE_FONT:
        pushButton = new QPushButton;
        pushButton->setText("...");
        connect(pushButton,SIGNAL(clicked()),this,SLOT(onSetFont()));
        widget = pushButton;
        break;
    case PSV::ROLE_TYPE_INT:
        spinBox = new QSpinBox;
        spinBox->setValue(value.toInt());
        connect(spinBox,SIGNAL(valueChanged(int)),this,SLOT(onSetInt(int)));
        widget = spinBox;
        break;
    case PSV::ROLE_TYPE_STRING:
        lineEdit = new QLineEdit(value.toString());
        connect(lineEdit,SIGNAL(textChanged(QString)),this,SLOT(onSetText(QString)));
        widget = lineEdit;
        break;
    case PSV::ROLE_TYPE_DOUBLE:
        doubleSpinBox = new QDoubleSpinBox;
        doubleSpinBox->setValue(value.toDouble());
        connect(doubleSpinBox,SIGNAL(valueChanged(double)),this,SLOT(onSetDouble(double)));
        widget = doubleSpinBox;
        break;
    default:
        PSV_Public::printMes(QString("name = %1,role = %2 is not found type(%3)")
                             .arg(d.name)
                             .arg(d.role)
                             .arg(d.type),"warning");
        return false;
        break;
    }
    QLabel* label = new QLabel(labelText);
    ui->gLayout->addWidget(label,row,col);
    widget->setProperty(PSV_PROPERTY,role);
    widget->setSizePolicy(QSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred,QSizePolicy::Label));
    ui->gLayout->addWidget(widget,row,col+1);
    return true;
}

void PSV_CfgDlg_Item::setColor(QPushButton *button, const QColor &color)
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

void PSV_CfgDlg_Item::updateItem(int role, const QVariant &value)
{
    m_item.setData(role,value);
    m_item.refreshItem();
}

void PSV_CfgDlg_Item::onSetFont()
{
    QPushButton* pushButton = qobject_cast<QPushButton *> (sender());
    if(pushButton != NULL)
    {
        int role = pushButton->property(PSV_PROPERTY).toInt();
        QFont initFont = m_item.getData(role,QFont()).value<QFont>();
        bool ok = false;
        QFont font = QFontDialog::getFont(&ok,initFont,this);
        if(!ok)
        {
            return;
        }
        if(font != initFont)
        {
            updateItem(role,font);
        }
    }
}

void PSV_CfgDlg_Item::onSetColor()
{
    QPushButton* pushButton = qobject_cast<QPushButton *> (sender());
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
            int role = pushButton->property(PSV_PROPERTY).toInt();
//            PSV_Public::printMes(role,"TEST_ROLE");
//            m_item.setData(role,newColor);
//            m_item.refreshItem();
            updateItem(role,newColor);
        }
    }
}

void PSV_CfgDlg_Item::onSetText(const QString &text)
{
    QLineEdit* widget = qobject_cast<QLineEdit *> (sender());
    if(widget != NULL)
    {
        int role = widget->property(PSV_PROPERTY).toInt();
        updateItem(role,text);
    }
}

void PSV_CfgDlg_Item::onSetInt(int value)
{
    QSpinBox* widget = qobject_cast<QSpinBox *> (sender());
    if(widget != NULL)
    {
        int role = widget->property(PSV_PROPERTY).toInt();
        updateItem(role,value);
    }
}

void PSV_CfgDlg_Item::onSetDouble(double value)
{
    QDoubleSpinBox* widget = qobject_cast<QDoubleSpinBox *> (sender());
    if(widget != NULL)
    {
        int role = widget->property(PSV_PROPERTY).toInt();
        updateItem(role,value);
    }
}

void PSV_CfgDlg_Item::onSetBool(bool value)
{
    QCheckBox* widget = qobject_cast<QCheckBox *> (sender());
    if(widget != NULL)
    {
        int role = widget->property(PSV_PROPERTY).toInt();
        updateItem(role,value);
    }
}

void PSV_CfgDlg_Item::on_btn_save_clicked()
{
    this->accept();
}

void PSV_CfgDlg_Item::on_btn_cancel_clicked()
{
    this->reject();
}
