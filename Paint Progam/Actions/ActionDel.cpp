#include "ActionDel.h"

#include "..\ApplicationManager.h"

#include "..\GUI\GUI.h"

ActionDel::ActionDel(ApplicationManager * pApp) :Action(pApp)
{}

//Execute the action
void ActionDel::Execute()
{
	GUI* pGUI = pManager->GetGUI();
	//pGUI->PrintMessage("You want to Delete.");

	pManager->DeleteSelectedFigures();
}
