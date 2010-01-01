/*
 * Copyright (c) 2009, Sysu
 * 保留所有权利。( All rights reserved. )
 * 
 * 文件名称：PrefsDialog.h
 * 文件标识：
 * 摘    要：
 * 
 * 当前版本：1.0
 * 作    者：Coolboy
 * 完成日期：2009年12月31日
 *
 * 取代版本：
 * 原作者  ：
 * 完成日期：
 */
#pragma once

#include "uic/ui_settings.h"

class PrefsDialog:public QDialog, public Ui::Dialog
{
	Q_OBJECT

public:
	PrefsDialog(QWidget * parent = 0, Qt::WFlags f = 0);
	~PrefsDialog(){}
};
