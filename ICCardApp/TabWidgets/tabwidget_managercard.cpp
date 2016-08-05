#include "tabwidget_managercard.h"
#include "ui_tabwidget_managercard.h"

TabWidget_ManagerCard::TabWidget_ManagerCard(QWidget *parent) :
    QTabWidget(parent),
    ui(new Ui::TabWidget_ManagerCard)
{
    ui->setupUi(this);

    ui->dateEdit11->setDate(QDate::currentDate());
    ui->dateEdit12->setDate(QDate::currentDate());
    ui->dateEdit21->setDate(QDate::currentDate());
    ui->dateEdit22->setDate(QDate::currentDate());
    ui->dateEdit31->setDate(QDate::currentDate());
    ui->dateEdit32->setDate(QDate::currentDate());
}

TabWidget_ManagerCard::~TabWidget_ManagerCard()
{
    delete ui;
}
