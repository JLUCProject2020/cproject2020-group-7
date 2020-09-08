
// ManagerDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "btnst.h"
#include "UserManager.h"
#include "UserQuery.h"
#include "UserTotal.h"
#include "EwmCreate.h"
#include "EwmLoad.h"


// CManagerDlg �Ի���
class CManagerDlg : public CDialogEx
{
// ����
public:
	CManagerDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MANAGER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();

private:
	int OnInitChk(void);

public:
	// //������ʼ������������ҳ��
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
