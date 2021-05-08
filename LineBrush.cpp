//
// LineBrush.cpp
//
// The implementation of Point Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "LineBrush.h"

#include <math.h>
#include "ultilities.h"

extern float frand();

LineBrush::LineBrush(ImpressionistDoc* pDoc, char* name) :
	ImpBrush(pDoc, name),
	sobelX(KRN_SOBEL_X),
	sobelY(KRN_SOBEL_Y)
{
}

void LineBrush::BrushBegin(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	glLineWidth((float)dlg->getThickness());
	lastB = target;

	BrushMove(source, target);
}

void LineBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	if (pDoc == NULL) {
		printf("LineBrush::BrushMove  document is NULL\n");
		return;
	}
	// edge clipping
	if (source.x < 0 ||
		source.x > pDoc->m_nWidth ||
		source.y < 0 ||
		source.y > pDoc->m_nHeight)
		return;

	// set the angle to be the dir of cursor movement
	if (dlg->getDirType() == DIR_CURSOR_MOVEMENT)
	{
		int	angleToSet = atan2(target.y - lastB.y , target.x - lastB.x) / M_PI * 180;
		dlg->setAngle(angleToSet);
		lastB = target;
	}

	if (dlg->getDirType() == DIR_IMG_GRAD)
	{
		GLubyte originalBufferRGB[3 * 9];
		pDoc->GetOriginalArea(originalBufferRGB, source.x - 1, source.y - 1, source.x + 1, source.y + 1);
		GLdouble originalBufferD[9];
		for (int i = 0; i < 9; ++i)
		{
			originalBufferD[i] = rgb2g(originalBufferRGB + 3 * i);
		}
		double gx = sobelX.conv(originalBufferD);
		double gy = sobelY.conv(originalBufferD);
		int	angleToSet = atan2(gy, gx) / M_PI * 180;
		dlg->setAngle(angleToSet);
	}

	int size = pDoc->getSize();

	int angle = dlg->getAngle();
	Point pt1, pt2, pt1C, pt2C;
	pt1.x = target.x - size /2.0f * cos(angle * M_PI / 180.0f );
	pt1.y = target.y - size /2.0f * sin(angle * M_PI / 180.0f );
	pt2.x = target.x + size /2.0f * cos(angle * M_PI / 180.0f );
	pt2.y = target.y + size /2.0f * sin(angle * M_PI / 180.0f );
	// clip points
	pt1C = ClippedPoint(target, pt1);
	pt2C = ClippedPoint(target, pt2);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glBegin( GL_LINES );
		SetColor( source , dlg->getAlpha());
		glVertex2d(pt1C.x, pt1C.y);
		glVertex2d(pt2C.x, pt2C.y);

	glEnd();
}

void LineBrush::BrushEnd(const Point source, const Point target) {}

void LineBrush::AlterBegin(const Point source, const Point target)
{
	startA = target;
}

void LineBrush::AlterMove(const Point source, const Point target)
{
	glBegin( GL_LINES );
		glColor3ub(0xFF, 0, 0);
		glVertex2d(startA.x, startA.y);
		glVertex2d(target.x, target.y);
	glEnd();
	glFlush();
}

void LineBrush::AlterEnd(const Point source, const Point target)
{
	ImpressionistUI* dlg = GetDocument()->m_pUI;
	if (dlg->getDirType() == DIR_RIGHT_DRAG)
	{
		int size = sqrt((startA.x - target.x) * (startA.x - target.x)  + (startA.y - target.y) * (startA.y - target.y));
		int	angle = atan2(startA.y - target.y , startA.x - target.x) / M_PI * 180;
		dlg->setSize(size);
		dlg->setAngle(angle);
	}
}

bool LineBrush::PointOutOfRange(const Point& point)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = GetDocument()->m_pUI;
	return (point.x < 0 || point.x > pDoc->m_nPaintWidth
		|| point.y < dlg->m_paintView->h() - pDoc->m_nPaintHeight
		|| point.y > dlg->m_paintView->h());
}

const Point LineBrush::ClippedPoint(const Point& origin, const Point& dest)
{
	if (!PointOutOfRange(dest))
		return dest;
	if (	(origin.x - dest.x <= 1 && dest.x - origin.x <= 1)
		&&	(origin.y - dest.y <= 1 && dest.y - origin.y <= 1))
		return origin;
	Point mid((origin.x + dest.x) / 2, (origin.y + dest.y) / 2 );
	if (PointOutOfRange(mid))
		return ClippedPoint(origin, mid);
	else
		return ClippedPoint(mid, dest);
}
