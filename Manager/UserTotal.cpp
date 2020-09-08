// UserTotal.cpp : 实现文件
//

#include "stdafx.h"
#include "Manager.h"
#include "UserTotal.h"
#include "afxdialogex.h"
#include "AdoWorker.h"


// CUserTotal 对话框

IMPLEMENT_DYNAMIC(CUserTotal, CDialogEx)

CUserTotal::CUserTotal(CWnd* pParent /*=NULL*/)
	: CDialogEx(CUserTotal::IDD, pParent)
{

}

CUserTotal::~CUserTotal()
{
}

void CUserTotal::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_type_select);
	DDX_Control(pDX, IDC_USER_LIST, m_UserList);
	DDX_Control(pDX, IDC_USER_STATE_LIST, m_UserStatusList);
}


BEGIN_MESSAGE_MAP(CUserTotal, CDialogEx)
	ON_BN_CLICKED(IDC_QUERY, &CUserTotal::OnBnClickedQuery)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CUserTotal::OnSelchangeCombo1)
END_MESSAGE_MAP()


// CUserTotal 消息处理程序


BOOL CUserTotal::OnInitDialog()
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

	m_type_select.AddString(TEXT("人员信息"));
	m_type_select.AddString(TEXT("人员出行信息"));
	m_type_select.SetCurSel(0);
	
	m_UserList.ShowWindow(SW_SHOW);
	m_UserStatusList.ShowWindow(SW_HIDE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void CUserTotal::OnBnClickedQuery()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	int nSelect = m_type_select.GetCurSel();
	if (nSelect == 0)
	{
		CString strSqlText;
		strSqlText.Format(TEXT("select * from userinfo"));
		//////////////////////////////////创建SQL语句执行类实例
		AdoWorker *ado = NULL;
		_RecordUserInfo *pUserNameInfo = NULL;
		ado = new AdoWorker();
		pUserNameInfo = (_RecordUserInfo *)ado->ExecuteSql(strSqlText, 4);

		if (pUserNameInfo == NULL)
		{
			delete pUserNameInfo;
			delete ado;
			return;
		}
		else//存在这样的账号，在此设定表格中第二行的姓名
		{
			WriteAllUserList(pUserNameInfo);
			delete ado;
		}

	}
	else if (nSelect == 1)
	{
		CString strSqlText;
		strSqlText.Format(TEXT("select * from Recordinfo"));

		//////////////////////////////////创建SQL语句执行类实例
		AdoWorker *ado = NULL;
		_RecordStatusInfo *pUserNameInfo = NULL;
		ado = new AdoWorker();
		pUserNameInfo = (_RecordStatusInfo *)ado->ExecuteSql(strSqlText, 3);

		if (pUserNameInfo == NULL)
		{

			delete pUserNameInfo;
			delete ado;
			return;
		}
		else//存在这样的账号，在此设定表格中第二行的姓名
		{
			WriteAllUserStateList(pUserNameInfo);
			delete ado;
		}

	}
}

void CUserTotal::WriteAllUserList(_RecordUserInfo *pRecordInfo)
{
	m_UserList.DeleteAllItems();
	_RecordUserInfo *pDelete = NULL;
	pDelete = pRecordInfo;
	for (int i = 0; pRecordInfo != NULL; i++)
	{
		m_UserList.InsertItem(i, NULL);//新插入一行
		//AfxMessageBox(m_UserAddDlg.m_user_name);
		m_UserList.SetItemText(i, 0, pRecordInfo->UserName);
		CString strAge = _T("");
		strAge.Format(TEXT("%d"), pRecordInfo->UserAge);
		m_UserList.SetItemText(i, 1, strAge);
		if (pRecordInfo->UserSex == 0)
			m_UserList.SetItemText(i, 2, TEXT("男"));
		else
			m_UserList.SetItemText(i, 2, TEXT("女"));
		m_UserList.SetItemText(i, 3, pRecordInfo->UserSfz);
		m_UserList.SetItemText(i, 4, pRecordInfo->UserPhone);

		if (pRecordInfo->UserStatus == 0)
			m_UserList.SetItemText(i, 5, TEXT("未出行"));
		else
			m_UserList.SetItemText(i, 5, TEXT("出行"));

		m_UserList.SetItemText(i, 6, pRecordInfo->UserAddress);

		pRecordInfo = pRecordInfo->Next;
		delete pDelete;
		pDelete = pRecordInfo;
	}
}
void CUserTotal::WriteAllUserStateList(_RecordStatusInfo *pRecordInfo)
{
	m_UserStatusList.DeleteAllItems();
	_RecordStatusInfo *pDelete = NULL;
	pDelete = pRecordInfo;
	for (int i = 0; pRecordInfo != NULL; i++)
	{
		m_UserStatusList.InsertItem(i, NULL);


		m_UserStatusList.SetItemText(i, 0, pRecordInfo->UserName);
		m_UserStatusList.SetItemText(i, 1, pRecordInfo->BeginTime);
		m_UserStatusList.SetItemText(i, 2, pRecordInfo->EndTime);
		m_UserStatusList.SetItemText(i, 3, pRecordInfo->BeginAddr);
		m_UserStatusList.SetItemText(i, 4, pRecordInfo->EndAddr);

		if (pRecordInfo->UserTool == 0)
			m_UserStatusList.SetItemText(i, 5, TEXT("飞机"));
		else if (pRecordInfo->UserTool == 1)
			m_UserStatusList.SetItemText(i, 5, TEXT("火车"));
		else if (pRecordInfo->UserTool == 2)
			m_UserStatusList.SetItemText(i, 5, TEXT("汽车"));
		else if (pRecordInfo->UserTool == 3)
			m_UserStatusList.SetItemText(i, 5, TEXT("自驾"));
		else if (pRecordInfo->UserTool == 4)
			m_UserStatusList.SetItemText(i, 5, TEXT("步行"));
		else
			m_UserStatusList.SetItemText(i, 5, TEXT("其他"));

		m_UserStatusList.SetItemText(i, 6, pRecordInfo->ToolInfo);

		if (pRecordInfo->Hasisolace == 0)
			m_UserStatusList.SetItemText(i, 7, TEXT("无"));
		else
			m_UserStatusList.SetItemText(i, 7, TEXT("有"));

		if (pRecordInfo->Hasinfect == 0)
			m_UserStatusList.SetItemText(i, 8, TEXT("无"));
		else
			m_UserStatusList.SetItemText(i, 8, TEXT("有"));

		pRecordInfo = pRecordInfo->Next;
		delete pDelete;
		pDelete = pRecordInfo;
	}
}

void CUserTotal::OnSelchangeCombo1()
{
	// TODO:  在此添加控件通知处理程序代码
	int nSelect = m_type_select.GetCurSel();
	if (nSelect == 0)
	{
		m_UserList.ShowWindow(SW_SHOW);
		m_UserStatusList.ShowWindow(SW_HIDE);
	}
	else if (nSelect == 1)
	{
		m_UserList.ShowWindow(SW_HIDE);
		m_UserStatusList.ShowWindow(SW_SHOW);
	}
}
