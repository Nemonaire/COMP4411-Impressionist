//
// PointBrush.cpp
//
// The implementation of Point Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "pointbrush.h"

extern float frand();

PointBrush::PointBrush( ImpressionistDoc* pDoc, char* name ) :
	ImpBrush(pDoc,name)
{
}

void PointBrush::BrushBegin( const Point source, const Point target )
{
	BrushMove( source, target );
}

void PointBrush::BrushMove( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg=pDoc->m_pUI;

	if ( pDoc == NULL ) {
		printf( "PointBrush::BrushMove  document is NULL\n" );
		return;
	}

	// edge clipping
	if (source.x < 0 ||
		source.x > pDoc->m_nWidth ||
		source.y < 0 ||
		source.y > pDoc->m_nHeight)
		return;

	int size = pDoc->getSize();
	float alpha = dlg->getAlpha();
	int startX = max(target.x - size / 2, 0);
	int endX = min(target.x + size / 2, pDoc->m_nPaintWidth);
	int startY = max(target.y - size / 2, dlg->m_paintView->h() - pDoc->m_nPaintHeight);
	int endY = min(target.y + size / 2, dlg->m_paintView->h());

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glBegin( GL_POINTS );
		SetColor( Point(source.x, source.y) , dlg->getAlpha());
		for ( int i = startX; i <= endX; ++i)
		{
			for (int j = startY; j <= endY; ++j)
			{
				glVertex2d( i, j );
			}
		}
	glEnd();
}

void PointBrush::BrushEnd(const Point source, const Point target) {}

void PointBrush::AlterBegin(const Point source, const Point target) {}
void PointBrush::AlterMove(const Point source, const Point target) {}
void PointBrush::AlterEnd(const Point source, const Point target) {}

