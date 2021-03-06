// QRcodeImage.cpp: implementation of the QRcodeImage class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "QRcodeImage.h"

#include<vector>
using std::vector;
#include<math.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
QRcodeImage::QRcodeImage()
{
	DECIMAL_POINT=21;

	bitmap = NULL;
	bitMatrix = NULL;
	m_pBitmap = NULL;
	m_pOldBitmap = NULL;
	m_pDC = NULL;
	m_finderPattern=NULL;
	m_alignmentPattern=NULL;
	m_samplingGrid=NULL;
}

QRcodeImage::QRcodeImage(CString FilePathName)
{
	m_finderPattern=NULL;
	m_alignmentPattern=NULL;
	m_samplingGrid=NULL;
	DECIMAL_POINT=21;
	//载入图片，抽取位值
	HBITMAP hbmp = (HBITMAP)::LoadImage(AfxGetInstanceHandle(), FilePathName, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION|LR_LOADFROMFILE);
	m_pBitmap = new CBitmap;
	m_pBitmap->Attach(hbmp);

	//获取图片信息
	BITMAP   BmpInfo;   
	m_pBitmap->GetBitmap(&BmpInfo);
	nWidth=BmpInfo.bmWidth;
	nHeight=BmpInfo.bmHeight;

	//读入图片数据
	//int ok=m_pBitmap->GetBitmapBits(2000,m_CodeData);

	//读入绘图设备
	m_pDC = new CDC;
	m_pDC->CreateCompatibleDC(NULL);
	m_pOldBitmap = m_pDC->SelectObject(m_pBitmap);
	
}

QRcodeImage::~QRcodeImage()
{
	int i, j;
	if ( bitmap != NULL )
	{
		for (i=0; i<nWidth; i++)
			delete bitmap[i];
		delete bitmap;
	}

	if ( bitMatrix != NULL)
	{
		for (i=0; i<gridSize; i++)
			delete bitMatrix[i];
		delete bitMatrix;
	}
	if ( m_pBitmap != NULL)
	{
		delete m_pBitmap;
	}
	if ( m_pDC != NULL)
	{
		::ReleaseDC(NULL, m_pDC->GetSafeHdc());
		delete m_pDC;
		m_pDC=NULL;
	}
	if(m_finderPattern)
	{
		delete m_finderPattern;
		m_finderPattern=NULL;
	}
	if(m_alignmentPattern)
	{
		delete m_alignmentPattern;
		m_alignmentPattern=NULL;
	}
	if(m_samplingGrid)
	{
		delete m_samplingGrid;
		m_samplingGrid=NULL;
	}
}

void QRcodeImage::GetImageData()
{
	DECIMAL_POINT=21;
	filterImage();
	
	if(m_finderPattern)
	{
		delete m_finderPattern;
		m_finderPattern=NULL;
	}
	m_finderPattern=new FinderPattern();
	m_finderPattern->findFinderPattern(bitmap,nWidth,nHeight,DECIMAL_POINT);

	if(m_alignmentPattern)
	{
		delete m_alignmentPattern;
		m_alignmentPattern=NULL;
	}
	m_alignmentPattern=new AlignmentPattern();
	m_alignmentPattern->findAlignmentPattern(bitmap,nWidth,nHeight,m_finderPattern,DECIMAL_POINT);


	//Creating sampling grid
	//samplingGrid = getSamplingGrid2_6(finderPattern, alignmentPattern);
//	m_samplingGrid = getSamplingGrid(m_finderPattern, m_alignmentPattern);
	getSamplingGrid(m_finderPattern, m_alignmentPattern);
	
	//Reading grid
	if(m_samplingGrid)
		getQRCodeMatrix(*m_samplingGrid);

/*	boolean[][] qRCodeMatrix = null;
	try {
		qRCodeMatrix = getQRCodeMatrix(bitmap, samplingGrid);
	} catch (ArrayIndexOutOfBoundsException e) {
		throw new SymbolNotFoundException("Sampling grid exceeded image boundary");
	}
	//canvas.drawMatrix(qRCodeMatrix);
	return new QRCodeSymbol(qRCodeMatrix);
*/
}

