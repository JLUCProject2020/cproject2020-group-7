#pragma once
#include "UserAdd.h"
#include "UserEdit.h"
#include "UserDel.h"
#include "UserStatusAdd.h"
#include "UserStatusEdit.h"
#include "UserStatusDel.h"

#include "afxcmn.h"

// CUserManager �Ի���

class CUserManager : public CDialogEx
{
	DECLARE_DYNAMIC(CUserManager)

public:
	CUserManager(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CUserManager();

// �Ի�������
	enum { IDD = IDD_MANAGER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CUserAdd m_UserAddDlg;
	CUserEdit m_UserEditDlg;
	CUserDel m_UserDelDlg;
	CUserStatusAdd m_UserStatusDlg;
	CUserStatusEdit m_UserStatusEditDlg;
	CUserStatusDel m_UserStatusDelDlg;
	

	afx_msg void OnBnClickedAdd();
	afx_msg void OnBnClickedEdit();
	afx_msg void OnBnClickedDel();
	virtual BOOL OnInitDialog();
	CListCtrl m_UserList;
	CListCtrl m_UserStatusList;
	afx_msg void OnBnClickedUserStatusAdd();
	afx_msg void OnBnClickedUserStatusEdit();
	afx_msg void OnBnClickedUserStatusDel();
};
