
#include "StdAfx.h"
#include ".\adoworker.h"
#include "_StructDefine.h"
AdoWorker::AdoWorker(void)
{
	m_pRecordset=NULL;
	HRESULT hr; 
	try {
		hr = m_pRecordset.CreateInstance("ADODB.Recordset");;///创建Recordset对象 
		} 
	catch(_com_error e)///捕捉异常 
	{ 
		CString errormessage; 
		errormessage.Format(TEXT("连接数据库失败!\r\n错误信息:%s"),e.ErrorMessage()); 
		AfxMessageBox(errormessage);///显示错误信息
		return;
	} 
}

AdoWorker::~AdoWorker(void)
{
}

BOOL AdoWorker::ExecuteSql(CString strSqlText)//用来执行无返回的语句
{
	//AfxMessageBox(strSqlText);
	_bstr_t vSqlText=_bstr_t(strSqlText);
	_variant_t RecordsAffected; 
	m_pConnection->Execute(vSqlText,&RecordsAffected,adCmdText);
	if(m_pRecordset->State) 
		m_pRecordset->Close();
	if(RecordsAffected.lVal>0)
	   return TRUE;
	else 
	   return FALSE;
}
void *AdoWorker::ExecuteSql(CString strSqlText,int iFlag)//用来执行有返回的语句，返回为void型指针，返回主函数后强制转换
{
  //AfxMessageBox(strSqlText); 
  _bstr_t vSqlText=_bstr_t(strSqlText);
   _variant_t RecordsAffected; 
   m_pRecordset=m_pConnection->Execute(vSqlText,&RecordsAffected,adCmdText);
   ////////////////////////////////////////////判断查询是否成功，成功就应返回记录集
   if(m_pRecordset->adoEOF) 
	{ if(m_pRecordset->State)
	      m_pRecordset->Close();
	  return (void *)NULL;
	}
   ////////////////////////////////////////////
   void *pVoid=NULL;
   pVoid=this->ChooseStructFill(iFlag);
   if(m_pRecordset->State) 
	   m_pRecordset->Close();
   return pVoid;
}
void *AdoWorker::ChooseStructFill(int iFlag)
{
	 void *pVoid=NULL;
	switch(iFlag)
	{
	case 0:
		pVoid=this->FillUserInfo();
		break;
	case 1:
		pVoid=this->FillUserStatus();
		break;
	case 2:
		pVoid = this->FillUserNameInfo();
		break;
	case 3:
		pVoid = this->FillUserStatusInfo();
		break;
	case 4:
		pVoid = this->FillAllUserInfo();
		break;
	default:
		break;
	}
	return pVoid;
}

void *AdoWorker::FillUserInfo()
{
	_UserInfo *pUserInfo=NULL;
	pUserInfo=new _UserInfo;
	_variant_t vUserInfo;
	
	vUserInfo=m_pRecordset->GetCollect("UserName");
	pUserInfo->UserName=(CString)vUserInfo;
	vUserInfo.Clear();

	vUserInfo=m_pRecordset->GetCollect("UserAge");
	pUserInfo->UserAge = vUserInfo.intVal;
	vUserInfo.Clear();

	vUserInfo=m_pRecordset->GetCollect("UserSex");
	pUserInfo->UserSex = vUserInfo.intVal;
	vUserInfo.Clear();

	vUserInfo=m_pRecordset->GetCollect("UserSfz");
	pUserInfo->UserSfz = (CString)vUserInfo;
	vUserInfo.Clear();

	vUserInfo=m_pRecordset->GetCollect("UserPhone");
	pUserInfo->UserPhone = (CString)vUserInfo;
	vUserInfo.Clear();

	vUserInfo = m_pRecordset->GetCollect("UserStatus");
	pUserInfo->UserStatus = vUserInfo.intVal;
	vUserInfo.Clear();

	vUserInfo = m_pRecordset->GetCollect("UserAddr");
	pUserInfo->UserAddress = (CString)vUserInfo;
	vUserInfo.Clear();
	return (void *)pUserInfo;
}
void *AdoWorker::FillUserStatus()
{
	_UserStatus *pCurrentInfo = NULL;
	pCurrentInfo = new _UserStatus;
    _variant_t vCurrentInfo;
	vCurrentInfo=m_pRecordset->GetCollect("UserName");
	pCurrentInfo->UserName = (CString)vCurrentInfo;
	vCurrentInfo.Clear();

	vCurrentInfo=m_pRecordset->GetCollect("BeginTime");
	pCurrentInfo->BeginTime = (CString)vCurrentInfo;
	vCurrentInfo.Clear();


	vCurrentInfo=m_pRecordset->GetCollect("EndTime");
	pCurrentInfo->EndTime = (CString)vCurrentInfo;
	vCurrentInfo.Clear();

	vCurrentInfo = m_pRecordset->GetCollect("BeginAddr");
	pCurrentInfo->BeginAddr = (CString)vCurrentInfo;
	vCurrentInfo.Clear();

	vCurrentInfo = m_pRecordset->GetCollect("EndAddr");
	pCurrentInfo->EndAddr = (CString)vCurrentInfo;
	vCurrentInfo.Clear();

	vCurrentInfo=m_pRecordset->GetCollect("UserTool");
	pCurrentInfo->UserTool = vCurrentInfo.intVal;
	vCurrentInfo.Clear();

	vCurrentInfo = m_pRecordset->GetCollect("ToolInfo");
	pCurrentInfo->ToolInfo = (CString)vCurrentInfo;
	vCurrentInfo.Clear();

	vCurrentInfo = m_pRecordset->GetCollect("Hasisolace");
	pCurrentInfo->Hasisolace = vCurrentInfo.intVal;
	vCurrentInfo.Clear();

	vCurrentInfo = m_pRecordset->GetCollect("Hasinfect");
	pCurrentInfo->Hasinfect = vCurrentInfo.intVal;
	vCurrentInfo.Clear();


	return (void *)pCurrentInfo;
}

