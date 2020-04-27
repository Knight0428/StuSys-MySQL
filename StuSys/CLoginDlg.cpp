// CLoginDlg.cpp: 实现文件
//

#include "pch.h"
#include "StuSys.h"
#include "CLoginDlg.h"
#include "afxdialogex.h"


// CLoginDlg 对话框

IMPLEMENT_DYNAMIC(CLoginDlg, CDialogEx)

CLoginDlg::CLoginDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CLoginDlg, pParent)
	, m_csAccount(_T("admin"))
	, m_csPassword(_T("12345"))
{

}

CLoginDlg::~CLoginDlg()
{
}

void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, EDIT_ACCOUNT, m_csAccount);
	DDX_Text(pDX, EDIT_PASSWORD, m_csPassword);
}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CLoginDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CLoginDlg 消息处理程序


void CLoginDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码

	UpdateData(TRUE);
	if (m_csAccount.IsEmpty() || m_csPassword.IsEmpty())
	{
		AfxMessageBox("账号或密码不能为空");
		return;
	}

	//查询数据库的账号密码
	CString csSQL;
	csSQL.Format("select *from t_user where account = '%s' and password = '%s'", m_csAccount, m_csPassword);
	CStuSysApp* pApp = (CStuSysApp*)AfxGetApp();
	int result = mysql_query(&pApp->m_mysql, csSQL);

	//查询失败则退出，重新输
	if (result != 0)
	{
		CString csErrMsg = "mysql_query ";
		csErrMsg += mysql_error(&pApp->m_mysql);
		AfxMessageBox(csErrMsg);
		return;
	}

	//查询成功，再用结果函数判断是否有此账号密码，然后进入主界面
	result = mysql_affected_rows(&pApp->m_mysql);
	MYSQL_RES* res = mysql_store_result(&pApp->m_mysql);
	int nRows = mysql_num_rows(res);
	if (nRows < 1)
	{
		AfxMessageBox("账号或密码错误");
		return;
	}

	CDialogEx::OnOK();
}
