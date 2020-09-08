#pragma once
#include "afxwin.h"


// CEwmCreate �Ի���

class CEwmCreate : public CDialogEx
{
	DECLARE_DYNAMIC(CEwmCreate)

public:
	CEwmCreate(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CEwmCreate();

// �Ի�������
	enum { IDD = IDD_EWM_CREATE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CString m_user_name;
	CString m_file_name;
	
	void Showpicture(CString Bmpname);
	void CreateEwm(CString strInfo);

	CString OnUserInfo(CString UserName);
	CString OnUserStatusInfo(CString UserName);

	afx_msg void OnBnClickedQuery();
	
	
	CStatic m_picture;
	afx_msg void OnPaint();
};
