#include "ActionFillClr.h"

#include "..\ApplicationManager.h"

#include "..\GUI\GUI.h"

ActionFillClr::ActionFillClr(ApplicationManager * pApp) :Action(pApp)
{}

//Execute the action
void ActionFillClr::Execute()
{
	GUI* pGUI = pManager->GetGUI();
	pGUI->pWind->DrawImage("images\\Other\\ColorPalette.jpg", ITM_FILL_CLR * UI.MenuItemWidth, UI.ToolBarHeight, 108, 89); //draws an image at (x, y).  The width and height parameters can be used to scale the image.
	pGUI->PrintMessage("Pick color from palette");
	int x, y;
	pGUI->pWind->WaitMouseClick(x, y);	//Get the coordinates of the user click
	pGUI->LastClickedPoint.x = x;
	pGUI->LastClickedPoint.y = y;
	if (x >= ITM_FILL_CLR * UI.MenuItemWidth && x <= ITM_FILL_CLR * UI.MenuItemWidth + 108 && y >= UI.ToolBarHeight && y <= UI.ToolBarHeight + 89)
	{
		pManager->SetGraphSaved(false);
		int countsel = 0;
		int fignum = pManager->FigCount;
		for (int i = 0; i < fignum; i++)
		{
			bool sel = pManager->FigList[i]->IsSelected();
			if (sel == 1)
			{
				color setselfillcolor = pGUI->pWind->GetColor(x, y); //returns the color of the pixel at location (x, y) as a color type
				pGUI->PrintMessage("Color selected");
				color getselfillcolor = pGUI->getCrntFillColor();
				pManager->FigList[i]->ChngFillClr(setselfillcolor);
				pGUI->PrintMessage("Color changed");
				countsel++;
			}
		}
		if (countsel == 0)
		{
			color setfillcolor = pGUI->pWind->GetColor(x, y); //returns the color of the pixel at location (x, y) as a color type
			pGUI->PrintMessage("Color selected");
			pGUI->ischngfillclr = 1;
			color getfillcolor = pGUI->getCrntFillColor();
			pGUI->setFillColor(setfillcolor); //sets the color of the current brush (used when drawing in the FILLED style) and returns the color of the old brush
			pGUI->PrintMessage("Brush set");
		}
		pManager->DeselectAllFigures();

	}
}