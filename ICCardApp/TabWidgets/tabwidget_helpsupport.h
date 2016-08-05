#ifndef TABWIDGET_HELPSUPPORT_H
#define TABWIDGET_HELPSUPPORT_H

#include <QTabWidget>

namespace Ui {
class TabWidget_HelpSupport;
}

class TabWidget_HelpSupport : public QTabWidget
{
    Q_OBJECT

public:
    explicit TabWidget_HelpSupport(QWidget *parent = 0);
    ~TabWidget_HelpSupport();

private:
    Ui::TabWidget_HelpSupport *ui;
};

#endif // TABWIDGET_HELPSUPPORT_H
