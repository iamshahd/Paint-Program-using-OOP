#include "ActionDrawClr.h"

#include "..\ApplicationManager.h"

#include "..\GUI\GUI.h"

ActionDrawClr::ActionDrawClr(ApplicationManager * pApp) :Action(pApp)
{}

//Execute the action
void ActionDrawClr::Execute()
{
	GUI* pGUI = pManager->GetGUI();
	pGUI->pWind->DrawImage("images\\Other\\ColorPalette.jpg", ITM_DRAW_CLR * UI.MenuItemWidth, UI.ToolBarHeight, 108, 89); //draws an image at (x, y).  The width and height parameters can be used to scale the image.
	pGUI->PrintMessage("Pick color from palette");
	int x, y;
	pGUI->pWind->WaitMouseClick(x, y);	//Get the coordinates of the user click
	pGUI->LastClickedPoint.x = x;
	pGUI->LastClickedPoint.y = y;
	if (x >= ITM_DRAW_CLR * UI.MenuItemWidth && x <= ITM_DRAW_CLR * UI.MenuItemWidth + 108 && y >= UI.ToolBarHeight && y <= UI.ToolBarHeight + 89)
	{		
		int countsel = 0;
		int fignum = pManager->FigCount;
		for (int i = 0; i < fignum; i++)
		{
			if (pManager->FigList[i]->IsSelected())
			{
				color setselpencolor = pGUI->pWind->GetColor(x, y); //returns the color of the pixel at location (x, y) as a color type
				pGUI->PrintMessage("Color selected");
				color getselpencolor = pGUI->getCrntDrawColor();
				pManager->FigList[i]->ChngDrawClr(setselpencolor);
				pGUI->PrintMessage("Color changed");
				countsel++;
			}
		}
		if (countsel == 0)
		{
			color setpencolor = pGUI->pWind->GetColor(x, y); //returns the color of the pixel at location (x, y) as a color type
			pGUI->PrintMessage("Color selected");
			color getpencolor = pGUI->getCrntDrawColor();
			pGUI->setDrawColor(setpencolor); //sets the color and size(default is 1) of current pen (used when drawing in the FRAME style, as well as the border when drawing in the FILLED style) and returns the color of the old pen
			pGUI->PrintMessage("Pen color set");
		}
		pManager->DeselectAllFigures();
		pManager->SetGraphSaved(false);
	}
}
