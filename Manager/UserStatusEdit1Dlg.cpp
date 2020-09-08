// UserStatusEdit1Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Manager.h"
#include "UserStatusEdit1Dlg.h"
#include "afxdialogex.h"
#include "AdoWorker.h"


// CUserStatusEdit1Dlg �Ի���

IMPLEMENT_DYNAMIC(CUserStatusEdit1Dlg, CDialogEx)

CUserStatusEdit1Dlg::CUserStatusEdit1Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CUserStatusEdit1Dlg::IDD, pParent)
	, m_user_name(_T(""))
	, m_begin_time(_T(""))
	, m_end_time(_T(""))
	, m_begin_addr(_T(""))
	, m_end_addr(_T(""))
	, m_tool_info(_T(""))
{

}

CUserStatusEdit1Dlg::~CUserStatusEdit1Dlg()
{
}

void CUserStatusEdit1Dlg::DoDataExchange(CDataExchange* pDX)
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


BEGIN_MESSAGE_MAP(CUserStatusEdit1Dlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CUserStatusEdit1Dlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CUserStatusEdit1Dlg ��Ϣ�������
BOOL CUserStatusEdit1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	UpdateData(TRUE);

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_tool.AddString(TEXT("�ɻ�"));
	m_tool.AddString(TEXT("��"));
	m_tool.AddString(TEXT("����"));
	m_tool.AddString(TEXT("�Լ�"));
	m_tool.AddString(TEXT("����"));
	m_tool.AddString(TEXT("����"));
	m_tool.SetCurSel(m_nTool);
	m_is_olace.AddString(TEXT("��"));
	m_is_olace.AddString(TEXT("��"));
	m_is_olace.SetCurSel(m_nOlace);
	m_is_infect.AddString(TEXT("��"));
	m_is_infect.AddString(TEXT("��"));
	m_is_infect.SetCurSel(m_nInfect);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}

void CUserStatusEdit1Dlg::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);

	if (m_user_name.IsEmpty())    /*�ж���Ϣ�Ƿ�Ϊ��*/
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

	m_nTool = m_tool.GetCurSel();
	m_nOlace = m_is_olace.GetCurSel();
	m_nInfect = m_is_infect.GetCurSel();
	
	strSqlText.Format(TEXT("update RecordInfo set UserName='%s',BeginTime='%s',EndTime='%s',BeginAddr='%s',EndAddr='%s',ToolInfo='%s',HasIsOlace=%d,HasIsInfect=%d,UserTool=%d where AutoId=%d"),
		m_user_name, m_begin_time, m_end_time, m_begin_addr, m_end_addr, m_tool_info, m_nOlace, m_nInfect, m_nTool, m_nAutoId);

	AdoWorker *ado = NULL;
	ado = new AdoWorker();
	BOOL bExec = FALSE;
	//��ɾ��ԭ������

	bExec = ado->ExecuteSql(strSqlText);//�����ݲ��뵽�˱����

	if (bExec)
	{
		CDialogEx::OnOK();
	}
	else
		AfxMessageBox(TEXT("�û������г�ͻ�����飡"));


	CDialogEx::OnOK();
}



