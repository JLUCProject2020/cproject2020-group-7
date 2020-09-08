#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "_StructDefine.h"

// CUserQuery �Ի���

class CUserQuery : public CDialogEx
{
	DECLARE_DYNAMIC(CUserQuery)

public:
	CUserQuery(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CUserQuery();

// �Ի�������
	enum { IDD = IDD_QUERY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CComboBox m_select_type;
	CString m_user_name;
	CListCtrl m_UserList;
	CListCtrl m_UserStatusList;
	CComboBox m_tool_select;
	CEdit m_edit_user_name;

	void WriteQueryList(CString QuerySql);
	void WriteUserList(CString UserName);
	void WriteUserStateList(CString UserName);
	void WriteList(_UserInfo *pRecordInfo);
	void WriteAllUserList(_RecordUserInfo *pRecordInfo);
	void WriteList(_RecordUserInfo *pRecordInfo);
	void WriteList(_RecordStatusInfo *pRecordInfo);
	afx_msg void OnBnClickedQuery();
	afx_msg void OnSelchangeCombo1();
	
	CListCtrl m_age_list;
};
