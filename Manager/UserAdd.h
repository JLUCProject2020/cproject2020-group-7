#pragma once
#include "afxwin.h"


// CUserAdd �Ի���

class CUserAdd : public CDialogEx
{
	DECLARE_DYNAMIC(CUserAdd)

public:
	CUserAdd(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CUserAdd();

// �Ի�������
	enum { IDD = IDD_USER_ADD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_user_name;
	int m_age;
	CComboBox m_sex;
	int m_nSex;
	CString m_sfz;
	CString m_phone;
	CComboBox m_status;
	int  m_nStatus;
	CString m_addr;



	bool CheckID(CString ID_num);
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
};
