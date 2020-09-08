// UserStatusDel.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Manager.h"
#include "UserStatusDel.h"
#include "afxdialogex.h"
#include "AdoWorker.h"
#include "_StructDefine.h"


// CUserStatusDel �Ի���

IMPLEMENT_DYNAMIC(CUserStatusDel, CDialogEx)

CUserStatusDel::CUserStatusDel(CWnd* pParent /*=NULL*/)
	: CDialogEx(CUserStatusDel::IDD, pParent)
	, m_user_name(_T(""))
{

}

CUserStatusDel::~CUserStatusDel()
{
}

void CUserStatusDel::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_user_name);
	DDX_Control(pDX, IDC_USER_LIST2, m_UserStatusList);
}


BEGIN_MESSAGE_MAP(CUserStatusDel, CDialogEx)
	ON_BN_CLICKED(IDC_QUERY, &CUserStatusDel::OnBnClickedQuery)
	ON_BN_CLICKED(IDOK, &CUserStatusDel::OnBnClickedOk)
END_MESSAGE_MAP()


// CUserStatusDel ��Ϣ�������


BOOL CUserStatusDel::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	m_UserStatusList.InsertColumn(0, TEXT("ID"), LVCFMT_LEFT, 30);
	m_UserStatusList.InsertColumn(1, TEXT("����"), LVCFMT_LEFT, 80);
	m_UserStatusList.InsertColumn(2, TEXT("��ʼʱ��"), LVCFMT_LEFT, 80);
	m_UserStatusList.InsertColumn(3, TEXT("����ʱ��"), LVCFMT_LEFT, 80);
	m_UserStatusList.InsertColumn(4, TEXT("���е�ַ"), LVCFMT_LEFT, 100);
	m_UserStatusList.InsertColumn(5, TEXT("������ַ"), LVCFMT_LEFT, 100);
	m_UserStatusList.InsertColumn(6, TEXT("���й���"), LVCFMT_LEFT, 60);
	m_UserStatusList.InsertColumn(7, TEXT("������Ϣ"), LVCFMT_LEFT, 120);
	m_UserStatusList.InsertColumn(8, TEXT("����"), LVCFMT_LEFT, 40);
	m_UserStatusList.InsertColumn(9, TEXT("����"), LVCFMT_LEFT, 40);

	m_UserStatusList.SetExtendedStyle(LVS_EX_GRIDLINES);
	m_UserStatusList.InsertItem(0, NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void CUserStatusDel::OnBnClickedQuery()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if (m_user_name.IsEmpty())    /*�ж��û�����Ϣ�Ƿ�Ϊ��*/
	{
		AfxMessageBox(TEXT("�������û�����"));
		return;
	}

	CString strSqlText;
	strSqlText.Format(TEXT("select * from Recordinfo where UserName='%s'"), m_user_name);

	//////////////////////////////////����SQL���ִ����ʵ��
	AdoWorker *ado = NULL;
	_RecordStatusInfo *pUserNameInfo = NULL;
	ado = new AdoWorker();
	pUserNameInfo = (_RecordStatusInfo *)ado->ExecuteSql(strSqlText, 3);

	if (pUserNameInfo == NULL)
	{
		MessageBox(TEXT("û���������˺ţ����ȼ���˺ŵ���ȷ�ԣ�"), NULL, MB_ICONERROR);
		delete pUserNameInfo;
		delete ado;
		return;
	}
	else//�����������˺ţ��ڴ��趨����еڶ��е�����
	{

		WriteList(pUserNameInfo);

		delete ado;
	}
	UpdateData(FALSE);
}

void CUserStatusDel::WriteList(_RecordStatusInfo *pRecordInfo)
{
	_RecordStatusInfo *pDelete = NULL;
	pDelete = pRecordInfo;
	for (int i = 0; pRecordInfo != NULL; i++)
	{
		m_UserStatusList.InsertItem(i, NULL);

		CString strAutoId = _T("");
		strAutoId.Format(TEXT("%d"), pRecordInfo->AutoId);
		m_UserStatusList.SetItemText(i, 0, strAutoId);
		m_UserStatusList.SetItemText(i, 1, pRecordInfo->UserName);
		m_UserStatusList.SetItemText(i, 2, pRecordInfo->BeginTime);
		m_UserStatusList.SetItemText(i, 3, pRecordInfo->EndTime);
		m_UserStatusList.SetItemText(i, 4, pRecordInfo->BeginAddr);
		m_UserStatusList.SetItemText(i, 5, pRecordInfo->EndAddr);

		if (pRecordInfo->UserTool == 0)
			m_UserStatusList.SetItemText(i, 6, TEXT("�ɻ�"));
		else if (pRecordInfo->UserTool == 1)
			m_UserStatusList.SetItemText(i, 6, TEXT("��"));
		else if (pRecordInfo->UserTool == 2)
			m_UserStatusList.SetItemText(i, 6, TEXT("����"));
		else if (pRecordInfo->UserTool == 3)
			m_UserStatusList.SetItemText(i, 6, TEXT("�Լ�"));
		else if (pRecordInfo->UserTool == 4)
			m_UserStatusList.SetItemText(i, 6, TEXT("����"));
		else
			m_UserStatusList.SetItemText(i, 6, TEXT("����"));

		m_UserStatusList.SetItemText(i, 7, pRecordInfo->ToolInfo);

		if (pRecordInfo->Hasisolace == 0)
			m_UserStatusList.SetItemText(i, 8, TEXT("��"));
		else
			m_UserStatusList.SetItemText(i, 8, TEXT("��"));

		if (pRecordInfo->Hasinfect == 0)
			m_UserStatusList.SetItemText(i, 9, TEXT("��"));
		else
			m_UserStatusList.SetItemText(i, 9, TEXT("��"));

		pRecordInfo = pRecordInfo->Next;
		delete pDelete;
		pDelete = pRecordInfo;
	}
}


void CUserStatusDel::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	POSITION pos = m_UserStatusList.GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		MessageBox(TEXT("�����б���ѡ����Ҫ�޸ĵ�ѡ�"), NULL, MB_ICONERROR);
		return;
	}
	else
	{
		CString strSqlText;

		int nItem = m_UserStatusList.GetNextSelectedItem(pos);

		m_nAutoId = _ttoi(m_UserStatusList.GetItemText(nItem, 0));

		strSqlText.Format(TEXT("delete from RecordInfo  where AutoId=%d"), m_nAutoId);
		
		AdoWorker *ado = NULL;
		ado = new AdoWorker();
		BOOL bExec = FALSE;
		//��ɾ��ԭ������

		bExec = ado->ExecuteSql(strSqlText);//�����ݲ��뵽�˱����

		if (bExec)
		{
			m_UserStatusList.DeleteItem(nItem);
			CDialogEx::OnOK();
		}
		else
			AfxMessageBox(TEXT("�û����ֲ���ȷ�����飡"));
	}

	
}
