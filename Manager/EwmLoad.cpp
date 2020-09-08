// EwmLoad.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Manager.h"
#include "EwmLoad.h"
#include "afxdialogex.h"
#include "QRCode\\ProductQRCode.h"


// CEwmLoad �Ի���

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


// CEwmLoad ��Ϣ�������


void CEwmLoad::OnBnClickedQuery()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	CString filePath = _T("");
	CString szName = _T("Picture File|*.bmp||");// ��ʾ��һ���ļ�
	CString tSelectName = _T("");// ѡ����ļ�
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
	m_picture.GetClientRect(&rect);     //m_pictureΪPicture Control�ؼ���������ÿؼ����������  

	CImage image;       //ʹ��ͼƬ��   
	image.Load(Bmpname);   //װ��·����ͼƬ��Ϣ��ͼƬ��  
	CDC* pDC = m_picture.GetWindowDC();    //�����ʾ�ؼ���DC  
	rect1.top = rect.top;
	rect1.left = rect.left;
	rect1.bottom = rect.top + 264;
	rect1.right = rect.left + 264;
	image.Draw(pDC->m_hDC, rect1);      //ͼƬ���ͼƬ����Draw����  
	ReleaseDC(pDC);

}

void CEwmLoad::OnPaint()
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
// "Static", SS_BITMAP, 