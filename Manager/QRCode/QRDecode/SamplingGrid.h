// SamplingGrid.h: interface for the SamplingGrid class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SAMPLINGGRID_H__BB8247B0_0139_411B_A5B5_2C099149DA95__INCLUDED_)
#define AFX_SAMPLINGGRID_H__BB8247B0_0139_411B_A5B5_2C099149DA95__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Line.h"

//A grid for a single area	 
class AreaGrid
{
public:
	Line * xLine;
	Line * yLine;
	int width;
	int height;

	AreaGrid()
	{
		xLine=NULL;
		yLine=NULL;
		width=0;
		height=0;
	}
	~AreaGrid()
	{
		if(xLine)
		{
			delete [] xLine;
			xLine=NULL;
		}
		if(yLine)
		{
			delete [] yLine;
			yLine=NULL;
		}
	}

	AreaGrid(int nwidth, int nheight)
	{
		xLine=new Line[nwidth];
		yLine=new Line[nheight];
		width=nwidth;
		height=nheight;
	}
	//赋值
	AreaGrid & operator=(const AreaGrid & pAreaGrid)
	{
		if(xLine)
		{
			delete [] xLine;
			xLine=NULL;
		}
		if(yLine)
		{
			delete [] yLine;
			yLine=NULL;
		}
		xLine=new Line[pAreaGrid.width];
		yLine=new Line[pAreaGrid.height];
		width=pAreaGrid.width;
		height=pAreaGrid.height;
		for(int i=0;i<width;++i)
		{
			xLine[i].x1 = pAreaGrid.xLine[i].x1;
			xLine[i].x2 = pAreaGrid.xLine[i].x2;
			xLine[i].y1 = pAreaGrid.xLine[i].y1;
			xLine[i].y2 = pAreaGrid.xLine[i].y2;	
		}
		for(int i=0;i<height;++i)
		{
			yLine[i].x1 = pAreaGrid.yLine[i].x1;
			yLine[i].x2 = pAreaGrid.yLine[i].x2;
			yLine[i].y1 = pAreaGrid.yLine[i].y1;
			yLine[i].y2 = pAreaGrid.yLine[i].y2;	
		}
		return *this;
	}
	int getWidth()
	{
		return width;
	}

	int getHeight()
	{
		return height;
	}

	Line getXLine(int x)
	{
		return xLine[x];
	}
	
	Line getYLine(int y)
	{
		return yLine[y];
	}

	Line * getXLines()
	{
		return xLine;
	}
	
	Line * getYLines()
	{
		return yLine;
	}

	void setXLine(int x, Line line)
	{
		xLine[x]=line;
	}

	void setYLine(int y, Line line)
	{
		yLine[y]=line;
	}
};

class SamplingGrid  
{
public:
	SamplingGrid();
	virtual ~SamplingGrid();
	SamplingGrid & operator=(const SamplingGrid & pSamplingGrid);
	SamplingGrid(const SamplingGrid & pSamplingGrid);
public:
	AreaGrid ** m_grid;//gy 加个 m_
	int m_size;//gy 加个 m_

	SamplingGrid(int sqrtNumArea);
	void initGrid(int ax,int ay, int width, int height);
	void setXLine(int ax, int ay, int x, Line line);
	void setYLine(int ax, int ay, int y, Line line);
	Line getXLine(int ax, int ay, int x);
	Line getYLine(int ax, int ay, int y);
	Line * getXLines(int ax, int ay);
	Line * getYLines(int ax, int ay);
	int getWidth();
	int getHeight();
	int getWidth(int ax, int ay);
	int getHeight(int ax, int ay);
	int getTotalWidth();
	int getTotalHeight();
	int getX(int ax, int x);
	int getY(int ay, int y);
	void adjust(Point adjust);
};

#endif // !defined(AFX_SAMPLINGGRID_H__BB8247B0_0139_411B_A5B5_2C099149DA95__INCLUDED_)
