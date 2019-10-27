#include "ActionMove.h"

#include "..\ApplicationManager.h"

#include "..\GUI\GUI.h"

ActionMove::ActionMove(ApplicationManager * pApp) :Action(pApp)
{}

//Execute the action
void ActionMove::Execute()
{
	GUI* pGUI = pManager->GetGUI();
	
	pManager->DeselectAllFigures();
	pManager->UpdateInterface();
	pGUI->PrintMessage("Select a figure to Move");
	Point p;
	pGUI->pWind->WaitMouseClick(p.x, p.y);
	if ((p.y > UI.ToolBarHeight) && (p.y < (UI.height - UI.StatusBarHeight))) {
		pManager->SelectFigure(p);
		if (pManager->GetSelectedCount() == 0){
			pGUI->PrintMessage("No figure was selected.");
		}
		else {
			pManager->UpdateInterface();
			pGUI->PrintMessage("Click to drop the figure.");
			Point pMoveTo;
			Point dummyPoint;
			bool isMoveOK;
			//until the user left-clicks the mouse, keep moving the figure
			while (pGUI->pWind->GetMouseClick(dummyPoint.x, dummyPoint.y) != LEFT_CLICK){
				pGUI->pWind->GetMouseCoord(pMoveTo.x, pMoveTo.y);
				int refreshPixels = 10; //pixels after which we move the figure and refresh
				if ((abs(p.x - pMoveTo.x) > refreshPixels) || (abs(p.y - pMoveTo.y) >refreshPixels))
				{ 
					isMoveOK=pManager->MoveSelected(p, pMoveTo);
					//if move is successful, update point  p to be pMoveTo
					p = (isMoveOK) ? pMoveTo : p;
					//update interface using a special function we made
					pManager->OurOwnUpdateInterface();
				}
			}
			pManager->DeselectAllFigures();
			pGUI->PrintMessage("Figure(s) moved.");
		}
	}
	else
		pGUI->PrintMessage("Click inside the drawing area.");

	pManager->SetGraphSaved(false);
}
	
