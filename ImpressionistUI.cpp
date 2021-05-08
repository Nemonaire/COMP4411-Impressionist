//
// impressionistUI.h
//
// The user interface part for the program.
//


#include <FL/fl_ask.h>

#include <math.h>

#include "impressionistUI.h"
#include "impressionistDoc.h"

extern int irand(int max);

/*
//------------------------------ Widget Examples -------------------------------------------------
Here is some example code for all of the widgets that you may need to add to the 
project.  You can copy and paste these into your code and then change them to 
make them look how you want.  Descriptions for all of the widgets here can be found 
in links on the fltk help session page.

//---------Window/Dialog and Menubar-----------------------------------
	
	//----To install a window--------------------------
	Fl_Window* myWindow = new Fl_Window(600, 300, "MyWindow");
		myWindow->user_data((void*)(this));	// record self to be used by static callback functions
		
		// install menu bar
		myMenubar = new Fl_Menu_Bar(0, 0, 600, 25);
		Fl_Menu_Item ImpressionistUI::myMenuItems[] = {
			{ "&File",		0, 0, 0, FL_SUBMENU },
				{ "&Load...",	FL_ALT + 'l', (Fl_Callback *)ImpressionistUI::cb_load },
				{ "&Save...",	FL_ALT + 's', (Fl_Callback *)ImpressionistUI::cb_save }.
				{ "&Quit",			FL_ALT + 'q', (Fl_Callback *)ImpressionistUI::cb_exit },
				{ 0 },
			{ "&Edit",		0, 0, 0, FL_SUBMENU },
				{ "&Copy",FL_ALT + 'c', (Fl_Callback *)ImpressionistUI::cb_copy, (void *)COPY },
				{ "&Cut",	FL_ALT + 'x', (Fl_Callback *)ImpressionistUI::cb_cut, (void *)CUT },
				{ "&Paste",	FL_ALT + 'v', (Fl_Callback *)ImpressionistUI::cb_paste, (void *)PASTE },
				{ 0 },
			{ "&Help",		0, 0, 0, FL_SUBMENU },
				{ "&About",	FL_ALT + 'a', (Fl_Callback *)ImpressionistUI::cb_about },
				{ 0 },
			{ 0 }
		};
		myMenubar->menu(myMenuItems);
    m_mainWindow->end();

	//----The window callback--------------------------
	// One of the callbacks
	void ImpressionistUI::cb_load(Fl_Menu_* o, void* v) 
	{	
		ImpressionistDoc *pDoc=whoami(o)->getDocument();

		char* newfile = fl_file_chooser("Open File?", "*.bmp", pDoc->getImageName() );
		if (newfile != NULL) {
			pDoc->loadImage(newfile);
		}
	}


//------------Slider---------------------------------------

	//----To install a slider--------------------------
	Fl_Value_Slider * mySlider = new Fl_Value_Slider(10, 80, 300, 20, "My Value");
	mySlider->user_data((void*)(this));	// record self to be used by static callback functions
	mySlider->type(FL_HOR_NICE_SLIDER);
    mySlider->labelfont(FL_COURIER);
    mySlider->labelsize(12);
	mySlider->minimum(1);
	mySlider->maximum(40);
	mySlider->step(1);
	mySlider->value(m_nMyValue);
	mySlider->align(FL_ALIGN_RIGHT);
	mySlider->callback(cb_MyValueSlides);

	//----The slider callback--------------------------
	void ImpressionistUI::cb_MyValueSlides(Fl_Widget* o, void* v)
	{
		((ImpressionistUI*)(o->user_data()))->m_nMyValue=int( ((Fl_Slider *)o)->value() ) ;
	}
	

//------------Choice---------------------------------------
	
	//----To install a choice--------------------------
	Fl_Choice * myChoice = new Fl_Choice(50,10,150,25,"&myChoiceLabel");
	myChoice->user_data((void*)(this));	 // record self to be used by static callback functions
	Fl_Menu_Item ImpressionistUI::myChoiceMenu[3+1] = {
	  {"one",FL_ALT+'p', (Fl_Callback *)ImpressionistUI::cb_myChoice, (void *)ONE},
	  {"two",FL_ALT+'l', (Fl_Callback *)ImpressionistUI::cb_myChoice, (void *)TWO},
	  {"three",FL_ALT+'c', (Fl_Callback *)ImpressionistUI::cb_myChoice, (void *)THREE},
	  {0}
	};
	myChoice->menu(myChoiceMenu);
	myChoice->callback(cb_myChoice);
	
	//-----The choice callback-------------------------
	void ImpressionistUI::cb_myChoice(Fl_Widget* o, void* v)
	{
		ImpressionistUI* pUI=((ImpressionistUI *)(o->user_data()));
		ImpressionistDoc* pDoc=pUI->getDocument();

		int type=(int)v;

		pDoc->setMyType(type);
	}


//------------Button---------------------------------------

	//---To install a button---------------------------
	Fl_Button* myButton = new Fl_Button(330,220,50,20,"&myButtonLabel");
	myButton->user_data((void*)(this));   // record self to be used by static callback functions
	myButton->callback(cb_myButton);

	//---The button callback---------------------------
	void ImpressionistUI::cb_myButton(Fl_Widget* o, void* v)
	{
		ImpressionistUI* pUI=((ImpressionistUI*)(o->user_data()));
		ImpressionistDoc* pDoc = pUI->getDocument();
		pDoc->startPainting();
	}


//---------Light Button------------------------------------
	
	//---To install a light button---------------------
	Fl_Light_Button* myLightButton = new Fl_Light_Button(240,10,150,25,"&myLightButtonLabel");
	myLightButton->user_data((void*)(this));   // record self to be used by static callback functions
	myLightButton->callback(cb_myLightButton);

	//---The light button callback---------------------
	void ImpressionistUI::cb_myLightButton(Fl_Widget* o, void* v)
	{
		ImpressionistUI *pUI=((ImpressionistUI*)(o->user_data()));

		if (pUI->myBool==TRUE) pUI->myBool=FALSE;
		else pUI->myBool=TRUE;
	}

//----------Int Input--------------------------------------

    //---To install an int input-----------------------
	Fl_Int_Input* myInput = new Fl_Int_Input(200, 50, 5, 5, "&My Input");
	myInput->user_data((void*)(this));   // record self to be used by static callback functions
	myInput->callback(cb_myInput);

	//---The int input callback------------------------
	void ImpressionistUI::cb_myInput(Fl_Widget* o, void* v)
	{
		((ImpressionistUI*)(o->user_data()))->m_nMyInputValue=int( ((Fl_Int_Input *)o)->value() );
	}

//------------------------------------------------------------------------------------------------
*/

