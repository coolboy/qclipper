/*
 * Copyright (c) 2009, Sysu
 * ��������Ȩ����( All rights reserved. )
 * 
 * �ļ����ƣ�PrefsDialog.h
 * �ļ���ʶ��
 * ժ    Ҫ��
 * 
 * ��ǰ�汾��1.0
 * ��    �ߣ�Coolboy
 * ������ڣ�2009��12��31��
 *
 * ȡ���汾��
 * ԭ����  ��
 * ������ڣ�
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
