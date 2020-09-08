
// ManagerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Manager.h"
#include "ManagerDlg.h"
#include "afxdialogex.h"
#include "SkinPlusPlus.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CManagerDlg �Ի���



CManagerDlg::CManagerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CManagerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CManagerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHOOSESTC, m_ChooseStc);
	DDX_Control(pDX, IDC_WORKSTC, m_WorkStc);
	DDX_Control(pDX, IDC_MANAGER, m_ManagerChk);
	DDX_Control(pDX, IDC_CHECK, m_CheckChk);
	DDX_Control(pDX, IDC_TOTAL, m_TotalChk);
	DDX_Control(pDX, IDC_EWM_CREATE, m_ManChk);
	DDX_Control(pDX, IDC_CANCEL_BTN, m_CancelBtn);
	DDX_Control(pDX, IDC_EWM_YY, m_EwmYyChk);
}

BEGIN_MESSAGE_MAP(CManagerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CHOOSESTC, &CManagerDlg::OnBnClickedChoosestc)
	ON_BN_CLICKED(IDC_MANAGER, &CManagerDlg::OnBnClickedManager)
	ON_BN_CLICKED(IDC_CHECK, &CManagerDlg::OnBnClickedCheck)
	ON_BN_CLICKED(IDC_TOTAL, &CManagerDlg::OnBnClickedTotal)
	ON_BN_CLICKED(IDC_EWM_CREATE, &CManagerDlg::OnBnClickedDeleteuserchk)
	ON_BN_CLICKED(IDC_EWM_YY, &CManagerDlg::OnBnClickedEwmYy)
	ON_BN_CLICKED(IDC_CANCEL_BTN, &CManagerDlg::OnBnClickedCancelBtn)
END_MESSAGE_MAP()


// CManagerDlg ��Ϣ�������

BOOL CManagerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	if (!(this->OnInitChk()) || !(this->OnInitPage()))
		return FALSE;

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CManagerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CManagerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CManagerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


int CManagerDlg::OnInitChk(void)
{
	//ȡ����߷�������Ļ����
	HWND hWnd;
	hWnd = m_ChooseStc.GetSafeHwnd();
	CWnd *pWnd;
	pWnd = this->FromHandle(hWnd);
	CRect lpRect;
	pWnd->GetWindowRect(lpRect);
	this->ScreenToClient(lpRect);
	//�� lpRect�б�������߷������û���������
	//��ʼ����4����ť����ʽ��λ��
	//��ʼ��������Ϣ
	int iChkWide = lpRect.right - lpRect.left - 12;//ÿ����ť�Ŀ��
	int iChkHeight = (lpRect.bottom - lpRect.top - 25) / 5;//ÿ����ť�ĸ߶�
	int iChkLeft = lpRect.left + 2;//��һ����ť���Ͻ�x����
	int iChkTop = lpRect.top + 15;//��һ����ť�����Ͻ�Y����
	///////////////////////////////////////////////// �������һ��ͼ�갴ť
	hWnd = m_ManagerChk.GetSafeHwnd();
	SetNoSkinHwnd(hWnd);
	m_ManagerChk.SetIcon(IDI_KEY2ICO, IDI_KEY1ICO);
	m_ManagerChk.SetTooltipText(_T("��Ա���������Ϣ���ӡ��޸ġ�ɾ��"));
	m_ManagerChk.DrawTransparent(TRUE);
	m_ManagerChk.MoveWindow(iChkLeft, iChkTop, iChkWide, iChkHeight);//�ƶ���һ����ť
	m_ManagerChk.SetCheck(1);
	iChkTop += iChkHeight;
	////////////////////////////////////////////////��һ��ͼ�갴ť�������
	///////////////////////////////////////////////// �������һ��ͼ�갴ť
	hWnd = m_CheckChk.GetSafeHwnd();
	SetNoSkinHwnd(hWnd);
	m_CheckChk.SetIcon(IDI_KEY2ICO, IDI_KEY1ICO);
	m_CheckChk.SetTooltipText(_T("��Ϣ��ѯ"));
	m_CheckChk.DrawTransparent(TRUE);
	m_CheckChk.MoveWindow(iChkLeft, iChkTop, iChkWide, iChkHeight);//�ƶ���һ����ť
	iChkTop += iChkHeight;
	////////////////////////////////////////////////��һ��ͼ�갴ť�������
	///////////////////////////////////////////////// �������һ��ͼ�갴ť
	hWnd = m_TotalChk.GetSafeHwnd();
	SetNoSkinHwnd(hWnd);
	m_TotalChk.SetIcon(IDI_KEY2ICO, IDI_KEY1ICO);
	m_TotalChk.SetTooltipText(_T("��Ϣͳ�ƣ�"));
	m_TotalChk.DrawTransparent(TRUE);
	m_TotalChk.MoveWindow(iChkLeft, iChkTop, iChkWide, iChkHeight);//�ƶ���һ����ť
	iChkTop += iChkHeight;
	////////////////////////////////////////////////��һ��ͼ�갴ť�������
	///////////////////////////////////////////////// �������һ��ͼ�갴ť
	hWnd = m_ManChk.GetSafeHwnd();
	SetNoSkinHwnd(hWnd);
	m_ManChk.SetIcon(IDI_KEY2ICO, IDI_KEY1ICO);
	m_ManChk.SetTooltipText(_T("��ά������,���û���Ϣת���ɶ�ά�룡"));
	m_ManChk.DrawTransparent(TRUE);
	m_ManChk.MoveWindow(iChkLeft, iChkTop, iChkWide, iChkHeight);//�ƶ���һ����ť
	iChkTop += iChkHeight;

	///////////////////////////////////////////////// �������һ��ͼ�갴ť
	hWnd = m_EwmYyChk.GetSafeHwnd();
	SetNoSkinHwnd(hWnd);
	m_EwmYyChk.SetIcon(IDI_KEY2ICO, IDI_KEY1ICO);
	m_EwmYyChk.SetTooltipText(_T("�򿪶�ά�룬��ʾ�������ݣ�"));
	m_EwmYyChk.DrawTransparent(TRUE);
	m_EwmYyChk.MoveWindow(iChkLeft, iChkTop, iChkWide, iChkHeight);//�ƶ���һ����ť
	iChkTop += iChkHeight;
	

	////////////////////////////////////////////////��һ��ͼ�갴ť�������
	//�����˳���ť
	hWnd = m_CancelBtn.GetSafeHwnd();
	SetNoSkinHwnd(hWnd);
	m_CancelBtn.SetIcon(IDI_CANCELICO);
	m_CancelBtn.SetAlign(CButtonST::ST_ALIGN_HORIZ_RIGHT);
	m_CancelBtn.SetTooltipText(_T("�˳��˳���"));
	m_CancelBtn.DrawTransparent(TRUE);

	return 1;
}

