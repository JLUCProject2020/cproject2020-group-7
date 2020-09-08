// UserStatusEdit1Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Manager.h"
#include "UserStatusEdit1Dlg.h"
#include "afxdialogex.h"
#include "AdoWorker.h"


// CUserStatusEdit1Dlg 对话框

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


// CUserStatusEdit1Dlg 消息处理程序
BOOL CUserStatusEdit1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	UpdateData(TRUE);

	// TODO:  在此添加额外的初始化
	m_tool.AddString(TEXT("飞机"));
	m_tool.AddString(TEXT("火车"));
	m_tool.AddString(TEXT("汽车"));
	m_tool.AddString(TEXT("自驾"));
	m_tool.AddString(TEXT("步行"));
	m_tool.AddString(TEXT("其他"));
	m_tool.SetCurSel(m_nTool);
	m_is_olace.AddString(TEXT("无"));
	m_is_olace.AddString(TEXT("有"));
	m_is_olace.SetCurSel(m_nOlace);
	m_is_infect.AddString(TEXT("无"));
	m_is_infect.AddString(TEXT("有"));
	m_is_infect.SetCurSel(m_nInfect);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}

void CUserStatusEdit1Dlg::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);

	if (m_user_name.IsEmpty())    /*判断信息是否为空*/
	{
		AfxMessageBox(TEXT("请输入用户名！"));
		return;
	}
	if (m_begin_time.IsEmpty())    /*判断信息是否为空*/
	{
		AfxMessageBox(TEXT("请输入开始时间！"));
		return;
	}
	if (m_end_time.IsEmpty())    /*判断信息是否为空*/
	{
		AfxMessageBox(TEXT("请输入结束时间！"));
		return;
	}
	if (m_begin_addr.IsEmpty())    /*判断信息是否为空*/
	{
		AfxMessageBox(TEXT("请输入开始地址！"));
		return;
	}
	if (m_end_addr.IsEmpty())    /*判断信息是否为空*/
	{
		AfxMessageBox(TEXT("请输入结束地址！"));
		return;
	}
	if (m_tool_info.IsEmpty())    /*判断信息是否为空*/
	{
		AfxMessageBox(TEXT("请输入工具信息！"));
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
	//先删除原有数据

	bExec = ado->ExecuteSql(strSqlText);//将数据插入到了表格中

	if (bExec)
	{
		CDialogEx::OnOK();
	}
	else
		AfxMessageBox(TEXT("用户名字有冲突，请检查！"));


	CDialogEx::OnOK();
}



