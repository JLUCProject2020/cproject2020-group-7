// UserTotal.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Manager.h"
#include "UserTotal.h"
#include "afxdialogex.h"
#include "AdoWorker.h"


// CUserTotal �Ի���

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


// CUserTotal ��Ϣ�������


BOOL CUserTotal::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
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

	m_type_select.AddString(TEXT("��Ա��Ϣ"));
	m_type_select.AddString(TEXT("��Ա������Ϣ"));
	m_type_select.SetCurSel(0);
	
	m_UserList.ShowWindow(SW_SHOW);
	m_UserStatusList.ShowWindow(SW_HIDE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void CUserTotal::OnBnClickedQuery()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	int nSelect = m_type_select.GetCurSel();
	if (nSelect == 0)
	{
		CString strSqlText;
		strSqlText.Format(TEXT("select * from userinfo"));
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
	else if (nSelect == 1)
	{
		CString strSqlText;
		strSqlText.Format(TEXT("select * from Recordinfo"));

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
		m_UserList.InsertItem(i, NULL);//�²���һ��
		//AfxMessageBox(m_UserAddDlg.m_user_name);
		m_UserList.SetItemText(i, 0, pRecordInfo->UserName);
		CString strAge = _T("");
		strAge.Format(TEXT("%d"), pRecordInfo->UserAge);
		m_UserList.SetItemText(i, 1, strAge);
		if (pRecordInfo->UserSex == 0)
			m_UserList.SetItemText(i, 2, TEXT("��"));
		else
			m_UserList.SetItemText(i, 2, TEXT("Ů"));
		m_UserList.SetItemText(i, 3, pRecordInfo->UserSfz);
		m_UserList.SetItemText(i, 4, pRecordInfo->UserPhone);

		if (pRecordInfo->UserStatus == 0)
			m_UserList.SetItemText(i, 5, TEXT("δ����"));
		else
			m_UserList.SetItemText(i, 5, TEXT("����"));

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

void CUserTotal::OnSelchangeCombo1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
