#ifndef SELECTLIFTDLG_H
#define SELECTLIFTDLG_H

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class SelectLiftDlg;
}

class SelectLiftDlg : public QDialog
{
    Q_OBJECT

public:
    explicit SelectLiftDlg(QWidget *parent = 0);
    ~SelectLiftDlg();

public:
    std::vector<QString> arrValues;

private slots:
    void on_pushBtnSel_clicked();

    void on_pushBtnCancel_clicked();

private:
    Ui::SelectLiftDlg *ui;
};

#endif // SELECTLIFTDLG_H