//------------------------------------- Help Functions --------------------------------------------

//------------------------------------------------------------
// This returns the UI, given the menu item.  It provides a
// link from the menu items to the UI
//------------------------------------------------------------
ImpressionistUI* ImpressionistUI::whoami(Fl_Menu_* o)	
{
	return ( (ImpressionistUI*)(o->parent()->user_data()) );
}


//--------------------------------- Callback Functions --------------------------------------------

//------------------------------------------------------------------
// Brings up a file chooser and then loads the chosen image
// This is called by the UI when the load image menu item is chosen
//------------------------------------------------------------------
void ImpressionistUI::cb_load_image(Fl_Menu_* o, void* v) 
{
	ImpressionistDoc *pDoc=whoami(o)->getDocument();

	char* newfile = fl_file_chooser("Open File?", "*.bmp", pDoc->getImageName() );
	if (newfile != NULL) {
		pDoc->loadImage(newfile);
	}
}

void ImpressionistUI::cb_dissolve(Fl_Menu_* o, void* v)
{
	ImpressionistDoc* pDoc = whoami(o)->getDocument();

	char* newfile = fl_file_chooser("Open File?", "*.bmp", pDoc->getImageName());
	if (newfile != NULL) {
		pDoc->dissolve(newfile);
	}
}


