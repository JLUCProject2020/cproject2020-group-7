#pragma once
#include "afxcmn.h"
#include "_StructDefine.h"

// CUserStatusDel 对话框

class CUserStatusDel : public CDialogEx
{
	DECLARE_DYNAMIC(CUserStatusDel)

public:
	CUserStatusDel(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CUserStatusDel();

// 对话框数据
	enum { IDD = IDD_USER_STATUS_DEL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	int m_nAutoId;
	CString m_user_name;
	CListCtrl m_UserStatusList;

	void WriteList(_RecordStatusInfo *pRecordInfo);
	afx_msg void OnBnClickedQuery();
	afx_msg void OnBnClickedOk();
};
