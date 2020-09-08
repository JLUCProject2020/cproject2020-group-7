// UserManager.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Manager.h"
#include "UserManager.h"
#include "afxdialogex.h"


// CUserManager �Ի���

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


// CUserManager ��Ϣ�������


void CUserManager::OnBnClickedAdd()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (m_UserAddDlg.DoModal() == IDOK)
	{
		//AfxMessageBox(m_UserAddDlg.m_user_name);
		m_UserList.SetItemText(0, 0, m_UserAddDlg.m_user_name);
		CString strAge = _T("");
		strAge.Format(TEXT("%d"), m_UserAddDlg.m_age);
		m_UserList.SetItemText(0, 1, strAge);
		if (m_UserAddDlg.m_nSex==0)
			m_UserList.SetItemText(0, 2, TEXT("��"));
		else
			m_UserList.SetItemText(0, 2, TEXT("Ů"));
		m_UserList.SetItemText(0, 3, m_UserAddDlg.m_sfz);
		m_UserList.SetItemText(0, 4, m_UserAddDlg.m_phone);

		if (m_UserAddDlg.m_nStatus == 0)
			m_UserList.SetItemText(0, 5, TEXT("δ����"));
		else
			m_UserList.SetItemText(0, 5, TEXT("����"));

		m_UserList.SetItemText(0, 6, m_UserAddDlg.m_addr);
	};
}


void CUserManager::OnBnClickedEdit()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (m_UserEditDlg.DoModal() == IDOK)
	{
		m_UserList.DeleteAllItems();
		m_UserList.InsertItem(0, NULL);//�²���һ��
		//AfxMessageBox(m_UserAddDlg.m_user_name);
		m_UserList.SetItemText(0, 0, m_UserEditDlg.m_user_name);
		CString strAge = _T("");
		strAge.Format(TEXT("%d"), m_UserEditDlg.m_age);
		m_UserList.SetItemText(0, 1, strAge);
		if (m_UserAddDlg.m_nSex == 0)
			m_UserList.SetItemText(0, 2, TEXT("��"));
		else
			m_UserList.SetItemText(0, 2, TEXT("Ů"));
		m_UserList.SetItemText(0, 3, m_UserEditDlg.m_sfz);
		m_UserList.SetItemText(0, 4, m_UserEditDlg.m_phone);

		if (m_UserAddDlg.m_nStatus == 0)
			m_UserList.SetItemText(0, 5, TEXT("δ����"));
		else
			m_UserList.SetItemText(0, 5, TEXT("����"));

		m_UserList.SetItemText(0, 6, m_UserEditDlg.m_addr);
	};
}


void CUserManager::OnBnClickedDel()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	m_UserDelDlg.DoModal();

}


BOOL CUserManager::OnInitDialog()
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



	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void CUserManager::OnBnClickedUserStatusAdd()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (m_UserStatusDlg.DoModal() == IDOK)
	{
		//AfxMessageBox(m_UserAddDlg.m_user_name);
		m_UserStatusList.SetItemText(0, 0, m_UserStatusDlg.m_user_name);
		m_UserStatusList.SetItemText(0, 1, m_UserStatusDlg.m_begin_time);
		m_UserStatusList.SetItemText(0, 2, m_UserStatusDlg.m_end_time);
		m_UserStatusList.SetItemText(0, 3, m_UserStatusDlg.m_begin_addr);
		m_UserStatusList.SetItemText(0, 4, m_UserStatusDlg.m_end_addr);
		
		if (m_UserStatusDlg.m_nTool == 0)
			m_UserStatusList.SetItemText(0, 5, TEXT("�ɻ�"));
		else if (m_UserStatusDlg.m_nTool == 1)
			m_UserStatusList.SetItemText(0, 5, TEXT("��"));
		else if (m_UserStatusDlg.m_nTool == 2)
			m_UserStatusList.SetItemText(0, 5, TEXT("����"));
		else if (m_UserStatusDlg.m_nTool == 3)
			m_UserStatusList.SetItemText(0, 5, TEXT("�Լ�"));
		else if (m_UserStatusDlg.m_nTool == 4)
			m_UserStatusList.SetItemText(0, 5, TEXT("����"));
		else
			m_UserStatusList.SetItemText(0, 5, TEXT("����"));

		m_UserStatusList.SetItemText(0, 6, m_UserStatusDlg.m_tool_info);

		if (m_UserStatusDlg.m_nOlace == 0)
			m_UserStatusList.SetItemText(0, 7, TEXT("��"));
		else
			m_UserStatusList.SetItemText(0, 7, TEXT("��"));

		if (m_UserStatusDlg.m_nInfect == 0)
			m_UserStatusList.SetItemText(0, 8, TEXT("��"));
		else
			m_UserStatusList.SetItemText(0, 8, TEXT("��"));

		
	};

}


void CUserManager::OnBnClickedUserStatusEdit()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	m_UserStatusEditDlg.DoModal();
}


void CUserManager::OnBnClickedUserStatusDel()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	m_UserStatusDelDlg.DoModal();
}