//------------------------------------------------------------------
// Brings up a file chooser and then saves the painted image
// This is called by the UI when the save image menu item is chosen
//------------------------------------------------------------------
void ImpressionistUI::cb_save_image(Fl_Menu_* o, void* v) 
{
	ImpressionistDoc *pDoc=whoami(o)->getDocument();

	char* newfile = fl_file_chooser("Save File?", "*.bmp", "save.bmp" );
	if (newfile != NULL) {
		pDoc->saveImage(newfile);
	}
}

//-------------------------------------------------------------
// Brings up the paint dialog
// This is called by the UI when the brushes menu item
// is chosen
//-------------------------------------------------------------
void ImpressionistUI::cb_brushes(Fl_Menu_* o, void* v) 
{
	whoami(o)->m_brushDialog->show();
}

//------------------------------------------------------------
// Clears the paintview canvas.
// Called by the UI when the clear canvas menu item is chosen
//------------------------------------------------------------
void ImpressionistUI::cb_clear_canvas(Fl_Menu_* o, void* v)
{
	ImpressionistDoc* pDoc=whoami(o)->getDocument();

	pDoc->clearCanvas();
}

void ImpressionistUI::cb_undo(Fl_Menu_* o, void* v)
{
	ImpressionistDoc* pDoc = whoami(o)->getDocument();

	pDoc->undo();
}

//------------------------------------------------------------
// Causes the Impressionist program to exit
// Called by the UI when the quit menu item is chosen
//------------------------------------------------------------
void ImpressionistUI::cb_exit(Fl_Menu_* o, void* v) 
{
	whoami(o)->m_mainWindow->hide();
	whoami(o)->m_brushDialog->hide();

}

//-----------------------------------------------------------
// Brings up an about dialog box
// Called by the UI when the about menu item is chosen
//-----------------------------------------------------------
void ImpressionistUI::cb_about(Fl_Menu_* o, void* v) 
{
	fl_message("Impressionist FLTK version for CS341, Spring 2002");
}

//------- UI should keep track of the current for all the controls for answering the query from Doc ---------
//-------------------------------------------------------------
// Sets the type of brush to use to the one chosen in the brush 
// choice.  
// Called by the UI when a brush is chosen in the brush choice
//-------------------------------------------------------------
void ImpressionistUI::cb_brushChoice(Fl_Widget* o, void* v)
{
	ImpressionistUI* pUI=((ImpressionistUI *)(o->user_data()));
	ImpressionistDoc* pDoc=pUI->getDocument();

	int type=(int)v;

	pDoc->setBrushType(type);
	if ((int)v != BRUSH_LINES)
	{
		pUI->m_BrushThicknessSlider->deactivate();
		pUI->m_BrushAngleSlider->deactivate();
	}
	if ((int)v == BRUSH_LINES)
	{
		pUI->m_BrushThicknessSlider->activate();
		pUI->m_BrushAngleSlider->activate();
	}
}

//------------------------------------------------------------
// Clears the paintview canvas.
// Called by the UI when the clear canvas button is pushed
//------------------------------------------------------------
void ImpressionistUI::cb_clear_canvas_button(Fl_Widget* o, void* v)
{
	ImpressionistDoc * pDoc = ((ImpressionistUI*)(o->user_data()))->getDocument();

	pDoc->clearCanvas();
}

//---------------------------------- per instance functions --------------------------------------

//------------------------------------------------
// Return the ImpressionistDoc used
//------------------------------------------------
ImpressionistDoc* ImpressionistUI::getDocument()
{
	return m_pDoc;
}

//------------------------------------------------
// Draw the main window
//------------------------------------------------
void ImpressionistUI::show() {
	m_mainWindow->show();
	m_paintView->show();
	m_origView->show();
}

//------------------------------------------------
// Change the paint and original window sizes to 
// w by h
//------------------------------------------------
void ImpressionistUI::resize_windows(int w, int h) {
	m_paintView->size(w,h);
	m_origView->size(w,h);
}

//------------------------------------------------ 
// Set the ImpressionistDoc used by the UI to 
// communicate with the brushes 
//------------------------------------------------
void ImpressionistUI::setDocument(ImpressionistDoc* doc)
{
	m_pDoc = doc;

	m_origView->m_pDoc = doc;
	m_paintView->m_pDoc = doc;
}

