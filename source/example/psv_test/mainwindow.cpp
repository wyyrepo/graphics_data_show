#include <QStandardItemModel>
#include <QDebug>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "testpublic.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_dataRole = Qt::UserRole + 1;
    m_timer.setInterval(1000);
    m_timer_value.setInterval(5000);
    connect(&m_timer,SIGNAL(timeout()),this,SLOT(updateView()));
    connect(&m_timer_value,SIGNAL(timeout()),this,SLOT(updateViewValue()));
    m_stackedWidget = new QStackedWidget;
    ui->hLayout->addWidget(m_stackedWidget);
    connect(ui->pushButton_close,SIGNAL(clicked()),this,SLOT(close()));
//    connect(ui->pushButton_ok,SIGNAL(clicked()),this,SLOT(close()));
    connect(ui->treeWidget,SIGNAL(itemClicked(QTreeWidgetItem*,int)),this,SLOT(itemIsChanged(QTreeWidgetItem*,int)));
    m_PSV_PainterPathItem = NULL;
//    m_PSV_ButtonItem = NULL;
    ui->treeWidget->setHeaderLabel(QString::fromLocal8Bit("测试项"));
    colorList = TestPublic::listColor(10);
    init();
//    testAll2();
    m_timer.start();
    m_timer_value.start();
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::init()
{
    QList<QColor> colorList = TestPublic::listColor(10);
    QMap<int, QVariant> param;
    QFont valueFont;
    QFont titleFont;
    valueFont.setPointSize(16);
    param.insert(PSV::boundingRect, QRectF(0, 0, 1200, 600));
    param.insert(PSV::valueFont, valueFont);
    param.insert(PSV::titleText, "Test");
    param.insert(PSV::titleFont, titleFont);
    param.insert(PSV::titleColor, QColor(Qt::blue));
    param.insert(PSV::value, 83);
    param.insert(PSV::maxValue, 100);
    param.insert(PSV::minValue, 0);
    addChartRealItem(QString::fromLocal8Bit("曲线_double"),param);
    addChartTimeItem(QString::fromLocal8Bit("曲线_time"),param);
    addChartDateTimeItem(QString::fromLocal8Bit("曲线_dateTime"),param);

    addChartDateItem(QString::fromLocal8Bit("曲线_date"),param);
    addChartHistogramItem(QString::fromLocal8Bit("直方图"),param);
    addChartHistogramItemAdd(QString::fromLocal8Bit("直方图_累计"),param);
    addChartAreaItem(QString::fromLocal8Bit("面积图"),param);
    addPie3Item(QString::fromLocal8Bit("3D圆饼"),param);
    addCircularIndicatorItem(QString::fromLocal8Bit("圆形指示盘"),param);
    //=======================================
    addTableItem(QString::fromLocal8Bit("表格"),param);
    addTableWidgetItem(QString::fromLocal8Bit("表格Widget"),param);
    addPainterPathItem(QString::fromLocal8Bit("路径"),param);
    addVerticalIndicatorItem(QString::fromLocal8Bit("垂直指示器"),param);
    addChartBarItem(QString::fromLocal8Bit("条形图"),param);
    addButtonItem(QString::fromLocal8Bit("按钮"),param);

m_stackedWidget->setCurrentIndex(0);
    return;///////////////TTTTTTTTTTTTTTTTTTTTT
}

