//
// ScatteredCircleBrush.cpp
//
// The implementation of Point Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "ScatteredCircleBrush.h"

extern float frand();
extern int irand(int);

ScatteredCircleBrush::ScatteredCircleBrush( ImpressionistDoc* pDoc, char* name ) :
	CircleBrush(pDoc,name)
{
}

void ScatteredCircleBrush::BrushBegin( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg=pDoc->m_pUI;

	int size = pDoc->getSize();



	glPointSize( (float)size );

	BrushMove( source, target );
}

void ScatteredCircleBrush::BrushMove( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg=pDoc->m_pUI;

	if ( pDoc == NULL ) {
		printf( "ScatteredCircleBrush::BrushMove  document is NULL\n" );
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
		CircleBrush::BrushMove(src, dst);
	}
}

void ScatteredCircleBrush::BrushEnd( const Point source, const Point target )
{
	// do nothing so far
}

