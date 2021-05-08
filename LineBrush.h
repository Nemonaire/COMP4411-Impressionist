//
// PointBrush.h
//
// The header file for Point Brush. 
//

#ifndef LINEBRUSH_H
#define LINEBRUSH_H

#include "ImpBrush.h"
#include "kernels.h"

class LineBrush : public ImpBrush
{
	int thickness, angle;
	Point lastB;	// left button
	Point startA;	// right button
	bool PointOutOfRange(const Point& p);
	const Point ClippedPoint(const Point& origin, const Point& dest);
	Kernel sobelX, sobelY;
public:
	LineBrush(ImpressionistDoc* pDoc = NULL, char* name = NULL);

	void BrushBegin(const Point source, const Point target);
	void BrushMove(const Point source, const Point target);
	void BrushEnd(const Point source, const Point target);
	void AlterBegin(const Point source, const Point target);
	void AlterMove(const Point source, const Point target);
	void AlterEnd(const Point source, const Point target);


	char* BrushName(void);
};

#endif