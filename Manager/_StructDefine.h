#ifndef _STRUCTDEFIE_
#define _STRUCTDEFIE_

///////////////////////////////////用户信息
typedef struct UserInfo 
{
	CString UserName;		//用户姓名
	int  UserAge;			//用户年龄 
	int  UserSex;			//用户性别 0 女 1 男 
	CString UserSfz;		//用户身份证
	CString UserPhone;		//用户电话
	int  UserStatus;		//用户是否有出行历史 0 没有 1 有 
	CString UserAddress;	//用户地址
}_UserInfo;
//////////////////////////////////用户状态
typedef struct UserStatus 
{
	CString UserName;		//用户姓名
	CString BeginTime;		//用户出行开始时间
	CString EndTime;		//用户出行结束时间
	CString BeginAddr;		//用户出行开始地址
	CString EndAddr;		//用户出行结束地址
	int  UserTool; 			//用户出行工具 0 飞机 1 火车 3 汽车 4 自驾 5 步行 6 其他 
	CString ToolInfo;		//工具具体信息 航班号 火车列次等 
	int	 Hasisolace;		//是否隔离 0 无 1 有  
	int  Hasinfect;			//用户患病 0 无 1 有 

}_UserStatus;

//////////////////////////////////用户状态返回的查询
typedef struct RecordStatusInfo
{
	int AutoId;
	CString UserName;		//用户姓名
	CString BeginTime;		//用户出行开始时间
	CString EndTime;		//用户出行结束时间
	CString BeginAddr;		//用户出行开始地址
	CString EndAddr;		//用户出行结束地址
	int  UserTool; 			//用户出行工具 0 飞机 1 火车 3 汽车 4 自驾 5 步行 6 其他 
	CString ToolInfo;		//工具具体信息 航班号 火车列次等 
	int	 Hasisolace;		//是否隔离 0 无 1 有  
	int  Hasinfect;			//用户患病 0 无 1 有 
	struct RecordStatusInfo *Next;
}_RecordStatusInfo;

//////////////////////////////////用户状态返回的查询
typedef struct RecordUserInfo
{
	CString UserName;		//用户姓名
	int  UserAge;			//用户年龄 
	int  UserSex;			//用户性别 0 女 1 男 
	CString UserSfz;		//用户身份证
	CString UserPhone;		//用户电话
	int  UserStatus;		//用户是否有出行历史 0 没有 1 有 
	CString UserAddress;	//用户地址
	struct RecordUserInfo *Next;
}_RecordUserInfo;

///////////////////////////////查找该账号是否存在，返回仅仅是姓名
typedef struct UserNameInfo 
{
	CString UserName;
}_UserNameInfo;
#endif