#pragma once


// CUserDel 对话框

class CUserDel : public CDialogEx
{
	DECLARE_DYNAMIC(CUserDel)

public:
	CUserDel(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CUserDel();

// 对话框数据
	enum { IDD = IDD_USER_DEL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_user_name;
	afx_msg void OnBnClickedOk();
};
