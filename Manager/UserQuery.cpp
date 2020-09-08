// UserQuery.cpp : 实现文件
//

#include "stdafx.h"
#include "Manager.h"
#include "UserQuery.h"
#include "afxdialogex.h"
#include "AdoWorker.h"
#include "_StructDefine.h"


// CUserQuery 对话框

IMPLEMENT_DYNAMIC(CUserQuery, CDialogEx)

CUserQuery::CUserQuery(CWnd* pParent /*=NULL*/)
	: CDialogEx(CUserQuery::IDD, pParent)
	, m_user_name(_T(""))
{

}

CUserQuery::~CUserQuery()
{
}

void CUserQuery::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_select_type);
	DDX_Text(pDX, IDC_USER_NAME, m_user_name);
	DDX_Control(pDX, IDC_USER_LIST, m_UserList);
	DDX_Control(pDX, IDC_USER_LIST2, m_UserStatusList);
	DDX_Control(pDX, IDC_COMBO2, m_tool_select);
	DDX_Control(pDX, IDC_USER_NAME, m_edit_user_name);
	DDX_Control(pDX, IDC_USER_AGE_LIST, m_age_list);
}


BEGIN_MESSAGE_MAP(CUserQuery, CDialogEx)
	ON_BN_CLICKED(IDC_QUERY, &CUserQuery::OnBnClickedQuery)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CUserQuery::OnSelchangeCombo1)
END_MESSAGE_MAP()


// CUserQuery 消息处理程序


BOOL CUserQuery::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_age_list.InsertColumn(0, TEXT("姓名"), LVCFMT_LEFT, 80);
	m_age_list.InsertColumn(1, TEXT("年龄"), LVCFMT_LEFT, 40);
	m_age_list.InsertColumn(2, TEXT("性别"), LVCFMT_LEFT, 40);
	m_age_list.InsertColumn(3, TEXT("身份证"), LVCFMT_LEFT, 160);
	m_age_list.InsertColumn(4, TEXT("电话"), LVCFMT_LEFT, 90);
	m_age_list.InsertColumn(5, TEXT("状态"), LVCFMT_LEFT, 50);
	m_age_list.InsertColumn(6, TEXT("地址"), LVCFMT_LEFT, 200);

	m_age_list.SetExtendedStyle(LVS_EX_GRIDLINES);
	m_age_list.InsertItem(0, NULL);

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

	m_select_type.AddString(TEXT("按姓名查询"));
	m_select_type.AddString(TEXT("按目的地查询"));
	m_select_type.AddString(TEXT("按交通工具查询"));
	m_select_type.AddString(TEXT("按隔离人员查询"));
	m_select_type.AddString(TEXT("按患病人员查询"));
	m_select_type.AddString(TEXT("按年龄查询"));
	m_select_type.SetCurSel(0);

	m_tool_select.AddString(TEXT("飞机"));
	m_tool_select.AddString(TEXT("火车"));
	m_tool_select.AddString(TEXT("汽车"));
	m_tool_select.AddString(TEXT("自驾"));
	m_tool_select.AddString(TEXT("步行"));
	m_tool_select.AddString(TEXT("其他"));
	m_tool_select.SetCurSel(0);

	
	m_edit_user_name.ShowWindow(SW_SHOW);
	m_tool_select.ShowWindow(SW_HIDE);

	m_age_list.ShowWindow(SW_HIDE);
	m_UserList.ShowWindow(SW_SHOW);
	m_UserStatusList.ShowWindow(SW_SHOW);

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void CUserQuery::OnBnClickedQuery()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	int nSelect = m_select_type.GetCurSel();
	if (nSelect == 0)
	{
		if (m_user_name.IsEmpty())    /*判断用户名信息是否为空*/
		{
			AfxMessageBox(TEXT("请输入用户名！"));
			return;
		}
		WriteUserList(m_user_name);
		WriteUserStateList(m_user_name);

	}
	else if (nSelect == 1)
	{
		if (m_user_name.IsEmpty())    /*判断用户名信息是否为空*/
		{
			AfxMessageBox(TEXT("请输入目的地信息！"));
			return;
		}
		CString strSqlText;
		strSqlText.Format(TEXT("select * from Recordinfo where EndAddr='%s'"), m_user_name);

		WriteQueryList(strSqlText);
		

	}
	else if (nSelect == 2)
	{
		int nToosSelect = m_tool_select.GetCurSel();
		CString strSqlText;
		strSqlText.Format(TEXT("select * from Recordinfo where UserTool=%d"), nToosSelect);
		WriteQueryList(strSqlText);
		
	}
	else if (nSelect == 3)
	{
		CString strSqlText;
		strSqlText.Format(TEXT("select * from Recordinfo where HasIsOlace=%d"), 1);
		WriteQueryList(strSqlText);
	}
	else if (nSelect == 4)
	{
		CString strSqlText;
		strSqlText.Format(TEXT("select * from Recordinfo where HasIsInfect=%d"), 1);
		WriteQueryList(strSqlText);
	}
	else if (nSelect == 5)
	{
		CString strSqlText;
		strSqlText.Format(TEXT("select * from userinfo order by UserAge"));
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
	
}

