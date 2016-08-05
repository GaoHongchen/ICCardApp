#ifndef TABWIDGET_OWNERCARD_H
#define TABWIDGET_OWNERCARD_H

#include <QTabWidget>

#include "../DataBase/sqldbmodel.h"

#include "../SubDlg/selectliftdlg.h"
#include "../SubDlg/selectfloordlg.h"

#include "../DataStructure/ds_usercard.h"

namespace Ui {
class TabWidget_OwnerCard;
}

class TabWidget_OwnerCard : public QTabWidget
{
    Q_OBJECT

public:
    explicit TabWidget_OwnerCard(QWidget *parent = 0);
    ~TabWidget_OwnerCard();

public:
    SqlDBModel *modelDBUsrCard;

    std::vector<QString> newcardArrValuesLiftInfos;
    int newcardLiftNum;
    std::map<int,QString> newcardMapFloorsA;

    std::vector<QString> datachangeArrValuesLiftInfos;
    int datachangeLiftNum;
    std::map<int,QString> datachangeMapFloorsA;

    std::vector<QString> reissueArrValuesLiftInfos;
    int reissueLiftNum;
    std::map<int,QString> reissueMapFloorsA;

private slots:
    void on_newcardPushBtnLiftNum1_clicked();

    void on_newcardPushBtnFloorNum1_clicked();

    void on_newcardPushBtnLiftNum2_clicked();

    void on_newcardPushBtnFloorNum2_clicked();

    void on_newcardPushBtnLiftNum3_clicked();

    void on_newcardPushBtnFloorNum3_clicked();

    void on_newcardPushBtnWrite_clicked();

    void on_datachangePushBtnLiftNum1_clicked();

    void on_datachangePushBtnLiftNum2_clicked();

    void on_datachangePushBtnLiftNum3_clicked();

    void on_datachangePushBtnFloorNum1_clicked();

    void on_datachangePushBtnFloorNum2_clicked();

    void on_datachangePushBtnFloorNum3_clicked();

    void on_datachangePushBtnFindUsr_clicked();

    void on_datachangePushBtnWrite_clicked();

    void on_reissuePushBtnLiftNum1_clicked();

    void on_reissuePushBtnLiftNum2_clicked();

    void on_reissuePushBtnLiftNum3_clicked();

    void on_reissuePushBtnFloorNum1_clicked();

    void on_reissuePushBtnFloorNum2_clicked();

    void on_reissuePushBtnFloorNum3_clicked();

    void on_reissuePushBtnFind_clicked();

    void on_reissuePushBtnWrite_clicked();

private:
    Ui::TabWidget_OwnerCard *ui;
};

#endif // TABWIDGET_OWNERCARD_H
