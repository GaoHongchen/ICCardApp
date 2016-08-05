#include "tabwidget_remoteoperation.h"
#include "ui_tabwidget_remoteoperation.h"

TabWidget_RemoteOperation::TabWidget_RemoteOperation(QWidget *parent) :
    QTabWidget(parent),
    ui(new Ui::TabWidget_RemoteOperation)
{
    ui->setupUi(this);

    ui->dateTimeEdit11->setDateTime(QDateTime::currentDateTime());
}

TabWidget_RemoteOperation::~TabWidget_RemoteOperation()
{
    delete ui;
}
