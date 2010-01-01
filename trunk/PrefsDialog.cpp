#include "StdAfx.h"
#include "PrefsDialog.hxx"

#include <QSettings>
#include "moc/moc_PrefsDialog.cpp"
PrefsDialog::PrefsDialog(QWidget * parent, Qt::WFlags f)
        : QDialog(parent, f)
{
    setupUi(this);

    QSettings settings;
    settings.beginGroup("MAIN");
     spEntryWidth->setValue(settings.value("entry_display_max_size", 60).toInt());
     spHistoryCount->setValue(settings.value("history_max_size", 10).toInt());
     cbClipboardSave->setChecked(settings.value("clipboard_history_save", true).toBool());
    settings.endGroup();
}

