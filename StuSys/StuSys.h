
// StuSys.h: PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// 主符号

#include <mysql.h>

#pragma comment(lib,"libmysql.lib")

// CStuSysApp:
// 有关此类的实现，请参阅 StuSys.cpp
//

class CStuSysApp : public CWinApp
{
public:
	CStuSysApp();

// 重写
public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()

	//初始化数据库
	int initMysql();

	//创建数据库
	int creatMysql();

	//创建表
	int createTable();

public:
	MYSQL m_mysql;
	virtual int ExitInstance();
};

extern CStuSysApp theApp;
