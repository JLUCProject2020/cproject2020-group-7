#pragma once
#include "afxwin.h"


// CUserEdit 对话框

class CUserEdit : public CDialogEx
{
	DECLARE_DYNAMIC(CUserEdit)

public:
	CUserEdit(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CUserEdit();

// 对话框数据
	enum { IDD = IDD_USER_EDIT };

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
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
};
