// UserAdd.cpp : 实现文件
//

#include "stdafx.h"
#include "Manager.h"
#include "UserAdd.h"
#include "afxdialogex.h"
#include "AdoWorker.h"


// CUserAdd 对话框

IMPLEMENT_DYNAMIC(CUserAdd, CDialogEx)

CUserAdd::CUserAdd(CWnd* pParent /*=NULL*/)
	: CDialogEx(CUserAdd::IDD, pParent)
	, m_user_name(_T(""))
	, m_age(0)
	, m_sfz(_T(""))
	, m_phone(_T(""))
{

}

CUserAdd::~CUserAdd()
{
}

void CUserAdd::DoDataExchange(CDataExchange* pDX)
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


BEGIN_MESSAGE_MAP(CUserAdd, CDialogEx)
	ON_BN_CLICKED(IDOK, &CUserAdd::OnBnClickedOk)
END_MESSAGE_MAP()


BOOL CUserAdd::OnInitDialog()
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

// CUserAdd 消息处理程序


void CUserAdd::OnBnClickedOk()
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
	strSqlText.Format(TEXT("insert into UserInfo(UserName,UserAge,UserSex,UserSfz,UserPhone,UserStatus,UserAddr) values ('%s',%d,%d,'%s','%s',%d,'%s')"),
		m_user_name, m_age, m_sex.GetCurSel(), m_sfz, m_phone, m_status.GetCurSel(), m_addr);

	//strSqlText.Format(TEXT("insert into UserInfo(UserName) values ('%s')"),m_user_name);





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

	delete ado;
}

bool CUserAdd::CheckID(CString ID_num)/*身份证校验*/
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



