#pragma once
#include "afxcmn.h"
#include "_StructDefine.h"
#include "UserStatusEdit1Dlg.h"

// CUserStatusEdit 对话框

class CUserStatusEdit : public CDialogEx
{
	DECLARE_DYNAMIC(CUserStatusEdit)

public:
	CUserStatusEdit(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CUserStatusEdit();

// 对话框数据
	enum { IDD = IDD_USER_STATUS_EDIT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedQuery();
	CString m_user_name;
	CListCtrl m_UserStatusList;

	CUserStatusEdit1Dlg m_UserStatusEdit1Dlg;
	void WriteList(_RecordStatusInfo *pRecordInfo);
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
};
