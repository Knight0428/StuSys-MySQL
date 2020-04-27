
// StuSys.cpp: 定义应用程序的类行为。
//

#include "pch.h"
#include "framework.h"
#include "StuSys.h"
#include "StuSysDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CStuSysApp

BEGIN_MESSAGE_MAP(CStuSysApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CStuSysApp 构造

CStuSysApp::CStuSysApp()
{
	// 支持重新启动管理器
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的 CStuSysApp 对象

CStuSysApp theApp;


// CStuSysApp 初始化

BOOL CStuSysApp::InitInstance()
{
	//初始化MYSQL失败，退出进程
	if (initMysql() < 0)
	{
		return FALSE;
	}


	//创建数据库失败
	//if (creatMysql() < 0)
	//{
	//	return FALSE;
	//}

	//创建表失败
	//if (createTable() < 0)
	//{
	//	return FALSE;
	//}

	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。  否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// 创建 shell 管理器，以防对话框包含
	// 任何 shell 树视图控件或 shell 列表视图控件。
	CShellManager *pShellManager = new CShellManager;

	// 激活“Windows Native”视觉管理器，以便在 MFC 控件中启用主题
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));

	CStuSysDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: 在此放置处理何时用
		//  “确定”来关闭对话框的代码
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 在此放置处理何时用
		//  “取消”来关闭对话框的代码
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "警告: 对话框创建失败，应用程序将意外终止。\n");
		TRACE(traceAppMsg, 0, "警告: 如果您在对话框上使用 MFC 控件，则无法 #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS。\n");
	}

	// 删除上面创建的 shell 管理器。
	if (pShellManager != nullptr)
	{
		delete pShellManager;
	}

#if !defined(_AFXDLL) && !defined(_AFX_NO_MFC_CONTROLS_IN_DIALOGS)
	ControlBarCleanUp();
#endif

	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	//  而不是启动应用程序的消息泵。


	return FALSE;
}



int CStuSysApp::initMysql()
{
	// TODO: 在此处添加实现代码.

	//初始化
	if (mysql_init(&m_mysql) == NULL)
	{
		CString csErrMsg = "mysql_init ";
		csErrMsg += mysql_error(&m_mysql);
		AfxMessageBox(csErrMsg);
		//数据库初始化失败
		return -1;
	}

	//设置字符集
	mysql_set_character_set(&m_mysql, "gbk");

	//连接数据库
	if (mysql_real_connect(&m_mysql, "localhost", "root", "root",
		"student", 3306, NULL, 0) == NULL)
	{
		CString csErrMsg = "mysql_real_connect ";
		csErrMsg += mysql_error(&m_mysql);
		AfxMessageBox(csErrMsg);
		mysql_close(&m_mysql);
		return -1;
	}

	return 0;
}


int CStuSysApp::creatMysql()
{
	// TODO: 在此处添加实现代码.

	if (mysql_query(&m_mysql, "CREATE DATABASE IF NOT EXISTS student") != 0)
	{
		AfxMessageBox(mysql_error(&m_mysql));
		do
		{
			MYSQL_RES* res = mysql_store_result(&m_mysql);
			if (res != NULL)
			{
				mysql_free_result(res);
			}
		} while (!mysql_next_result(&m_mysql));

		return -1;
	}

	do
	{
		MYSQL_RES* res = mysql_store_result(&m_mysql);
		if (res != NULL)
		{
			mysql_free_result(res);
		}
	} while (!mysql_next_result(&m_mysql));

	return 0;
}


int CStuSysApp::createTable()
{
	// TODO: 在此处添加实现代码.

	if (mysql_query(&m_mysql, "create TABLE IF NOT EXISTS student.t_student (sid varchar(64) PRIMARY KEY, sname varchar(64), cid varchar(64), ssex varchar(64))") != 0)
	{
		AfxMessageBox(mysql_error(&m_mysql));
		do
		{
			MYSQL_RES* res = mysql_store_result(&m_mysql);
			if (res != NULL)
			{
				mysql_free_result(res);
			}
		} while (!mysql_next_result(&m_mysql));
		return -1;
	}

	do
	{
		MYSQL_RES* res = mysql_store_result(&m_mysql);
		if (res != NULL)
		{
			mysql_free_result(res);
		}
	} while (!mysql_next_result(&m_mysql));

	return 0;
}

//重写虚函数，软件退出也要退数据库
int CStuSysApp::ExitInstance()
{
	// TODO: 在此添加专用代码和/或调用基类

	mysql_close(&m_mysql);

	return CWinApp::ExitInstance();
}
