#include "ActionAddElps.h"
#include "..\Figures\CEllipse.h"

#include "..\ApplicationManager.h"

#include "..\GUI\GUI.h"

ActionAddElps::ActionAddElps(ApplicationManager * pApp) :Action(pApp)
{}

//Execute the action

void ActionAddElps::Execute()
{
	Point P1, P2;

	//Get a Pointer to the Interface
	GUI* pGUI = pManager->GetGUI();


	GfxInfo EllipseGfxInfo;
	EllipseGfxInfo.isFilled = false;	//default is not filled
	if (pGUI->ischngfillclr == 1)
	{
		EllipseGfxInfo.isFilled = true;
	}
	//get drawing, filling colors and pen width from the interface
	EllipseGfxInfo.DrawClr = pGUI->getCrntDrawColor();
	EllipseGfxInfo.FillClr = pGUI->getCrntFillColor();
	EllipseGfxInfo.BorderWdth = pGUI->getCrntPenWidth();


	//Step 1 - Read Ellipse data from the user

	pGUI->PrintMessage("New Ellipse: Click at first point");
	//Read 1st point and store in point P1
	pGUI->GetPointClicked(P1.x, P1.y);

	if ((P1.y <= UI.ToolBarHeight) || (P1.y >= (UI.height - UI.StatusBarHeight))) {
		pGUI->PrintMessage("Please select a point inside the drawing area.");
	}

	else if ((P1.y > UI.ToolBarHeight) && (P1.y < (UI.height - UI.StatusBarHeight))) {

		pGUI->PrintMessage("New Ellipse: Click at second point");
		//Read 2nd point and store in point P2
		pGUI->GetPointClicked(P2.x, P2.y);

		if ((P2.y <= UI.ToolBarHeight) || (P2.y >= (UI.height - UI.StatusBarHeight))) {
			pGUI->PrintMessage("Please select a point inside the drawing area.");
		}

		else if ((P2.y > UI.ToolBarHeight) && (P2.y < (UI.height - UI.StatusBarHeight))) {

			
			pGUI->ClearStatusBar();


			//Step 3 - Create a Ellipse with the parameters read from the user
			CEllipse *R = new CEllipse(P1, P2, EllipseGfxInfo);

			//Step 4 - Make sure ellipse is inside Drawing Area borders
			if (R->IsFigInsideBorders(0, UI.width, UI.ToolBarHeight, UI.height - UI.StatusBarHeight))
			{
				// Add the Ellipse to the list of figures
				pManager->AddFigure(R);
				pManager->SetGraphSaved(false);
			}
			else {
				delete R;
				R = NULL;
				pGUI->PrintMessage("Figure cannot extend beyond Drawing Area.");
			}
		}
	}
}