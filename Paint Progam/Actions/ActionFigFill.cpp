#include "ActionFigFill.h"

#include "..\ApplicationManager.h"

#include "..\GUI\GUI.h"
#include <string> 

ActionFigFill::ActionFigFill(ApplicationManager * pApp) :Action(pApp)
{}

//Execute the action
void ActionFigFill::Execute()
{
	GUI* pGUI = pManager->GetGUI();
	pGUI->PrintMessage("You want to pick figures with the same fill color.");

	pManager->PlayFigFill();
}