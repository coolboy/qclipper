/*
 * Copyright (c) 2010, Sysu
 * 保留所有权利。( All rights reserved. )
 * 
 * 文件名称：systrayicon.hxx
 * 文件标识：
 * 摘    要：
 * 
 * 当前版本：1.0
 * 作    者：Coolboy
 * 完成日期：2010年1月1日
 *
 * 取代版本：
 * 原作者  ：
 * 完成日期：
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
