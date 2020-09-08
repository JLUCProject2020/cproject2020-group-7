// UserEdit.cpp : 实现文件
//

#include "stdafx.h"
#include "Manager.h"
#include "UserEdit.h"
#include "afxdialogex.h"
#include "AdoWorker.h"
#include "_StructDefine.h"


// CUserEdit 对话框

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


// CUserEdit 消息处理程序


void CUserEdit::OnBnClickedButton1()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (m_user_name.IsEmpty())    /*判断用户名信息是否为空*/
	{
		AfxMessageBox(TEXT("请输入用户名！"));
		return;
	}

	CString strSqlText;
	strSqlText.Format(TEXT("select * from userinfo where UserName='%s'"), m_user_name);

	//////////////////////////////////创建SQL语句执行类实例
	AdoWorker *ado = NULL;
	_UserInfo *pUserNameInfo = NULL;
	ado = new AdoWorker();
	pUserNameInfo = (_UserInfo *)ado->ExecuteSql(strSqlText, 0);

	if (pUserNameInfo == NULL)
	{
		MessageBox(TEXT("没有这样的账号，请先检查账号的正确性！"), NULL, MB_ICONERROR);
		delete pUserNameInfo;
		delete ado;
		return;
	}
	else//存在这样的账号，在此设定表格中第二行的姓名
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
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);

	if (m_user_name.IsEmpty())    /*判断用户名信息是否为空*/
	{
		AfxMessageBox(TEXT("请输入用户名！"));
		return;
	}
	if (m_sfz.IsEmpty())    /*判断信息是否为空*/
	{
		AfxMessageBox(TEXT("请输入用户密码！"));
		return;
	}
	if (m_phone.IsEmpty())    /*判断信息是否为空*/
	{
		AfxMessageBox(TEXT("请输入用户身份证信息！"));
		return;
	}
	if (m_addr.IsEmpty())    /*判断信息是否为空*/
	{
		AfxMessageBox(TEXT("请输入用户地址！"));
		return;
	}

	if (CheckID(m_sfz) == false)
	{
		AfxMessageBox(TEXT("身份证信息不正确,请重新输入！"));
		return;
	}
	CString strSqlText;
	

	strSqlText.Format(TEXT("update UserInfo set UserAge=%d,UserSex=%d,UserSfz='%s',UserPhone='%s',UserStatus=%d,UserAddr='%s' where UserName='%s'"), m_age, m_sex.GetCurSel(), m_sfz, m_phone, m_status.GetCurSel(), m_addr, m_user_name);





	AdoWorker *ado = NULL;
	ado = new AdoWorker();
	BOOL bExec = FALSE;
	//先删除原有数据

	bExec = ado->ExecuteSql(strSqlText);//将数据插入到了表格中

	if (bExec)
	{
		m_nSex = m_sex.GetCurSel();
		m_nStatus = m_status.GetCurSel();
		CDialogEx::OnOK();
	}
	else
		AfxMessageBox(TEXT("用户名字有冲突，请检查！"));

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

	m_sex.AddString(TEXT("男"));
	m_sex.AddString(TEXT("女"));
	m_sex.SetCurSel(0);

	m_status.AddString(TEXT("未出行"));
	m_status.AddString(TEXT("出行"));
	m_status.SetCurSel(0);

	UpdateData(FALSE);

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}
bool CUserEdit::CheckID(CString ID_num)/*身份证校验*/
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
