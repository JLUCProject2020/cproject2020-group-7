
// ManagerDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "btnst.h"
#include "UserManager.h"
#include "UserQuery.h"
#include "UserTotal.h"
#include "EwmCreate.h"
#include "EwmLoad.h"


// CManagerDlg 对话框
class CManagerDlg : public CDialogEx
{
// 构造
public:
	CManagerDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MANAGER_DIALOG };

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

private:
	int OnInitChk(void);

public:
	// //用来初始化６个工作区页面
	int OnInitPage(void);

	DECLARE_MESSAGE_MAP()
	afx_msg void OnBnClickedChoosestc();
	CStatic m_ChooseStc;
	CStatic m_WorkStc;
	CButtonST m_ManagerChk;
	CButtonST m_CheckChk;
	CButtonST m_TotalChk;
	CButtonST m_ManChk;
	CButtonST m_EwmYyChk;
	CButtonST m_CancelBtn;

	CUserManager m_UserManager;
	CUserQuery	 m_UserQuery;
	CUserTotal   m_UserTotal;
	CEwmCreate	 m_EwmCreate;
	CEwmLoad	 m_EvmLoad;
	afx_msg void OnBnClickedManager();
	afx_msg void OnBnClickedCheck();
	afx_msg void OnBnClickedTotal();
	afx_msg void OnBnClickedDeleteuserchk();
	afx_msg void OnBnClickedEwmYy();
	
	afx_msg void OnBnClickedCancelBtn();
};