void CUserQuery::WriteQueryList(CString QuerySql)
{
	
	//////////////////////////////////创建SQL语句执行类实例
	AdoWorker *ado = NULL;
	_RecordStatusInfo *pUserNameInfo = NULL;
	ado = new AdoWorker();
	pUserNameInfo = (_RecordStatusInfo *)ado->ExecuteSql(QuerySql, 3);

	if (pUserNameInfo == NULL)
	{
		delete pUserNameInfo;
		delete ado;
		return;
	}
	else//存在这样的账号，在此设定表格中第二行的姓名
	{
		WriteList(pUserNameInfo);
		delete ado;
	}
}

void CUserQuery::WriteUserList(CString UserName)
{
	CString strSqlText;
	strSqlText.Format(TEXT("select * from userinfo where UserName='%s'"), UserName);

	//////////////////////////////////创建SQL语句执行类实例
	AdoWorker *ado = NULL;
	_UserInfo *pUserNameInfo = NULL;
	ado = new AdoWorker();
	pUserNameInfo = (_UserInfo *)ado->ExecuteSql(strSqlText, 0);

	if (pUserNameInfo == NULL)
	{
		
		delete pUserNameInfo;
		delete ado;
		return;
	}
	else//存在这样的账号，在此设定表格中第二行的姓名
	{
		WriteList(pUserNameInfo);
		delete pUserNameInfo;
		delete ado;
	}
}
void CUserQuery::WriteUserStateList(CString UserName)
{
	CString strSqlText;
	strSqlText.Format(TEXT("select * from Recordinfo where UserName='%s'"), UserName);

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
		WriteList(pUserNameInfo);
		delete ado;
	}
}

void CUserQuery::WriteList(_UserInfo *pRecordInfo)
{
	m_UserList.DeleteAllItems();
	m_UserList.InsertItem(0, NULL);//新插入一行
	//AfxMessageBox(m_UserAddDlg.m_user_name);
	m_UserList.SetItemText(0, 0, pRecordInfo->UserName);
	CString strAge = _T("");
	strAge.Format(TEXT("%d"), pRecordInfo->UserAge);
	m_UserList.SetItemText(0, 1, strAge);
	if (pRecordInfo->UserSex == 0)
		m_UserList.SetItemText(0, 2, TEXT("男"));
	else
		m_UserList.SetItemText(0, 2, TEXT("女"));
	m_UserList.SetItemText(0, 3, pRecordInfo->UserSfz);
	m_UserList.SetItemText(0, 4, pRecordInfo->UserPhone);

	if (pRecordInfo->UserStatus == 0)
		m_UserList.SetItemText(0, 5, TEXT("未出行"));
	else
		m_UserList.SetItemText(0, 5, TEXT("出行"));

	m_UserList.SetItemText(0, 6, pRecordInfo->UserAddress);
}

void CUserQuery::WriteAllUserList(_RecordUserInfo *pRecordInfo)
{
	m_age_list.DeleteAllItems();
	_RecordUserInfo *pDelete = NULL;
	pDelete = pRecordInfo;
	for (int i = 0; pRecordInfo != NULL; i++)
	{
		m_age_list.InsertItem(i, NULL);//新插入一行
		//AfxMessageBox(m_UserAddDlg.m_user_name);
		m_age_list.SetItemText(i, 0, pRecordInfo->UserName);
		CString strAge = _T("");
		strAge.Format(TEXT("%d"), pRecordInfo->UserAge);
		m_age_list.SetItemText(i, 1, strAge);
		if (pRecordInfo->UserSex == 0)
			m_age_list.SetItemText(i, 2, TEXT("男"));
		else
			m_age_list.SetItemText(i, 2, TEXT("女"));
		m_age_list.SetItemText(i, 3, pRecordInfo->UserSfz);
		m_age_list.SetItemText(i, 4, pRecordInfo->UserPhone);

		if (pRecordInfo->UserStatus == 0)
			m_age_list.SetItemText(i, 5, TEXT("未出行"));
		else
			m_age_list.SetItemText(i, 5, TEXT("出行"));

		m_age_list.SetItemText(i, 6, pRecordInfo->UserAddress);

		pRecordInfo = pRecordInfo->Next;
		delete pDelete;
		pDelete = pRecordInfo;
	}
}
void CUserQuery::WriteList(_RecordStatusInfo *pRecordInfo)
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
void CUserQuery::OnSelchangeCombo1()
{
	// TODO:  在此添加控件通知处理程序代码
	m_age_list.ShowWindow(SW_HIDE);
	m_UserList.ShowWindow(SW_SHOW);
	m_UserStatusList.ShowWindow(SW_SHOW);

	int nSelect = m_select_type.GetCurSel();
	if (nSelect==0)
	{
		m_edit_user_name.ShowWindow(SW_SHOW);
		m_tool_select.ShowWindow(SW_HIDE);
	}
	else if (nSelect == 1)
	{
		m_edit_user_name.ShowWindow(SW_SHOW);
		m_tool_select.ShowWindow(SW_HIDE);
	}
	else if (nSelect == 2)
	{
		m_edit_user_name.ShowWindow(SW_HIDE);
		m_tool_select.ShowWindow(SW_SHOW);
	}
	else if (nSelect == 5)
	{
		m_age_list.ShowWindow(SW_SHOW);
		m_UserList.ShowWindow(SW_HIDE);
		m_UserStatusList.ShowWindow(SW_HIDE);

		m_edit_user_name.ShowWindow(SW_HIDE);
		m_tool_select.ShowWindow(SW_HIDE);

	}
	else 
	{
		m_edit_user_name.ShowWindow(SW_HIDE);
		m_tool_select.ShowWindow(SW_HIDE);
	}

}