//灰度过滤
void QRcodeImage::filterImage()
{
	int x,y,i,j;

	//读入图形点阵
	int ** intImage=new int * [nWidth];
	for(i=0;i<nWidth;i++)
		intImage[i]=new int[nHeight];
	for (y = 0; y < nHeight; y++)
	{
		for (x = 0; x < nWidth; x++)
		{
			intImage[x][y] = m_pDC->GetPixel(x,y);
		}
	}

	int longSide = (nWidth < nHeight) ? nHeight : nWidth;
	DECIMAL_POINT = (int)(23-sqrt((double)(longSide/256)));
	
	//image to gray scale
	///////////////////////////////////////////////////////////////
	for (y = 0; y < nHeight; y++) {
		for (x = 0; x < nWidth; x++) {
			int r = intImage[x][y] >> 16 & 0xFF;
			int g = intImage[x][y] >> 8 & 0xFF;
			int b = intImage[x][y] & 0xFF;
			int m = (r * 30 + g * 59 + b * 11) / 100;
			intImage[x][y] = m;
		}
	}

	//get middle brightness per area
	/////////////////////////////////////////////////////////////////
	int numSqrtArea = 4;
	//obtain middle brightness((min + max) / 2) per area
	int areaWidth = nWidth / numSqrtArea;
	int areaHeight = nHeight / numSqrtArea;

	int *** minmax = new int **[numSqrtArea];
	for(i=0;i<numSqrtArea;i++)
	{
		minmax[i]=new int * [numSqrtArea];
		for(j=0;j<numSqrtArea;j++)
			minmax[i][j]=new int[2];
	}
	//int[][][] minmax = new int[numSqrtArea][numSqrtArea][2];

	int ax,ay,dy,dx;
	for (ay = 0; ay < numSqrtArea; ay++) {
		for (ax = 0; ax < numSqrtArea; ax++) {
			minmax[ax][ay][0] = 0xFF;
			for (int dy = 0; dy < areaHeight; dy++) {
				for (int dx = 0; dx < areaWidth; dx++) {
					int target = intImage[areaWidth * ax + dx][areaHeight * ay + dy];
					if (target < minmax[ax][ay][0]) minmax[ax][ay][0] = target;
					if (target > minmax[ax][ay][1]) minmax[ax][ay][1] = target;
				}
			}
			//minmax[ax][ay][0] = (minmax[ax][ay][0] + minmax[ax][ay][1]) / 2;
		}
	}

	int ** middle = new int * [numSqrtArea];
	for(i=0;i<numSqrtArea;i++)
		middle[i]=new int[numSqrtArea];
	//int[][] middle =  new int[numSqrtArea][numSqrtArea];

	for (ay = 0; ay < numSqrtArea; ay++) {
		for (ax = 0; ax < numSqrtArea; ax++) {
			middle[ax][ay] = (minmax[ax][ay][0] + minmax[ax][ay][1]) / 2;
		}
	}

	//gray scale to bitmap
	///////////////////////////////////////////////////////////////
	bitmap = new BYTE *[nWidth];
	for(i=0;i<nWidth;i++)
		bitmap[i]=new BYTE[nHeight];
	//boolean[][] bitmap = new boolean[nWidth][nHeight];

	for (ay = 0; ay < numSqrtArea; ay++) {
		for (ax = 0; ax < numSqrtArea; ax++) {
			for (dy = 0; dy < areaHeight; dy++) {
				for (dx = 0; dx < areaWidth; dx++) {
					bitmap[areaWidth * ax + dx][areaHeight * ay + dy] = (intImage[areaWidth * ax + dx][areaHeight * ay + dy] < middle[ax][ay]) ? true : false;
				}
			}
		}
	}

	for (i=0; i<nWidth; i++)
		delete intImage[i];
	delete intImage;

	for (i=0; i<numSqrtArea; i++)
	{
		for(j=0;j<numSqrtArea;j++)
			delete [] minmax[i][j];
		delete minmax[i];
		delete middle[i];
	}
	delete minmax;
	delete middle;
}


