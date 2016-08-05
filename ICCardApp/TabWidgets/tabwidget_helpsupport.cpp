#include "tabwidget_helpsupport.h"
#include "ui_tabwidget_helpsupport.h"

TabWidget_HelpSupport::TabWidget_HelpSupport(QWidget *parent) :
    QTabWidget(parent),
    ui(new Ui::TabWidget_HelpSupport)
{
    ui->setupUi(this);
}

TabWidget_HelpSupport::~TabWidget_HelpSupport()
{
    delete ui;
}
