#include "StdAfx.h"

#include "systrayicon.hxx"
#include "SettingsInfo.hxx"
#include "PrefsDialog.hxx"

#include <QSignalMapper>

#include "moc/moc_systrayicon.cpp"


SystrayIcon::SystrayIcon(QObject * parent) : QSystemTrayIcon (parent)
{
	// Get Settings from config file
	QSettings settings;
	settings.beginGroup("MAIN");
	entry_display_max_size = settings.value("entry_display_max_size", 60).toInt();
	history_max_size = settings.value("history_max_size", 10).toInt();
	clipboard_history_save = settings.value("clipboard_history_save", true).toBool();
	settings.endGroup();

	if (!QFile::exists(SettingsInfo::configDir()))
	{        
		saveSettings();
		if (!QFile::exists(SettingsInfo::configDir()))
		{
			qDebug("could not write conf file");
			exit( -1 );
		}
	}    

	history_file_name = QString("%1/%2").arg(SettingsInfo::configDir()).arg("history.log");

	quitAction = new QAction( QIcon(":images/exit.png"), tr("&Quit"), this);
	connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));

	configureAction = new QAction( QIcon(":images/configure.png"), tr("&Configure"), this);
	connect(configureAction, SIGNAL(triggered()), this, SLOT(showTextEditDialog()));

	aboutAction = new QAction( QIcon(":images/info.png"), tr("&About"), this);
	connect(aboutAction, SIGNAL(triggered()), this, SLOT(showAbout()));

	// Restore clipboard history frome file
	QFile file(history_file_name); //QFile file("history.log");
	if (file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		QTextStream in(&file);
		QString buffer = in.readAll();
		QStringList strlst = buffer.split("--SEPARATOR--");

		for (int i = 0; i < strlst.size(); ++i)
		{
			//qDebug() << qPrintable(strlst.at(i).simplified()) ;
			queue.enqueue(strlst.at(i));
		}

		file.close();
	}

	setIcon(QIcon(":images/klipper_dock.png"));
	setToolTip(tr("Qlipper - a clipboard history without KDE"));
	constructSystrayMenu();
	//setContextMenu(trayIconMenu);

	QClipboard *clipboard = QApplication::clipboard();

	connect( clipboard, SIGNAL(dataChanged()), this, SLOT( constructSystrayMenu() ) );
	connect( this, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT( systrayClicked(QSystemTrayIcon::ActivationReason) ) );
}

void SystrayIcon::constructSystrayMenu()
{
	//qDebug("initSystrayMenu");

	// Add new clipboard entry in menu list
	QClipboard *clipboard = QApplication::clipboard();
	if (!clipboard->text().isEmpty())
	{
		queue.enqueue(clipboard->text());

		// check for duplicates
		for (int i = 0; i < queue.size()-1; ++i)
		{
			if (clipboard->text() == queue.at(i))
			{
				queue.removeAt(i); //qDebug("removed !");
				//break;
			}
		}
	}

	// check maximum entries limit
	if (queue.size()>history_max_size)
		queue.dequeue();

	// format display for entry
	QString clipText = "";
	/*
	QString clipText = clipboard->text().simplified();
	if ( clipText.size() > 60 )
	clipText = clipText.left(60) + " ...";
	*/

	trayIconMenu = new QMenu(/*this*/);
	//stuffAction = new QAction(  clipText, this);
	//connect(stuffAction, SIGNAL(triggered()), qApp, SLOT(quit()));
	//trayIconMenu->addAction(stuffAction);
	//trayIconMenu->addSeparator();

	QSignalMapper *signalMapper = new QSignalMapper(this);
	connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(clipTextClicked(int)));
	for (int j = 0; j < queue.size(); ++j)
	{
		clipText = getDisplayText( queue.at( queue.size()-j-1) ); // clipText = queue.at(j) + "kk";
		QAction * actionT = new QAction( clipText, this );
		signalMapper->setMapping(actionT, queue.size()-j-1); // signalMapper->setMapping(actionT, j);
		connect( actionT, SIGNAL( triggered() ), signalMapper, SLOT( map() ) );
		trayIconMenu->addAction(actionT);
	}

	trayIconMenu->addSeparator();
	trayIconMenu->addAction(configureAction);
	trayIconMenu->addAction(aboutAction);
	trayIconMenu->addSeparator();
	trayIconMenu->addAction(quitAction);
	setContextMenu(trayIconMenu);
}

void SystrayIcon::systrayClicked(QSystemTrayIcon::ActivationReason reason)
{
	switch	( reason )
	{
	case QSystemTrayIcon::DoubleClick:
		break;
	case QSystemTrayIcon::Trigger:
		trayIconMenu->exec(QCursor::pos());
		break;
	case QSystemTrayIcon::MiddleClick:
		break;
	case QSystemTrayIcon::Context:
		//showAbout();
		break;
	case QSystemTrayIcon::Unknown:
		//showAbout();
		qDebug("QSystemTrayIcon : Activated for Unknown reason");
		break;
	}
}

QString SystrayIcon::getDisplayText(QString str)
{
	QString clipText = str.simplified();
	if ( clipText.size() > entry_display_max_size )
		clipText = clipText.left(entry_display_max_size) + " ...";

	return clipText;
}

void SystrayIcon::clipTextClicked(int idx)
{
	qDebug() << "clipTextClicked " << qPrintable(QString::number(idx));
	QClipboard *clipboard = QApplication::clipboard();
	clipboard->setText(queue.at(idx));
}

void SystrayIcon::showAbout()
{
	QMessageBox::information(0, tr("Qlipper"), tr("Clipboard history without KDE.\n\n(c) 2010-2011 thierry deseez"));
	return;

	QMessageBox msgBox;
	msgBox.setText("The document has been modified.");
	msgBox.setInformativeText("Do you want to save your changes?");
	msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
	msgBox.setDefaultButton(QMessageBox::Save);
	int ret = msgBox.exec();
	if (ret==QMessageBox::Save)
		qDebug("Must Save message");
}

void SystrayIcon::showTextEditDialog()
{
	PrefsDialog *dlg = new PrefsDialog();
	dlg->setAttribute (Qt::WA_DeleteOnClose);

	if (dlg->exec() == QDialog::Accepted)
	{
		entry_display_max_size = dlg->spEntryWidth->value();
		history_max_size = dlg->spHistoryCount->value();
		clipboard_history_save = dlg->cbClipboardSave->isChecked();
		saveSettings();
	}
}

void SystrayIcon::saveSettings()
{
	QSettings settings;
	settings.beginGroup("MAIN");
	settings.setValue("entry_display_max_size", entry_display_max_size);
	settings.setValue("history_max_size", history_max_size);
	settings.setValue("clipboard_history_save", clipboard_history_save);
	settings.endGroup();
}

SystrayIcon::~SystrayIcon()
{
	qDebug() << "Bye";
	if (clipboard_history_save == true)
	{
		QFile logfile (history_file_name);
		QTextStream ts( &logfile );
		if (logfile.open(QFile::WriteOnly | QFile::Text))
		{
			for (int i = 0; i < queue.size(); ++i)
			{
				if (i == queue.size()-1)
					ts << queue.at(i);
				else
					ts << queue.at(i) << "--SEPARATOR--";
			}
			logfile.close();
		}
	}
}
