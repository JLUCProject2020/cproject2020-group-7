#pragma once
#include "afxwin.h"


// CEwmLoad 对话框

class CEwmLoad : public CDialogEx
{
	DECLARE_DYNAMIC(CEwmLoad)

public:
	CEwmLoad(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CEwmLoad();

// 对话框数据
	enum { IDD = IDD_EWM_LOAD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedQuery();
	CStatic m_picture;
	CString m_strShowText;
	CEdit m_ShowText;

	CString m_file_name;
	void Showpicture(CString Bmpname);
	void ShowText();

	afx_msg void OnPaint();
};
