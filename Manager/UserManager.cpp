// UserManager.cpp : 实现文件
//

#include "stdafx.h"
#include "Manager.h"
#include "UserManager.h"
#include "afxdialogex.h"


// CUserManager 对话框

IMPLEMENT_DYNAMIC(CUserManager, CDialogEx)

CUserManager::CUserManager(CWnd* pParent /*=NULL*/)
	: CDialogEx(CUserManager::IDD, pParent)
{

}

CUserManager::~CUserManager()
{
}

void CUserManager::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_USER_LIST, m_UserList);
	DDX_Control(pDX, IDC_USER_LIST2, m_UserStatusList);
}


BEGIN_MESSAGE_MAP(CUserManager, CDialogEx)
	ON_BN_CLICKED(IDC_ADD, &CUserManager::OnBnClickedAdd)
	ON_BN_CLICKED(IDC_EDIT, &CUserManager::OnBnClickedEdit)
	ON_BN_CLICKED(IDC_DEL, &CUserManager::OnBnClickedDel)
	ON_BN_CLICKED(IDC_USER_STATUS_ADD, &CUserManager::OnBnClickedUserStatusAdd)
	ON_BN_CLICKED(IDC_USER_STATUS_EDIT, &CUserManager::OnBnClickedUserStatusEdit)
	ON_BN_CLICKED(IDC_USER_STATUS_DEL, &CUserManager::OnBnClickedUserStatusDel)
END_MESSAGE_MAP()


// CUserManager 消息处理程序


void CUserManager::OnBnClickedAdd()
{
	// TODO:  在此添加控件通知处理程序代码
	if (m_UserAddDlg.DoModal() == IDOK)
	{
		//AfxMessageBox(m_UserAddDlg.m_user_name);
		m_UserList.SetItemText(0, 0, m_UserAddDlg.m_user_name);
		CString strAge = _T("");
		strAge.Format(TEXT("%d"), m_UserAddDlg.m_age);
		m_UserList.SetItemText(0, 1, strAge);
		if (m_UserAddDlg.m_nSex==0)
			m_UserList.SetItemText(0, 2, TEXT("男"));
		else
			m_UserList.SetItemText(0, 2, TEXT("女"));
		m_UserList.SetItemText(0, 3, m_UserAddDlg.m_sfz);
		m_UserList.SetItemText(0, 4, m_UserAddDlg.m_phone);

		if (m_UserAddDlg.m_nStatus == 0)
			m_UserList.SetItemText(0, 5, TEXT("未出行"));
		else
			m_UserList.SetItemText(0, 5, TEXT("出行"));

		m_UserList.SetItemText(0, 6, m_UserAddDlg.m_addr);
	};
}


void CUserManager::OnBnClickedEdit()
{
	// TODO:  在此添加控件通知处理程序代码
	if (m_UserEditDlg.DoModal() == IDOK)
	{
		m_UserList.DeleteAllItems();
		m_UserList.InsertItem(0, NULL);//新插入一行
		//AfxMessageBox(m_UserAddDlg.m_user_name);
		m_UserList.SetItemText(0, 0, m_UserEditDlg.m_user_name);
		CString strAge = _T("");
		strAge.Format(TEXT("%d"), m_UserEditDlg.m_age);
		m_UserList.SetItemText(0, 1, strAge);
		if (m_UserAddDlg.m_nSex == 0)
			m_UserList.SetItemText(0, 2, TEXT("男"));
		else
			m_UserList.SetItemText(0, 2, TEXT("女"));
		m_UserList.SetItemText(0, 3, m_UserEditDlg.m_sfz);
		m_UserList.SetItemText(0, 4, m_UserEditDlg.m_phone);

		if (m_UserAddDlg.m_nStatus == 0)
			m_UserList.SetItemText(0, 5, TEXT("未出行"));
		else
			m_UserList.SetItemText(0, 5, TEXT("出行"));

		m_UserList.SetItemText(0, 6, m_UserEditDlg.m_addr);
	};
}


void CUserManager::OnBnClickedDel()
{
	// TODO:  在此添加控件通知处理程序代码
	m_UserDelDlg.DoModal();

}


