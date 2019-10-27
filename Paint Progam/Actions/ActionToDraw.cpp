#include "ActionToDraw.h"

#include "..\ApplicationManager.h"

#include "..\GUI\GUI.h"

ActionToDraw::ActionToDraw(ApplicationManager * pApp) :Action(pApp)
{}

//Execute the action
void ActionToDraw::Execute()
{
	GUI* pGUI = pManager->GetGUI();
	pGUI->PrintMessage("Switched to Draw Mode.");
	pManager->isplay = 0;
	pManager->ShowAllFigures();
}
