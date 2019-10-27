#ifndef GUI_H
#define GUI_H

#include "..\DEFS.h"
#include "UI_Info.h" 
#include "..\CMUgraphicsLib\CMUgraphics.h"


//This class is responsible for Grphical User Interface handling
//All user input and program outputs MUST be done through this class
//No other class is allowed to perform direct i/o
class GUI	
{
public:	
	window* pWind;	//Pointer to the Graphics Window
	Point LastClickedPoint;

public:
	GUI();	
	~GUI();	
	window* CreateWind(int, int, int , int) const; //creates the application window

	/////////// Input Functoinality  /////////////////
	void GetPointClicked(int &x, int &y) const;//Get coordinate where user clicks
	string GetString() const ;	 //Returns a string entered by the user
	ActionType MapInputToActionType(); //Read the user click and map to an action
	//void MapHoverToToolTips(); //Read the mouse hover and shows a label for the buttons

	/////////// Output Functoinality  ////////////////
	void CreateDrawToolBar();	//creates Draw mode toolbar & menu
	void CreatePlayToolBar() const;	//creates Play mode toolbar & menu
	void CreateStatusBar() const;	//create the status bar

	void ClearStatusBar() const;	//Clears the status bar
	void ClearDrawArea() const;	//Clears the drawing area
	
	// -- Figures Drawing functions
	void DrawSquare(Point P1, Point P2, GfxInfo RectGfxInfo, bool selected=false) const;  //Draw a Square
	void DrawEllipse(Point P1, Point P2, GfxInfo EllipseGfxInfo, bool selected = false) const;  //Draw an Ellipse
	void DrawHex(int* ppts6x, int* ppts6y, GfxInfo HexGfxInfo, bool selected = false) const;
	
	///TODO: Make similar functions for drawing all other figures.
	
	void PrintMessage(string msg) const;	//Print a message on Status bar

	color getCrntDrawColor() const;	//get current drwawing color
	color getCrntFillColor() const;	//get current filling color
	color GUI::getCrntBkGrndColor() const; //get current background color
	int getCrntPenWidth() const;		//get current pen width
	void setDrawColor(color newColor) const;	//set current drwawing color
	void setFillColor(color newColor) const;	//set current filling color
	void GUI::setBkGrndColor(color newColor) const; //set current background color
	bool ischngfillclr;
};


#endif