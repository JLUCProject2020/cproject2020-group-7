
// ManagerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Manager.h"
#include "ManagerDlg.h"
#include "afxdialogex.h"
#include "SkinPlusPlus.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CManagerDlg 对话框



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


// CManagerDlg 消息处理程序

BOOL CManagerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	if (!(this->OnInitChk()) || !(this->OnInitPage()))
		return FALSE;

	// TODO:  在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CManagerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CManagerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


int CManagerDlg::OnInitChk(void)
{
	//取得左边分组框的屏幕坐标
	HWND hWnd;
	hWnd = m_ChooseStc.GetSafeHwnd();
	CWnd *pWnd;
	pWnd = this->FromHandle(hWnd);
	CRect lpRect;
	pWnd->GetWindowRect(lpRect);
	this->ScreenToClient(lpRect);
	//在 lpRect中保存了左边分组框的用户区域坐标
	//开始处理4个按钮的样式和位置
	//初始化坐标信息
	int iChkWide = lpRect.right - lpRect.left - 12;//每个按钮的宽度
	int iChkHeight = (lpRect.bottom - lpRect.top - 25) / 5;//每个按钮的高度
	int iChkLeft = lpRect.left + 2;//第一个按钮左上角x坐标
	int iChkTop = lpRect.top + 15;//第一个按钮的左上角Y坐标
	///////////////////////////////////////////////// 处理完第一个图标按钮
	hWnd = m_ManagerChk.GetSafeHwnd();
	SetNoSkinHwnd(hWnd);
	m_ManagerChk.SetIcon(IDI_KEY2ICO, IDI_KEY1ICO);
	m_ManagerChk.SetTooltipText(_T("人员管理，完成信息增加。修改。删除"));
	m_ManagerChk.DrawTransparent(TRUE);
	m_ManagerChk.MoveWindow(iChkLeft, iChkTop, iChkWide, iChkHeight);//移动第一个按钮
	m_ManagerChk.SetCheck(1);
	iChkTop += iChkHeight;
	////////////////////////////////////////////////第一个图标按钮处理完毕
	///////////////////////////////////////////////// 处理完第一个图标按钮
	hWnd = m_CheckChk.GetSafeHwnd();
	SetNoSkinHwnd(hWnd);
	m_CheckChk.SetIcon(IDI_KEY2ICO, IDI_KEY1ICO);
	m_CheckChk.SetTooltipText(_T("信息查询"));
	m_CheckChk.DrawTransparent(TRUE);
	m_CheckChk.MoveWindow(iChkLeft, iChkTop, iChkWide, iChkHeight);//移动第一个按钮
	iChkTop += iChkHeight;
	////////////////////////////////////////////////第一个图标按钮处理完毕
	///////////////////////////////////////////////// 处理完第一个图标按钮
	hWnd = m_TotalChk.GetSafeHwnd();
	SetNoSkinHwnd(hWnd);
	m_TotalChk.SetIcon(IDI_KEY2ICO, IDI_KEY1ICO);
	m_TotalChk.SetTooltipText(_T("信息统计！"));
	m_TotalChk.DrawTransparent(TRUE);
	m_TotalChk.MoveWindow(iChkLeft, iChkTop, iChkWide, iChkHeight);//移动第一个按钮
	iChkTop += iChkHeight;
	////////////////////////////////////////////////第一个图标按钮处理完毕
	///////////////////////////////////////////////// 处理完第一个图标按钮
	hWnd = m_ManChk.GetSafeHwnd();
	SetNoSkinHwnd(hWnd);
	m_ManChk.SetIcon(IDI_KEY2ICO, IDI_KEY1ICO);
	m_ManChk.SetTooltipText(_T("二维码生成,把用户信息转换成二维码！"));
	m_ManChk.DrawTransparent(TRUE);
	m_ManChk.MoveWindow(iChkLeft, iChkTop, iChkWide, iChkHeight);//移动第一个按钮
	iChkTop += iChkHeight;

	///////////////////////////////////////////////// 处理完第一个图标按钮
	hWnd = m_EwmYyChk.GetSafeHwnd();
	SetNoSkinHwnd(hWnd);
	m_EwmYyChk.SetIcon(IDI_KEY2ICO, IDI_KEY1ICO);
	m_EwmYyChk.SetTooltipText(_T("打开二维码，显示其中内容！"));
	m_EwmYyChk.DrawTransparent(TRUE);
	m_EwmYyChk.MoveWindow(iChkLeft, iChkTop, iChkWide, iChkHeight);//移动第一个按钮
	iChkTop += iChkHeight;
	

	////////////////////////////////////////////////第一个图标按钮处理完毕
	//处理退出按钮
	hWnd = m_CancelBtn.GetSafeHwnd();
	SetNoSkinHwnd(hWnd);
	m_CancelBtn.SetIcon(IDI_CANCELICO);
	m_CancelBtn.SetAlign(CButtonST::ST_ALIGN_HORIZ_RIGHT);
	m_CancelBtn.SetTooltipText(_T("退出此程序！"));
	m_CancelBtn.DrawTransparent(TRUE);

	return 1;
}

// //用来初始化６个工作区页面
int CManagerDlg::OnInitPage(void)
{
	//取得右边分组框的屏幕坐标
	HWND hWnd;
	hWnd = m_WorkStc.GetSafeHwnd();
	CWnd *pWnd;
	pWnd = this->FromHandle(hWnd);
	CRect lpRect;
	pWnd->GetWindowRect(lpRect);
	this->ScreenToClient(lpRect);

	///////////////////////////////////////////////// 处理第page
	//开始生成右边页面中的4个工作区域窗口
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
	////////////////////////////////////////////////page处理完毕
	return 1;
}

void CManagerDlg::OnBnClickedChoosestc()
{
	// TODO:  在此添加控件通知处理程序代码
}


void CManagerDlg::OnBnClickedManager()
{
	// TODO:  在此添加控件通知处理程序代码
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
	// TODO:  在此添加控件通知处理程序代码
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
	// TODO:  在此添加控件通知处理程序代码
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
	// TODO:  在此添加控件通知处理程序代码
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
	// TODO:  在此添加控件通知处理程序代码
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
	// TODO:  在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}
