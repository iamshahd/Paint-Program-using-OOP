#ifndef UI_INFO_H
#define UI_INFO_H

#include "..\CMUgraphicsLib\CMUgraphics.h"

//User Interface information file.
//This file contains info that is needed by Input and Output classes to
//handle the user interface

enum GUI_MODE	//Graphical user interface mode
{
	MODE_DRAW,	//Drawing mode (startup mode)
	MODE_PLAY	//Playing mode
};

enum DrawMenuItem //The items of the Draw menu (you should add more items)
{
	//Note: Items are ordered here as they appear in menu
	//If you want to change the menu items order, change the order here
	ITM_NEW,
	ITM_SQUR,
	ITM_ELPS,
	ITM_HEXA,
	ITM_DRAW_CLR,
	ITM_FILL_CLR,
	ITM_BK_CLR,
	ITM_BACK,
	ITM_FRONT,
	ITM_MOVE,
	ITM_RESIZE,
	ITM_UNDO,
	ITM_REDO,
	ITM_DELETE,
	ITM_LOAD,
	ITM_SAVE,
	ITM_PLAY,
	ITM_HELP,
	ITM_INFO,
	ITM_EXIT,

	DRAW_ITM_COUNT
	
};

enum PlayMenuItem //The items of the Play menu (you should add more items)
{
	//Note: Items are ordered here as they appear in menu
	//If you want to change the menu items order, change the order here

	//TODO: Add more items names here
	ITM_FIG_TYPE,
	ITM_FIG_FILL,
	ITM_FIG_TYPE_FILL,
	ITM_RESTART,
	ITM_DRAW,
	ITM_HELP_PLAY,
	ITM_INFO_PLAY,

	PLAY_ITM_COUNT		//no. of menu items ==> This should be the last line in this enum

};





__declspec(selectany) //This line to prevent "redefinition error"

struct UI_Info	//User Interface Info.
{
	GUI_MODE InterfaceMode;
	
	int	width, height,	//Window width and height
		wx , wy,			//Window starting coordinates
		StatusBarHeight,	//Status Bar Height
		ToolBarHeight,		//Tool Bar Height (distance from top of window to bottom line of toolbar)
		MenuItemWidth;		//Width of each item in toolbar menu
	

	color DrawColor;		//Drawing color
	color FillColor;		//Filling color
	color HighlightColor;	//Highlighting color
	color MsgColor;			//Messages color
	color BkGrndColor;		//Background color
	color StatusBarColor;	//Status bar color
	int PenWidth;			//width of the pen that draws shapes

	/// Add more members if needed
	
}UI;	//create a global object UI

#endif