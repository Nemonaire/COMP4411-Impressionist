//
// KernelBrush.cpp
//
// The implementation of Point Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "KernelBrush.h"
#include "ultilities.h"

extern void rgb3c(void* rgb, int len, int size, void* r, void* g, void* b);
extern void ub2d(unsigned char* src, double* dst, size_t size);

KernelBrush::KernelBrush(ImpressionistDoc* pDoc, char* name) :
	ImpBrush(pDoc, name), type(-1)
{
	for (int i = 0; i < NUM_KRN_TYPE; ++i)
		kernels[i] = new Kernel(i);
}
KernelBrush::~KernelBrush()
{
	for (int i = 0; i < NUM_KRN_TYPE; ++i)
		delete kernels[i];
}

void KernelBrush::BrushBegin( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg=pDoc->m_pUI;

	type = dlg->getKernelType();
	BrushMove( source, target );
}

void KernelBrush::BrushMove( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg=pDoc->m_pUI;

	if ( pDoc == NULL ) {
		printf( "KernelBrush::BrushMove  document is NULL\n" );
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

	type = dlg->getKernelType();
	if (type < 0 || type >= NUM_KRN_TYPE)
		return;

	int kernelSize = kernels[type]->getSize();
	GLubyte* bufRGB = new GLubyte[kernelSize * kernelSize * 3];
	GLubyte* bufRu = new GLubyte[kernelSize * kernelSize];
	GLubyte* bufGu = new GLubyte[kernelSize * kernelSize];
	GLubyte* bufBu = new GLubyte[kernelSize * kernelSize];
	GLdouble* bufRd = new GLdouble[kernelSize * kernelSize];
	GLdouble* bufGd = new GLdouble[kernelSize * kernelSize];
	GLdouble* bufBd = new GLdouble[kernelSize * kernelSize];

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glBegin( GL_POINTS );
		for ( int i = startX; i <= endX; ++i)
		{
			for (int j = startY; j <= endY; ++j)
			{
				pDoc->GetOriginalArea(bufRGB,
					i - (kernelSize - 1) / 2,
					j - (kernelSize - 1) / 2,
					i + (kernelSize - 1) / 2,
					j + (kernelSize - 1) / 2);
				rgb3c((const void*)bufRGB, kernelSize * kernelSize, sizeof(GLubyte),
					(void*)bufRu, (void*)bufGu,(void*)bufBu);
				ub2d(bufRu, bufRd, kernelSize * kernelSize);
				ub2d(bufGu, bufGd, kernelSize * kernelSize);
				ub2d(bufBu, bufBd, kernelSize * kernelSize);
				double rd = kernels[type]->conv(bufRd);
				double gd = kernels[type]->conv(bufGd);
				double bd = kernels[type]->conv(bufBd);

				glColor4f(rd, gd, bd, dlg->getAlpha());
				glVertex2d(i, j);
			}
		}

	glEnd();

	delete[] bufRGB;
	delete[] bufRu, bufGu, bufBu;
	delete[] bufRd, bufGd, bufBd;
}

void KernelBrush::BrushEnd( const Point source, const Point target ){}

void KernelBrush::AlterBegin(const Point source, const Point target) {}
void KernelBrush::AlterMove(const Point source, const Point target) {}
void KernelBrush::AlterEnd(const Point source, const Point target) {}