// Main menu definition
Fl_Menu_Item ImpressionistUI::menuitems[] = {
	{ "&File",		0, 0, 0, FL_SUBMENU },
		{ "&Load Image...",	FL_ALT + 'l', (Fl_Callback *)ImpressionistUI::cb_load_image },
		{ "&Dissolve Image...",	FL_ALT + 'n', (Fl_Callback *)ImpressionistUI::cb_dissolve },
		{ "&Save Image...",	FL_ALT + 's', (Fl_Callback *)ImpressionistUI::cb_save_image },
		{ "&Brushes...",	FL_ALT + 'b', (Fl_Callback *)ImpressionistUI::cb_brushes }, 
		{ "&Clear Canvas",	FL_ALT + 'c', (Fl_Callback *)ImpressionistUI::cb_clear_canvas },
		{ "&Undo",			FL_ALT + 'z', (Fl_Callback *)ImpressionistUI::cb_undo, 0, FL_MENU_DIVIDER },
		
		{ "&Quit",			FL_ALT + 'q', (Fl_Callback *)ImpressionistUI::cb_exit },
		{ 0 },

	{ "&Help",		0, 0, 0, FL_SUBMENU },
		{ "&About",	FL_ALT + 'a', (Fl_Callback *)ImpressionistUI::cb_about },
		{ 0 },

	{ 0 }
};

// Brush choice menu definition
Fl_Menu_Item ImpressionistUI::brushTypeMenu[NUM_BRUSH_TYPE+1] = {
  {"Points",			FL_ALT+'p', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_POINTS},
  {"Lines",				FL_ALT+'l', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_LINES},
  {"Circles",			FL_ALT+'c', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_CIRCLES},
  {"Scattered Points",	FL_ALT+'q', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_SCATTERED_POINTS},
  {"Scattered Lines",	FL_ALT+'m', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_SCATTERED_LINES},
  {"Scattered Circles",	FL_ALT+'d', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_SCATTERED_CIRCLES},
  {"Kernel",			FL_ALT+'k', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_KERNEL},
  {"Star",				FL_ALT+'s', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_STAR},
  {0}
};

Fl_Menu_Item ImpressionistUI::dirTypeMenu[NUM_DIR_TYPE+1] = {
	{"slider value",	FL_ALT+'1', (Fl_Callback *)ImpressionistUI::cb_dirChoice, (void *)DIR_SLIDER},
	{"right drag",		FL_ALT+'2', (Fl_Callback *)ImpressionistUI::cb_dirChoice, (void *)DIR_RIGHT_DRAG},
	{"cursor move",		FL_ALT+'3', (Fl_Callback *)ImpressionistUI::cb_dirChoice, (void *)DIR_CURSOR_MOVEMENT},
	{"image gradient",	FL_ALT+'4', (Fl_Callback *)ImpressionistUI::cb_dirChoice, (void *)DIR_IMG_GRAD},
	{0}
};

Fl_Menu_Item ImpressionistUI::kernelTypeMenu[NUM_KRN_TYPE + 1] = {
	{"Blur",		FL_ALT+'1', (Fl_Callback *)ImpressionistUI::cb_kernelChoice, (void *)KRN_AVG},
	{"Sharpen",		FL_ALT+'2', (Fl_Callback *)ImpressionistUI::cb_kernelChoice, (void *)KRN_SHARP},
	{0}
};


