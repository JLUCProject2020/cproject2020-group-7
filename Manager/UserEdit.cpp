// UserEdit.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Manager.h"
#include "UserEdit.h"
#include "afxdialogex.h"
#include "AdoWorker.h"
#include "_StructDefine.h"


// CUserEdit �Ի���

IMPLEMENT_DYNAMIC(CUserEdit, CDialogEx)

CUserEdit::CUserEdit(CWnd* pParent /*=NULL*/)
	: CDialogEx(CUserEdit::IDD, pParent)
	, m_user_name(_T(""))
	, m_age(0)
	, m_sfz(_T(""))
	, m_phone(_T(""))
	, m_addr(_T(""))
{

}

CUserEdit::~CUserEdit()
{
}

void CUserEdit::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_user_name);
	DDX_Text(pDX, IDC_EDIT3, m_age);
	DDX_Control(pDX, IDC_COMBO1, m_sex);
	DDX_Text(pDX, IDC_EDIT4, m_sfz);
	DDX_Text(pDX, IDC_EDIT5, m_phone);
	DDX_Control(pDX, IDC_COMBO2, m_status);
	DDX_Text(pDX, IDC_EDIT6, m_addr);
}


BEGIN_MESSAGE_MAP(CUserEdit, CDialogEx)
	ON_BN_CLICKED(IDC_QUERY, &CUserEdit::OnBnClickedButton1)
	ON_BN_CLICKED(IDOK, &CUserEdit::OnBnClickedOk)
END_MESSAGE_MAP()


// CUserEdit ��Ϣ�������


void CUserEdit::OnBnClickedButton1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if (m_user_name.IsEmpty())    /*�ж��û�����Ϣ�Ƿ�Ϊ��*/
	{
		AfxMessageBox(TEXT("�������û�����"));
		return;
	}

	CString strSqlText;
	strSqlText.Format(TEXT("select * from userinfo where UserName='%s'"), m_user_name);

	//////////////////////////////////����SQL���ִ����ʵ��
	AdoWorker *ado = NULL;
	_UserInfo *pUserNameInfo = NULL;
	ado = new AdoWorker();
	pUserNameInfo = (_UserInfo *)ado->ExecuteSql(strSqlText, 0);

	if (pUserNameInfo == NULL)
	{
		MessageBox(TEXT("û���������˺ţ����ȼ���˺ŵ���ȷ�ԣ�"), NULL, MB_ICONERROR);
		delete pUserNameInfo;
		delete ado;
		return;
	}
	else//�����������˺ţ��ڴ��趨����еڶ��е�����
	{
		m_user_name = pUserNameInfo->UserName;
		m_age = pUserNameInfo->UserAge;
		m_sex.SetCurSel(pUserNameInfo->UserSex);
		m_sfz = pUserNameInfo->UserSfz;
		m_phone = pUserNameInfo->UserPhone;
		m_addr = pUserNameInfo->UserAddress;
		m_status.SetCurSel(pUserNameInfo->UserStatus);

		delete pUserNameInfo;
		delete ado;
	}
	UpdateData(FALSE);
}


void CUserEdit::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);

	if (m_user_name.IsEmpty())    /*�ж��û�����Ϣ�Ƿ�Ϊ��*/
	{
		AfxMessageBox(TEXT("�������û�����"));
		return;
	}
	if (m_sfz.IsEmpty())    /*�ж���Ϣ�Ƿ�Ϊ��*/
	{
		AfxMessageBox(TEXT("�������û����룡"));
		return;
	}
	if (m_phone.IsEmpty())    /*�ж���Ϣ�Ƿ�Ϊ��*/
	{
		AfxMessageBox(TEXT("�������û����֤��Ϣ��"));
		return;
	}
	if (m_addr.IsEmpty())    /*�ж���Ϣ�Ƿ�Ϊ��*/
	{
		AfxMessageBox(TEXT("�������û���ַ��"));
		return;
	}

	if (CheckID(m_sfz) == false)
	{
		AfxMessageBox(TEXT("���֤��Ϣ����ȷ,���������룡"));
		return;
	}
	CString strSqlText;
	

	strSqlText.Format(TEXT("update UserInfo set UserAge=%d,UserSex=%d,UserSfz='%s',UserPhone='%s',UserStatus=%d,UserAddr='%s' where UserName='%s'"), m_age, m_sex.GetCurSel(), m_sfz, m_phone, m_status.GetCurSel(), m_addr, m_user_name);





	AdoWorker *ado = NULL;
	ado = new AdoWorker();
	BOOL bExec = FALSE;
	//��ɾ��ԭ������

	bExec = ado->ExecuteSql(strSqlText);//�����ݲ��뵽�˱����

	if (bExec)
	{
		m_nSex = m_sex.GetCurSel();
		m_nStatus = m_status.GetCurSel();
		CDialogEx::OnOK();
	}
	else
		AfxMessageBox(TEXT("�û������г�ͻ�����飡"));

	CDialogEx::OnOK();
}


BOOL CUserEdit::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_user_name = TEXT("");
	m_sfz = TEXT("");
	m_phone = TEXT("");
	m_addr = TEXT("");
	m_age = 0;

	m_sex.AddString(TEXT("��"));
	m_sex.AddString(TEXT("Ů"));
	m_sex.SetCurSel(0);

	m_status.AddString(TEXT("δ����"));
	m_status.AddString(TEXT("����"));
	m_status.SetCurSel(0);

	UpdateData(FALSE);

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}
bool CUserEdit::CheckID(CString ID_num)/*���֤У��*/
{
	int weight[] = { 7, 9, 10, 5, 8, 4, 2, 1, 6, 3, 7, 9, 10, 5, 8, 4, 2 };
	char validate[] = { '1', '0', 'X', '9', '8', '7', '6', '5', '4', '3', '2' };
	int sum = 0;
	int mode = 0;
	int i = 0;
	int length = ID_num.GetLength();
	if (length == 18)
	{
		for (i = 0; i<length - 1; i++)
			sum = sum + (ID_num[i] - '0') * weight[i];
		mode = sum % 11;
		if (validate[mode] == ID_num[17])
			return true;
	}
	return false;
}
