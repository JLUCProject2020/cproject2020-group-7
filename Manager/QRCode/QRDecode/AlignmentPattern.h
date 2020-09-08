// AlignmentPattern.h: interface for the AlignmentPattern class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ALIGNMENTPATTERN_H__93CF4CC8_0FFC_4961_BD84_F52A524CA14E__INCLUDED_)
#define AFX_ALIGNMENTPATTERN_H__93CF4CC8_0FFC_4961_BD84_F52A524CA14E__INCLUDED_

#include "FinderPattern.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class AlignmentPattern  
{
public:
	AlignmentPattern();
	virtual ~AlignmentPattern();

public:

	int DECIMAL_POINT;
	BYTE ** bitmap;
	int m_nWidth;//gy �Ӹ� m_
	int m_nHeight;//gy �Ӹ� m_

	FinderPattern * m_finderPattern;
	Point ** m_logicalCenters;//gy �Ӹ� m_
	int m_logicalSeedsCnt;
	int m_logicalCentersCnt;//gy �Ӹ� m_
	int m_logicalDistance;//gy �Ӹ� m_
	Point ** m_centers;
	int m_centersCnt;

	void findAlignmentPattern(BYTE ** mybitmap, int mynWidth, int mynHeight, FinderPattern * finderPattern, int myDECIMAL_POINT);
	void getLogicalCenter(FinderPattern * finderPattern);
	void getCenter();
	Point getPrecisionCenter(Point targetPoint);
	bool targetPointOnTheCorner(int x, int y, int nx, int ny);

};

#endif // !defined(AFX_ALIGNMENTPATTERN_H__93CF4CC8_0FFC_4961_BD84_F52A524CA14E__INCLUDED_)
