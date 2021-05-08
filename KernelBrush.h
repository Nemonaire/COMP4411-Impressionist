#ifndef KERNEL_BRUSH_H
#define KERNEL_BRUSH_H

#include "ImpBrush.h"
#include "kernels.h"

class KernelBrush : public ImpBrush
{
	int type;
	Kernel* kernels[NUM_KRN_TYPE];
public:
	KernelBrush(ImpressionistDoc* pDoc = NULL, char* name = NULL);
	~KernelBrush();

	void BrushBegin(const Point source, const Point target);
	void BrushMove(const Point source, const Point target);
	void BrushEnd(const Point source, const Point target);
	void AlterBegin(const Point source, const Point target);
	void AlterMove(const Point source, const Point target);
	void AlterEnd(const Point source, const Point target);


	char* BrushName(void);
};
#endif
