//
// ScatteredPointBrush.cpp
//
// The implementation of Point Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "ScatteredPointBrush.h"

extern float frand();

ScatteredPointBrush::ScatteredPointBrush( ImpressionistDoc* pDoc, char* name ) :
	ImpBrush(pDoc,name)
{
}

void ScatteredPointBrush::BrushBegin( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg=pDoc->m_pUI;

	glPointSize( (float)1 );

	BrushMove( source, target );
}

void ScatteredPointBrush::BrushMove( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg=pDoc->m_pUI;

	if ( pDoc == NULL ) {
		printf( "ScatteredPointBrush::BrushMove  document is NULL\n" );
		return;
	}
	// edge clipping
	if (source.x < 0 ||
		source.x > pDoc->m_nWidth ||
		source.y < 0 ||
		source.y > pDoc->m_nHeight)
		return;

	int size = pDoc->getSize();
	int startX = max(target.x - size / 2, 0);
	int endX = min(target.x + size / 2, pDoc->m_nPaintWidth);
	int startY = max(target.y - size / 2, dlg->m_paintView->h() - pDoc->m_nPaintHeight);
	int endY = min(target.y + size / 2, dlg->m_paintView->h());

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glBegin( GL_POINTS );
		for ( int i = startX; i <= endX; ++i)
		{
			for (int j = startY; j <= endY; ++j)
			{
				if (frand() < 0.3)
				{
					SetColor( Point(source.x + i - startX, source.y + j - startY) , dlg->getAlpha());
					glVertex2d( i, j );
				}
			}
		}

	glEnd();
}

void ScatteredPointBrush::BrushEnd( const Point source, const Point target ){}

void ScatteredPointBrush::AlterBegin(const Point source, const Point target) {}
void ScatteredPointBrush::AlterMove(const Point source, const Point target) {}
void ScatteredPointBrush::AlterEnd(const Point source, const Point target) {}