void *AdoWorker::FillAllUserInfo()
{
	_RecordUserInfo *pRecordInfo = NULL;
	_RecordUserInfo *pRecordHeader = NULL;
	_RecordUserInfo *pRecordPre = NULL;
	_variant_t vRecordInfo;
	int iNodeFlag = 1;
	for (; !(m_pRecordset->adoEOF);)
	{
		pRecordInfo = new _RecordUserInfo;
		pRecordInfo->Next = NULL;
		if (iNodeFlag == 1)//判断这是否是第一次建立节点
		{
			pRecordHeader = pRecordInfo;
			pRecordPre = pRecordInfo;
			iNodeFlag++;
		}
		else
		{
			pRecordPre->Next = pRecordInfo;
			pRecordPre = pRecordInfo;
		}
		/////////////////////////////////开始填充节点
		
		vRecordInfo = m_pRecordset->GetCollect("UserName");
		pRecordInfo->UserName = (CString)vRecordInfo;
		vRecordInfo.Clear();
		vRecordInfo = m_pRecordset->GetCollect("UserAge");
		pRecordInfo->UserAge = vRecordInfo.intVal;
		vRecordInfo.Clear();
		vRecordInfo = m_pRecordset->GetCollect("UserSex");
		pRecordInfo->UserSex = vRecordInfo.intVal;
		vRecordInfo.Clear();
		vRecordInfo = m_pRecordset->GetCollect("UserSfz");
		pRecordInfo->UserSfz = (CString)vRecordInfo;
		vRecordInfo.Clear();
		vRecordInfo = m_pRecordset->GetCollect("UserPhone");
		pRecordInfo->UserPhone = (CString)vRecordInfo;
		vRecordInfo.Clear();
		vRecordInfo = m_pRecordset->GetCollect("UserStatus");
		pRecordInfo->UserStatus = vRecordInfo.intVal;
		vRecordInfo.Clear();
		vRecordInfo = m_pRecordset->GetCollect("UserAddr");
		pRecordInfo->UserAddress = (CString)vRecordInfo;
		vRecordInfo.Clear();
	
		/////////////////////////////////节点填充完毕
		////////////////////////////////m_pRecordset指针后移
		m_pRecordset->MoveNext();
	}
	return (void *)pRecordHeader;
}


void *AdoWorker::FillUserStatusInfo()
{
	_RecordStatusInfo *pRecordInfo = NULL;
	_RecordStatusInfo *pRecordHeader = NULL;
	_RecordStatusInfo *pRecordPre = NULL;
	_variant_t vRecordInfo;
	int iNodeFlag=1;
	for(;!(m_pRecordset->adoEOF);)
	{
		pRecordInfo = new _RecordStatusInfo;
		pRecordInfo->Next=NULL;
		if(iNodeFlag==1)//判断这是否是第一次建立节点
		{
			pRecordHeader=pRecordInfo;
			pRecordPre=pRecordInfo;
			iNodeFlag++;
		}
		else
		{
			pRecordPre->Next=pRecordInfo;
			pRecordPre=pRecordInfo;
		}
		/////////////////////////////////开始填充节点
        vRecordInfo=m_pRecordset->GetCollect("AutoId");
		pRecordInfo->AutoId = vRecordInfo.intVal;
		vRecordInfo.Clear();
		vRecordInfo=m_pRecordset->GetCollect("UserName");
		pRecordInfo->UserName = (CString)vRecordInfo;
		vRecordInfo.Clear();
		vRecordInfo=m_pRecordset->GetCollect("BeginTime");
		pRecordInfo->BeginTime = (CString)vRecordInfo;
		vRecordInfo.Clear();
		vRecordInfo=m_pRecordset->GetCollect("EndTime");
		pRecordInfo->EndTime = (CString)vRecordInfo;
		vRecordInfo.Clear();
		vRecordInfo=m_pRecordset->GetCollect("BeginAddr");
		pRecordInfo->BeginAddr = (CString)vRecordInfo;
		vRecordInfo.Clear();
		vRecordInfo=m_pRecordset->GetCollect("EndAddr");
		pRecordInfo->EndAddr = (CString)vRecordInfo;
		vRecordInfo.Clear();
		vRecordInfo = m_pRecordset->GetCollect("UserTool");
		pRecordInfo->UserTool = vRecordInfo.intVal;
		vRecordInfo.Clear();
		vRecordInfo = m_pRecordset->GetCollect("ToolInfo");
		pRecordInfo->ToolInfo = (CString)vRecordInfo;
		vRecordInfo.Clear();
		vRecordInfo = m_pRecordset->GetCollect("HasIsOlace");
		pRecordInfo->Hasisolace = vRecordInfo.intVal;
		vRecordInfo.Clear();
		vRecordInfo = m_pRecordset->GetCollect("HasIsInfect");
		pRecordInfo->Hasinfect = vRecordInfo.intVal;
		vRecordInfo.Clear();
		/////////////////////////////////节点填充完毕
		////////////////////////////////m_pRecordset指针后移
		m_pRecordset->MoveNext();
	}
	return (void *)pRecordHeader;
}

void *AdoWorker::FillUserNameInfo()
{
	_UserNameInfo *pUserNameInfo=NULL;
	pUserNameInfo=new _UserNameInfo;
	_variant_t vUserNameInfo;
	vUserNameInfo=m_pRecordset->GetCollect("UserName");
	pUserNameInfo->UserName=(CString)vUserNameInfo;
	vUserNameInfo.Clear();
	return (void *)pUserNameInfo;
}