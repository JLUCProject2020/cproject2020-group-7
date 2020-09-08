// EwmCreate.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Manager.h"
#include "EwmCreate.h"
#include "afxdialogex.h"
#include "AdoWorker.h"
#include "_StructDefine.h"
#include "QRCode\\ProductQRCode.h"

// CEwmCreate �Ի���

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


// CEwmCreate ��Ϣ�������


BOOL CEwmCreate::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void CEwmCreate::OnBnClickedQuery()
{
	UpdateData(TRUE);
	if (m_user_name.IsEmpty())    /*�ж��û�����Ϣ�Ƿ�Ϊ��*/
	{
		AfxMessageBox(TEXT("�������û�����"));
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
			MessageBox(_T("����!"));
		}
		//CreateEwm(Info);
	}
}

CString  CEwmCreate::OnUserInfo(CString UserName)
{
	CString Info = TEXT("");

	CString strSqlText;
	strSqlText.Format(TEXT("select * from userinfo where UserName='%s'"), UserName);

	//////////////////////////////////����SQL���ִ����ʵ��
	AdoWorker *ado = NULL;
	_UserInfo *pUserNameInfo = NULL;
	ado = new AdoWorker();
	pUserNameInfo = (_UserInfo *)ado->ExecuteSql(strSqlText, 0);

	if (pUserNameInfo == NULL)
	{
		AfxMessageBox(TEXT("û������û���"));
		delete pUserNameInfo;
		delete ado;
		return TEXT("");
	}
	else//�����������˺ţ��ڴ��趨����еڶ��е�����
	{
		CString strSex, strStatus;
		if (pUserNameInfo->UserSex == 0)
			strSex = TEXT("��");
		else
			strSex = TEXT("Ů");

		if (pUserNameInfo->UserStatus == 0)
			strStatus = TEXT("δ����");
		else
			strStatus = TEXT("����");

		Info.Format(TEXT("�û�:%s,����:%d,�Ա�:%s,���֤:%s,�绰:%s,״̬:%s,��ַ:%s"),
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

	//////////////////////////////////����SQL���ִ����ʵ��
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
	else//�����������˺ţ��ڴ��趨����еڶ��е�����
	{
		
		_RecordStatusInfo *pDelete = NULL;
		pDelete = pRecordInfo;
		for (int i = 0; pRecordInfo != NULL; i++)
		{
			CString strTemp;
			CString strTool, strIsOlace, strIsInfect;
			if (pRecordInfo->UserTool == 0)
				strTool = TEXT("�ɻ�");
			else if (pRecordInfo->UserTool == 1)
				strTool = TEXT("��");
			else if (pRecordInfo->UserTool == 2)
				strTool = TEXT("����");
			else if (pRecordInfo->UserTool == 3)
				strTool = TEXT("�Լ�");
			else if (pRecordInfo->UserTool == 4)
				strTool = TEXT("����");
			else
				strTool = TEXT("����");



			if (pRecordInfo->Hasisolace == 0)
				strIsOlace = TEXT("��");
			else
				strIsOlace = TEXT("��");

			if (pRecordInfo->Hasinfect == 0)
				strIsInfect = TEXT("��");
			else
				strIsInfect = TEXT("��");

			strTemp.Format(TEXT("�û�:%s,��ʼʱ��:%s,����ʱ��:%s,��ʼ��ַ:%s,������ַ:%s,����:%s,������Ϣ:%s,����:%s,����:%s"),
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
	m_picture.GetClientRect(&rect);     //m_pictureΪPicture Control�ؼ���������ÿؼ����������  

	CImage image;       //ʹ��ͼƬ��   
	image.Load(Bmpname);   //װ��·����ͼƬ��Ϣ��ͼƬ��  
	CDC* pDC = m_picture.GetWindowDC();    //�����ʾ�ؼ���DC  
	rect1.top = rect.top;
	rect1.left = rect.left;
	rect1.bottom = rect.top+264;
	rect1.right = rect.left+264;
	image.Draw(pDC->m_hDC, rect1);      //ͼƬ���ͼƬ����Draw����  
	ReleaseDC(pDC);

}




void CEwmCreate::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
	if (IsIconic())
	{
	}
	else
	{
		CDialog::UpdateWindow(); //����windows����  
		Showpicture(m_file_name);
	}
}	
