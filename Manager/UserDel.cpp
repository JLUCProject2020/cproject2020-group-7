// UserDel.cpp : 实现文件
//

#include "stdafx.h"
#include "Manager.h"
#include "UserDel.h"
#include "afxdialogex.h"
#include "AdoWorker.h"


// CUserDel 对话框

IMPLEMENT_DYNAMIC(CUserDel, CDialogEx)

CUserDel::CUserDel(CWnd* pParent /*=NULL*/)
	: CDialogEx(CUserDel::IDD, pParent)
	, m_user_name(_T(""))
{

}

CUserDel::~CUserDel()
{
}

void CUserDel::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_user_name);
}


BEGIN_MESSAGE_MAP(CUserDel, CDialogEx)
	ON_BN_CLICKED(IDOK, &CUserDel::OnBnClickedOk)
END_MESSAGE_MAP()


// CUserDel 消息处理程序


void CUserDel::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);

	if (m_user_name.IsEmpty())    /*判断用户名信息是否为空*/
	{
		AfxMessageBox(TEXT("请输入用户名！"));
		return;
	}

	CString strSqlText;


	strSqlText.Format(TEXT("delete from UserInfo  where UserName='%s'"), m_user_name);


	AdoWorker *ado = NULL;
	ado = new AdoWorker();
	BOOL bExec = FALSE;
	//先删除原有数据

	bExec = ado->ExecuteSql(strSqlText);//将数据插入到了表格中

	if (bExec)
	{
		CDialogEx::OnOK();
	}
	else
		AfxMessageBox(TEXT("用户名字不正确，请检查！"));

	CDialogEx::OnOK();
}
