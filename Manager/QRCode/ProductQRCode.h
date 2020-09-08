#ifndef ProductQRCode_H_
#define ProductQRCode_H_

#ifdef __cplusplus
extern "C" {
#endif

//生成二维码
// scale 放大比例
// strIn 要生成的二维码的内容
// strFilePathName 文件图片保存的全路径名
// 返回 true成功， false失败
bool ProductQRCodeA(int scale,char * strIn,char * strFilePathName);
bool ProductQRCodeW(int scale,wchar_t * strIn,wchar_t * strFilePathName);

//解析二维码
//strFilePathName 被解析的二维码的图片全路径名
//strQRContent 解析出来的内容
// 返回 true成功， false失败
bool DeQRCodeA(char * strFilePathName,char * strQRContent);
bool DeQRCodeW(wchar_t * strFilePathName,wchar_t * strQRContent);

#ifdef UNICODE
    #define gyProductQRCode ProductQRCodeW
	#define DeQRCode DeQRCodeW
#else
    #define gyProductQRCode ProductQRCodeA
	#define DeQRCode DeQRCodeA
#endif // !UNICODE


#ifdef __cplusplus
}
#endif

#endif