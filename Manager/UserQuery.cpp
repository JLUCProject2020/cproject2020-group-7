// UserQuery.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Manager.h"
#include "UserQuery.h"
#include "afxdialogex.h"
#include "AdoWorker.h"
#include "_StructDefine.h"


// CUserQuery �Ի���

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


// CUserQuery ��Ϣ�������


BOOL CUserQuery::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_age_list.InsertColumn(0, TEXT("����"), LVCFMT_LEFT, 80);
	m_age_list.InsertColumn(1, TEXT("����"), LVCFMT_LEFT, 40);
	m_age_list.InsertColumn(2, TEXT("�Ա�"), LVCFMT_LEFT, 40);
	m_age_list.InsertColumn(3, TEXT("���֤"), LVCFMT_LEFT, 160);
	m_age_list.InsertColumn(4, TEXT("�绰"), LVCFMT_LEFT, 90);
	m_age_list.InsertColumn(5, TEXT("״̬"), LVCFMT_LEFT, 50);
	m_age_list.InsertColumn(6, TEXT("��ַ"), LVCFMT_LEFT, 200);

	m_age_list.SetExtendedStyle(LVS_EX_GRIDLINES);
	m_age_list.InsertItem(0, NULL);

	m_UserList.InsertColumn(0, TEXT("����"), LVCFMT_LEFT, 80);
	m_UserList.InsertColumn(1, TEXT("����"), LVCFMT_LEFT, 40);
	m_UserList.InsertColumn(2, TEXT("�Ա�"), LVCFMT_LEFT, 40);
	m_UserList.InsertColumn(3, TEXT("���֤"), LVCFMT_LEFT, 160);
	m_UserList.InsertColumn(4, TEXT("�绰"), LVCFMT_LEFT, 90);
	m_UserList.InsertColumn(5, TEXT("״̬"), LVCFMT_LEFT, 50);
	m_UserList.InsertColumn(6, TEXT("��ַ"), LVCFMT_LEFT, 200);

	m_UserList.SetExtendedStyle(LVS_EX_GRIDLINES);
	m_UserList.InsertItem(0, NULL);


	m_UserStatusList.InsertColumn(0, TEXT("����"), LVCFMT_LEFT, 80);
	m_UserStatusList.InsertColumn(1, TEXT("��ʼʱ��"), LVCFMT_LEFT, 80);
	m_UserStatusList.InsertColumn(2, TEXT("����ʱ��"), LVCFMT_LEFT, 80);
	m_UserStatusList.InsertColumn(3, TEXT("���е�ַ"), LVCFMT_LEFT, 100);
	m_UserStatusList.InsertColumn(4, TEXT("������ַ"), LVCFMT_LEFT, 100);
	m_UserStatusList.InsertColumn(5, TEXT("���й���"), LVCFMT_LEFT, 60);
	m_UserStatusList.InsertColumn(6, TEXT("������Ϣ"), LVCFMT_LEFT, 120);
	m_UserStatusList.InsertColumn(7, TEXT("����"), LVCFMT_LEFT, 40);
	m_UserStatusList.InsertColumn(8, TEXT("����"), LVCFMT_LEFT, 40);

	m_UserStatusList.SetExtendedStyle(LVS_EX_GRIDLINES);
	m_UserStatusList.InsertItem(0, NULL);

	m_select_type.AddString(TEXT("��������ѯ"));
	m_select_type.AddString(TEXT("��Ŀ�ĵز�ѯ"));
	m_select_type.AddString(TEXT("����ͨ���߲�ѯ"));
	m_select_type.AddString(TEXT("��������Ա��ѯ"));
	m_select_type.AddString(TEXT("��������Ա��ѯ"));
	m_select_type.AddString(TEXT("�������ѯ"));
	m_select_type.SetCurSel(0);

	m_tool_select.AddString(TEXT("�ɻ�"));
	m_tool_select.AddString(TEXT("��"));
	m_tool_select.AddString(TEXT("����"));
	m_tool_select.AddString(TEXT("�Լ�"));
	m_tool_select.AddString(TEXT("����"));
	m_tool_select.AddString(TEXT("����"));
	m_tool_select.SetCurSel(0);

	
	m_edit_user_name.ShowWindow(SW_SHOW);
	m_tool_select.ShowWindow(SW_HIDE);

	m_age_list.ShowWindow(SW_HIDE);
	m_UserList.ShowWindow(SW_SHOW);
	m_UserStatusList.ShowWindow(SW_SHOW);

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void CUserQuery::OnBnClickedQuery()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	int nSelect = m_select_type.GetCurSel();
	if (nSelect == 0)
	{
		if (m_user_name.IsEmpty())    /*�ж��û�����Ϣ�Ƿ�Ϊ��*/
		{
			AfxMessageBox(TEXT("�������û�����"));
			return;
		}
		WriteUserList(m_user_name);
		WriteUserStateList(m_user_name);

	}
	else if (nSelect == 1)
	{
		if (m_user_name.IsEmpty())    /*�ж��û�����Ϣ�Ƿ�Ϊ��*/
		{
			AfxMessageBox(TEXT("������Ŀ�ĵ���Ϣ��"));
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
		//////////////////////////////////����SQL���ִ����ʵ��
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
		else//�����������˺ţ��ڴ��趨����еڶ��е�����
		{
			WriteAllUserList(pUserNameInfo);
			delete ado;
		}
	}
	
}

