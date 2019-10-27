#include "ActionToFront.h"

#include "..\ApplicationManager.h"

#include "..\GUI\GUI.h"

ActionToFront::ActionToFront(ApplicationManager * pApp):Action(pApp)
{}

//Execute the action
void ActionToFront::Execute() 
{
	GUI* pGUI = pManager->GetGUI();
	pGUI->PrintMessage("You want to Bring to Front.");	
	
	pManager->BringSelectedFiguresToFront();
}
