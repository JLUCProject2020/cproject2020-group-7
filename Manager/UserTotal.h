#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "_StructDefine.h"


// CUserTotal 对话框

class CUserTotal : public CDialogEx
{
	DECLARE_DYNAMIC(CUserTotal)

public:
	CUserTotal(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CUserTotal();

// 对话框数据
	enum { IDD = IDD_TOTAL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

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
