#pragma once


// CUserDel �Ի���

class CUserDel : public CDialogEx
{
	DECLARE_DYNAMIC(CUserDel)

public:
	CUserDel(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CUserDel();

// �Ի�������
	enum { IDD = IDD_USER_DEL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_user_name;
	afx_msg void OnBnClickedOk();
};
