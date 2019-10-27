#include "ActionToBack.h"

#include "..\ApplicationManager.h"

#include "..\GUI\GUI.h"

ActionToBack::ActionToBack(ApplicationManager * pApp):Action(pApp)
{}

//Execute the action
void ActionToBack::Execute() 
{
	GUI* pGUI = pManager->GetGUI();
	pGUI->PrintMessage("You want to Send to Back.");	
	
	pManager->SendSelectedFiguresToBack();
}
