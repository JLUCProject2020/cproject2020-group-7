// Login.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Manager.h"
#include "Login.h"
#include "afxdialogex.h"
#include "AdoWorker.h"


// CLogin �Ի���

IMPLEMENT_DYNAMIC(CLogin, CDialogEx)

CLogin::CLogin(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLogin::IDD, pParent)
	, m_user_name(_T(""))
	, m_user_password(_T(""))
{

}

CLogin::~CLogin()
{
}

void CLogin::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_USER_NAME, m_user_name);
	DDX_Text(pDX, IDC_USER_PASSWORD, m_user_password);
}


BEGIN_MESSAGE_MAP(CLogin, CDialogEx)
	ON_BN_CLICKED(IDOK, &CLogin::OnBnClickedOk)
END_MESSAGE_MAP()


// CLogin ��Ϣ�������


void CLogin::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);

	if (m_user_name.IsEmpty())    /*�ж��û�����Ϣ�Ƿ�Ϊ��*/
	{
		AfxMessageBox(TEXT("�������û�����"));
		return;
	}
	if (m_user_password.IsEmpty())    /*�ж���Ϣ�Ƿ�Ϊ��*/
	{
		AfxMessageBox(TEXT("�������û����룡"));
		return;
	}

	AdoWorker *ado = NULL;
	ado = new AdoWorker();

	CString strSqlText;
	
	strSqlText.Format(TEXT("select * from manager where UserName='%s' and UserPass='%s'"), m_user_name, m_user_password);
	if (ado->ExecuteSql(strSqlText,2))
	{
		delete ado;
		CDialog::OnOK();
	}
	else
	{
		AfxMessageBox(TEXT("�û����������������������"));
		delete ado;
		return;
	}



	
	
}
