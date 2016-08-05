#ifndef TABWIDGET_STATISTICALANALYSIS_H
#define TABWIDGET_STATISTICALANALYSIS_H

#include <QTabWidget>

namespace Ui {
class TabWidget_StatisticalAnalysis;
}

class TabWidget_StatisticalAnalysis : public QTabWidget
{
    Q_OBJECT

public:
    explicit TabWidget_StatisticalAnalysis(QWidget *parent = 0);
    ~TabWidget_StatisticalAnalysis();

private:
    Ui::TabWidget_StatisticalAnalysis *ui;
};

#endif // TABWIDGET_STATISTICALANALYSIS_H
