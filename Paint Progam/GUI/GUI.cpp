#include "GUI.h"   
#include <math.h> 
#include "..\Figures\CHexagon.h"
#include "..\Figures\CFigure.h"

//constructor make necessary initializations
GUI::GUI()
{
	//Initialize user interface parameters
	UI.InterfaceMode = MODE_DRAW;
	
	UI.width = 1250;
	UI.height = 650;
	UI.wx = 5;
	UI.wy =5;

	
	UI.StatusBarHeight = 50;
	UI.ToolBarHeight = 50;
	UI.MenuItemWidth = 50;
	
	UI.DrawColor = BLUE;	//Drawing color
	UI.FillColor = GREEN;	//Filling color
	UI.MsgColor = RED;		//Messages color
	UI.BkGrndColor = LIGHTGOLDENRODYELLOW;	//Background color
	UI.HighlightColor = MAGENTA;	//This color should NOT be used to draw figures. use if for highlight only
	UI.StatusBarColor = LIGHTSALMON;
	UI.PenWidth = 3;	//width of the figures frames

	
	//Create the output window
	pWind = CreateWind(UI.width, UI.height, UI.wx, UI.wy);
	//Change the title
	pWind->ChangeTitle("Paint for Kids - Programming Techniques Project");
	
	CreateDrawToolBar();
	CreateStatusBar();
}


//======================================================================================//
//								Input Functions										    //
//======================================================================================//


void GUI::GetPointClicked(int &x, int &y) const
{
	pWind->WaitMouseClick(x, y);	//Wait for mouse click
}

string GUI::GetString() const 
{
	string Label;
	char Key;
	while(1)
	{
		pWind->WaitKeyPress(Key);
		if(Key == 27 )	//ESCAPE key is pressed
			return "";	//returns nothing as user has cancelled label
		if(Key == 13 )	//ENTER key is pressed
			return Label;
		if(Key == 8 )	//BackSpace is pressed
			Label.resize(Label.size() -1 );			
		else {
			Label += Key;
			PrintMessage(Label);
		}
		PrintMessage(Label);
	}
}

//void GUI::MapHoverToToolTips(){
//	int x, y;
//	pWind->GetMouseCoord(x, y);
//	if (UI.InterfaceMode == MODE_DRAW)	//GUI in the DRAW mode
//	{
//		if (y >= 0 && y < UI.ToolBarHeight)
//		{
//			int ClickedItemOrder = (x / UI.MenuItemWidth);
//			switch (ClickedItemOrder)
//			{
//			case ITM_SQUR:
//				pWind->DrawImage("images\\Tooltips\\square.jpg", (1 / 3)*UI.MenuItemWidth*ITM_SQUR, UI.ToolBarHeight, 84, 27);
//				break;
//			}
//			/*case ITM_ELPS:
//			case ITM_HEXA:
//			case ITM_DRAW_CLR:
//			case ITM_FILL_CLR:
//			case ITM_BK_CLR:
//			case ITM_DELETE:
//			case ITM_RESIZE:
//			case ITM_BACK:
//			case ITM_FRONT:
//			case ITM_LOAD:
//			case ITM_SAVE:
//			case ITM_PLAY:
//			case ITM_EXIT:
//			case ITM_MOVE:
//			case ITM_UNDO:
//			case ITM_REDO:
//			case ITM_NEW:*/
//
//			//default: return EMPTY;	//A click on empty place in desgin toolbar
//		}
//	}
//	}

