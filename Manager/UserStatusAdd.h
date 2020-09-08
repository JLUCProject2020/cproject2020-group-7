#pragma once
#include "afxwin.h"


// CUserStatusAdd �Ի���

class CUserStatusAdd : public CDialogEx
{
	DECLARE_DYNAMIC(CUserStatusAdd)

public:
	CUserStatusAdd(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CUserStatusAdd();

// �Ի�������
	enum { IDD = IDD_USER_STATUS_ADD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_user_name;
	CString m_begin_time;
	CString m_end_time;
	CString m_begin_addr;
	CString m_end_addr;
	CComboBox m_tool;
	int m_nTool;
	CString m_tool_info;
	CComboBox m_is_olace;
	int m_nOlace;
	CComboBox m_is_infect;
	int m_nInfect;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
};