BOOL CUserManager::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	m_UserList.InsertColumn(0, TEXT("姓名"), LVCFMT_LEFT, 80);
	m_UserList.InsertColumn(1, TEXT("年龄"), LVCFMT_LEFT, 40);
	m_UserList.InsertColumn(2, TEXT("性别"), LVCFMT_LEFT, 40);
	m_UserList.InsertColumn(3, TEXT("身份证"), LVCFMT_LEFT, 160);
	m_UserList.InsertColumn(4, TEXT("电话"), LVCFMT_LEFT, 90);
	m_UserList.InsertColumn(5, TEXT("状态"), LVCFMT_LEFT, 50);
	m_UserList.InsertColumn(6, TEXT("地址"), LVCFMT_LEFT, 200);

	m_UserList.SetExtendedStyle(LVS_EX_GRIDLINES);
	m_UserList.InsertItem(0, NULL);


	m_UserStatusList.InsertColumn(0, TEXT("姓名"), LVCFMT_LEFT, 80);
	m_UserStatusList.InsertColumn(1, TEXT("开始时间"), LVCFMT_LEFT, 80);
	m_UserStatusList.InsertColumn(2, TEXT("结束时间"), LVCFMT_LEFT, 80);
	m_UserStatusList.InsertColumn(3, TEXT("出行地址"), LVCFMT_LEFT, 100);
	m_UserStatusList.InsertColumn(4, TEXT("结束地址"), LVCFMT_LEFT, 100);
	m_UserStatusList.InsertColumn(5, TEXT("出行工具"), LVCFMT_LEFT, 60);
	m_UserStatusList.InsertColumn(6, TEXT("工具信息"), LVCFMT_LEFT, 120);
	m_UserStatusList.InsertColumn(7, TEXT("隔离"), LVCFMT_LEFT, 40);
	m_UserStatusList.InsertColumn(8, TEXT("患病"), LVCFMT_LEFT, 40);

	m_UserStatusList.SetExtendedStyle(LVS_EX_GRIDLINES);
	m_UserStatusList.InsertItem(0, NULL);



	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void CUserManager::OnBnClickedUserStatusAdd()
{
	// TODO:  在此添加控件通知处理程序代码
	if (m_UserStatusDlg.DoModal() == IDOK)
	{
		//AfxMessageBox(m_UserAddDlg.m_user_name);
		m_UserStatusList.SetItemText(0, 0, m_UserStatusDlg.m_user_name);
		m_UserStatusList.SetItemText(0, 1, m_UserStatusDlg.m_begin_time);
		m_UserStatusList.SetItemText(0, 2, m_UserStatusDlg.m_end_time);
		m_UserStatusList.SetItemText(0, 3, m_UserStatusDlg.m_begin_addr);
		m_UserStatusList.SetItemText(0, 4, m_UserStatusDlg.m_end_addr);
		
		if (m_UserStatusDlg.m_nTool == 0)
			m_UserStatusList.SetItemText(0, 5, TEXT("飞机"));
		else if (m_UserStatusDlg.m_nTool == 1)
			m_UserStatusList.SetItemText(0, 5, TEXT("火车"));
		else if (m_UserStatusDlg.m_nTool == 2)
			m_UserStatusList.SetItemText(0, 5, TEXT("汽车"));
		else if (m_UserStatusDlg.m_nTool == 3)
			m_UserStatusList.SetItemText(0, 5, TEXT("自驾"));
		else if (m_UserStatusDlg.m_nTool == 4)
			m_UserStatusList.SetItemText(0, 5, TEXT("步行"));
		else
			m_UserStatusList.SetItemText(0, 5, TEXT("其他"));

		m_UserStatusList.SetItemText(0, 6, m_UserStatusDlg.m_tool_info);

		if (m_UserStatusDlg.m_nOlace == 0)
			m_UserStatusList.SetItemText(0, 7, TEXT("无"));
		else
			m_UserStatusList.SetItemText(0, 7, TEXT("有"));

		if (m_UserStatusDlg.m_nInfect == 0)
			m_UserStatusList.SetItemText(0, 8, TEXT("无"));
		else
			m_UserStatusList.SetItemText(0, 8, TEXT("有"));

		
	};

}


void CUserManager::OnBnClickedUserStatusEdit()
{
	// TODO:  在此添加控件通知处理程序代码
	m_UserStatusEditDlg.DoModal();
}


void CUserManager::OnBnClickedUserStatusDel()
{
	// TODO:  在此添加控件通知处理程序代码
	m_UserStatusDelDlg.DoModal();
}
