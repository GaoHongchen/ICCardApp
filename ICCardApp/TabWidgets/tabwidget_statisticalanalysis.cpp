#include "tabwidget_statisticalanalysis.h"
#include "ui_tabwidget_statisticalanalysis.h"

TabWidget_StatisticalAnalysis::TabWidget_StatisticalAnalysis(QWidget *parent) :
    QTabWidget(parent),
    ui(new Ui::TabWidget_StatisticalAnalysis)
{
    ui->setupUi(this);
}

TabWidget_StatisticalAnalysis::~TabWidget_StatisticalAnalysis()
{
    delete ui;
}
