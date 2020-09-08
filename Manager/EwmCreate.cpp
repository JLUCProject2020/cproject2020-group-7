// EwmCreate.cpp : 实现文件
//

#include "stdafx.h"
#include "Manager.h"
#include "EwmCreate.h"
#include "afxdialogex.h"
#include "AdoWorker.h"
#include "_StructDefine.h"
#include "QRCode\\ProductQRCode.h"

// CEwmCreate 对话框

IMPLEMENT_DYNAMIC(CEwmCreate, CDialogEx)

CEwmCreate::CEwmCreate(CWnd* pParent /*=NULL*/)
	: CDialogEx(CEwmCreate::IDD, pParent)
	, m_user_name(_T(""))
{
}

CEwmCreate::~CEwmCreate()
{
	
}

void CEwmCreate::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_USER_NAME, m_user_name);

	DDX_Control(pDX, IDC_STATIC_PIC, m_picture);
}


BEGIN_MESSAGE_MAP(CEwmCreate, CDialogEx)
	ON_BN_CLICKED(IDC_QUERY, &CEwmCreate::OnBnClickedQuery)

	ON_WM_PAINT()
END_MESSAGE_MAP()


// CEwmCreate 消息处理程序


BOOL CEwmCreate::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void CEwmCreate::OnBnClickedQuery()
{
	UpdateData(TRUE);
	if (m_user_name.IsEmpty())    /*判断用户名信息是否为空*/
	{
		AfxMessageBox(TEXT("请输入用户名！"));
		return;
	}

	CString Info = TEXT("");
	Info = OnUserInfo(m_user_name) + TEXT("\n") + OnUserStatusInfo(m_user_name);

	CString  strPathName,strFileName;
	GetModuleFileName(NULL, strPathName.GetBuffer(256), 256);
	strPathName.ReleaseBuffer(256);
	int nPos = strPathName.ReverseFind('\\');
	strPathName = strPathName.Left(nPos + 1);   
	strFileName = strPathName + TEXT("evm\\") + m_user_name + TEXT(".bmp");
	m_file_name = strFileName;
	if(Info != "")
	{
		if (gyProductQRCode(10, Info.GetBuffer(0), m_file_name.GetBuffer(0)))
		{
			Showpicture(m_file_name);
		}
		else
		{
			MessageBox(_T("错误!"));
		}
		//CreateEwm(Info);
	}
}

CString  CEwmCreate::OnUserInfo(CString UserName)
{
	CString Info = TEXT("");

	CString strSqlText;
	strSqlText.Format(TEXT("select * from userinfo where UserName='%s'"), UserName);

	//////////////////////////////////创建SQL语句执行类实例
	AdoWorker *ado = NULL;
	_UserInfo *pUserNameInfo = NULL;
	ado = new AdoWorker();
	pUserNameInfo = (_UserInfo *)ado->ExecuteSql(strSqlText, 0);

	if (pUserNameInfo == NULL)
	{
		AfxMessageBox(TEXT("没有这个用户！"));
		delete pUserNameInfo;
		delete ado;
		return TEXT("");
	}
	else//存在这样的账号，在此设定表格中第二行的姓名
	{
		CString strSex, strStatus;
		if (pUserNameInfo->UserSex == 0)
			strSex = TEXT("男");
		else
			strSex = TEXT("女");

		if (pUserNameInfo->UserStatus == 0)
			strStatus = TEXT("未出行");
		else
			strStatus = TEXT("出行");

		Info.Format(TEXT("用户:%s,年龄:%d,性别:%s,身份证:%s,电话:%s,状态:%s,地址:%s"),
			pUserNameInfo->UserName, pUserNameInfo->UserAge, strSex, pUserNameInfo->UserSfz, pUserNameInfo->UserPhone, strStatus, pUserNameInfo->UserAddress);
		delete pUserNameInfo;
		delete ado;
	}
	return Info;
}
CString  CEwmCreate::OnUserStatusInfo(CString UserName)
{
	CString Info = TEXT("");

	CString strSqlText;
	strSqlText.Format(TEXT("select * from Recordinfo where UserName='%s'"), UserName);

	//////////////////////////////////创建SQL语句执行类实例
	AdoWorker *ado = NULL;
	_RecordStatusInfo *pRecordInfo = NULL;
	ado = new AdoWorker();
	pRecordInfo = (_RecordStatusInfo *)ado->ExecuteSql(strSqlText, 3);

	if (pRecordInfo == NULL)
	{
		delete pRecordInfo;
		delete ado;
		return TEXT("");
	}
	else//存在这样的账号，在此设定表格中第二行的姓名
	{
		
		_RecordStatusInfo *pDelete = NULL;
		pDelete = pRecordInfo;
		for (int i = 0; pRecordInfo != NULL; i++)
		{
			CString strTemp;
			CString strTool, strIsOlace, strIsInfect;
			if (pRecordInfo->UserTool == 0)
				strTool = TEXT("飞机");
			else if (pRecordInfo->UserTool == 1)
				strTool = TEXT("火车");
			else if (pRecordInfo->UserTool == 2)
				strTool = TEXT("汽车");
			else if (pRecordInfo->UserTool == 3)
				strTool = TEXT("自驾");
			else if (pRecordInfo->UserTool == 4)
				strTool = TEXT("步行");
			else
				strTool = TEXT("其他");



			if (pRecordInfo->Hasisolace == 0)
				strIsOlace = TEXT("无");
			else
				strIsOlace = TEXT("有");

			if (pRecordInfo->Hasinfect == 0)
				strIsInfect = TEXT("无");
			else
				strIsInfect = TEXT("有");

			strTemp.Format(TEXT("用户:%s,开始时间:%s,结束时间:%s,开始地址:%s,结束地址:%s,工具:%s,工具信息:%s,隔离:%s,患病:%s"),
				pRecordInfo->UserName, pRecordInfo->BeginTime, pRecordInfo->EndTime, pRecordInfo->BeginAddr, pRecordInfo->EndAddr, strTool, pRecordInfo->ToolInfo, strIsOlace, strIsInfect);

			pRecordInfo = pRecordInfo->Next;
			delete pDelete;
			pDelete = pRecordInfo;

			Info = Info + strTemp + TEXT("\n");
		}

		delete ado;
	}
	return Info;
}



void CEwmCreate::Showpicture(CString Bmpname)
{
	if (Bmpname=="")
		return;
	CRect rect,rect1;
	m_picture.GetClientRect(&rect);     //m_picture为Picture Control控件变量，获得控件的区域对象  

	CImage image;       //使用图片类   
	image.Load(Bmpname);   //装载路径下图片信息到图片类  
	CDC* pDC = m_picture.GetWindowDC();    //获得显示控件的DC  
	rect1.top = rect.top;
	rect1.left = rect.left;
	rect1.bottom = rect.top+264;
	rect1.right = rect.left+264;
	image.Draw(pDC->m_hDC, rect1);      //图片类的图片绘制Draw函数  
	ReleaseDC(pDC);

}




void CEwmCreate::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()
	if (IsIconic())
	{
	}
	else
	{
		CDialog::UpdateWindow(); //更新windows窗口  
		Showpicture(m_file_name);
	}
}	
