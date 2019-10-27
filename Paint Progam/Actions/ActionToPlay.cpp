#include "ActionToPlay.h"

#include "..\ApplicationManager.h"

#include "..\GUI\GUI.h"

ActionToPlay::ActionToPlay(ApplicationManager * pApp):Action(pApp)
{}

//Execute the action
void ActionToPlay::Execute() 
{
	GUI* pGUI = pManager->GetGUI();
	pGUI->PrintMessage("Switched to Play Mode.");	
	pManager->ToPlay();
}