void MainWindow::addChartRealItem(const QString &title, const QMap<int, QVariant> &param)
{//<PSV_ChartRealItem>曲线_double
//    QString title = QString::fromLocal8Bit("曲线_double");
    QTreeWidgetItem * treeItem = new QTreeWidgetItem(ui->treeWidget);
    treeItem->setText(0,title);//==================================
    treeItem->setData(0,m_dataRole,m_stackedWidget->count());
    PSV_GraphicsScene* scene = new PSV_GraphicsScene;
    PSV_GraphicsView* view = new PSV_GraphicsView;
    view->setRenderHint(QPainter::Antialiasing);
    //==================================
    PSV_ChartRealItem *item = new PSV_ChartRealItem(param);//
    scene->addItem(item);
    for(int i = 0; i < 3; ++i)
    {
        PSV_CurveParam curveParam(tr("test_%1").arg(i));
        if(i % 2 == 0)
        {
            curveParam.m_curveType = PSV::E_CURVE_PARELLEL;
        }
        else
        {
            curveParam.m_curveType = PSV::E_CURVE_LINE;
        }
        curveParam.m_isUpdate = false;
        QMap<double,double> tempData = TestPublic::mapDoubleDouble(12);
        item->addCurve(tempData,curveParam);
        {
            QMap<double,double> tempData = TestPublic::mapDoubleDoubleSin(i,12+i,i,0.1);
            PSV_CurveParam curveParam(QString("test_sin_%1").arg(i));
            curveParam.m_axisType = PSV::E_AXIS_RIGHT;
            item->addCurve(tempData,curveParam);
        }
    }
    //==================================
//        scene->setBackgroundBrush(QBrush(Qt::gray));
    scene->setBackgroundBrush(QBrush(Qt::darkGray));
    view->setScene(scene);
    item->setTitleText(title);
    item->setTitleColor(QColor(Qt::red));
    item->refreshItem();
    m_stackedWidget->addWidget(view);
    //        m_stackedWidget->setCurrentIndex(m_stackedWidget->count() - 1);
}

void MainWindow::addChartTimeItem(const QString &title, const QMap<int, QVariant> &param)
{//<PSV_ChartTimeItem>曲线_time
//    QString title = QString::fromLocal8Bit("曲线_time");
    QTreeWidgetItem * treeItem = new QTreeWidgetItem(ui->treeWidget);
    treeItem->setText(0,title);//==================================
    treeItem->setData(0,m_dataRole,m_stackedWidget->count());
    PSV_GraphicsScene* scene = new PSV_GraphicsScene;
    PSV_GraphicsView* view = new PSV_GraphicsView;
    view->setRenderHint(QPainter::Antialiasing);
    //==================================
    PSV_ChartTimeItem *item = new PSV_ChartTimeItem(param);//
    scene->addItem(item);
    for(int i = 0; i < 3; ++i)
    {
        PSV_CurveParam curveParam(tr("test_%1").arg(i));
        if(i % 2 == 0)
        {
            curveParam.m_curveType = PSV::E_CURVE_PARELLEL;
        }
        else
        {
            curveParam.m_curveType = PSV::E_CURVE_LINE;
        }
        curveParam.m_isUpdate = false;
        QMap<QTime,double> tempData = TestPublic::mapTimeDouble(3300);
        item->addCurve(tempData,curveParam);
    }
    //==================================
    scene->setBackgroundBrush(QBrush(Qt::gray));
    view->setScene(scene);
    item->setTitleText(title);
    item->setTitleColor(QColor(Qt::blue));
    item->refreshItem();
    m_stackedWidget->addWidget(view);
    //        m_stackedWidget->setCurrentIndex(m_stackedWidget->count() - 1);
}

void MainWindow::addChartDateTimeItem(const QString &title, const QMap<int, QVariant> &param)
{//<PSV_ChartDateTimeItem>曲线_dateTime
//    QString title = QString::fromLocal8Bit("曲线_dateTime");
    QTreeWidgetItem * treeItem = new QTreeWidgetItem(ui->treeWidget);
    treeItem->setText(0,title);//==================================
    treeItem->setData(0,m_dataRole,m_stackedWidget->count());
    PSV_GraphicsScene* scene = new PSV_GraphicsScene;
    PSV_GraphicsView* view = new PSV_GraphicsView;
    view->setRenderHint(QPainter::Antialiasing);
    //==================================
    PSV_ChartDateTimeItem *item = new PSV_ChartDateTimeItem(param);//
    scene->addItem(item);
    for(int i = 0; i < 2; ++i)
    {
        PSV_CurveParam curveParam(tr("test_%1").arg(i));
        if(i % 2 == 0)
        {
            curveParam.m_curveType = PSV::E_CURVE_PARELLEL;
        }
        else
        {
            curveParam.m_curveType = PSV::E_CURVE_LINE;
        }
        curveParam.m_isUpdate = false;
        QMap<QDateTime,double> tempData = TestPublic::mapDateTimeDouble(3900);
        item->addCurve(tempData,curveParam);
    }
    //==================================
    scene->setBackgroundBrush(QBrush(Qt::gray));
    view->setScene(scene);
    item->setTitleText(title);
    item->setTitleColor(QColor(Qt::green));
    item->refreshItem();
    m_stackedWidget->addWidget(view);
    //        m_stackedWidget->setCurrentIndex(m_stackedWidget->count() - 1);
}

