#include "ActionAddSquare.h"
#include "..\Figures\CSquare.h"

#include "..\ApplicationManager.h"

#include "..\GUI\GUI.h"

ActionAddSquare::ActionAddSquare(ApplicationManager * pApp) :Action(pApp)
{}

//Execute the action
void ActionAddSquare::Execute()
{
	Point P1, P2;

	//Get a Pointer to the Interface
	GUI* pGUI = pManager->GetGUI();


	GfxInfo SqrGfxInfo;
	SqrGfxInfo.isFilled = false;	//default is not filled
	if (pGUI->ischngfillclr == 1)
	{
		SqrGfxInfo.isFilled = true;
	}
	//get drawing, filling colors and pen width from the interface
	SqrGfxInfo.DrawClr = pGUI->getCrntDrawColor();
	SqrGfxInfo.FillClr = pGUI->getCrntFillColor();
	SqrGfxInfo.BorderWdth = pGUI->getCrntPenWidth();


	//Step 1 - Read Square data from the user

	pGUI->PrintMessage("New Square: Click at first point");
	//Read 1st point and store in point P1
	pGUI->GetPointClicked(P1.x, P1.y);

	if ((P1.y <= UI.ToolBarHeight) || (P1.y >= (UI.height - UI.StatusBarHeight))) {
		pGUI->PrintMessage("Please select a point inside the drawing area.");
	}

	else if ((P1.y > UI.ToolBarHeight) && (P1.y < (UI.height - UI.StatusBarHeight))) {

		pGUI->PrintMessage("New Square: Click at second point");
		//Read 2nd point and store in point P2
		pGUI->GetPointClicked(P2.x, P2.y);

		if ((P2.y <= UI.ToolBarHeight) || (P2.y >= (UI.height - UI.StatusBarHeight))) {
			pGUI->PrintMessage("Please select a point inside the drawing area.");
		}

		else if ((P2.y > UI.ToolBarHeight) && (P2.y < (UI.height - UI.StatusBarHeight))) {
			pManager->SetGraphSaved(false);

			pGUI->ClearStatusBar();


			//Step 2 - prepare square data
			//User has entered two points P1&P2
			//2.1- Identify the Top left corner of the square
			Point topLeft;
			topLeft.x = P1.x < P2.x ? P1.x : P2.x;
			topLeft.y = P1.y < P2.y ? P1.y : P2.y;

			//2.2- Calcuate square side legnth
			//The square side length would be the longer distance between the two points coordinates
			int SideLength = max(abs(P1.x - P2.x), abs(P1.y - P2.y));


			//Step 3 - Create a Square with the parameters read from the user
			CSquare *R = new CSquare(topLeft, SideLength, SqrGfxInfo);

			//Step 4 - Make sure square is inside borders
			if (R->IsFigInsideBorders(0, UI.width, UI.ToolBarHeight, UI.height - UI.StatusBarHeight))
			{
				//Add Square to the list of figures
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