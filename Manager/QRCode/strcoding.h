#ifndef _STRCODEING_H_
#define _STRCODEING_H_



#include <string>
#include <windows.h>


class strCoding
{
public:
    strCoding(void);
    ~strCoding(void);
   
    void UTF_8ToGB2312(std::string &pOut, const char *pText, int pLen);//utf_8转为gb2312
    void GB2312ToUTF_8(std::string& pOut,const char *pText, int pLen); //gb2312 转utf_8
    std::string UrlGB2312(const char *str);                           //urlgb2312编码
    std::string UrlUTF8(std::string str);                             //urlutf8 编码
    std::string UrlUTF8Decode(std::string str);                  //urlutf8解码
    std::string UrlGB2312Decode(std::string str);                //urlgb2312解码
	std::string UTF8GB2312 (std::string str);

    std::string sUtf82Gb2312 (std::string str);

	
private:
    void Gb2312ToUnicode(WCHAR* pOut,const char *gbBuffer);
    void UTF_8ToUnicode(WCHAR* pOut,const char *pText);
    void UnicodeToUTF_8(char* pOut,WCHAR* pText);
    void UnicodeToGB2312(char* pOut,WCHAR uData);
    char CharToInt(char ch);
    char StrToBin(char *str);

    void UTF8Decoding (unsigned char *p_ucOut, unsigned char *p_ucIn, int *p_iLen);

};

#endif
