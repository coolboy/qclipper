#ifndef SETTINGSINFO_H
#define SETTINGSINFO_H

#include <QSettings>
#include <QFileInfo>
#include <QString>

class SettingsInfo {
public:
                static QString fileName()
                {
                    QSettings appSettings;
                    return appSettings.fileName();
                }

                static QString configDir()
                {
                    QSettings appSettings;
                    QFileInfo location(appSettings.fileName());
                    return location.path();
                }
};

#endif // SETTINGSINFO_H