//----------------------------------------------------
// Constructor.  Creates all of the widgets.
// Add new widgets here
//----------------------------------------------------
ImpressionistUI::ImpressionistUI() :
	m_nSize(10),
	m_nThickness(1),
	m_nAngle(0),
	m_fAlpha(1.0f),
	m_eDirType(DIR_SLIDER),
	m_eKernelType(KRN_AVG),
	m_nRandomSpace(1),
	m_nRed(1),
	m_nGreen(1),
	m_nBlue(1)
{
	// Create the main window
	m_mainWindow = new Fl_Window(600, 300, "Impressionist");
		m_mainWindow->user_data((void*)(this));	// record self to be used by static callback functions
		// install menu bar
		m_menubar = new Fl_Menu_Bar(0, 0, 600, 25);
		m_menubar->menu(menuitems);

		// Create a group that will hold two sub windows inside the main
		// window
		Fl_Group* group = new Fl_Group(0, 25, 600, 275);

			// install paint view window
			m_paintView = new PaintView(300, 25, 300, 275, "This is the paint view");//0jon
			m_paintView->box(FL_DOWN_FRAME);

			// install original view window
			m_origView = new OriginalView(0, 25, 300, 275, "This is the orig view");//300jon
			m_origView->box(FL_DOWN_FRAME);
			m_origView->deactivate();

		group->end();
		Fl_Group::current()->resizable(group);
    m_mainWindow->end();

	// init values


	// brush dialog definition
	m_brushDialog = new Fl_Window(500, 325, "Brush Dialog");
		// Add a brush type choice to the dialog
		m_BrushTypeChoice = new Fl_Choice(50,10,150,25,"&Brush");
		m_BrushTypeChoice->user_data((void*)(this));	// record self to be used by static callback functions
		m_BrushTypeChoice->menu(brushTypeMenu);
		m_BrushTypeChoice->callback(cb_brushChoice);

		m_ClearCanvasButton = new Fl_Button(240,10,150,25,"&Clear Canvas");
		m_ClearCanvasButton->user_data((void*)(this));
		m_ClearCanvasButton->callback(cb_clear_canvas_button);


		// Add brush size slider to the dialog 
		m_BrushSizeSlider = new Fl_Value_Slider(10, 80, 300, 20, "Size");
		m_BrushSizeSlider->user_data((void*)(this));	// record self to be used by static callback functions
		m_BrushSizeSlider->type(FL_HOR_NICE_SLIDER);
        m_BrushSizeSlider->labelfont(FL_COURIER);
        m_BrushSizeSlider->labelsize(12);
		m_BrushSizeSlider->minimum(1);
		m_BrushSizeSlider->maximum(40);
		m_BrushSizeSlider->step(1);
		m_BrushSizeSlider->value(m_nSize);
		m_BrushSizeSlider->align(FL_ALIGN_RIGHT);
		m_BrushSizeSlider->callback(cb_sizeSlides);

		m_BrushThicknessSlider = new Fl_Value_Slider(10, 110, 300, 20, "Thickness");
		m_BrushThicknessSlider->user_data((void*)(this));	// record self to be used by static callback functions
		m_BrushThicknessSlider->type(FL_HOR_NICE_SLIDER);
        m_BrushThicknessSlider->labelfont(FL_COURIER);
        m_BrushThicknessSlider->labelsize(12);
		m_BrushThicknessSlider->minimum(1);
		m_BrushThicknessSlider->maximum(40);
		m_BrushThicknessSlider->step(1);
		m_BrushThicknessSlider->value(m_nThickness);
		m_BrushThicknessSlider->align(FL_ALIGN_RIGHT);
		m_BrushThicknessSlider->callback(cb_thicknessSlides);
		m_BrushThicknessSlider->deactivate();

		m_BrushAngleSlider = new Fl_Value_Slider(10, 140, 300, 20, "Angle");
		m_BrushAngleSlider->user_data((void*)(this));	// record self to be used by static callback functions
		m_BrushAngleSlider->type(FL_HOR_NICE_SLIDER);
        m_BrushAngleSlider->labelfont(FL_COURIER);
        m_BrushAngleSlider->labelsize(12);
		m_BrushAngleSlider->minimum(0);
		m_BrushAngleSlider->maximum(359);
		m_BrushAngleSlider->step(1);
		m_BrushAngleSlider->value(m_nAngle);
		m_BrushAngleSlider->align(FL_ALIGN_RIGHT);
		m_BrushAngleSlider->callback(cb_angleSlides);
		m_BrushAngleSlider->deactivate();

		m_BrushAlphaSlider = new Fl_Value_Slider(10, 170, 300, 20, "Alpha");
		m_BrushAlphaSlider->user_data((void*)(this));	// record self to be used by static callback functions
		m_BrushAlphaSlider->type(FL_HOR_NICE_SLIDER);
        m_BrushAlphaSlider->labelfont(FL_COURIER);
        m_BrushAlphaSlider->labelsize(12);
		m_BrushAlphaSlider->minimum(0);
		m_BrushAlphaSlider->maximum(1);
		m_BrushAlphaSlider->step(0.01);
		m_BrushAlphaSlider->value(m_fAlpha);
		m_BrushAlphaSlider->align(FL_ALIGN_RIGHT);
		m_BrushAlphaSlider->callback(cb_alphaSlides);
		
		m_RedSlider = new Fl_Value_Slider(10, 200, 300, 20, "Red");
		m_RedSlider->user_data((void*)(this));	// record self to be used by static callback functions
		m_RedSlider->type(FL_HOR_NICE_SLIDER);
		m_RedSlider->labelfont(FL_COURIER);
		m_RedSlider->labelsize(12);
		m_RedSlider->minimum(0);
		m_RedSlider->maximum(1);
		m_RedSlider->step(0.01);
		m_RedSlider->value(m_nRed);
		m_RedSlider->align(FL_ALIGN_RIGHT);
		m_RedSlider->callback(cb_RedSlides);

		m_GreenSlider = new Fl_Value_Slider(10, 230, 300, 20, "Green");
		m_GreenSlider->user_data((void*)(this));	// record self to be used by static callback functions
		m_GreenSlider->type(FL_HOR_NICE_SLIDER);
		m_GreenSlider->labelfont(FL_COURIER);
		m_GreenSlider->labelsize(12);
		m_GreenSlider->minimum(0);
		m_GreenSlider->maximum(1);
		m_GreenSlider->step(0.01);
		m_GreenSlider->value(m_nGreen);
		m_GreenSlider->align(FL_ALIGN_RIGHT);
		m_GreenSlider->callback(cb_GreenSlides);

		m_BlueSlider = new Fl_Value_Slider(10, 260, 300, 20, "Blue");
		m_BlueSlider->user_data((void*)(this));	// record self to be used by static callback functions
		m_BlueSlider->type(FL_HOR_NICE_SLIDER);
		m_BlueSlider->labelfont(FL_COURIER);
		m_BlueSlider->labelsize(12);
		m_BlueSlider->minimum(0);
		m_BlueSlider->maximum(1);
		m_BlueSlider->step(0.01);
		m_BlueSlider->value(m_nBlue);
		m_BlueSlider->align(FL_ALIGN_RIGHT);
		m_BlueSlider->callback(cb_BlueSlides);

		m_DirTypeChoice = new Fl_Choice(50,40,150,20,"Dir type");
		m_DirTypeChoice->user_data((void*)(this));	 // record self to be used by static callback functions
		m_DirTypeChoice->align(FL_ALIGN_RIGHT);
		m_DirTypeChoice->menu(dirTypeMenu);
		m_DirTypeChoice->callback(cb_dirChoice);
		
		m_KernelTypeChoice = new Fl_Choice(50,60,150,20,"Kernel type");
		m_KernelTypeChoice->user_data((void*)(this));	 // record self to be used by static callback functions
		m_KernelTypeChoice->align(FL_ALIGN_RIGHT);
		m_KernelTypeChoice->menu(kernelTypeMenu);
		m_KernelTypeChoice->callback(cb_kernelChoice);

		m_RandomSpaceSlider = new Fl_Value_Slider(10, 290, 200, 20, "Space");
		m_RandomSpaceSlider->user_data((void*)(this));	// record self to be used by static callback functions
		m_RandomSpaceSlider->type(FL_HOR_NICE_SLIDER);
        m_RandomSpaceSlider->labelfont(FL_COURIER);
        m_RandomSpaceSlider->labelsize(12);
		m_RandomSpaceSlider->minimum(1);
		m_RandomSpaceSlider->maximum(50);
		m_RandomSpaceSlider->step(1);
		m_RandomSpaceSlider->value(m_nRandomSpace);
		m_RandomSpaceSlider->align(FL_ALIGN_RIGHT);
		m_RandomSpaceSlider->callback(cb_randomSpaceSlides);

		m_RandomPaintButton = new Fl_Button(360,290,50,20,"Paint");
		m_RandomPaintButton->user_data((void*)(this));
		m_RandomPaintButton->callback(cb_randomPaintButton);


    m_brushDialog->end();	

}

