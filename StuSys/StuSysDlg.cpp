
// StuSysDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "StuSys.h"
#include "StuSysDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CStuSysDlg 对话框



CStuSysDlg::CStuSysDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_STUSYS_DIALOG, pParent)
	, m_csStuID(_T(""))
	, m_csStuName(_T(""))
	, m_csStuClass(_T(""))
	, m_csStuSex(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CStuSysDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_listCtrl);
	DDX_Text(pDX, EDIT_NO, m_csStuID);
	DDX_Text(pDX, EDIT_NAME, m_csStuName);
	DDX_Text(pDX, EDIT_CLASS, m_csStuClass);
	DDX_Text(pDX, EDIT_SEX, m_csStuSex);
}

BEGIN_MESSAGE_MAP(CStuSysDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(BTN_QUERY, &CStuSysDlg::OnBnClickedQuery)
	ON_BN_CLICKED(BTN_ADD, &CStuSysDlg::OnBnClickedAdd)
	ON_BN_CLICKED(BTN_DEL, &CStuSysDlg::OnBnClickedDel)
	ON_BN_CLICKED(BTN_ALTER, &CStuSysDlg::OnBnClickedAlter)
END_MESSAGE_MAP()


// CStuSysDlg 消息处理程序

BOOL CStuSysDlg::OnInitDialog()
{
	CLoginDlg dlg;
	if (dlg.DoModal()==IDCANCEL)
	{
		EndDialog(0);
		return FALSE;
	}

	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CStuSysDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}

	initControl();
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CStuSysDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CStuSysDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



// 初始化控件
int CStuSysDlg::initControl()
{
	// TODO: 在此处添加实现代码.
	return 0;
}


void CStuSysDlg::OnBnClickedQuery()
{
	// TODO: 在此添加控件通知处理程序代码

	CStuSysApp* pApp = (CStuSysApp*)AfxGetApp();

	UpdateData(TRUE);

	//清除列表数据
	m_listCtrl.DeleteAllItems();

	//查询语法
	CString csSQL;
	csSQL.Format("select *from t_student where 1=1");

	if (!m_csStuID.IsEmpty())
	{
		csSQL += " and sid = '" + m_csStuID + "'";
	}
	if (!m_csStuName.IsEmpty())
	{
		csSQL += " and sname = '" + m_csStuName + "'";
	}
	if (!m_csStuClass.IsEmpty())
	{
		csSQL += " and cid = '" + m_csStuClass + "'";
	}
	if (!m_csStuSex.IsEmpty())
	{
		csSQL += " and ssex = '" + m_csStuSex + "'";
	}

	int result = mysql_query(&pApp->m_mysql, csSQL);

	//查询失败则退出，重新输
	if (result != 0)
	{
		CString csErrMsg = "mysql_query ";
		csErrMsg += mysql_error(&pApp->m_mysql);
		AfxMessageBox(csErrMsg);
		return;
	}

	//查询成功，保存结果，输出
	MYSQL_RES* res = mysql_store_result(&pApp->m_mysql);
	//long long nRows = mysql_num_rows(res);

	//遍历字段
	//遍历列表，清空
	int nCount = m_listCtrl.GetHeaderCtrl()->GetItemCount();
	for (int i = 0; i < nCount; i++)
	{
		m_listCtrl.DeleteColumn(0);
	}
	//插入字段
	int nPos = 0;
	MYSQL_FIELD* field = NULL;
	while ((field = mysql_fetch_field(res)))
	{
		m_listCtrl.InsertColumn(nPos, field->name, LVCFMT_RIGHT, 100);
		nPos++;
	}
	//插入数据
	nPos = 0;
	MYSQL_ROW row;
	int num_fields = mysql_num_fields(res);
	while ((row = mysql_fetch_row(res)))
	{
		unsigned long* lengths;
		lengths = mysql_fetch_lengths(res);
		//列表控件要先插入第一行，后面才能继续插入
		m_listCtrl.InsertItem(nPos, "item");
		for (int i = 0; i < num_fields; i++)
		{
			m_listCtrl.SetItemText(nPos, i, row[i] ? row[i] : "NULL");
		}
		nPos++;
	}

	mysql_free_result(res);

}


void CStuSysDlg::OnBnClickedAdd()
{
	// TODO: 在此添加控件通知处理程序代码

	CStuSysApp* pApp= (CStuSysApp*)AfxGetApp();

	UpdateData(TRUE);
	if (m_csStuID.IsEmpty())
	{
		AfxMessageBox("请输入学号");
		return;
	}
	if (m_csStuName.IsEmpty())
	{
		AfxMessageBox("请输入姓名");
		return;
	}
	if (m_csStuClass.IsEmpty())
	{
		AfxMessageBox("请输入班级");
		return;
	}
	if (m_csStuSex.IsEmpty())
	{
		AfxMessageBox("请输入性别");
		return;
	}
	if (m_csStuSex != "男" && m_csStuSex != "女" && m_csStuSex != "未知")
	{
		AfxMessageBox("请输入性别为：男，女或未知");
		return;
	}
	//插入数据
	CString csSQL;
	csSQL.Format("insert into t_student values('%s', '%s', '%s', '%s')",
		m_csStuID, m_csStuName, m_csStuClass, m_csStuSex);

	//检查是否插入成功
	int result = mysql_query(&pApp->m_mysql, csSQL);
	if (result != 0)
	{
		CString csErrMsg = "mysql_query ";
		csErrMsg += mysql_error(&pApp->m_mysql);
		AfxMessageBox(csErrMsg);
		return;
	}
	else
		AfxMessageBox("插入成功");

}


void CStuSysDlg::OnBnClickedDel()
{
	// TODO: 在此添加控件通知处理程序代码

	CStuSysApp* pApp = (CStuSysApp*)AfxGetApp();

	UpdateData(TRUE);

	if (m_csStuID.IsEmpty() && m_csStuName.IsEmpty() && m_csStuClass.IsEmpty() && m_csStuSex.IsEmpty())
	{
		AfxMessageBox("请输入删除学生的信息");
		return;
	}

	//删除语法
	CString csSQL;
	csSQL.Format("delete from t_student where 1=1");

	if (!m_csStuID.IsEmpty())
	{
		csSQL += " and sid = '" + m_csStuID + "'";
	}
	if (!m_csStuName.IsEmpty())
	{
		csSQL += " and sname = '" + m_csStuName + "'";
	}
	if (!m_csStuClass.IsEmpty())
	{
		csSQL += " and cid = '" + m_csStuClass + "'";
	}
	if (!m_csStuSex.IsEmpty())
	{
		csSQL += " and ssex = '" + m_csStuSex + "'";
	}

	int result = mysql_query(&pApp->m_mysql, csSQL);

	//删除失败则退出，重新输
	if (result != 0)
	{
		CString csErrMsg = "mysql_query ";
		csErrMsg += mysql_error(&pApp->m_mysql);
		AfxMessageBox(csErrMsg);
		return;
	}

	//检查是否删除成功
	result = mysql_affected_rows(&pApp->m_mysql);
	if (result < 1)
	{
		AfxMessageBox("删除目标不存在");
		return;
	}
	else
	{
		AfxMessageBox("删除成功");
	}

}


void CStuSysDlg::OnBnClickedAlter()
{
	// TODO: 在此添加控件通知处理程序代码

	CStuSysApp* pApp = (CStuSysApp*)AfxGetApp();

	UpdateData(TRUE);

	if (m_csStuID.IsEmpty())
	{
		AfxMessageBox("请输入修改学生的学号");
		return;
	}
	if (m_csStuName.IsEmpty())
	{
		AfxMessageBox("请输入姓名");
		return;
	}
	if (m_csStuClass.IsEmpty())
	{
		AfxMessageBox("请输入班级");
		return;
	}
	if (m_csStuSex.IsEmpty())
	{
		AfxMessageBox("请输入性别");
		return;
	}
	if (m_csStuSex != "男" && m_csStuSex != "女" && m_csStuSex != "未知")
	{
		AfxMessageBox("请输入性别为：男，女或未知");
		return;
	}

	//修改语法
	CString csSQL;
	csSQL.Format("UPDATE t_student set sname = '%s' , cid = '%s' , ssex = '%s' where sid = '%s'", 
		m_csStuName, m_csStuClass, m_csStuSex, m_csStuID);

	int result = mysql_query(&pApp->m_mysql, csSQL);

	//语法执行失败则退出，重新输
	if (result != 0)
	{
		CString csErrMsg = "mysql_query ";
		csErrMsg += mysql_error(&pApp->m_mysql);
		AfxMessageBox(csErrMsg);
		return;
	}

	//检查修改是否成功
	result = mysql_affected_rows(&pApp->m_mysql);
	if (result < 1)
	{
		AfxMessageBox("修改失败");
		return;
	}
	else
	{
		AfxMessageBox("修改成功");
	}

}
