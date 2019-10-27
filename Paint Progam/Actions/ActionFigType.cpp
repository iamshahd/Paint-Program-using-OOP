#include "ActionFigType.h"

#include "..\ApplicationManager.h"

#include "..\GUI\GUI.h"
#include <string> 


ActionFigType::ActionFigType(ApplicationManager * pApp) :Action(pApp)
{}

//Execute the action
void ActionFigType::Execute()
{
	GUI* pGUI = pManager->GetGUI();
	pGUI->PrintMessage("You want to pick figures with the same type.");
	
	pManager->PlayFigType();

}