void MainWindow::addChartDateItem(const QString &title, const QMap<int, QVariant> &param)
{//<PSV_ChartDateItem>曲线_date
//    QString title = QString::fromLocal8Bit("曲线_date");
    QTreeWidgetItem * treeItem = new QTreeWidgetItem(ui->treeWidget);
    treeItem->setText(0,title);//==================================
    treeItem->setData(0,m_dataRole,m_stackedWidget->count());
    PSV_GraphicsScene* scene = new PSV_GraphicsScene;
    PSV_GraphicsView* view = new PSV_GraphicsView;
    view->setRenderHint(QPainter::Antialiasing);
    //==================================
    PSV_ChartDateTimeItem *item = new PSV_ChartDateTimeItem(param);//
    scene->addItem(item);
    for(int i = 0; i < 3; ++i)
    {
        PSV_CurveParam curveParam(tr("test_%1").arg(i));
        if(i % 2 == 0)
        {
            curveParam.m_curveType = PSV::E_CURVE_PARELLEL;
        }
        else
        {
            curveParam.m_curveType = PSV::E_CURVE_LINE;
        }
        curveParam.m_isUpdate = false;
        QMap<QDate,double> tempData = TestPublic::mapDateDouble(12);
        item->addCurve(tempData,curveParam);
    }
    //==================================
    scene->setBackgroundBrush(QBrush(Qt::gray));
    view->setScene(scene);
    item->setTitleText(title);
    item->setTitleColor(QColor(Qt::yellow));
    item->refreshItem();
    m_stackedWidget->addWidget(view);
    //        m_stackedWidget->setCurrentIndex(m_stackedWidget->count() - 1);
}

void MainWindow::addChartHistogramItem(const QString &title, const QMap<int, QVariant> &param)
{//<PSV_ChartHistogramItem>直方图
//    QString title = QString::fromLocal8Bit("直方图");//==================================
    QTreeWidgetItem * treeItem = new QTreeWidgetItem(ui->treeWidget);
    treeItem->setText(0,title);
    treeItem->setData(0,m_dataRole,m_stackedWidget->count());
    PSV_GraphicsScene* scene = new PSV_GraphicsScene;
    PSV_GraphicsView* view = new PSV_GraphicsView;
    view->setRenderHint(QPainter::Antialiasing);
    //==================================
    PSV_ChartHistogramItem *item = new PSV_ChartHistogramItem(param);//
    scene->addItem(item);
    QMap<QString,double> tempData = TestPublic::mapStringDouble(12,50);
    QList<QColor> colorList =TestPublic::listColor(12);
    item->addHistogram(tempData,colorList);
    PSV_CurveParam curveParam(QString::fromLocal8Bit("产值"));
    item->addCurve(tempData,curveParam);
    item->setTitleText(title);
    item->refreshItem();
    //==================================
    scene->setBackgroundBrush(QBrush(Qt::gray));
    view->setScene(scene);
    m_stackedWidget->addWidget(view);
    //        m_stackedWidget->setCurrentIndex(m_stackedWidget->count() - 1);
}

