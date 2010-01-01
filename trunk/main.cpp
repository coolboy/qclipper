#include "StdAfx.h"

#include "systrayicon.hxx"

#include "qrc/qrc_QClip.cpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("qlipper");
    a.setApplicationVersion("1.2");
    a.setOrganizationDomain("qlipper.org");
    a.setOrganizationName("Qlipper");

		QSettings::setDefaultFormat(QSettings::IniFormat);

    SystrayIcon w;
    w.show();
    a.setQuitOnLastWindowClosed(false);
    return a.exec();
}
