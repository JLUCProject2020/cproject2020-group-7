
#pragma once
class AdoWorker
{
public:
	AdoWorker(void);
	~AdoWorker(void);
public:
	BOOL ExecuteSql(CString strSqlText);
	void *ExecuteSql(CString strSqlText,int iFlag);
private:
	_RecordsetPtr m_pRecordset;
private:
	void *ChooseStructFill(int);
	void *FillUserInfo();
	void *FillUserStatus();
	void *FillAllUserInfo();
	void *FillUserStatusInfo();
	void *FillAllUserStatus();
	void *FillUserNameInfo();
};
