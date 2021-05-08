//
// ImpBrush.cpp
//
// The implementation of virtual brush. All the other brushes inherit from it.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "ImpBrush.h"

// Static class member initializations
int			ImpBrush::c_nBrushCount	= 0;
ImpBrush**	ImpBrush::c_pBrushes	= NULL;

ImpBrush::ImpBrush(ImpressionistDoc*	pDoc, 
				   char*				name) :
					m_pDoc(pDoc), 
					m_pBrushName(name)
{
}

//---------------------------------------------------
// Return m_pDoc, which connects the UI and brushes
//---------------------------------------------------
ImpressionistDoc* ImpBrush::GetDocument(void)
{
	return m_pDoc;
}

//---------------------------------------------------
// Return the name of the current brush
//---------------------------------------------------
char* ImpBrush::BrushName(void)
{
	return m_pBrushName;
}

//----------------------------------------------------
// Set the color to paint with to the color at source,
// which is the coord at the original window to sample 
// the color from
//----------------------------------------------------
void ImpBrush::SetColor (const Point source, float alpha=1.0f)
{
	ImpressionistDoc* pDoc = GetDocument();

	float red = pDoc->m_pUI->getRed();
	float green = pDoc->m_pUI->getGreen();
	float blue = pDoc->m_pUI->getBlue();

	GLubyte color[4];

	memcpy ( color, pDoc->GetOriginalPixel( source ), 3 );
	color[3] = 0xFF * alpha;
	color[0] *= red;
	color[1] *= green;
	color[2] *= blue;
	glColor4ubv( color );

}