#include "StdAfx.h"

#include "systrayicon.hxx"

#include "qrc/qrc_QClip.cpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName("qlipper");
    app.setApplicationVersion("1.2");
    app.setOrganizationDomain("qlipper.org");
    app.setOrganizationName("Qlipper");

		QSettings::setDefaultFormat(QSettings::IniFormat);

    SystrayIcon mwin;
    mwin.show();
    app.setQuitOnLastWindowClosed(false);
    return app.exec();
}
