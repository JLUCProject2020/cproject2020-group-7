// EwmLoad.cpp : 实现文件
//

#include "stdafx.h"
#include "Manager.h"
#include "EwmLoad.h"
#include "afxdialogex.h"
#include "QRCode\\ProductQRCode.h"


// CEwmLoad 对话框

IMPLEMENT_DYNAMIC(CEwmLoad, CDialogEx)

CEwmLoad::CEwmLoad(CWnd* pParent /*=NULL*/)
	: CDialogEx(CEwmLoad::IDD, pParent)
{

}

CEwmLoad::~CEwmLoad()
{
}

void CEwmLoad::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_PIC, m_picture);
	DDX_Control(pDX, IDC_TEXT_SHOW, m_ShowText);
}


BEGIN_MESSAGE_MAP(CEwmLoad, CDialogEx)
	ON_BN_CLICKED(IDC_QUERY, &CEwmLoad::OnBnClickedQuery)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CEwmLoad 消息处理程序


void CEwmLoad::OnBnClickedQuery()
{
	// TODO:  在此添加控件通知处理程序代码

	CString filePath = _T("");
	CString szName = _T("Picture File|*.bmp||");// 显示这一类文件
	CString tSelectName = _T("");// 选择此文件
	CFileDialog fd(TRUE, NULL, tSelectName, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szName);
	

	if (fd.DoModal() == IDOK)
	{
		filePath = fd.GetPathName();


		m_file_name = filePath;
		ShowText();

		UpdateData(FALSE);
	}
	
	
}

void CEwmLoad::ShowText()
{
	bool b2 = false;
#ifdef UNICODE
	wchar_t tmpch[10000] = { 0 };
	b2 = DeQRCode(m_file_name.GetBuffer(0), tmpch);
	if (b2)
	{
		m_strShowText = tmpch;
	}
#else
	char tmpch[10000] = { 0 };
	b2 = DeQRCode(m_file_name.GetBuffer(0), tmpch);
	if (b2)
	{
		m_strShowText = tmpch;
	}
#endif // !UNICODE
	if (b2)
	{
		UpdateData(FALSE);


		SetDlgItemText(IDC_TEXT_SHOW, m_strShowText);
	}

	Showpicture(m_file_name);
}


void CEwmLoad::Showpicture(CString Bmpname)
{
	if (Bmpname == "")
		return;
	CRect rect, rect1;
	m_picture.GetClientRect(&rect);     //m_picture为Picture Control控件变量，获得控件的区域对象  

	CImage image;       //使用图片类   
	image.Load(Bmpname);   //装载路径下图片信息到图片类  
	CDC* pDC = m_picture.GetWindowDC();    //获得显示控件的DC  
	rect1.top = rect.top;
	rect1.left = rect.left;
	rect1.bottom = rect.top + 264;
	rect1.right = rect.left + 264;
	image.Draw(pDC->m_hDC, rect1);      //图片类的图片绘制Draw函数  
	ReleaseDC(pDC);

}

void CEwmLoad::OnPaint()
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
// "Static", SS_BITMAP, 