void CUserQuery::WriteQueryList(CString QuerySql)
{
	
	//////////////////////////////////����SQL���ִ����ʵ��
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
	else//�����������˺ţ��ڴ��趨����еڶ��е�����
	{
		WriteList(pUserNameInfo);
		delete ado;
	}
}

void CUserQuery::WriteUserList(CString UserName)
{
	CString strSqlText;
	strSqlText.Format(TEXT("select * from userinfo where UserName='%s'"), UserName);

	//////////////////////////////////����SQL���ִ����ʵ��
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
	else//�����������˺ţ��ڴ��趨����еڶ��е�����
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

	//////////////////////////////////����SQL���ִ����ʵ��
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
	else//�����������˺ţ��ڴ��趨����еڶ��е�����
	{
		WriteList(pUserNameInfo);
		delete ado;
	}
}

void CUserQuery::WriteList(_UserInfo *pRecordInfo)
{
	m_UserList.DeleteAllItems();
	m_UserList.InsertItem(0, NULL);//�²���һ��
	//AfxMessageBox(m_UserAddDlg.m_user_name);
	m_UserList.SetItemText(0, 0, pRecordInfo->UserName);
	CString strAge = _T("");
	strAge.Format(TEXT("%d"), pRecordInfo->UserAge);
	m_UserList.SetItemText(0, 1, strAge);
	if (pRecordInfo->UserSex == 0)
		m_UserList.SetItemText(0, 2, TEXT("��"));
	else
		m_UserList.SetItemText(0, 2, TEXT("Ů"));
	m_UserList.SetItemText(0, 3, pRecordInfo->UserSfz);
	m_UserList.SetItemText(0, 4, pRecordInfo->UserPhone);

	if (pRecordInfo->UserStatus == 0)
		m_UserList.SetItemText(0, 5, TEXT("δ����"));
	else
		m_UserList.SetItemText(0, 5, TEXT("����"));

	m_UserList.SetItemText(0, 6, pRecordInfo->UserAddress);
}

void CUserQuery::WriteAllUserList(_RecordUserInfo *pRecordInfo)
{
	m_age_list.DeleteAllItems();
	_RecordUserInfo *pDelete = NULL;
	pDelete = pRecordInfo;
	for (int i = 0; pRecordInfo != NULL; i++)
	{
		m_age_list.InsertItem(i, NULL);//�²���һ��
		//AfxMessageBox(m_UserAddDlg.m_user_name);
		m_age_list.SetItemText(i, 0, pRecordInfo->UserName);
		CString strAge = _T("");
		strAge.Format(TEXT("%d"), pRecordInfo->UserAge);
		m_age_list.SetItemText(i, 1, strAge);
		if (pRecordInfo->UserSex == 0)
			m_age_list.SetItemText(i, 2, TEXT("��"));
		else
			m_age_list.SetItemText(i, 2, TEXT("Ů"));
		m_age_list.SetItemText(i, 3, pRecordInfo->UserSfz);
		m_age_list.SetItemText(i, 4, pRecordInfo->UserPhone);

		if (pRecordInfo->UserStatus == 0)
			m_age_list.SetItemText(i, 5, TEXT("δ����"));
		else
			m_age_list.SetItemText(i, 5, TEXT("����"));

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
			m_UserStatusList.SetItemText(i, 5, TEXT("�ɻ�"));
		else if (pRecordInfo->UserTool == 1)
			m_UserStatusList.SetItemText(i, 5, TEXT("��"));
		else if (pRecordInfo->UserTool == 2)
			m_UserStatusList.SetItemText(i, 5, TEXT("����"));
		else if (pRecordInfo->UserTool == 3)
			m_UserStatusList.SetItemText(i, 5, TEXT("�Լ�"));
		else if (pRecordInfo->UserTool == 4)
			m_UserStatusList.SetItemText(i, 5, TEXT("����"));
		else
			m_UserStatusList.SetItemText(i, 5, TEXT("����"));

		m_UserStatusList.SetItemText(i, 6, pRecordInfo->ToolInfo);

		if (pRecordInfo->Hasisolace == 0)
			m_UserStatusList.SetItemText(i, 7, TEXT("��"));
		else
			m_UserStatusList.SetItemText(i, 7, TEXT("��"));

		if (pRecordInfo->Hasinfect == 0)
			m_UserStatusList.SetItemText(i, 8, TEXT("��"));
		else
			m_UserStatusList.SetItemText(i, 8, TEXT("��"));

		pRecordInfo = pRecordInfo->Next;
		delete pDelete;
		pDelete = pRecordInfo;
	}

}
void CUserQuery::OnSelchangeCombo1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