void MainWindow::addChartHistogramItemAdd(const QString &title, const QMap<int, QVariant> &param)
{//<PSV_ChartHistogramItem>直方图_累计
//    QString title = QString::fromLocal8Bit("直方图_累计");//==================================
    QTreeWidgetItem * treeItem = new QTreeWidgetItem(ui->treeWidget);
    treeItem->setText(0,title);
    treeItem->setData(0,m_dataRole,m_stackedWidget->count());
    PSV_GraphicsScene* scene = new PSV_GraphicsScene;
    PSV_GraphicsView* view = new PSV_GraphicsView;
    view->setRenderHint(QPainter::Antialiasing);
    //==================================
    PSV_ChartHistogramItem *item = new PSV_ChartHistogramItem(param);//
    scene->addItem(item);

    QList<QPair<QString,QList<double> > > tempData = TestPublic::listPairStringListDouble(5,2);
    QList<QColor> colorList =TestPublic::listColor(5);
    item->addHistogram(tempData,colorList,true);
    item->setTitleText(title);
    item->refreshItem();
    //==================================
    scene->setBackgroundBrush(QBrush(Qt::gray));
    view->setScene(scene);
    m_stackedWidget->addWidget(view);
    //        m_stackedWidget->setCurrentIndex(m_stackedWidget->count() - 1);
}

void MainWindow::addChartAreaItem(const QString &title, const QMap<int, QVariant> &param)
{//<PSV_ChartAreaItem>面积图
//        QString title = QString::fromLocal8Bit("面积图");//==================================
    QTreeWidgetItem * treeItem = new QTreeWidgetItem(ui->treeWidget);
    treeItem->setText(0,title);
    treeItem->setData(0,m_dataRole,m_stackedWidget->count());
    PSV_GraphicsScene* scene = new PSV_GraphicsScene;
    PSV_GraphicsView* view = new PSV_GraphicsView;
    view->setRenderHint(QPainter::Antialiasing);
    //==================================
    PSV_ChartAreaItem *item = new PSV_ChartAreaItem(param);//
    scene->addItem(item);
    QList<QPair<QString,QList<double> > > tempData = TestPublic::listPairStringListDouble(5,3);
    QList<QColor> colorList =TestPublic::listColor(5);
    item->addCurve(tempData,colorList);
    item->setTitleText(title);
    item->refreshItem();
    //==================================
    scene->setBackgroundBrush(QBrush(Qt::gray));
    view->setScene(scene);
    m_stackedWidget->addWidget(view);
    //        m_stackedWidget->setCurrentIndex(m_stackedWidget->count() - 1);
}

void MainWindow::addPie3Item(const QString &title, const QMap<int, QVariant> &param)
{//<PSV_Pie3Item>3D圆饼
//    QString title = QString::fromLocal8Bit("3D圆饼");//==================================
    QTreeWidgetItem * treeItem = new QTreeWidgetItem(ui->treeWidget);
    treeItem->setText(0,title);
    treeItem->setData(0,m_dataRole,m_stackedWidget->count());
    PSV_GraphicsScene* scene = new PSV_GraphicsScene;
    PSV_GraphicsView* view = new PSV_GraphicsView;
    view->setRenderHint(QPainter::Antialiasing);
    //==================================
//        QGraphicsLineItem *parentItem = new QGraphicsLineItem;
    PSV_Pie3Item *item = new PSV_Pie3Item(param);//
    scene->addItem(item);
    QMap<QString,double> tempData = TestPublic::mapStringDouble(12,0);
    item->setChartData(tempData);
    item->refreshItem();
    //==================================
    scene->setBackgroundBrush(QBrush(Qt::gray));
    view->setScene(scene);
    m_stackedWidget->addWidget(view);
    //        m_stackedWidget->setCurrentIndex(m_stackedWidget->count() - 1);
}

void MainWindow::addCircularIndicatorItem(const QString &title, const QMap<int, QVariant> &param)
{//《PSV_CircularIndicatorItem》圆形指示盘
//    QString title = QString::fromLocal8Bit("圆形指示盘");//==================================
    QTreeWidgetItem * treeItem = new QTreeWidgetItem(ui->treeWidget);
    treeItem->setText(0,title);
    treeItem->setData(0,m_dataRole,m_stackedWidget->count());
    PSV_GraphicsScene* scene = new PSV_GraphicsScene;
    PSV_GraphicsView* view = new PSV_GraphicsView;
    view->setRenderHint(QPainter::Antialiasing);
    //==================================
    m_PSV_CircularIndicatorItem = new PSV_CircularIndicatorItem(param);//
    PSV_CircularIndicatorItem *item = m_PSV_CircularIndicatorItem;
    scene->addItem(item);
    item->setValue(33);
    //==================================
    scene->setBackgroundBrush(QBrush(Qt::gray));
    view->setScene(scene);
    m_stackedWidget->addWidget(view);
    //        m_stackedWidget->setCurrentIndex(m_stackedWidget->count() - 1);
}

