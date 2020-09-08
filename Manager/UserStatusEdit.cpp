// UserStatusEdit.cpp : 实现文件
//

#include "stdafx.h"
#include "Manager.h"
#include "UserStatusEdit.h"
#include "afxdialogex.h"
#include "AdoWorker.h"
#include "_StructDefine.h"

// CUserStatusEdit 对话框

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


// CUserStatusEdit 消息处理程序





BOOL CUserStatusEdit::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_UserStatusList.InsertColumn(0, TEXT("ID"), LVCFMT_LEFT, 30);
	m_UserStatusList.InsertColumn(1, TEXT("姓名"), LVCFMT_LEFT, 80);
	m_UserStatusList.InsertColumn(2, TEXT("开始时间"), LVCFMT_LEFT, 80);
	m_UserStatusList.InsertColumn(3, TEXT("结束时间"), LVCFMT_LEFT, 80);
	m_UserStatusList.InsertColumn(4, TEXT("出行地址"), LVCFMT_LEFT, 100);
	m_UserStatusList.InsertColumn(5, TEXT("结束地址"), LVCFMT_LEFT, 100);
	m_UserStatusList.InsertColumn(6, TEXT("出行工具"), LVCFMT_LEFT, 60);
	m_UserStatusList.InsertColumn(7, TEXT("工具信息"), LVCFMT_LEFT, 120);
	m_UserStatusList.InsertColumn(8, TEXT("隔离"), LVCFMT_LEFT, 40);
	m_UserStatusList.InsertColumn(9, TEXT("患病"), LVCFMT_LEFT, 40);

	m_UserStatusList.SetExtendedStyle(LVS_EX_GRIDLINES);
	m_UserStatusList.InsertItem(0, NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}

void CUserStatusEdit::OnBnClickedQuery()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (m_user_name.IsEmpty())    /*判断用户名信息是否为空*/
	{
		AfxMessageBox(TEXT("请输入用户名！"));
		return;
	}

	CString strSqlText;
	strSqlText.Format(TEXT("select * from Recordinfo where UserName='%s'"), m_user_name);

	//////////////////////////////////创建SQL语句执行类实例
	AdoWorker *ado = NULL;
	_RecordStatusInfo *pUserNameInfo = NULL;
	ado = new AdoWorker();
	pUserNameInfo = (_RecordStatusInfo *)ado->ExecuteSql(strSqlText, 3);

	if (pUserNameInfo == NULL)
	{
		MessageBox(TEXT("没有这样的账号，请先检查账号的正确性！"), NULL, MB_ICONERROR);
		delete pUserNameInfo;
		delete ado;
		return;
	}
	else//存在这样的账号，在此设定表格中第二行的姓名
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
			m_UserStatusList.SetItemText(i, 6, TEXT("飞机"));
		else if (pRecordInfo->UserTool == 1)
			m_UserStatusList.SetItemText(i, 6, TEXT("火车"));
		else if (pRecordInfo->UserTool == 2)
			m_UserStatusList.SetItemText(i, 6, TEXT("汽车"));
		else if (pRecordInfo->UserTool == 3)
			m_UserStatusList.SetItemText(i, 6, TEXT("自驾"));
		else if (pRecordInfo->UserTool == 4)
			m_UserStatusList.SetItemText(i, 6, TEXT("步行"));
		else
			m_UserStatusList.SetItemText(i, 6, TEXT("其他"));

		m_UserStatusList.SetItemText(i, 7, pRecordInfo->ToolInfo);

		if (pRecordInfo->Hasisolace == 0)
			m_UserStatusList.SetItemText(i, 8, TEXT("无"));
		else
			m_UserStatusList.SetItemText(i, 8, TEXT("有"));

		if (pRecordInfo->Hasinfect == 0)
			m_UserStatusList.SetItemText(i, 9, TEXT("无"));
		else
			m_UserStatusList.SetItemText(i, 9, TEXT("有"));

		pRecordInfo = pRecordInfo->Next;
		delete pDelete;
		pDelete = pRecordInfo;
	}
}


void CUserStatusEdit::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	POSITION pos = m_UserStatusList.GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		MessageBox(TEXT("请在列表中选择需要修改的选项！"), NULL, MB_ICONERROR);
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
		if (strTool == TEXT("飞机"))
			m_UserStatusEdit1Dlg.m_nTool = 0;
		else if (strTool == TEXT("火车"))
			m_UserStatusEdit1Dlg.m_nTool = 1;
		else if (strTool == TEXT("汽车"))
			m_UserStatusEdit1Dlg.m_nTool = 2;
		else if (strTool == TEXT("自驾"))
			m_UserStatusEdit1Dlg.m_nTool = 3;
		else if (strTool == TEXT("步行"))
			m_UserStatusEdit1Dlg.m_nTool = 4;
		else
			m_UserStatusEdit1Dlg.m_nTool = 5;

		

		m_UserStatusEdit1Dlg.m_tool_info = m_UserStatusList.GetItemText(nItem, 7);

		CString strTool1 = m_UserStatusList.GetItemText(nItem, 8);
		if (strTool1 == TEXT("无"))
			m_UserStatusEdit1Dlg.m_nOlace = 0;
		else 
			m_UserStatusEdit1Dlg.m_nOlace = 1;
		

		CString strTool2 = m_UserStatusList.GetItemText(nItem, 9);
		if (strTool2 == TEXT("无"))
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
				m_UserStatusList.SetItemText(nItem, 6, TEXT("飞机"));
			else if (m_UserStatusEdit1Dlg.m_nTool == 1)
				m_UserStatusList.SetItemText(nItem, 6, TEXT("火车"));
			else if (m_UserStatusEdit1Dlg.m_nTool == 2)
				m_UserStatusList.SetItemText(nItem, 6, TEXT("汽车"));
			else if (m_UserStatusEdit1Dlg.m_nTool == 3)
				m_UserStatusList.SetItemText(nItem, 6, TEXT("自驾"));
			else if (m_UserStatusEdit1Dlg.m_nTool == 4)
				m_UserStatusList.SetItemText(nItem, 6, TEXT("步行"));
			else
				m_UserStatusList.SetItemText(nItem, 6, TEXT("其他"));

			m_UserStatusList.SetItemText(nItem, 7, m_UserStatusEdit1Dlg.m_tool_info);

			if (m_UserStatusEdit1Dlg.m_nOlace == 0)
				m_UserStatusList.SetItemText(nItem, 8, TEXT("无"));
			else
				m_UserStatusList.SetItemText(nItem, 8, TEXT("有"));

			if (m_UserStatusEdit1Dlg.m_nInfect == 0)
				m_UserStatusList.SetItemText(nItem, 9, TEXT("无"));
			else
				m_UserStatusList.SetItemText(nItem, 9, TEXT("有"));

		}


	}
	
}
