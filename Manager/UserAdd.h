#pragma once
#include "afxwin.h"


// CUserAdd 对话框

class CUserAdd : public CDialogEx
{
	DECLARE_DYNAMIC(CUserAdd)

public:
	CUserAdd(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CUserAdd();

// 对话框数据
	enum { IDD = IDD_USER_ADD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

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
