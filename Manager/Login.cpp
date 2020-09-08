// Login.cpp : 实现文件
//

#include "stdafx.h"
#include "Manager.h"
#include "Login.h"
#include "afxdialogex.h"
#include "AdoWorker.h"


// CLogin 对话框

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


// CLogin 消息处理程序


void CLogin::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);

	if (m_user_name.IsEmpty())    /*判断用户名信息是否为空*/
	{
		AfxMessageBox(TEXT("请输入用户名！"));
		return;
	}
	if (m_user_password.IsEmpty())    /*判断信息是否为空*/
	{
		AfxMessageBox(TEXT("请输入用户密码！"));
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
		AfxMessageBox(TEXT("用户名或密码错误，请重新输入"));
		delete ado;
		return;
	}



	
	
}