void ImpressionistUI::cb_sizeSlides(Fl_Widget* o, void* v)
{
	((ImpressionistUI*)(o->user_data()))->setSize( ((Fl_Slider *)o)->value()) ;
}

void ImpressionistUI::cb_thicknessSlides(Fl_Widget* o, void* v)
{
	((ImpressionistUI*)(o->user_data()))->setThickness( ((Fl_Slider *)o)->value() ) ;
}

void ImpressionistUI::cb_angleSlides(Fl_Widget* o, void* v)
{
	if ( ((ImpressionistUI*)(o->user_data()))->getDirType() == DIR_SLIDER )
		((ImpressionistUI*)(o->user_data()))->setAngle( ((Fl_Slider *)o)->value() ) ;
}

void ImpressionistUI::cb_alphaSlides(Fl_Widget* o, void* v)
{
	((ImpressionistUI*)(o->user_data()))->setAlpha( ((Fl_Slider *)o)->value() ) ;
}

void ImpressionistUI::cb_RedSlides(Fl_Widget* o, void* v)
{
	((ImpressionistUI*)(o->user_data()))->setRed(((Fl_Slider*)o)->value());
}

void ImpressionistUI::cb_GreenSlides(Fl_Widget* o, void* v)
{
	((ImpressionistUI*)(o->user_data()))->setGreen(((Fl_Slider*)o)->value());
}

