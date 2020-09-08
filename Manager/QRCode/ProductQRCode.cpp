#include "stdafx.h"
#include"ProductQRCode.h"
#include "QR_Encode.h"
#include<string>
#include "QRDecode\\QRcodeImage.h"
#include "strcoding.h"
// nLevel������
//nVersion �汾
//bAutoExtent���Ƿ�����
//pScaleFactor�����ű���
//pCodeStr ����
//pFilenameStr��������ļ���
bool ProcessEncode(int nLevel, int nVersion, 
								 BOOL bAutoExtent, 
								 int nMaskingNo, 
								 int pScaleFactor, 
								 const char * pCodeStr, 
								 const char * pFilenameStr)
{
	if(pScaleFactor < 1)
		return false;

	int i, j;
	CQR_Encode* pQR_Encode = new CQR_Encode;

	if (pQR_Encode->EncodeData(nLevel, nVersion, bAutoExtent, nMaskingNo, pCodeStr))
	{
		// ����ԭʼ�ı����ļ�
		int originalSize = pQR_Encode->m_nSymbleSize + (QR_MARGIN * 2);
		CBitmap* saveBmp = new CBitmap;
		saveBmp->CreateBitmap(originalSize, originalSize, 1, 1, NULL);
		CDC *saveDC = new CDC;
		saveDC->CreateCompatibleDC(NULL);
		CBitmap* pOldBitmap = saveDC->SelectObject(saveBmp);
		saveDC->PatBlt(0, 0, originalSize, originalSize, WHITENESS);

		// ���ݽ����ֵ
		for (i = 0; i < pQR_Encode->m_nSymbleSize; ++i)
		{
			for (j = 0; j < pQR_Encode->m_nSymbleSize; ++j)
			{
				if (pQR_Encode->m_byModuleData[i][j])
					saveDC->SetPixel(i+ QR_MARGIN, j+ QR_MARGIN, RGB(0, 0, 0));
			}
		}

		// ����10��
		int scaleSize = originalSize * pScaleFactor;
		int nBmpSize = ((scaleSize + 31) / 32) * 32 / 8;
		nBmpSize *= scaleSize;

		HANDLE hFile = CreateFileA(pFilenameStr, GENERIC_READ | GENERIC_WRITE, 0, NULL,
			CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		if (hFile == INVALID_HANDLE_VALUE)
			return FALSE;

		HANDLE hFileMapping = CreateFileMapping(hFile, NULL, PAGE_READWRITE | SEC_COMMIT, 0, 
			sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * 2 + nBmpSize, NULL);
		LPBYTE lpbyMapView = (LPBYTE)MapViewOfFile(hFileMapping, FILE_MAP_WRITE, 0, 0, 0);

		ZeroMemory(lpbyMapView, sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * 2 + nBmpSize);

		LPBITMAPFILEHEADER pbfh = (LPBITMAPFILEHEADER)lpbyMapView;
		LPBITMAPINFO       pbmi = (LPBITMAPINFO)(lpbyMapView + sizeof(BITMAPFILEHEADER));
		LPVOID             pbdt = lpbyMapView + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * 2;

		pbfh->bfType      = (WORD) (('M' << 8) | 'B'); // "BM"
		pbfh->bfSize      = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * 2 + nBmpSize;
		pbfh->bfReserved1 = 0;
		pbfh->bfReserved2 = 0;
		pbfh->bfOffBits   = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * 2;

		pbmi->bmiHeader.biSize			= sizeof(BITMAPINFOHEADER);
		pbmi->bmiHeader.biWidth			= scaleSize;
		pbmi->bmiHeader.biHeight		= scaleSize;
		pbmi->bmiHeader.biPlanes		= 1;
		pbmi->bmiHeader.biBitCount		= 1;
		pbmi->bmiHeader.biCompression	= BI_RGB;
		pbmi->bmiHeader.biSizeImage		= nBmpSize;
		pbmi->bmiHeader.biXPelsPerMeter = 3780;
		pbmi->bmiHeader.biYPelsPerMeter = 3780;
		pbmi->bmiHeader.biClrUsed		= 0;
		pbmi->bmiHeader.biClrImportant	= 0;

		CDC* pWorkDC = new CDC;
		pWorkDC->CreateCompatibleDC(NULL);
		CBitmap* pWorkBitmap = new CBitmap;
		pWorkBitmap->CreateBitmap(scaleSize, scaleSize, 1, 1, NULL);
		pOldBitmap = pWorkDC->SelectObject(pWorkBitmap);
		pWorkDC->StretchBlt(0, 0, scaleSize, scaleSize, saveDC, 0, 0, originalSize, originalSize, SRCCOPY);
		GetDIBits(pWorkDC->m_hDC, (HBITMAP)*pWorkBitmap, 0, scaleSize, pbdt, pbmi, DIB_RGB_COLORS);
		pWorkDC->SelectObject(pOldBitmap);
		delete pWorkBitmap;
		delete pWorkDC;
		UnmapViewOfFile(lpbyMapView);
		CloseHandle(hFileMapping);
		CloseHandle(hFile);

		delete saveDC;
		delete saveBmp;
	}
	else
		return false;

	delete pQR_Encode;
	pQR_Encode = NULL;

	return true;
}


//���ɶ�ά��
// scale �Ŵ����
// strIn Ҫ���ɵĶ�ά�������
// strFilePathName �ļ�ͼƬ�����ȫ·����
// ���� true�ɹ��� falseʧ��
bool ProductQRCodeA(int scale,char * strIn,char * strFilePathName)
{
	bool bBack = false;
	if(!strIn || !strFilePathName)
		return false;
	int nLen = strlen(strIn);
	if(nLen<=0)
		return false;

	// ����
	bBack = ProcessEncode(0,1,1,-1,scale,strIn,strFilePathName);
	
	return bBack;
}

bool ProductQRCodeW(int scale,wchar_t * strIn,wchar_t * strFilePathName)
{
	bool bBack = false;
	if(!strIn || !strFilePathName)
		return false;
	int nLen = wcslen(strIn);
	if(nLen<=0)
		return false;
	USES_CONVERSION;
	std::string strInTemp = W2A(strIn);
	std::string strFilePathNameTemp = W2A(strFilePathName);
	// ����
	bBack = ProcessEncode(0,1,1,-1,scale,strInTemp.c_str(),strFilePathNameTemp.c_str());
	
	return bBack;
}

bool DeQRCodeA(char * strFilePathName,char * strQRContent)
{
	bool bBack = false;
	BYTE m_CodeData[MAX_MODULESIZE][MAX_MODULESIZE]; // �洢������λ����
	int m_nCodeSize;//���������С
	int m_nMoudleSize;//ģ���С
	int m_nVersion;//�汾��
	int m_nLevel;//����ȼ�

	CString filePathName, tempStr;	
	filePathName = strFilePathName;
		QRcodeImage *QR_image = new QRcodeImage(filePathName);
		QR_image->GetImageData();
		m_nVersion = QR_image->m_finderPattern->m_version;
		m_nCodeSize = m_nVersion * 4 +17;
		for(int j=0;j<m_nCodeSize;j++)
			for(int k=0;k<m_nCodeSize;k++)
				m_CodeData[j][k]=QR_image->bitMatrix[j][k];

		ContentDecoder *QR_Decode = new ContentDecoder;
		if(QR_Decode->DecodeData(m_nCodeSize, m_nVersion, m_CodeData))
		{
		//	m_nPendingListCtrl.SetItemText(i, 2, _T("�������"));
		//	m_nPendingListCtrl.SetItemText(i, 3, QR_Decode->m_strData);
		//	USES_CONVERSION;
		//	sprintf(strQRContent,"%s",T2A(QR_Decode->m_strData.GetBuffer(0)));
			sprintf(strQRContent,"%s",QR_Decode->m_strData.c_str());
			switch(QR_Decode->m_nLevel)
			{
			case QR_LEVEL_L:tempStr="L(%7)";break;
			case QR_LEVEL_M:tempStr="M(%15)";break;
			case QR_LEVEL_Q:tempStr="Q(%25)";break;
			case QR_LEVEL_H:tempStr="H(%30)";break;
			}
		//	m_nPendingListCtrl.SetItemText(i, 4, tempStr);
		//	tempStr.Format("%d", QR_Decode->m_nVersion);
		//	m_nPendingListCtrl.SetItemText(i, 5, tempStr);

		//	tempStr.Format("%d", QR_Decode->m_nMaskingNo);
		//	m_nPendingListCtrl.SetItemText(i, 6, tempStr);
			bBack=true;
		}
		else
		{
			bBack=false;
		}

		delete QR_Decode;
		delete QR_image;
	
	return bBack;
}

bool DeQRCodeW(wchar_t * strFilePathName,wchar_t * strQRContent)
{
	bool bBack = false;
	BYTE m_CodeData[MAX_MODULESIZE][MAX_MODULESIZE]; // �洢������λ����
	int m_nCodeSize;//���������С
	int m_nMoudleSize;//ģ���С
	int m_nVersion;//�汾��
	int m_nLevel;//����ȼ�

	CString filePathName, tempStr;	
	filePathName = strFilePathName;
		QRcodeImage *QR_image = new QRcodeImage(filePathName);
		QR_image->GetImageData();
		m_nVersion = QR_image->m_finderPattern->m_version;
		m_nCodeSize = m_nVersion * 4 +17;
		for(int j=0;j<m_nCodeSize;j++)
			for(int k=0;k<m_nCodeSize;k++)
				m_CodeData[j][k]=QR_image->bitMatrix[j][k];

		ContentDecoder *QR_Decode = new ContentDecoder;
		if(QR_Decode->DecodeData(m_nCodeSize, m_nVersion, m_CodeData))
		{
		//	m_nPendingListCtrl.SetItemText(i, 2, _T("�������"));
		//	m_nPendingListCtrl.SetItemText(i, 3, QR_Decode->m_strData);
			USES_CONVERSION;
			strCoding clsCoding;
		//	tempStr = QR_Decode->m_strData;
		//	std::string strTmp = T2A(tempStr.GetBuffer(0));
			std::string strTmp = QR_Decode->m_strData;
		//	strTmp = clsCoding.UTF8GB2312 (strTmp);
			#ifdef UNICODE
				::wsprintf(strQRContent,_T("%s"),A2T(strTmp.c_str()));			
			#endif
			switch(QR_Decode->m_nLevel)
			{
			case QR_LEVEL_L:tempStr="L(%7)";break;
			case QR_LEVEL_M:tempStr="M(%15)";break;
			case QR_LEVEL_Q:tempStr="Q(%25)";break;
			case QR_LEVEL_H:tempStr="H(%30)";break;
			}
		//	m_nPendingListCtrl.SetItemText(i, 4, tempStr);
		//	tempStr.Format("%d", QR_Decode->m_nVersion);
		//	m_nPendingListCtrl.SetItemText(i, 5, tempStr);

		//	tempStr.Format("%d", QR_Decode->m_nMaskingNo);
		//	m_nPendingListCtrl.SetItemText(i, 6, tempStr);
			bBack=true;
		}
		else
		{
			bBack=false;
		}

		delete QR_Decode;
		delete QR_image;
	
	return bBack;
}