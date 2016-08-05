#ifndef TABWIDGET_REMOTEOPERATION_H
#define TABWIDGET_REMOTEOPERATION_H

#include <QTabWidget>

namespace Ui {
class TabWidget_RemoteOperation;
}

class TabWidget_RemoteOperation : public QTabWidget
{
    Q_OBJECT

public:
    explicit TabWidget_RemoteOperation(QWidget *parent = 0);
    ~TabWidget_RemoteOperation();

private:
    Ui::TabWidget_RemoteOperation *ui;
};

#endif // TABWIDGET_REMOTEOPERATION_H
