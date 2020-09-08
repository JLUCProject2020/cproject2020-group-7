#include "stdafx.h"
#include "strcoding.h"
#include <iostream>
#include <stdio.h>



strCoding::strCoding(void)
{
}

strCoding::~strCoding(void)
{
}
void strCoding::Gb2312ToUnicode(WCHAR* pOut,const char *gbBuffer)
{
    ::MultiByteToWideChar(CP_ACP,MB_PRECOMPOSED,gbBuffer,2,pOut,1);
    return;
}
void strCoding::UTF_8ToUnicode(WCHAR* pOut,const char *pText)
{
    char* uchar = (char *)pOut;
     
    uchar[1] = ((pText[0] & 0x0F) << 4) + ((pText[1] >> 2) & 0x0F);
    uchar[0] = ((pText[1] & 0x03) << 6) + (pText[2] & 0x3F);

    return;
}

void strCoding::UnicodeToUTF_8(char* pOut,WCHAR* pText)
{
    // 注意 WCHAR高低字的顺序,低字节在前，高字节在后
    char* pchar = (char *)pText;

    pOut[0] = (0xE0 | ((pchar[1] & 0xF0) >> 4));
    pOut[1] = (0x80 | ((pchar[1] & 0x0F) << 2)) + ((pchar[0] & 0xC0) >> 6);
    pOut[2] = (0x80 | (pchar[0] & 0x3F));

    return;
}
void strCoding::UnicodeToGB2312(char* pOut,WCHAR uData)
{
    WideCharToMultiByte(CP_ACP,NULL,&uData,1,pOut,sizeof(WCHAR),NULL,NULL);
    return;
}

//做为解Url使用
char strCoding:: CharToInt(char ch){
        if(ch>='0' && ch<='9')return (char)(ch-'0');
        if(ch>='a' && ch<='f')return (char)(ch-'a'+10);
        if(ch>='A' && ch<='F')return (char)(ch-'A'+10);
        return -1;
}
char strCoding::StrToBin(char *str){
        char tempWord[2];
        char chn;

        tempWord[0] = CharToInt(str[0]);                         //make the B to 11 -- 00001011
        tempWord[1] = CharToInt(str[1]);                         //make the 0 to 0  -- 00000000

        chn = (tempWord[0] << 4) | tempWord[1];                //to change the BO to 10110000

        return chn;
}


//UTF_8 转gb2312
void strCoding::UTF_8ToGB2312(std::string &pOut, const char *pText, int pLen)
{
     char buf[4];
     char* rst = new char[pLen + (pLen >> 2) + 2];
    memset(buf,0,4);
    memset(rst,0,pLen + (pLen >> 2) + 2);

    int i =0;
    int j = 0;

    pOut.clear();  
    while(i < pLen)
    {
        if(*(pText + i) >= 0)
        {
            
            rst[j++] = pText[i++];
        }
        else                 
        {
            WCHAR Wtemp;

            
            UTF_8ToUnicode(&Wtemp,pText + i);
              
            UnicodeToGB2312(buf,Wtemp);
            
            unsigned short int tmp = 0;
            tmp = rst[j] = buf[0];
            tmp = rst[j+1] = buf[1];
            tmp = rst[j+2] = buf[2];

            //newBuf[j] = Ctemp[0];
            //newBuf[j + 1] = Ctemp[1];

            i += 3;    
            j += 2;   
        }
        
  }
    rst[j]='\0';
   pOut.append(rst, j); 
    delete []rst;
}

//GB2312 转为 UTF-8
void strCoding::GB2312ToUTF_8(std::string& pOut,const char *pText, int pLen)
{
    char buf[4];
    memset(buf,0,4);

    pOut.clear();

    int i = 0;
    while(i < pLen)
    {
        //如果是英文直接复制就可以
        if( pText[i] >= 0)
        {
            char asciistr[2]={0};
            asciistr[0] = (pText[i++]);
            pOut.append(asciistr, 1);
        }
        else
        {
            WCHAR pbuffer;
            Gb2312ToUnicode(&pbuffer,pText+i);

            UnicodeToUTF_8(buf,&pbuffer);

            pOut.append(buf);

            i += 2;
        }
    }

    return;
}
//把str编码为网页中的 GB2312 url encode ,英文不变，汉字双字节  如%3D%AE%88
std::string strCoding::UrlGB2312(const char * str)
{
    std::string dd;
    size_t len = strlen(str);
    for (size_t i=0;i<len;i++)
    {
        if(isalnum((BYTE)str[i]))
        {
			char tempbuff[2]={0};
            sprintf_s(tempbuff,2,"%c",str[i]);
            dd.append(tempbuff);
        }
        else if (isspace((BYTE)str[i]))
        {
            dd.append("+");
        }
        else
        {
            char tempbuff[4]={0};
            sprintf_s(tempbuff,4,"%%%X%X",((BYTE*)str)[i] >>4,((BYTE*)str)[i] %16);
            dd.append(tempbuff);
        }

    }
    return dd;
}