void QRcodeImage::getSamplingGrid(FinderPattern * finderPattern, AlignmentPattern * alignmentPattern)
{

	Point ** centers = alignmentPattern->m_centers;

	int i;

	int version = finderPattern->m_version;
	int sqrtCenters = (version / 7) + 2;
	
	centers[0][0] = finderPattern->m_center[UL];
	centers[sqrtCenters-1][0] = finderPattern->m_center[UR];
	centers[0][sqrtCenters-1] = finderPattern->m_center[DL];
	//int sqrtNumModules = finderPattern.getSqrtNumModules(); /// The number of modules per one side is obtained
	int sqrtNumArea = sqrtCenters-1;
	
	if(m_samplingGrid)
	{
		delete m_samplingGrid;
		m_samplingGrid=NULL;
	}
	m_samplingGrid = new SamplingGrid(sqrtNumArea);
//	SamplingGrid samplingGrid = SamplingGrid(sqrtNumArea);

	Line baseLineX, baseLineY, gridLineX, gridLineY;

	//int logicalDistance = alignmentPattern.getLogicalDistance();
	Axis axis = Axis(finderPattern->m_sincos, finderPattern->m_moduleSize[UL],DECIMAL_POINT);
	ModulePitch modulePitch;

	// for each area :
	for (int ay = 0; ay < sqrtNumArea; ay++)
	{
		for (int ax = 0; ax < sqrtNumArea; ax++)
		{
			modulePitch = ModulePitch(); // Housing to order 
			baseLineX = Line();
			baseLineY = Line();
			axis.setModulePitch(finderPattern->m_moduleSize[UL]);

			alignmentPattern->getLogicalCenter(finderPattern);
			Point ** logicalCenters= alignmentPattern->m_logicalCenters;

			Point upperLeftPoint	=	centers[ax][ay];
			Point upperRightPoint	=	centers[ax+1][ay];
			Point lowerLeftPoint	=	centers[ax][ay+1];
			Point lowerRightPoint	=	centers[ax+1][ay+1];

			Point logicalUpperLeftPoint	=	logicalCenters[ax][ay];
			Point logicalUpperRightPoint	=	logicalCenters[ax+1][ay];
			Point logicalLowerLeftPoint	=	logicalCenters[ax][ay+1];
			Point logicalLowerRightPoint	=	logicalCenters[ax+1][ay+1];

			if(ax==0 && ay==0) // left upper corner
			{
				if (sqrtNumArea == 1) {
					upperLeftPoint = axis.translate(upperLeftPoint,-3,-3);
					upperRightPoint = axis.translate(upperRightPoint,3,-3);
					lowerLeftPoint = axis.translate(lowerLeftPoint,-3,3);
					lowerRightPoint = axis.translate(lowerRightPoint,6,6);

					logicalUpperLeftPoint.translate(-6,-6);
					logicalUpperRightPoint.translate(3,-3);
					logicalLowerLeftPoint.translate(-3,3);						
					logicalLowerRightPoint.translate(6,6);						
				}
				else {
					upperLeftPoint = axis.translate(upperLeftPoint,-3,-3);
					upperRightPoint = axis.translate(upperRightPoint,0,-6);
					lowerLeftPoint = axis.translate(lowerLeftPoint,-6,0);

					logicalUpperLeftPoint.translate(-6,-6);
					logicalUpperRightPoint.translate(0,-6);
					logicalLowerLeftPoint.translate(-6,0);
				}
			}
			else if(ax==0 && ay==sqrtNumArea-1) // left bottom corner
			{
				upperLeftPoint = axis.translate(upperLeftPoint,-6,0);
				lowerLeftPoint = axis.translate(lowerLeftPoint,-3,3);
				lowerRightPoint = axis.translate(lowerRightPoint, 0, 6);


				logicalUpperLeftPoint.translate(-6,0);
				logicalLowerLeftPoint.translate(-6,6);
				logicalLowerRightPoint.translate(0,6);
			}
			else if(ax==sqrtNumArea-1 && ay==0) // right upper corner
			{
				upperLeftPoint = axis.translate(upperLeftPoint,0,-6);
				upperRightPoint = axis.translate(upperRightPoint,3,-3);
				lowerRightPoint = axis.translate(lowerRightPoint,6,0);

				logicalUpperLeftPoint.translate(0,-6);
				logicalUpperRightPoint.translate(6,-6);
				logicalLowerRightPoint.translate(6,0);
			}
			else if(ax==sqrtNumArea-1 && ay==sqrtNumArea-1) // right bottom corner
			{
				lowerLeftPoint = axis.translate(lowerLeftPoint,0,6);
				upperRightPoint = axis.translate(upperRightPoint,6,0);
				lowerRightPoint = axis.translate(lowerRightPoint,6,6);

				logicalLowerLeftPoint.translate(0,6);
				logicalUpperRightPoint.translate(6,0);
				logicalLowerRightPoint.translate(6,6);
			}
			else if(ax==0) // left side
			{
				upperLeftPoint = axis.translate(upperLeftPoint,-6,0);
				lowerLeftPoint = axis.translate(lowerLeftPoint,-6,0);

				logicalUpperLeftPoint.translate(-6,0);
				logicalLowerLeftPoint.translate(-6,0);

			}
			else if(ax==sqrtNumArea-1) // right
			{
				upperRightPoint = axis.translate(upperRightPoint,6,0);
				lowerRightPoint = axis.translate(lowerRightPoint,6,0);

				logicalUpperRightPoint.translate(6,0);
				logicalLowerRightPoint.translate(6,0);
			}
			else if(ay==0) // top
			{
				upperLeftPoint = axis.translate(upperLeftPoint,0,-6);
				upperRightPoint = axis.translate(upperRightPoint,0,-6);

				logicalUpperLeftPoint.translate(0,-6);
				logicalUpperRightPoint.translate(0,-6);

			}
			else if(ay==sqrtNumArea-1) // bottom
			{
				lowerLeftPoint = axis.translate(lowerLeftPoint,0,6);
				lowerRightPoint = axis.translate(lowerRightPoint,0,6);

				logicalLowerLeftPoint.translate(0,6);
				logicalLowerRightPoint.translate(0,6);
			}
			
			if(ax==0)
			{
				logicalUpperRightPoint.translate(1,0);
				logicalLowerRightPoint.translate(1,0);
			}
			else
			{
				logicalUpperLeftPoint.translate(-1,0);
				logicalLowerLeftPoint.translate(-1,0);
			}

			if(ay==0)
			{
				logicalLowerLeftPoint.translate(0,1);
				logicalLowerRightPoint.translate(0,1);
			}
			else
			{
				logicalUpperLeftPoint.translate(0,-1);
				logicalUpperRightPoint.translate(0,-1);
			}
			
			int logicalWidth=logicalUpperRightPoint.x-logicalUpperLeftPoint.x;
			int logicalHeight=logicalLowerLeftPoint.y-logicalUpperLeftPoint.y;

			if (version < 7) {
				logicalWidth += 3;
				logicalHeight += 3;
				
			}
			modulePitch.top = getAreaModulePitch(upperLeftPoint, upperRightPoint, logicalWidth-1);
			modulePitch.left = getAreaModulePitch(upperLeftPoint, lowerLeftPoint, logicalHeight-1);
			modulePitch.bottom = getAreaModulePitch(lowerLeftPoint, lowerRightPoint, logicalWidth-1);
			modulePitch.right = getAreaModulePitch(upperRightPoint, lowerRightPoint, logicalHeight-1);

			baseLineX.setP1(upperLeftPoint);
			baseLineY.setP1(upperLeftPoint);
			baseLineX.setP2(lowerLeftPoint);
			baseLineY.setP2(upperRightPoint);

			m_samplingGrid->initGrid(ax,ay,logicalWidth,logicalHeight);

			for (i = 0; i < logicalWidth; i++)
			{
				gridLineX = Line(baseLineX.getP1(), baseLineX.getP2());

				axis.setOrigin(gridLineX.getP1());
				axis.setModulePitch(modulePitch.top);
				gridLineX.setP1(axis.translate(i,0));

				axis.setOrigin(gridLineX.getP2());
				axis.setModulePitch(modulePitch.bottom);
				gridLineX.setP2(axis.translate(i,0));

				m_samplingGrid->setXLine(ax,ay,i,gridLineX);
			}

			for (i = 0; i < logicalHeight; i++)
			{
				gridLineY = Line(baseLineY.getP1(), baseLineY.getP2());

				axis.setOrigin(gridLineY.getP1());
				axis.setModulePitch(modulePitch.left);
				gridLineY.setP1(axis.translate(0,i));

				axis.setOrigin(gridLineY.getP2());
				axis.setModulePitch(modulePitch.right);
				gridLineY.setP2(axis.translate(0,i));

				m_samplingGrid->setYLine(ax,ay,i,gridLineY);
			}
		}
	}
}

