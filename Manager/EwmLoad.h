#pragma once
#include "afxwin.h"


// CEwmLoad �Ի���

class CEwmLoad : public CDialogEx
{
	DECLARE_DYNAMIC(CEwmLoad)

public:
	CEwmLoad(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CEwmLoad();

// �Ի�������
	enum { IDD = IDD_EWM_LOAD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
