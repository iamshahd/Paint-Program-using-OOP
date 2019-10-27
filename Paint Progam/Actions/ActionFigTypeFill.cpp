#include "ActionFigTypeFill.h"

#include "..\ApplicationManager.h"

#include "..\GUI\GUI.h"

ActionFigTypeFill::ActionFigTypeFill(ApplicationManager * pApp) :Action(pApp)
{}

//Execute the action
void ActionFigTypeFill::Execute()
{
	GUI* pGUI = pManager->GetGUI();
	pGUI->PrintMessage("You want to pick figures with the same type and fill color.");

	pManager->PlayFigTypeFill();
}
