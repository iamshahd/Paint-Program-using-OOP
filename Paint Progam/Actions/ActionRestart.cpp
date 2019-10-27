#include "ActionRestart.h"

#include "..\ApplicationManager.h"

#include "..\GUI\GUI.h"

ActionRestart::ActionRestart(ApplicationManager * pApp) :Action(pApp)
{}

//Execute the action
void ActionRestart::Execute()
{
	GUI* pGUI = pManager->GetGUI();
	pGUI->PrintMessage("You want to restart the game.");

	pManager->ToRestart();
}
