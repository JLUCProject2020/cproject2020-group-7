/////////////////////////////////////////////////////////////////////////////
typedef struct tagRS_BLOCKINFO
{
	int ncRSBlock;		// 纠错块数
	int ncAllCodeWord;	// 块内码字数
	int ncDataCodeWord;	// 数据码字数（码字数-RS码字数）

} RS_BLOCKINFO, *LPRS_BLOCKINFO;

/////////////////////////////////////////////////////////////////////////////
//QRcode版本相关信息
typedef struct tagQR_VERSIONINFO
{
	int nVersionNo;	   // 版本号1-40
	int ncAllCodeWord; // 总码字数
	int ncDataCodeWord[4];	// 数据码字（总码字-RS码字）

	int ncAlignPoint;	// 校正点数
	int nAlignPoint[6];	// 校正图形中心坐标

	RS_BLOCKINFO RS_BlockInfo1[4]; // 纠错块信息
	RS_BLOCKINFO RS_BlockInfo2[4]; // 纠错块信息

} QR_VERSIONINFO, *LPQR_VERSIONINFO;
////////////////////////////////////////////////////
//全局变量
////////////////////////////////////////////////////
extern int VersionInfoBit[];
extern int FormatInfoBit[];
extern int nIndicatorLenNumeral[];
extern int nIndicatorLenAlphabet[];
extern int nIndicatorLen8Bit[];
extern int nIndicatorLenHanzi[];
extern QR_VERSIONINFO QR_VersonInfo[];
///////////////////////////////////////////////////