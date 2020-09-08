// UserStatusEdit.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Manager.h"
#include "UserStatusEdit.h"
#include "afxdialogex.h"
#include "AdoWorker.h"
#include "_StructDefine.h"

// CUserStatusEdit �Ի���

IMPLEMENT_DYNAMIC(CUserStatusEdit, CDialogEx)

CUserStatusEdit::CUserStatusEdit(CWnd* pParent /*=NULL*/)
	: CDialogEx(CUserStatusEdit::IDD, pParent)
	, m_user_name(_T(""))
{

}

CUserStatusEdit::~CUserStatusEdit()
{
}

void CUserStatusEdit::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_user_name);
	DDX_Control(pDX, IDC_USER_LIST2, m_UserStatusList);
}


BEGIN_MESSAGE_MAP(CUserStatusEdit, CDialogEx)
	ON_BN_CLICKED(IDC_QUERY, &CUserStatusEdit::OnBnClickedQuery)
	ON_BN_CLICKED(IDOK, &CUserStatusEdit::OnBnClickedOk)
END_MESSAGE_MAP()


// CUserStatusEdit ��Ϣ�������





BOOL CUserStatusEdit::OnInitDialog()
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

void CUserStatusEdit::OnBnClickedQuery()
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

void CUserStatusEdit::WriteList(_RecordStatusInfo *pRecordInfo)
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


void CUserStatusEdit::OnBnClickedOk()
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
		int nItem = m_UserStatusList.GetNextSelectedItem(pos);

		m_UserStatusEdit1Dlg.m_nAutoId = _ttoi(m_UserStatusList.GetItemText(nItem, 0));
		m_UserStatusEdit1Dlg.m_user_name = m_UserStatusList.GetItemText(nItem, 1);
		m_UserStatusEdit1Dlg.m_begin_time = m_UserStatusList.GetItemText(nItem, 2);
		m_UserStatusEdit1Dlg.m_end_time = m_UserStatusList.GetItemText(nItem, 3);
		m_UserStatusEdit1Dlg.m_begin_addr = m_UserStatusList.GetItemText(nItem, 4);
		m_UserStatusEdit1Dlg.m_end_addr = m_UserStatusList.GetItemText(nItem, 5);

		CString strTool = m_UserStatusList.GetItemText(nItem, 6);
		if (strTool == TEXT("�ɻ�"))
			m_UserStatusEdit1Dlg.m_nTool = 0;
		else if (strTool == TEXT("��"))
			m_UserStatusEdit1Dlg.m_nTool = 1;
		else if (strTool == TEXT("����"))
			m_UserStatusEdit1Dlg.m_nTool = 2;
		else if (strTool == TEXT("�Լ�"))
			m_UserStatusEdit1Dlg.m_nTool = 3;
		else if (strTool == TEXT("����"))
			m_UserStatusEdit1Dlg.m_nTool = 4;
		else
			m_UserStatusEdit1Dlg.m_nTool = 5;

		

		m_UserStatusEdit1Dlg.m_tool_info = m_UserStatusList.GetItemText(nItem, 7);

		CString strTool1 = m_UserStatusList.GetItemText(nItem, 8);
		if (strTool1 == TEXT("��"))
			m_UserStatusEdit1Dlg.m_nOlace = 0;
		else 
			m_UserStatusEdit1Dlg.m_nOlace = 1;
		

		CString strTool2 = m_UserStatusList.GetItemText(nItem, 9);
		if (strTool2 == TEXT("��"))
			m_UserStatusEdit1Dlg.m_nInfect = 0;
		else
			m_UserStatusEdit1Dlg.m_nInfect = 1;
		

		if (m_UserStatusEdit1Dlg.DoModal() == IDOK)
		{
			CString strAutoId;
			strAutoId.Format(TEXT("%d"), m_UserStatusEdit1Dlg.m_nAutoId);
			m_UserStatusList.SetItemText(nItem, 0, strAutoId);
			m_UserStatusList.SetItemText(nItem, 1, m_UserStatusEdit1Dlg.m_user_name);
			m_UserStatusList.SetItemText(nItem, 2, m_UserStatusEdit1Dlg.m_begin_time);
			m_UserStatusList.SetItemText(nItem, 3, m_UserStatusEdit1Dlg.m_end_time);
			m_UserStatusList.SetItemText(nItem, 4, m_UserStatusEdit1Dlg.m_begin_addr);
			m_UserStatusList.SetItemText(nItem, 5, m_UserStatusEdit1Dlg.m_end_addr);

			if (m_UserStatusEdit1Dlg.m_nTool == 0)
				m_UserStatusList.SetItemText(nItem, 6, TEXT("�ɻ�"));
			else if (m_UserStatusEdit1Dlg.m_nTool == 1)
				m_UserStatusList.SetItemText(nItem, 6, TEXT("��"));
			else if (m_UserStatusEdit1Dlg.m_nTool == 2)
				m_UserStatusList.SetItemText(nItem, 6, TEXT("����"));
			else if (m_UserStatusEdit1Dlg.m_nTool == 3)
				m_UserStatusList.SetItemText(nItem, 6, TEXT("�Լ�"));
			else if (m_UserStatusEdit1Dlg.m_nTool == 4)
				m_UserStatusList.SetItemText(nItem, 6, TEXT("����"));
			else
				m_UserStatusList.SetItemText(nItem, 6, TEXT("����"));

			m_UserStatusList.SetItemText(nItem, 7, m_UserStatusEdit1Dlg.m_tool_info);

			if (m_UserStatusEdit1Dlg.m_nOlace == 0)
				m_UserStatusList.SetItemText(nItem, 8, TEXT("��"));
			else
				m_UserStatusList.SetItemText(nItem, 8, TEXT("��"));

			if (m_UserStatusEdit1Dlg.m_nInfect == 0)
				m_UserStatusList.SetItemText(nItem, 9, TEXT("��"));
			else
				m_UserStatusList.SetItemText(nItem, 9, TEXT("��"));

		}


	}
	
}
