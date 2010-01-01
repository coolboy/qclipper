#ifndef SYSTRAYICON_H
#define SYSTRAYICON_H

#include <QSystemTrayIcon>
#include <QQueue>
//#include <QMap>
//#include <QClipboard>

class QAction;
class QSystemTrayIcon;


//class SystrayIcon : public QMainWindow
class SystrayIcon : public QSystemTrayIcon
{
    Q_OBJECT

public:
    SystrayIcon( QObject * parent = 0 );//SystrayIcon(QWidget *parent = 0);
    ~SystrayIcon();

private slots:
    void constructSystrayMenu();
    void clipTextClicked(int);
    void systrayClicked(QSystemTrayIcon::ActivationReason);
    void showAbout();
    void showTextEditDialog();

private:
    QString getDisplayText(QString);
    void saveSettings();

    QQueue<QString> queue;// QMap <int, QStringList> messages_map;
    QMenu *trayIconMenu;
    QAction *quitAction;
    QAction *configureAction;
    QAction *aboutAction;

    //QDialog *textEditDlg;

    QString history_file_name;
    int history_max_size;
    int entry_display_max_size;
    bool clipboard_history_save;
};

#endif // SYSTRAYICON_H
