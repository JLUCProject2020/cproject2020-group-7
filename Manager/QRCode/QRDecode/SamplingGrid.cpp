// SamplingGrid.cpp: implementation of the SamplingGrid class.
//
/**
 * This class is used for sampling grid
 * It allows one area to have a different size from another area
 */
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SamplingGrid.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

SamplingGrid::SamplingGrid()
{
	m_grid = NULL;
	m_size=0;
}

SamplingGrid::~SamplingGrid()
{
	if(m_grid)
	{
		for(int i=0;i<m_size;i++)
		{
			if(m_grid[i])
			{
				delete [] m_grid[i];
				m_grid[i]=NULL;
			}
		}
		delete [] m_grid;
		m_grid=NULL;
	}
	m_size=0;
}


SamplingGrid::SamplingGrid(int sqrtNumArea)
{
	m_grid = NULL;
	m_size=0;

	m_size=sqrtNumArea;
	m_grid=new AreaGrid *[sqrtNumArea];
	for(int i=0;i<sqrtNumArea;i++)
		m_grid[i]=new AreaGrid[sqrtNumArea];
	//grid=new AreaGrid[sqrtNumArea][sqrtNumArea];
}

void SamplingGrid::initGrid(int ax,int ay, int width, int height)
{
	m_grid[ax][ay]=AreaGrid(width, height);
}
	
void SamplingGrid::setXLine(int ax, int ay, int x, Line line)
{
	m_grid[ax][ay].setXLine(x,line);
}

void SamplingGrid::setYLine(int ax, int ay, int y, Line line)
{
	m_grid[ax][ay].setYLine(y,line);
}

Line SamplingGrid::getXLine(int ax, int ay, int x)
{
	return(m_grid[ax][ay].getXLine(x));
}

Line SamplingGrid::getYLine(int ax, int ay, int y)
{
	return(m_grid[ax][ay].getYLine(y));
}

Line * SamplingGrid::getXLines(int ax, int ay)
{
	return (m_grid[ax][ay].getXLines());
}

Line * SamplingGrid::getYLines(int ax, int ay)
{
	return(m_grid[ax][ay].getYLines());
}

int SamplingGrid::getWidth()
{
	return m_size;
}

int SamplingGrid::getHeight()
{
	return m_size;
}

int SamplingGrid::getWidth(int ax, int ay)
{
	return(m_grid[ax][ay].getWidth());
}

int SamplingGrid::getHeight(int ax, int ay)
{
	return(m_grid[ax][ay].getHeight());
}
	
int SamplingGrid::getTotalWidth()
{
	int total=0;
	for(int i=0;i<m_size;i++)
	{
		total+=m_grid[i][0].getWidth();
		if(i>0)
			total-=1;
	}
	return total;
}

int SamplingGrid::getTotalHeight()
{
	int total=0;
	for(int i=0;i<m_size;i++)
	{
		total+=m_grid[0][i].getHeight();
		if(i>0)
			total-=1;
	}
	return total;
}

int SamplingGrid::getX(int ax, int x)
{
	int total=x;
	for(int i=0;i<ax;i++)
	{
		total+=m_grid[i][0].getWidth()-1;
	}
	return total;
}

int SamplingGrid::getY(int ay, int y)
{
	int total=y;
	for(int i=0;i<ay;i++)
	{
		total+=m_grid[0][i].getHeight()-1;
	}
	return total;
	}
	
void SamplingGrid::adjust(Point adjust)
{
	int dx = adjust.x, dy = adjust.y;
	for (int ay = 0; ay < m_size; ay++)
	{
		for (int ax = 0; ax < m_size; ax++)
		{
			for (int i = 0; i < m_grid[ax][ay].width; i++)
				m_grid[ax][ay].xLine[i].translate(dx, dy);
			for (int j = 0; j < m_grid[ax][ay].height; j++)
				m_grid[ax][ay].yLine[j].translate(dx, dy);
		}
	}
}

SamplingGrid & SamplingGrid::operator=(const SamplingGrid & pSamplingGrid)//代码未完成，赋值未完成。暂时用不到
{
	if(m_grid)
	{
		for(int i=0;i<m_size;i++)
		{
			if(m_grid[i])
			{
				delete [] m_grid[i];
				m_grid[i]=NULL;
			}
		}
		delete [] m_grid;
		m_grid=NULL;
	}

	m_size = pSamplingGrid.m_size;
	if(pSamplingGrid.m_grid)
	{
		m_grid=new AreaGrid *[m_size];
		for(int i=0;i<m_size;i++)
			m_grid[i]=new AreaGrid[m_size];
	}
	return * this;
}
SamplingGrid::SamplingGrid(const SamplingGrid & pSamplingGrid)//代码未完成，赋值未完成。暂时用不到
{
	if(m_grid)
	{
		for(int i=0;i<m_size;i++)
		{
			if(m_grid[i])
			{
				delete [] m_grid[i];
				m_grid[i]=NULL;
			}
		}
		delete [] m_grid;
		m_grid=NULL;
	}

	m_size = pSamplingGrid.m_size;
	if(pSamplingGrid.m_grid)
	{
		m_grid=new AreaGrid *[m_size];
		for(int i=0;i<m_size;i++)
			m_grid[i]=new AreaGrid[m_size];
	}
}