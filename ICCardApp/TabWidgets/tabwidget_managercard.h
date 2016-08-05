#ifndef TABWIDGET_MANAGERCARD_H
#define TABWIDGET_MANAGERCARD_H

#include <QTabWidget>

namespace Ui {
class TabWidget_ManagerCard;
}

class TabWidget_ManagerCard : public QTabWidget
{
    Q_OBJECT

public:
    explicit TabWidget_ManagerCard(QWidget *parent = 0);
    ~TabWidget_ManagerCard();

private:
    Ui::TabWidget_ManagerCard *ui;
};

#endif // TABWIDGET_MANAGERCARD_H
