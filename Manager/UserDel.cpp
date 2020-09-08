// UserDel.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Manager.h"
#include "UserDel.h"
#include "afxdialogex.h"
#include "AdoWorker.h"


// CUserDel �Ի���

IMPLEMENT_DYNAMIC(CUserDel, CDialogEx)

CUserDel::CUserDel(CWnd* pParent /*=NULL*/)
	: CDialogEx(CUserDel::IDD, pParent)
	, m_user_name(_T(""))
{

}

CUserDel::~CUserDel()
{
}

void CUserDel::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_user_name);
}


BEGIN_MESSAGE_MAP(CUserDel, CDialogEx)
	ON_BN_CLICKED(IDOK, &CUserDel::OnBnClickedOk)
END_MESSAGE_MAP()


// CUserDel ��Ϣ�������


void CUserDel::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);

	if (m_user_name.IsEmpty())    /*�ж��û�����Ϣ�Ƿ�Ϊ��*/
	{
		AfxMessageBox(TEXT("�������û�����"));
		return;
	}

	CString strSqlText;


	strSqlText.Format(TEXT("delete from UserInfo  where UserName='%s'"), m_user_name);


	AdoWorker *ado = NULL;
	ado = new AdoWorker();
	BOOL bExec = FALSE;
	//��ɾ��ԭ������

	bExec = ado->ExecuteSql(strSqlText);//�����ݲ��뵽�˱����

	if (bExec)
	{
		CDialogEx::OnOK();
	}
	else
		AfxMessageBox(TEXT("�û����ֲ���ȷ�����飡"));

	CDialogEx::OnOK();
}
