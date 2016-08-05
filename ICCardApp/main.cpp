#include "mainwindow.h"
#include "dialogsignin.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //QString str=QApplication::applicationDirPath();
    //QApplication::addLibraryPath(str);
    QApplication::setStyle("windowsxp");


    DialogSignin dlgSignin;
    if(dlgSignin.exec()==QDialog::Accepted)
    {
        MainWindow mainWnd;
        //mainWnd.strUsrName = dlgSignin.strUsrName;
        //mainWnd.strUsrLevel = dlgSignin.strUsrLevel;
        mainWnd.showMaximized();
        //w.show();
        a.installNativeEventFilter(&mainWnd);
        return a.exec();
    }
    else
    {
        return 0;
    }

    return a.exec();
}