//This function reads the position where the user clicks to determine the desired action
ActionType GUI::MapInputToActionType() 
{	
	int x,y;
	pWind->WaitMouseClick(x, y);	//Get the coordinates of the user click
	
	this->LastClickedPoint.x = x;
	this->LastClickedPoint.y = y;
	

	if(UI.InterfaceMode == MODE_DRAW)	//GUI in the DRAW mode
	{
		//[1] If user clicks on the Toolbar
		if ( y >= 0 && y < UI.ToolBarHeight)
		{	
			//Check whick Menu item was clicked
			//==> This assumes that menu items are lined up horizontally <==
			int ClickedItemOrder = (x / UI.MenuItemWidth);
			//Divide x coord of the point clicked by the menu item width (int division)
			//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

			switch (ClickedItemOrder)
			{
			case ITM_SQUR: return DRAW_SQUARE;
			case ITM_ELPS: return DRAW_ELPS;
			case ITM_HEXA: return DRAW_HEX;
			case ITM_DRAW_CLR: return CHNG_DRAW_CLR;
			case ITM_FILL_CLR: return CHNG_FILL_CLR;
			case ITM_BK_CLR: return CHNG_BK_CLR;
			case ITM_DELETE: return DEL;
			case ITM_RESIZE: return RESIZE;
			case ITM_BACK: return SEND_BACK;
			case ITM_FRONT: return BRNG_FRNT;
			case ITM_LOAD: return LOAD;
			case ITM_SAVE: return SAVE;
			case ITM_PLAY: return TO_PLAY;
			case ITM_EXIT: return EXIT;	
			case ITM_MOVE: return MOVE;
			case ITM_UNDO: return UNDO;
			case ITM_REDO: return REDO;
			case ITM_NEW: return NEW;
			case ITM_HELP: return HELP;
			case ITM_INFO: return INFO;

			default: return EMPTY;	//A click on empty place in desgin toolbar
			}
		}

		//[2] User clicks on the drawing area
		if ( y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
		{
			return DRAWING_AREA;	
		}
		
		//[3] User clicks on the status bar
		return STATUS;
	}
	else	//GUI is in PLAY mode
	{
		///TODO:
		//perform checks similar to Draw mode checks above
		//and return the correspoding action
		//return TO_PLAY;	//just for now. This should be updated
		//[1] If user clicks on the Toolbar
		if (y >= 0 && y < UI.ToolBarHeight)
		{
			//Check whick Menu item was clicked
			//==> This assumes that menu items are lined up horizontally <==
			int ClickedItemOrder = (x / UI.MenuItemWidth);
			//Divide x coord of the point clicked by the menu item width (int division)
			//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

			switch (ClickedItemOrder)
			{
			case ITM_FIG_TYPE: return FIG_TYPE;
			case ITM_FIG_FILL: return FIG_FILL;
			case ITM_FIG_TYPE_FILL: return FIG_TYPE_FILL;
			case ITM_RESTART: return RESTART;
			case ITM_DRAW: return TO_DRAW;
			case ITM_HELP_PLAY: return HELP;
			case ITM_INFO_PLAY: return INFO;

			default: return EMPTY;	//A click on empty place in desgin toolbar
			}
		}

		//[2] User clicks on the drawing area
		if (y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
		{
			return PLAYING_AREA;
		}

		//[3] User clicks on the status bar
		return STATUS;
	}	

}
//======================================================================================//
//								Output Functions										//
//======================================================================================//

window* GUI::CreateWind(int w, int h, int x, int y) const
{ 
	window* pW = new window(w, h, x, y);
	pW->SetBrush(UI.BkGrndColor);
	pW->SetPen(UI.BkGrndColor, 1);
	pW->DrawRectangle(0, UI.ToolBarHeight, w, h);	
	return pW;
}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::CreateStatusBar() const
{
	pWind->SetPen(UI.StatusBarColor, 1);
	pWind->SetBrush(UI.StatusBarColor);
	pWind->DrawRectangle(0, UI.height - UI.StatusBarHeight, UI.width, UI.height);
}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::ClearStatusBar() const
{
	//Clear Status bar by drawing a filled white Square
	pWind->SetPen(UI.StatusBarColor, 1);
	pWind->SetBrush(UI.StatusBarColor);
	pWind->DrawRectangle(0, UI.height - UI.StatusBarHeight, UI.width, UI.height);
}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::CreateDrawToolBar()
{
	UI.InterfaceMode = MODE_DRAW;

	//You can draw the tool bar icons in any way you want.
	//Below is one possible way
	
	UI.InterfaceMode = MODE_DRAW;
	color currentfill = UI.FillColor;
	color currentpen = UI.DrawColor;
	pWind->SetBrush(WHITE);
	pWind->SetPen(WHITE);
	pWind->DrawRectangle(0, 0, UI.width, UI.ToolBarHeight);
	pWind->SetBrush(currentfill);
	pWind->SetPen(currentpen);

	//First prepare List of images for each menu item
	//To control the order of these images in the menu, 
	//reoder them in UI_Info.h ==> enum DrawMenuItem
	string MenuItemImages[DRAW_ITM_COUNT];
	MenuItemImages[ITM_SQUR] = "images\\MenuItems\\Menu_Sqr.jpg";
	MenuItemImages[ITM_ELPS] = "images\\MenuItems\\Menu_Elps.jpg";
	MenuItemImages[ITM_HEXA] = "images\\MenuItems\\Menu_Hexa.jpg";
	MenuItemImages[ITM_DRAW_CLR] = "images\\MenuItems\\Menu_Drawclr.jpg";
	MenuItemImages[ITM_FILL_CLR] = "images\\MenuItems\\Menu_Fillclr.jpg";
	MenuItemImages[ITM_BK_CLR] = "images\\MenuItems\\Menu_Bkclr.jpg";
	MenuItemImages[ITM_DELETE] = "images\\MenuItems\\Menu_Del.jpg";
	MenuItemImages[ITM_RESIZE] = "images\\MenuItems\\Menu_Resize.jpg";
	MenuItemImages[ITM_BACK] = "images\\MenuItems\\Menu_Back.jpg";
	MenuItemImages[ITM_FRONT] = "images\\MenuItems\\Menu_Front.jpg";
	MenuItemImages[ITM_LOAD] = "images\\MenuItems\\Menu_Load.jpg";
	MenuItemImages[ITM_SAVE] = "images\\MenuItems\\Menu_Save.jpg";
	MenuItemImages[ITM_PLAY] = "images\\MenuItems\\Menu_Play.jpg";
	MenuItemImages[ITM_EXIT] = "images\\MenuItems\\Menu_Exit.jpg";
	MenuItemImages[ITM_UNDO] = "images\\MenuItems\\Menu_Undo.jpg";
	MenuItemImages[ITM_REDO] = "images\\MenuItems\\Menu_Redo.jpg";
	MenuItemImages[ITM_MOVE] = "images\\MenuItems\\Menu_Move.jpg";
	MenuItemImages[ITM_NEW] = "images\\MenuItems\\Menu_New.jpg";
	MenuItemImages[ITM_HELP] = "images\\MenuItems\\Menu_Help.jpg";
	MenuItemImages[ITM_INFO] = "images\\MenuItems\\Menu_Info.jpg";

	//TODO: Prepare images for each menu item and add it to the list

	//Draw menu item one image at a time
	for(int i=0; i<DRAW_ITM_COUNT; i++)
		pWind->DrawImage(MenuItemImages[i], i*UI.MenuItemWidth,0,UI.MenuItemWidth, UI.ToolBarHeight);



	//Draw a line under the toolbar
	pWind->SetPen(RED, 3);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);	

}
//////////////////////////////////////////////////////////////////////////////////////////

void GUI::CreatePlayToolBar() const
{
	UI.InterfaceMode = MODE_PLAY;
	color currentfill = UI.FillColor;
	color currentpen = UI.DrawColor;
	pWind->SetBrush(WHITE);
	pWind->SetPen(WHITE);
	pWind->DrawRectangle(0, 0, UI.width, UI.ToolBarHeight);
	pWind->SetBrush(currentfill);
	pWind->SetPen(currentpen);

	///TODO: write code to create Play mode menu
	string MenuItemImages[PLAY_ITM_COUNT];
	MenuItemImages[ITM_FIG_TYPE] = "images\\MenuItems\\Menu_Fig_Type.jpg";
	MenuItemImages[ITM_FIG_FILL] = "images\\MenuItems\\Menu_Fig_Fill.jpg";
	MenuItemImages[ITM_FIG_TYPE_FILL] = "images\\MenuItems\\Menu_Fig_Type_Fill.jpg";
	MenuItemImages[ITM_RESTART] = "images\\MenuItems\\Menu_Restart.jpg";
	MenuItemImages[ITM_DRAW] = "images\\MenuItems\\Menu_Draw2.jpg";
	MenuItemImages[ITM_HELP_PLAY]= "images\\MenuItems\\Menu_Help.jpg";
	MenuItemImages[ITM_INFO_PLAY] = "images\\MenuItems\\Menu_Info.jpg";
	//Draw menu item one image at a time
	for (int i = 0; i<PLAY_ITM_COUNT; i++)
		pWind->DrawImage(MenuItemImages[i], i*UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);



	//Draw a line under the toolbar
	pWind->SetPen(RED, 3);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);

}
//////////////////////////////////////////////////////////////////////////////////////////