void MainWindow::addTableItem(const QString &title, const QMap<int, QVariant> &param)
{//<PSV_TableItem>表格
//        QString title = QString::fromLocal8Bit("表格");//==================================
    QTreeWidgetItem * treeItem = new QTreeWidgetItem(ui->treeWidget);
    treeItem->setText(0,title);
    treeItem->setData(0,m_dataRole,m_stackedWidget->count());
    PSV_GraphicsScene* scene = new PSV_GraphicsScene;
    PSV_GraphicsView* view = new PSV_GraphicsView;
    view->setRenderHint(QPainter::Antialiasing);
    //==================================
    QMap<int, QVariant> tempParam = param;
    QFont font;
    font.setBold(true);
    font.setPointSize(16);
    tempParam.insert(PSV::titleFont,font);

    PSV_TableItem *item = new PSV_TableItem(tempParam);//
    scene->addItem(item);
    QMap<QString,QStringList> tempData = TestPublic::mapStringStringList(10,12);
    item->setTableData(tempData);
    item->setDataColor("test_0",QColor(Qt::red));
    item->setTableTile(title);
    //==================================
    scene->setBackgroundBrush(QBrush(Qt::gray));
    view->setScene(scene);
    m_stackedWidget->addWidget(view);
    //        m_stackedWidget->setCurrentIndex(m_stackedWidget->count() - 1);
}

void MainWindow::addTableWidgetItem(const QString &title, const QMap<int, QVariant> &param)
{//PSV_TableWidgetItem
//    QString title = QString::fromLocal8Bit("表格Widget");//==================================
    QTreeWidgetItem * treeItem = new QTreeWidgetItem(ui->treeWidget);
    treeItem->setText(0,title);
    treeItem->setData(0,m_dataRole,m_stackedWidget->count());
    PSV_GraphicsScene* scene = new PSV_GraphicsScene;
    PSV_GraphicsView* view = new PSV_GraphicsView;
    view->setRenderHint(QPainter::Antialiasing);
    //==================================
    PSV_TableWidgetItem *item = new PSV_TableWidgetItem();//
    QTableView *tableView = new QTableView;

    QStandardItemModel *model = new QStandardItemModel(13,9);
    for(int row = 0; row < model->rowCount(); ++row)
    {
        for(int col = 0; col < model->columnCount(); ++col)
        {
            QModelIndex index = model->index(row,col);
            model->setData(index,qrand() % 1000);
        }
    }
    tableView->setModel(model);
    item->setWidget(tableView);
    scene->addItem(item);
    //==================================
    scene->setBackgroundBrush(QBrush(Qt::gray));
    view->setScene(scene);
    m_stackedWidget->addWidget(view);
    //        m_stackedWidget->setCurrentIndex(m_stackedWidget->count() - 1);
}

