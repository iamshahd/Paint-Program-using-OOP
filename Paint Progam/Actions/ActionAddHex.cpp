#include "ActionAddHex.h"
#include "..\Figures\CHexagon.h"
#include <cmath>

#include "..\ApplicationManager.h"

#include "..\GUI\GUI.h"



ActionAddHex::ActionAddHex(ApplicationManager * pApp) :Action(pApp)
{}

//Execute the action
void ActionAddHex::Execute()
{
	//GUI* pGUI = pManager->GetGUI();
	//pGUI->PrintMessage("You want to draw a hexagon.");

	Point P1, P2;

	//Get a Pointer to the Interface
	GUI* pGUI = pManager->GetGUI();


	GfxInfo HexGfxInfo;
	HexGfxInfo.isFilled = false;	//default is not filled
	if (pGUI->ischngfillclr == 1)
	{
		HexGfxInfo.isFilled = true;
	}
	//get drawing, filling colors and pen width from the interface
	HexGfxInfo.DrawClr = pGUI->getCrntDrawColor();
	HexGfxInfo.FillClr = pGUI->getCrntFillColor();
	HexGfxInfo.BorderWdth = pGUI->getCrntPenWidth();


	//Step 1 - Read data from the user

	pGUI->PrintMessage("New Hexagon: Choose hexagon center");
	//Read 1st point and store in point P1
	pGUI->GetPointClicked(P1.x, P1.y);

	if ((P1.y <= UI.ToolBarHeight) || (P1.y >= (UI.height - UI.StatusBarHeight))) {
		pGUI->PrintMessage("Please select a point inside the drawing area.");
	}

	else if ((P1.y > UI.ToolBarHeight) && (P1.y < (UI.height - UI.StatusBarHeight))) {

		pGUI->PrintMessage("New Hexagon: Click at the second point");
		//Read 2nd point and store in point P2
		pGUI->GetPointClicked(P2.x, P2.y);

		if ((P2.y <= UI.ToolBarHeight) || (P2.y >= (UI.height - UI.StatusBarHeight))) {
			pGUI->PrintMessage("Please select a point inside the drawing area.");
		}

		else if ((P2.y > UI.ToolBarHeight) && (P2.y < (UI.height - UI.StatusBarHeight))) {

			pManager->SetGraphSaved(false);

			pGUI->ClearStatusBar();


			//Step 3 - Create a Hexagon with the parameters read from the user
			CHexagon *R = new CHexagon(P1, P2, HexGfxInfo);

			//Step 4 - Make sure hexagon is inside Drawing Area borders
			if (R->IsFigInsideBorders(0, UI.width, UI.ToolBarHeight, UI.height - UI.StatusBarHeight))
			{
				// Add the hexagon to the list of figures
				pManager->AddFigure(R);
			}
			else {
				delete R;
				R = NULL;
				pGUI->PrintMessage("Figure cannot extend beyond Drawing Area.");
			}

		}
	}
}