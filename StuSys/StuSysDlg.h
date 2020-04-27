
// StuSysDlg.h: 头文件
//

#pragma once
#include "CLoginDlg.h"


// CStuSysDlg 对话框
class CStuSysDlg : public CDialogEx
{
// 构造
public:
	CStuSysDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_STUSYS_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	// 初始化控件
	int initControl();
	CListCtrl m_listCtrl;
	afx_msg void OnBnClickedQuery();
	CString m_csStuID;
	CString m_csStuName;
	CString m_csStuClass;
	CString m_csStuSex;
	afx_msg void OnBnClickedAdd();
	afx_msg void OnBnClickedDel();
	afx_msg void OnBnClickedAlter();
};
