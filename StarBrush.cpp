//
// StarBrush.cpp
//
// The implementation of Point Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "StarBrush.h"

#include <math.h>

extern float frand();

StarBrush::StarBrush(ImpressionistDoc* pDoc, char* name) :
	ImpBrush(pDoc, name)
{
}

void StarBrush::BrushBegin(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	BrushMove(source, target);
}

void StarBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	if (pDoc == NULL) {
		printf("StarBrush::BrushMove  document is NULL\n");
		return;
	}
	// edge clipping
	if (source.x < 0 ||
		source.x > pDoc->m_nWidth ||
		source.y < 0 ||
		source.y > pDoc->m_nHeight)
		return;

	int size = pDoc->getSize();


	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glBegin(GL_LINE_LOOP);
		SetColor(Point(source.x, source.y), dlg->getAlpha());
		glVertex2d(target.x + cos(90 * M_PI / 180) * size / 2, target.y + sin(90 * M_PI / 180) * size / 2);
		glVertex2d(target.x + cos(306 * M_PI / 180) * size / 2, target.y + sin(306 * M_PI / 180) * size / 2);
		glVertex2d(target.x + cos(162 * M_PI / 180) * size / 2, target.y + sin(162 * M_PI / 180) * size / 2);
		glVertex2d(target.x + cos(18 * M_PI / 180) * size / 2, target.y + sin(18 * M_PI / 180) * size / 2);
		glVertex2d(target.x + cos(234 * M_PI / 180) * size / 2, target.y + sin(234 * M_PI / 180) * size / 2);

	glEnd();
}

void StarBrush::BrushEnd(const Point source, const Point target) {}

void StarBrush::AlterBegin(const Point source, const Point target) {}
void StarBrush::AlterMove(const Point source, const Point target) {}
void StarBrush::AlterEnd(const Point source, const Point target) {}