void MainWindow::addPainterPathItem(const QString &title, const QMap<int, QVariant> &param)
{//PSV_PainterPathItem
//    QString title = QString::fromLocal8Bit("路径");//==================================
    QTreeWidgetItem * treeItem = new QTreeWidgetItem(ui->treeWidget);
    treeItem->setText(0,title);
    treeItem->setData(0,m_dataRole,m_stackedWidget->count());
    PSV_GraphicsScene* scene = new PSV_GraphicsScene;
    PSV_GraphicsView* view = new PSV_GraphicsView;
    view->setRenderHint(QPainter::Antialiasing);
    //==================================
    QPainterPath path;
    qsrand(QTime::currentTime().secsTo(QTime()));
//        path.lineTo(112,0);
//        for(int i = 0 ; i < 20; ++i)
//        {
//            path.lineTo(qrand() % 1000,qrand() % 800);
//            if(i % 5 = 0)
//            {
//                path.lineTo(qrand() % 1000,qrand() % 800);
//            }
//        }
    path.lineTo(112,130);
    path.lineTo(112,45);
    path.lineTo(222,45);
    path.lineTo(9,120);
    path.lineTo(140,60);
    path.lineTo(360,60);
    path.lineTo(460,170);
    path.lineTo(460,60);
    PSV_PainterPathItem *item = new PSV_PainterPathItem(path);//
    scene->addItem(item);
    item->setPos(100,100);
    item->setPath(path);
    item->beginSet();
    item->setArrowsColor(QColor(Qt::blue));
    item->setArrowsLength(12);
    item->startAnimation();
    item->showArrows();
    item->endSet();
//        item->refreshItem();
    //==================================
    scene->setBackgroundBrush(QBrush(Qt::gray));
    view->setScene(scene);
    m_stackedWidget->addWidget(view);
    //        m_stackedWidget->setCurrentIndex(m_stackedWidget->count() - 1);
}

void MainWindow::addVerticalIndicatorItem(const QString &title, const QMap<int, QVariant> &param)
{//PSV_VerticalIndicatorItem
//        QString title = QString::fromLocal8Bit("垂直指示器");//==================================
    QTreeWidgetItem * treeItem = new QTreeWidgetItem(ui->treeWidget);
    treeItem->setText(0,title);
    treeItem->setData(0,m_dataRole,m_stackedWidget->count());
    PSV_GraphicsScene* scene = new PSV_GraphicsScene;
    PSV_GraphicsView* view = new PSV_GraphicsView;
    view->setRenderHint(QPainter::Antialiasing);
    //==================================
    m_PSV_VerticalIndicatorItem = new PSV_VerticalIndicatorItem(param);//
    PSV_VerticalIndicatorItem *item = m_PSV_VerticalIndicatorItem;
    scene->addItem(item);
    item->setValue(42);
    item->setAlign(false);
    //==================================
    scene->setBackgroundBrush(QBrush(Qt::gray));
    view->setScene(scene);
    m_stackedWidget->addWidget(view);
    //        m_stackedWidget->setCurrentIndex(m_stackedWidget->count() - 1);
}

void MainWindow::addChartBarItem(const QString &title, const QMap<int, QVariant> &param)
{//PSV_ChartBarItem
//    QString title = QString::fromLocal8Bit("条形图");//==================================
    QTreeWidgetItem * treeItem = new QTreeWidgetItem(ui->treeWidget);
    treeItem->setText(0,title);
    treeItem->setData(0,m_dataRole,m_stackedWidget->count());
    PSV_GraphicsScene* scene = new PSV_GraphicsScene;
    PSV_GraphicsView* view = new PSV_GraphicsView;
    view->setRenderHint(QPainter::Antialiasing);
    //==================================
    PSV_ChartBarItem *item = new PSV_ChartBarItem(param);//
    scene->addItem(item);
    QList<QString> keys = TestPublic::listString(10,"CCC");
    QList<double> values = TestPublic::listDoulbe(10);
    item->setChartValue(keys,values,colorList);
    item->refreshItem();
    //==================================
    scene->setBackgroundBrush(QBrush(Qt::gray));
    view->setScene(scene);
    m_stackedWidget->addWidget(view);
    m_stackedWidget->setCurrentIndex(m_stackedWidget->count() - 1);
}

