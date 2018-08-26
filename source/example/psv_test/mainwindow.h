#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include <QStackedWidget>
#include <QTreeWidgetItem>
#include <QTimer>
#include "psv_histogramitem.h"
#include "psv_graphicsscene.h"
#include "psv_graphicsview.h"
#include "psv_circularindicatoritem.h"
#include "psv_pie3item.h"
#include "psv_axisleftitem.h"
#include "psv_axisrightitem.h"
#include "psv_axisdownitem.h"
#include "psv_axisupitem.h"
#include "psv_tableitem.h"
#include "psv_pie3item.h"
#include "psv_chartitem.h"
#include "psv_charttimeitem.h"
#include "psv_chartdatetimeitem.h"
#include "psv_chartrealitem.h"
#include "psv_charthistogramitem.h"
#include "psv_chartareaitem.h"
#include "psv_tablewidgetitem.h"
#include "psv_painterpathitem.h"
#include "psv_verticalindicatoritem.h"
#include "psv_chartbaritem.h"
#include "psv_levelitem.h"
#include "psv_treeitem.h"
#include "psv_buttonitem.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void init();
    void addChartRealItem(const QString& title,const QMap<int, QVariant>& param);
    void addChartTimeItem(const QString& title,const QMap<int, QVariant>& param);
    void addChartDateTimeItem(const QString& title,const QMap<int, QVariant>& param);
    void addChartDateItem(const QString& title,const QMap<int, QVariant>& param);
    void addChartHistogramItem(const QString& title,const QMap<int, QVariant>& param);
    void addChartHistogramItemAdd(const QString& title,const QMap<int, QVariant>& param);//累计
    void addChartAreaItem(const QString& title,const QMap<int, QVariant>& param);
    void addPie3Item(const QString& title,const QMap<int, QVariant>& param);
    void addCircularIndicatorItem(const QString& title,const QMap<int, QVariant>& param);
    void addTableItem(const QString& title,const QMap<int, QVariant>& param);
    void addTableWidgetItem(const QString& title,const QMap<int, QVariant>& param);
    void addPainterPathItem(const QString& title,const QMap<int, QVariant>& param);
    void addVerticalIndicatorItem(const QString& title,const QMap<int, QVariant>& param);
    void addChartBarItem(const QString& title,const QMap<int, QVariant>& param);
    void addButtonItem(const QString& title,const QMap<int, QVariant>& param);

public slots:
    void itemIsChanged(QTreeWidgetItem *item,int index);
    void updateView();
    void updateViewValue();
    void test();
//    void test2();
//    void test3(const QString& text);
//    void testAll();
//    void testAll2();

private slots:
    void on_btn_test_clicked();

private:
    Ui::MainWindow *ui;
    QTimer m_timer;
    QTimer m_timer_value;

    PSV_GraphicsScene* m_scene;
    PSV_GraphicsView* m_view;

    QStackedWidget *m_stackedWidget;
    int m_dataRole;
    //=============================
    PSV_VerticalIndicatorItem *m_PSV_VerticalIndicatorItem;
    PSV_CircularIndicatorItem *m_PSV_CircularIndicatorItem;
    PSV_PainterPathItem *m_PSV_PainterPathItem;
//    PSV_ChartBarItem *m_PSV_ChartBarItem;
    QList<PSV_ButtonItem*> m_btnList;
//    PSV_ButtonItem * m_PSV_ButtonItem_1;
//    PSV_ButtonItem * m_PSV_ButtonItem_2;
//    PSV_ButtonItem * m_PSV_ButtonItem_3;
    QList<QColor> colorList;
};

#endif // MAINWINDOW_H