// //������ʼ������������ҳ��
int CManagerDlg::OnInitPage(void)
{
	//ȡ���ұ߷�������Ļ����
	HWND hWnd;
	hWnd = m_WorkStc.GetSafeHwnd();
	CWnd *pWnd;
	pWnd = this->FromHandle(hWnd);
	CRect lpRect;
	pWnd->GetWindowRect(lpRect);
	this->ScreenToClient(lpRect);

	///////////////////////////////////////////////// �����page
	//��ʼ�����ұ�ҳ���е�4���������򴰿�
	m_UserManager.Create(IDD_MANAGER, pWnd);
	m_UserManager.ShowWindow(SW_SHOW);
	////////////////////////////
	m_UserQuery.Create(IDD_QUERY, pWnd);
	m_UserQuery.ShowWindow(SW_HIDE);
	////////////////////////////
	m_UserTotal.Create(IDD_TOTAL, pWnd);
	m_UserTotal.ShowWindow(SW_HIDE);
	///////////////////////////
	m_EwmCreate.Create(IDD_EWM_CREATE, pWnd);
	m_EwmCreate.ShowWindow(SW_HIDE);
	///////////////////////////
	m_EvmLoad.Create(IDD_EWM_LOAD, pWnd);
	m_EvmLoad.ShowWindow(SW_HIDE);
	////////////////////////////////////////////////page�������
	return 1;
}

void CManagerDlg::OnBnClickedChoosestc()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CManagerDlg::OnBnClickedManager()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	m_ManagerChk.SetCheck(1);
	m_CheckChk.SetCheck(0);
	m_TotalChk.SetCheck(0);
	m_ManChk.SetCheck(0);
	m_EwmYyChk.SetCheck(0);
	m_UserQuery.ShowWindow(SW_HIDE);
	m_UserTotal.ShowWindow(SW_HIDE);

	m_UserManager.ShowWindow(SW_SHOW);
}


void CManagerDlg::OnBnClickedCheck()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	m_ManagerChk.SetCheck(0);
	m_CheckChk.SetCheck(1);
	m_TotalChk.SetCheck(0);
	m_ManChk.SetCheck(0);
	m_EwmYyChk.SetCheck(0);

	m_UserManager.ShowWindow(SW_HIDE);
	m_UserTotal.ShowWindow(SW_HIDE);
	m_EwmCreate.ShowWindow(SW_HIDE);
	m_EvmLoad.ShowWindow(SW_HIDE);


	m_UserQuery.ShowWindow(SW_SHOW);
}


void CManagerDlg::OnBnClickedTotal()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	m_ManagerChk.SetCheck(0);
	m_CheckChk.SetCheck(0);
	m_TotalChk.SetCheck(1);
	m_EwmYyChk.SetCheck(0);
	m_ManChk.SetCheck(0);
	m_UserManager.ShowWindow(SW_HIDE);
	m_UserQuery.ShowWindow(SW_HIDE);
	m_EwmCreate.ShowWindow(SW_HIDE);
	m_EvmLoad.ShowWindow(SW_HIDE);

	m_UserTotal.ShowWindow(SW_SHOW);
}


void CManagerDlg::OnBnClickedDeleteuserchk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	m_ManagerChk.SetCheck(0);
	m_CheckChk.SetCheck(0);
	m_TotalChk.SetCheck(0);
	m_EwmYyChk.SetCheck(0);
	m_ManChk.SetCheck(1);

	m_UserManager.ShowWindow(SW_HIDE);
	m_UserQuery.ShowWindow(SW_HIDE);
	m_UserTotal.ShowWindow(SW_HIDE);
	m_EvmLoad.ShowWindow(SW_HIDE);

	m_EwmCreate.ShowWindow(SW_SHOW);
}


void CManagerDlg::OnBnClickedEwmYy()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	m_ManagerChk.SetCheck(0);
	m_CheckChk.SetCheck(0);
	m_TotalChk.SetCheck(0);
	m_ManChk.SetCheck(0);
	m_EwmYyChk.SetCheck(1);

	m_UserManager.ShowWindow(SW_HIDE);
	m_UserQuery.ShowWindow(SW_HIDE);
	m_UserTotal.ShowWindow(SW_HIDE);
	m_EwmCreate.ShowWindow(SW_HIDE);

	m_EvmLoad.ShowWindow(SW_SHOW);
}


void CManagerDlg::OnBnClickedCancelBtn()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnOK();
}