void GUI::ClearDrawArea() const
{
	pWind->SetPen(UI.BkGrndColor, 1);
	pWind->SetBrush(UI.BkGrndColor);
	pWind->DrawRectangle(0, UI.ToolBarHeight + 2, UI.width, UI.height - UI.StatusBarHeight);
	//pWind->DrawRectangle(0, UI.ToolBarHeight, UI.width, UI.height - UI.StatusBarHeight);
	
}
//////////////////////////////////////////////////////////////////////////////////////////

void GUI::PrintMessage(string msg) const	//Prints a message on status bar
{
	ClearStatusBar();	//First clear the status bar
	
	pWind->SetPen(UI.MsgColor, 50);
	pWind->SetFont(20, BOLD , BY_NAME, "Arial");   
	pWind->DrawString(10, UI.height - (int)(UI.StatusBarHeight/1.5), msg);
}
//////////////////////////////////////////////////////////////////////////////////////////

color GUI::getCrntDrawColor() const	//get current drawing color
{	return UI.DrawColor;	}
//////////////////////////////////////////////////////////////////////////////////////////

color GUI::getCrntFillColor() const	//get current filling color
{	return UI.FillColor;	}
//////////////////////////////////////////////////////////////////////////////////////////

color GUI::getCrntBkGrndColor() const	//get current background color
{
	return UI.BkGrndColor;
}
//////////////////////////////////////////////////////////////////////////////////////////

