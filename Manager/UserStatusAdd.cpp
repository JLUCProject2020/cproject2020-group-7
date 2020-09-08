// UserStatusAdd.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Manager.h"
#include "UserStatusAdd.h"
#include "afxdialogex.h"
#include "AdoWorker.h"


// CUserStatusAdd �Ի���

IMPLEMENT_DYNAMIC(CUserStatusAdd, CDialogEx)

CUserStatusAdd::CUserStatusAdd(CWnd* pParent /*=NULL*/)
	: CDialogEx(CUserStatusAdd::IDD, pParent)
	, m_user_name(_T(""))
	, m_begin_time(_T(""))
	, m_end_time(_T(""))
	, m_begin_addr(_T(""))
	, m_end_addr(_T(""))
	, m_tool_info(_T(""))
{

}

CUserStatusAdd::~CUserStatusAdd()
{
}

void CUserStatusAdd::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_user_name);
	DDX_Text(pDX, IDC_EDIT3, m_begin_time);
	DDX_Text(pDX, IDC_EDIT7, m_end_time);
	DDX_Text(pDX, IDC_EDIT4, m_begin_addr);
	DDX_Text(pDX, IDC_EDIT5, m_end_addr);
	DDX_Control(pDX, IDC_COMBO2, m_tool);
	DDX_Text(pDX, IDC_EDIT6, m_tool_info);
	DDX_Control(pDX, IDC_COMBO3, m_is_olace);
	DDX_Control(pDX, IDC_COMBO4, m_is_infect);
}


BEGIN_MESSAGE_MAP(CUserStatusAdd, CDialogEx)
	ON_BN_CLICKED(IDOK, &CUserStatusAdd::OnBnClickedOk)
END_MESSAGE_MAP()


// CUserStatusAdd ��Ϣ�������


BOOL CUserStatusAdd::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	m_user_name = TEXT("");
	m_begin_time = TEXT("");
	m_end_time = TEXT("");
	m_begin_addr = TEXT("");
	m_end_addr = TEXT("");
	m_tool_info = TEXT("");
	

	m_tool.AddString(TEXT("�ɻ�"));
	m_tool.AddString(TEXT("��"));
	m_tool.AddString(TEXT("����"));
	m_tool.AddString(TEXT("�Լ�"));
	m_tool.AddString(TEXT("����"));
	m_tool.AddString(TEXT("����"));
	m_tool.SetCurSel(0);

	m_is_olace.AddString(TEXT("��"));
	m_is_olace.AddString(TEXT("��"));
	m_is_olace.SetCurSel(0);

	m_is_infect.AddString(TEXT("��"));
	m_is_infect.AddString(TEXT("��"));
	m_is_infect.SetCurSel(0);

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void CUserStatusAdd::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);

	if (m_user_name.IsEmpty())    /*�ж��û�����Ϣ�Ƿ�Ϊ��*/
	{
		AfxMessageBox(TEXT("�������û�����"));
		return;
	}
	if (m_begin_time.IsEmpty())    /*�ж���Ϣ�Ƿ�Ϊ��*/
	{
		AfxMessageBox(TEXT("�����뿪ʼʱ�䣡"));
		return;
	}
	if (m_end_time.IsEmpty())    /*�ж���Ϣ�Ƿ�Ϊ��*/
	{
		AfxMessageBox(TEXT("���������ʱ�䣡"));
		return;
	}
	if (m_begin_addr.IsEmpty())    /*�ж���Ϣ�Ƿ�Ϊ��*/
	{
		AfxMessageBox(TEXT("�����뿪ʼ��ַ��"));
		return;
	}
	if (m_end_addr.IsEmpty())    /*�ж���Ϣ�Ƿ�Ϊ��*/
	{
		AfxMessageBox(TEXT("�����������ַ��"));
		return;
	}
	if (m_tool_info.IsEmpty())    /*�ж���Ϣ�Ƿ�Ϊ��*/
	{
		AfxMessageBox(TEXT("�����빤����Ϣ��"));
		return;
	}


	CString strSqlText;

	strSqlText.Format(TEXT("insert into RecordInfo(UserName,BeginTime,EndTime,BeginAddr,EndAddr,ToolInfo,HasIsOlace,HasIsInfect,UserTool) values ('%s','%s','%s','%s','%s','%s',%d,%d,%d)"),
		m_user_name, m_begin_time, m_end_time, m_begin_addr, m_end_addr, m_tool_info, m_is_olace.GetCurSel(), m_is_infect.GetCurSel(), m_tool.GetCurSel());





	AdoWorker *ado = NULL;
	ado = new AdoWorker();
	BOOL bExec = FALSE;
	//��ɾ��ԭ������

	bExec = ado->ExecuteSql(strSqlText);//�����ݲ��뵽�˱����

	if (bExec)
	{
		m_nTool = m_tool.GetCurSel();
		m_nOlace = m_is_olace.GetCurSel();
		m_nInfect = m_is_infect.GetCurSel();
		CDialogEx::OnOK();
	}
	else
		AfxMessageBox(TEXT("�û������г�ͻ�����飡"));

	CDialogEx::OnOK();
}