void ImpressionistUI::cb_BlueSlides(Fl_Widget* o, void* v)
{
	((ImpressionistUI*)(o->user_data()))->setBlue(((Fl_Slider*)o)->value());
}

void ImpressionistUI::cb_dirChoice(Fl_Widget* o, void* v)
{
	((ImpressionistUI *)(o->user_data()))->setDirType((int)v);
}

void ImpressionistUI::cb_kernelChoice(Fl_Widget* o, void* v)
{
	((ImpressionistUI *)(o->user_data()))->setKernelType((int)v);
}

void ImpressionistUI::cb_randomSpaceSlides(Fl_Widget* o, void* v)
{
	((ImpressionistUI *)(o->user_data()))->setRandomSpace( ((Fl_Slider *)o)->value() );
}

void ImpressionistUI::cb_randomPaintButton(Fl_Widget* o, void* v)
{
	((ImpressionistUI *)(o->user_data()))->m_paintView->randomDraw();
}

// geters 
int ImpressionistUI::getSize() { return m_nSize; }
int ImpressionistUI::getAngle() { return m_nAngle; }
int ImpressionistUI::getThickness() { return m_nThickness; }
float ImpressionistUI::getAlpha() { return m_fAlpha; }
int ImpressionistUI::getDirType() { return m_eDirType; }
int ImpressionistUI::getKernelType() { return m_eKernelType; }
int ImpressionistUI::getRandomSpace() { return m_nRandomSpace; }
float ImpressionistUI::getRed() { return m_nRed; }
float ImpressionistUI::getGreen() { return m_nGreen; }
float ImpressionistUI::getBlue() { return m_nBlue; }
// seters
void ImpressionistUI::setSize( int size )
{
	m_nSize=size;
	m_BrushSizeSlider->value(m_nSize);
}

void ImpressionistUI::setAngle(const int v) { m_nAngle = v; }
void ImpressionistUI::setThickness(const int v) { m_nThickness = v; }
void ImpressionistUI::setAlpha(const float v) { m_fAlpha = v; }
void ImpressionistUI::setDirType(const int v)
{ 
	m_eDirType = v;
	if (m_eDirType == DIR_RIGHT_DRAG)
	{
		m_BrushAngleSlider->deactivate();
	}
}
void ImpressionistUI::setKernelType(const int v) { m_eKernelType = v; }
void ImpressionistUI::setRandomSpace(const int v) { m_nRandomSpace = v; }
void ImpressionistUI::setRed(const float red) { m_nRed = red; }
void ImpressionistUI::setGreen(const float green) { m_nGreen = green; }
void ImpressionistUI::setBlue(const float blue) { m_nBlue = blue; }