int GUI::getCrntPenWidth() const		//get current pen width
{	return UI.PenWidth;	}
//////////////////////////////////////////////////////////////////////////////////////////

void GUI::setDrawColor(color newColor) const	//get current drawing color
{
	UI.DrawColor = newColor;
}
//////////////////////////////////////////////////////////////////////////////////////////

void GUI::setFillColor(color newColor) const	//get current filling color
{
	UI.FillColor = newColor;
}
//////////////////////////////////////////////////////////////////////////////////////////

void GUI::setBkGrndColor(color newColor) const	//get current background color
{
	UI.BkGrndColor = newColor;
}
//////////////////////////////////////////////////////////////////////////////////////////
//======================================================================================//
//								Figures Drawing Functions								//
//======================================================================================//



void GUI::DrawEllipse(Point P1, Point P2, GfxInfo EllipseGfxInfo, bool selected) const
{
	color DrawingClr;
	if (selected)
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else
		DrawingClr = EllipseGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, EllipseGfxInfo.BorderWdth);	//Set Drawing color & width

	drawstyle style;
	if (EllipseGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(EllipseGfxInfo.FillClr);
	}
	else
		style = FRAME;


	pWind->DrawEllipse(P1.x, P1.y, P2.x, P2.y, style);
	//(const int iX1, const int iY1, const int iX2, const int iY2, const drawstyle dsStyle, const int iWidth, const int iHeight)
}


//////////////////////////////////////////////////////////////////////////////////////////


void GUI::DrawSquare(Point P1, Point P2, GfxInfo RectGfxInfo, bool selected) const
{
	color DrawingClr;
	if(selected)	
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else			
		DrawingClr = RectGfxInfo.DrawClr;
	
	pWind->SetPen(DrawingClr, RectGfxInfo.BorderWdth);	//Set Drawing color & width

	drawstyle style;
	if (RectGfxInfo.isFilled)
	{
		style = FILLED;		
		pWind->SetBrush(RectGfxInfo.FillClr);
	}
	else	
		style = FRAME;

	
	pWind->DrawRectangle(P1.x, P1.y, P2.x, P2.y, style);
	//(const int iX1, const int iY1, const int iX2, const int iY2, const drawstyle dsStyle, const int iWidth, const int iHeight)
}

void GUI::DrawHex(int* ppts6x, int* ppts6y, GfxInfo HexGfxInfo, bool selected) const
{
 	color DrawingClr;
	if (selected)
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else
		DrawingClr = HexGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, HexGfxInfo.BorderWdth);	//Set Drawing color & width

	drawstyle style;
	if (HexGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(HexGfxInfo.FillClr);
	}
	else
		style = FRAME;

	
	const int iVertices = 6;
	
	pWind->DrawPolygon(ppts6x, ppts6y, iVertices, style);
	//(const int* ipX, const int* ipY, const int iVertices, const drawstyle dsStyle) 
}



//////////////////////////////////////////////////////////////////////////////////////////
GUI::~GUI()
{
	delete pWind;
}