//get module pitch in single area
int QRcodeImage::getAreaModulePitch(Point start, Point end, int logicalDistance)
{
	Line tempLine;
	tempLine = Line(start, end);
	int realDistance = tempLine.getLength();
	int modulePitch = (realDistance << DECIMAL_POINT) / logicalDistance;
	return modulePitch;
}

//gridLines[areaX][areaY][direction(x=0,y=1)][EachLines]	
void QRcodeImage::getQRCodeMatrix(SamplingGrid  & gridLines)
{
	//int gridSize = gridLines.getWidth() * gridLines.getWidth(0,0);
	gridSize = gridLines.getTotalWidth();

	Point bottomRightPoint;
	bitMatrix=new BYTE * [gridSize];
	for(int i=0;i<gridSize;i++)
		bitMatrix[i]=new BYTE[gridSize];
	//boolean[][] sampledMatrix = new boolean[gridSize][gridSize];

	for (int ay = 0; ay < gridLines.getHeight(); ay++)
	{
		for (int ax = 0; ax < gridLines.getWidth(); ax++)
		{
			//vector sampledPoints = new Vector(); //only for visualize;
			for (int y = 0; y < gridLines.getHeight(ax,ay); y++)
			{
				for (int x = 0; x < gridLines.getWidth(ax,ay); x++)
				{
					int x1 = gridLines.getXLine(ax,ay,x).getP1().x;
					int y1 = gridLines.getXLine(ax,ay,x).getP1().y;
					int x2 = gridLines.getXLine(ax,ay,x).getP2().x;
					int y2 = gridLines.getXLine(ax,ay,x).getP2().y;
					int x3 = gridLines.getYLine(ax,ay,y).getP1().x;
					int y3 = gridLines.getYLine(ax,ay,y).getP1().y;
					int x4 = gridLines.getYLine(ax,ay,y).getP2().x;
					int y4 = gridLines.getYLine(ax,ay,y).getP2().y;
					
					int e = (y2 - y1) * (x3 - x4) - (y4 - y3) * (x1 - x2);
					int f = (x1 * y2 - x2 * y1) * (x3 - x4) - (x3 * y4 - x4 * y3) * (x1 - x2);
					int g = (x3 * y4 - x4 * y3) * (y2 - y1) - (x1 * y2 - x2 * y1) * (y4 - y3);
					bitMatrix[gridLines.getX(ax, x)][gridLines.getY(ay, y)] = bitmap[f / e][g / e];
					if ((ay == gridLines.getHeight() -1 && ax == gridLines.getWidth() - 1) &&
							y == gridLines.getHeight(ax, ay) - 1 && x == gridLines.getWidth(ax, ay) -1)
						bottomRightPoint = Point(f / e,g / e);
				}
			}
		}
	}

	if ((bottomRightPoint.x>nWidth-1 || bottomRightPoint.y>nHeight-1))
	{
#ifdef UNICODE
			AfxMessageBox(_T("Sampling grid pointed out of image"));
#else
			AfxMessageBox("Sampling grid pointed out of image");
#endif // !UNICODE
		exit(0);
	}

	//return bitMatrix;
}