//把str编码为网页中的 UTF-8 url encode ,英文不变，汉字三字节  如%3D%AE%88

std::string strCoding::UrlUTF8(std::string str)
{
    std::string tt;
    std::string dd;
	GB2312ToUTF_8(tt,str.c_str (),str.length ());

    size_t len=tt.length();
    for (size_t i=0;i<len;i++)
    {
        if(isalnum((BYTE)tt.at(i)))
        {
            char tempbuff[2]={0};
            sprintf_s(tempbuff,2,"%c",(BYTE)tt.at(i));
            dd.append(tempbuff);
        }
        else if (isspace((BYTE)tt.at(i)))
        {
            dd.append("+");
        }
        else
        {
            char tempbuff[4]={0};
            sprintf_s(tempbuff,4,"%%%X%X",((BYTE)tt.at(i)) >>4,((BYTE)tt.at(i)) %16);
            dd.append(tempbuff);
        }

    }
    return dd;
}
//把url GB2312解码
std::string strCoding::UrlGB2312Decode(std::string str)
{
   std::string output="";
        char tmp[2];
        int i=0,idx=0,len=str.length();
        
        while(i<len){
                if(str[i]=='%'){
                        tmp[0]=str[i+1];
                        tmp[1]=str[i+2];
                        output += StrToBin(tmp);
                        i=i+3;
                }
                else if(str[i]=='+'){
                        output+=' ';
                        i++;
                }
                else{
                        output+=str[i];
                        i++;
                }
        }
        
        return output;
}
//把url utf8解码
std::string strCoding::UrlUTF8Decode(std::string str)
{
     std::string output="";

	 if (str.length () == 0)
		 return output;

    std::string temp =UrlGB2312Decode(str);//

    UTF_8ToGB2312(output,(char *)temp.data(),strlen(temp.data()));

    return output;

}

//utf8 to gb2312
std::string strCoding::UTF8GB2312 (std::string str)
{
/*
	 std::string output="";
	 if (str.length () == 0)
		 return output;

	 UTF_8ToGB2312(output,str.c_str (),str.length ());

    return output;
*/
	 std::string output="";
	 if (str.length () == 0)
		 return output;

	 UTF_8ToGB2312(output,str.c_str (),str.length ());

         return output;
}


std::string strCoding::sUtf82Gb2312 (std::string str)
{
	std::string ss;
	unsigned char acTmp[4096]={0};
	unsigned char acBuf[4096]={0};
	int		len=0;

	strcpy ((char *)acBuf, str.c_str());
//	strncpy((char *)acBuf, str.c_str(),str.length());
	len = str.length ();
	UTF8Decoding (acTmp, acBuf, &len);

	ss.append ((char *)acTmp, len);

	return ss;
}


void strCoding::UTF8Decoding (unsigned char *p_ucOut, unsigned char *p_ucIn, int *p_iLen)
{
	int				iPos, iLen, i;
	unsigned short	acUnicode[4096];

	if (*p_iLen <= 0)
	{
		*p_iLen = strlen ((char *)p_ucIn);
	}

	memset (acUnicode, 0, 4096);
	iLen = 0;
	for (iPos = 0; iPos < *p_iLen; iPos++)
	{
		if (0 == (p_ucIn[iPos] & 0x80))
		{
			acUnicode[iLen++] = (unsigned short)p_ucIn[iPos];
			continue;
		}
		else
		{
			i = 1;
			while (1)
			{
				if (0 != ((p_ucIn[iPos] << i) & 0x80))
				{
					i++;
					continue;
				}
				break;
			}

			if (i == 1)
			{
				continue;
			}
			if (i == 2)
			{
				acUnicode[iLen++] = (((unsigned short) (p_ucIn[iPos] & 0x1f)) << 6) | (p_ucIn[iPos + 1] & 0x3f);
			}
			else if (i == 3)
			{
				acUnicode[iLen++] = (((unsigned short) (p_ucIn[iPos] & 0x0f)) << 12) | (((unsigned short) (p_ucIn[iPos + 1] & 0x3f)) << 6) | (p_ucIn[iPos + 2] & 0x3f);
			}

			iPos += i - 1;
		}
	}

	i = WideCharToMultiByte (CP_ACP, 0, (LPCWSTR)acUnicode, iLen, NULL, 0, NULL, 0);
	WideCharToMultiByte (CP_ACP, 0, (LPCWSTR)acUnicode, iLen, (LPSTR)p_ucOut, i, NULL, 0);
	*p_iLen = i;
}

