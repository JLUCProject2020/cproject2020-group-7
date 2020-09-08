#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "_StructDefine.h"


// CUserTotal �Ի���

class CUserTotal : public CDialogEx
{
	DECLARE_DYNAMIC(CUserTotal)

public:
	CUserTotal(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CUserTotal();

// �Ի�������
	enum { IDD = IDD_TOTAL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_type_select;
	CListCtrl m_UserList;
	CListCtrl m_UserStatusList;

	void WriteAllUserList(_RecordUserInfo *pRecordInfo);
	void WriteAllUserStateList(_RecordStatusInfo *pRecordInfo);
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedQuery();
	afx_msg void OnSelchangeCombo1();
};
