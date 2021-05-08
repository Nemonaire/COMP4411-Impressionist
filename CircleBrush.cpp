//
// CircleBrush.cpp
//
// The implementation of Point Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "CircleBrush.h"

#include <math.h>

extern float frand();

CircleBrush::CircleBrush(ImpressionistDoc* pDoc, char* name) :
	ImpBrush(pDoc, name)
{
}

void CircleBrush::BrushBegin(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	BrushMove(source, target);
}

void CircleBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	if (pDoc == NULL) {
		printf("CircleBrush::BrushMove  document is NULL\n");
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
	glBegin(GL_POLYGON);
		SetColor( Point(source.x, source.y ) , dlg->getAlpha());
		for ( int i = 0; i <= 360; ++i)
		{
			float rad = i * M_PI / 180.0f;
			float dx = target.x + size / 2.0f * cos(rad);
			float dy = target.y + size / 2.0f * sin(rad);
			dx = min(max(dx, startX), endX);
			dy = min(max(dy, startY), endY);
			glVertex2f( dx, dy );
		}
	glEnd();
}

void CircleBrush::BrushEnd(const Point source, const Point target) {}

void CircleBrush::AlterBegin(const Point source, const Point target) {}
void CircleBrush::AlterMove(const Point source, const Point target) {}
void CircleBrush::AlterEnd(const Point source, const Point target) {}

