//
// impressionistUI.h
//
// The header file for the UI part
//

#ifndef ImpressionistUI_h
#define ImpressionistUI_h

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/fl_file_chooser.H>		// FLTK file chooser
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Value_Slider.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Light_Button.H>

#include "Impressionist.h"
#include "OriginalView.h"
#include "PaintView.h"
#include "Kernels.h"

#include "ImpBrush.h"

class ImpressionistUI {
public:
	ImpressionistUI();

	// The FLTK widgets
	Fl_Window*			m_mainWindow;
	Fl_Menu_Bar*		m_menubar;
								
	PaintView*			m_paintView;
	OriginalView*		m_origView;

// for brush dialog
	Fl_Window*			m_brushDialog;
	Fl_Choice*			m_BrushTypeChoice;

	Fl_Slider*			m_BrushSizeSlider;
	Fl_Slider*			m_BrushThicknessSlider;
	Fl_Slider*			m_BrushAngleSlider;
	Fl_Slider*			m_BrushAlphaSlider;
	Fl_Slider*			m_RandomSpaceSlider;
	Fl_Choice*			m_DirTypeChoice;
	Fl_Choice*			m_KernelTypeChoice;
	Fl_Button*          m_ClearCanvasButton;
	Fl_Button*          m_RandomPaintButton;
	Fl_Slider*			m_RedSlider;
	Fl_Slider*			m_GreenSlider;
	Fl_Slider*			m_BlueSlider;

	// Member functions
	void				setDocument(ImpressionistDoc* doc);
	ImpressionistDoc*	getDocument();

	void				show();
	void				resize_windows(int w, int h);

	// Interface to get attribute

	int					getSize();
	int					getThickness();
	int					getAngle();
	float				getAlpha();
	int					getDirType();
	int					getKernelType();
	int					getRandomSpace();
	float				getRed();
	float				getGreen();
	float				getBlue();

	void				setSize(const int size);
	void				setThickness(const int v);
	void				setAngle(const int v);
	void				setAlpha(const float v);
	void				setDirType(const int v);
	void				setKernelType(const int v);
	void				setRandomSpace(const int v);
	void				setRed(const float red);
	void				setGreen(const float green);
	void				setBlue(const float blue);

	void				randomDraw();

private:
	ImpressionistDoc*	m_pDoc;		// pointer to document to communicate with the document

	// All attributes here
	int		m_nSize;
	int		m_nThickness;
	int		m_nAngle;
	float	m_fAlpha;
	int		m_eDirType;
	int		m_eKernelType;
	int		m_nRandomSpace;
	float	m_nRed;
	float	m_nGreen;
	float	m_nBlue;

	// Static class members
	static Fl_Menu_Item		menuitems[];
	static Fl_Menu_Item		brushTypeMenu[NUM_BRUSH_TYPE+1];
	static Fl_Menu_Item		dirTypeMenu[NUM_DIR_TYPE+1];
	static Fl_Menu_Item		kernelTypeMenu[NUM_KRN_TYPE+1];

	static ImpressionistUI*	whoami(Fl_Menu_* o);

	// All callbacks here.  Callbacks are declared 
	// static
	static void	cb_load_image(Fl_Menu_* o, void* v);
	static void	cb_save_image(Fl_Menu_* o, void* v);
	static void	cb_brushes(Fl_Menu_* o, void* v);
	static void	cb_clear_canvas(Fl_Menu_* o, void* v);
	static void cb_dissolve(Fl_Menu_* o, void* v);
	static void cb_undo(Fl_Menu_* o, void* v);
	static void	cb_exit(Fl_Menu_* o, void* v);
	static void	cb_about(Fl_Menu_* o, void* v);
	static void	cb_brushChoice(Fl_Widget* o, void* v);
	static void	cb_clear_canvas_button(Fl_Widget* o, void* v);
	static void	cb_sizeSlides(Fl_Widget* o, void* v);

	static void cb_thicknessSlides(Fl_Widget* o, void* v);
	static void cb_angleSlides(Fl_Widget* o, void* v);
	static void cb_alphaSlides(Fl_Widget* o, void* v);
	static void cb_dirChoice(Fl_Widget* o, void* v);
	static void cb_kernelChoice(Fl_Widget* o, void* v);
	static void	cb_randomSpaceSlides(Fl_Widget* o, void* v);
	static void	cb_randomPaintButton(Fl_Widget* o, void* v);

	static void cb_RedSlides(Fl_Widget* o, void* v);
	static void cb_GreenSlides(Fl_Widget* o, void* v);
	static void cb_BlueSlides(Fl_Widget* o, void* v);
};

#endif
