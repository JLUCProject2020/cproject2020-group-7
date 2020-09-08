#ifndef _STRUCTDEFIE_
#define _STRUCTDEFIE_

///////////////////////////////////�û���Ϣ
typedef struct UserInfo 
{
	CString UserName;		//�û�����
	int  UserAge;			//�û����� 
	int  UserSex;			//�û��Ա� 0 Ů 1 �� 
	CString UserSfz;		//�û����֤
	CString UserPhone;		//�û��绰
	int  UserStatus;		//�û��Ƿ��г�����ʷ 0 û�� 1 �� 
	CString UserAddress;	//�û���ַ
}_UserInfo;
//////////////////////////////////�û�״̬
typedef struct UserStatus 
{
	CString UserName;		//�û�����
	CString BeginTime;		//�û����п�ʼʱ��
	CString EndTime;		//�û����н���ʱ��
	CString BeginAddr;		//�û����п�ʼ��ַ
	CString EndAddr;		//�û����н�����ַ
	int  UserTool; 			//�û����й��� 0 �ɻ� 1 �� 3 ���� 4 �Լ� 5 ���� 6 ���� 
	CString ToolInfo;		//���߾�����Ϣ ����� ���дε� 
	int	 Hasisolace;		//�Ƿ���� 0 �� 1 ��  
	int  Hasinfect;			//�û����� 0 �� 1 �� 

}_UserStatus;

//////////////////////////////////�û�״̬���صĲ�ѯ
typedef struct RecordStatusInfo
{
	int AutoId;
	CString UserName;		//�û�����
	CString BeginTime;		//�û����п�ʼʱ��
	CString EndTime;		//�û����н���ʱ��
	CString BeginAddr;		//�û����п�ʼ��ַ
	CString EndAddr;		//�û����н�����ַ
	int  UserTool; 			//�û����й��� 0 �ɻ� 1 �� 3 ���� 4 �Լ� 5 ���� 6 ���� 
	CString ToolInfo;		//���߾�����Ϣ ����� ���дε� 
	int	 Hasisolace;		//�Ƿ���� 0 �� 1 ��  
	int  Hasinfect;			//�û����� 0 �� 1 �� 
	struct RecordStatusInfo *Next;
}_RecordStatusInfo;

//////////////////////////////////�û�״̬���صĲ�ѯ
typedef struct RecordUserInfo
{
	CString UserName;		//�û�����
	int  UserAge;			//�û����� 
	int  UserSex;			//�û��Ա� 0 Ů 1 �� 
	CString UserSfz;		//�û����֤
	CString UserPhone;		//�û��绰
	int  UserStatus;		//�û��Ƿ��г�����ʷ 0 û�� 1 �� 
	CString UserAddress;	//�û���ַ
	struct RecordUserInfo *Next;
}_RecordUserInfo;

///////////////////////////////���Ҹ��˺��Ƿ���ڣ����ؽ���������
typedef struct UserNameInfo 
{
	CString UserName;
}_UserNameInfo;
#endif