void MainWindow::addButtonItem(const QString &title, const QMap<int, QVariant> &param)
{//PSV_ButtonItem
//        QString title = QString::fromLocal8Bit("按钮");//==================================
    QTreeWidgetItem * treeItem = new QTreeWidgetItem(ui->treeWidget);
    treeItem->setText(0,title);
    treeItem->setData(0,m_dataRole,m_stackedWidget->count());
    PSV_GraphicsScene* scene = new PSV_GraphicsScene;
    PSV_GraphicsView* view = new PSV_GraphicsView;
    view->setRenderHint(QPainter::Antialiasing);
    //==================================
    QMap<int, QVariant> tempParam = param;
    int size = 80;
    qreal px = 100;
    qreal py = 100;
    for(int row  = 0; row < 5;row++)
    {
        for(int col = 0 ; col < 5; col++)
        {
            tempParam.insert(PSV::boundingRect,QRectF(px + row * size,py + col * size,size,size));
            PSV_ButtonItem *item = new PSV_ButtonItem(tempParam);
            item->setStateColor(0,QColor(Qt::darkBlue),"darkBlue");
            item->setStateColor(1,QColor(Qt::yellow),"yellow");
            item->setStateColor(2,QColor(Qt::red),"red");
            item->setStateColor(3,QColor(Qt::green),"green");
            item->setStateColor(4,QColor(Qt::gray),"gray");
            item->setStateColor(5,QColor(Qt::darkGreen),"darkGreen");
            m_btnList.append(item);
            scene->addItem(item);
        }
    }

//    tempParam.insert(PSV::boundingRect,QRectF(420,150,80,80));
//    /*PSV_ButtonItem **/m_PSV_ButtonItem = new PSV_ButtonItem(tempParam);//
//    scene->addItem(m_PSV_ButtonItem);
//    m_PSV_ButtonItem->refreshItem();
    //==================================
    scene->setBackgroundBrush(QBrush(Qt::gray));
    view->setScene(scene);
    m_stackedWidget->addWidget(view);
    m_stackedWidget->setCurrentIndex(m_stackedWidget->count() - 1);
}

void MainWindow::itemIsChanged(QTreeWidgetItem *item, int /*index*/)
{
    if(item != NULL)
    {
        int tempIndex = item->data(0,m_dataRole).toInt();
        m_stackedWidget->setCurrentIndex(tempIndex);
    }
}

void MainWindow::updateView()
{
//    qDebug()<<"updateView";
    static int s_count = 0;
//    qDebug()<<"updateView"<<"s_count = "<<s_count;

//    if(m_PSV_ButtonItem)
//    {
////        QMap<int,QPair<QColor,QString> >stateMap;
////        stateMap.insert(0,QPair<QColor,QString>(QColor(Qt::darkBlue),"darkBlue"));
////        stateMap.insert(1,QPair<QColor,QString>(QColor(Qt::yellow),"yellow"));
////        stateMap.insert(2,QPair<QColor,QString>());
////        stateMap.insert(3,QPair<QColor,QString>();
////        stateMap.insert(4,QPair<QColor,QString>();
//        switch(s_count)
//        {
//        case 0:
//            m_PSV_ButtonItem->setStateColor(s_count,QColor(Qt::darkBlue),"darkBlue");
//            break;
//        case 1:
//            m_PSV_ButtonItem->setStateColor(s_count,QColor(Qt::yellow),"yellow");
//            break;
//        case 2:
//            m_PSV_ButtonItem->setStateColor(s_count,QColor(Qt::red),"red");
//            break;
//        case 3:
//            m_PSV_ButtonItem->setStateColor(s_count,QColor(Qt::green),"green");
//            break;
//        case 4:
//            m_PSV_ButtonItem->setStateColor(s_count,QColor(Qt::gray),"gray");
//            break;
//        default:
//            m_PSV_ButtonItem->setStateColor(s_count,QColor(Qt::darkGreen),"darkGreen");
//        }
//    }
//    m_PSV_ButtonItem->setCurrentState(s_count);
    int count = m_btnList.count();
    for(int i = 0; i < count; i++)
    {
        m_btnList.at(i)->setCurrentState((s_count + i) % 5);
    }
    s_count++;
    s_count %= 5;
}

void MainWindow::updateViewValue()
{
    int value = qrand() % 100;
    if(m_PSV_VerticalIndicatorItem)
    {
        m_PSV_VerticalIndicatorItem->setValue(value);
    }
    if(m_PSV_CircularIndicatorItem)
    {
        m_PSV_CircularIndicatorItem->setValue(value);
    }
}

void MainWindow::test()
{
    int value = qrand() % 100;
    if(m_PSV_CircularIndicatorItem)
    {
        m_PSV_CircularIndicatorItem->setValue(value);
    }
}

void MainWindow::on_btn_test_clicked()
{
    test();
}
