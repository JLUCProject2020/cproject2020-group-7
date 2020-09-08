#ifndef ProductQRCode_H_
#define ProductQRCode_H_

#ifdef __cplusplus
extern "C" {
#endif

//���ɶ�ά��
// scale �Ŵ����
// strIn Ҫ���ɵĶ�ά�������
// strFilePathName �ļ�ͼƬ�����ȫ·����
// ���� true�ɹ��� falseʧ��
bool ProductQRCodeA(int scale,char * strIn,char * strFilePathName);
bool ProductQRCodeW(int scale,wchar_t * strIn,wchar_t * strFilePathName);

//������ά��
//strFilePathName �������Ķ�ά���ͼƬȫ·����
//strQRContent ��������������
// ���� true�ɹ��� falseʧ��
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