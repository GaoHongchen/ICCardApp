#ifndef TABWIDGET_FUNCTIONCARD_H
#define TABWIDGET_FUNCTIONCARD_H

#include <QTabWidget>
#include <QMessageBox>

#include "CH375/ch375rw.h"

#include "../DataStructure/ds_timesetting.h"
#include "../DataStructure/ds_enablecard.h"
#include "../DataStructure/ds_sysswitchcard.h"

#include "../SubDlg/selectliftdlg.h"
#include "../SubDlg/selectfloordlg.h"
#include "../SubDlg/selectsysswitchdlg.h"

namespace Ui {
class TabWidget_FunctionCard;
}

class TabWidget_FunctionCard : public QTabWidget
{
    Q_OBJECT

public:
    explicit TabWidget_FunctionCard(QWidget *parent = 0);
    ~TabWidget_FunctionCard();

public:
    std::vector<QString> enablecardArrValuesLiftInfos;
    int enablecardLiftNum;
    std::vector<QString> sysswitchArrValuesLiftInfos;
    int sysswitchLiftNum;
    std::map<int,QString> sysswitchMapFloorsA;

private slots:
    void on_timesetPushBtnWrite_clicked();
    void on_ClearMemoryPushBtnWrite_clicked();

    void on_addrsetPushBtn_clicked();

    void on_enablecardPushBtnWrite_clicked();

    void on_enablecardRadioBtnCardNum_toggled(bool checked);

    void on_enablecardRadioBtnRoomNum_toggled(bool checked);

    void on_enablecardPushBtnSelLift_clicked();

    void on_sysswitchRadioBtnSys_toggled(bool checked);

    void on_sysswitchRadioBtnLayer_toggled(bool checked);

    void on_sysswitchRadioBtnCommonFloor_toggled(bool checked);

    void on_sysswitchPushBtnLift_clicked();

    void on_sysswitchPushBtnFloor_clicked();

    void on_sysswitchPushBtnFind_clicked();

    void on_sysswitchPushBtnReissue_clicked();

    void on_sysswitchPushBtnWrite_clicked();

private:
    Ui::TabWidget_FunctionCard *ui;
};

#endif // TABWIDGET_FUNCTIONCARD_H
