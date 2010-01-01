/*
 * Copyright (c) 2010, Sysu
 * ��������Ȩ����( All rights reserved. )
 * 
 * �ļ����ƣ�systrayicon.hxx
 * �ļ���ʶ��
 * ժ    Ҫ��
 * 
 * ��ǰ�汾��1.0
 * ��    �ߣ�Coolboy
 * ������ڣ�2010��1��1��
 *
 * ȡ���汾��
 * ԭ����  ��
 * ������ڣ�
 */
#pragma once
#include <QSystemTrayIcon>
#include <QQueue>

class QAction;
class QSystemTrayIcon;

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
    void showConfigDialog();

private:
    QString getDisplayText(QString);
    void saveSettings();

    QStringList strLst;
    QMenu *trayIconMenu;
    QAction *quitAction;
    QAction *configureAction;
    QAction *aboutAction;

    QString history_file_name;
    int history_max_size;
    int entry_display_max_size;
    bool clipboard_history_save;
};
