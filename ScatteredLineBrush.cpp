//
// ScatteredLineBrush.cpp
//
// The implementation of Point Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "ScatteredLineBrush.h"

extern float frand();
extern int irand(int);

ScatteredLineBrush::ScatteredLineBrush( ImpressionistDoc* pDoc, char* name ) :
	LineBrush(pDoc,name)
{
}

void ScatteredLineBrush::BrushBegin( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg=pDoc->m_pUI;

	int size = pDoc->getSize();



	glPointSize( (float)size );

	BrushMove( source, target );
}

void ScatteredLineBrush::BrushMove( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg=pDoc->m_pUI;

	if ( pDoc == NULL ) {
		printf( "ScatteredLineBrush::BrushMove  document is NULL\n" );
		return;
	}
	// edge clipping
	if (source.x < 0 ||
		source.x > pDoc->m_nPaintWidth ||
		source.y < 0 ||
		source.y > pDoc->m_nPaintHeight)
		return;

	int size = pDoc->getSize();

	for (int i = 0; i < 4; ++i)
	{
		int dx = irand(size) - size / 2;
		int dy = irand(size) - size / 2;
		Point src(source.x + dx, source.y + dy);
		Point dst(target.x + dx, target.y + dy);
		LineBrush::BrushMove(src, dst);
	}
}

void ScatteredLineBrush::BrushEnd( const Point source, const Point target )
{
	// do nothing so far
}

