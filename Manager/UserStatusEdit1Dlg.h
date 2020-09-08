#pragma once


// CUserStatusEdit1Dlg 对话框

class CUserStatusEdit1Dlg : public CDialogEx
{
	DECLARE_DYNAMIC(CUserStatusEdit1Dlg)

public:
	CUserStatusEdit1Dlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CUserStatusEdit1Dlg();

// 对话框数据
	enum { IDD = IDD_USER_STATUS_EDIT1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int m_nAutoId;
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
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
};
