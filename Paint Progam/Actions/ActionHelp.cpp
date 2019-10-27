#include "ActionHelp.h"

#include "..\ApplicationManager.h"

#include "..\GUI\GUI.h"
#include <string>

using namespace std;

ActionHelp::ActionHelp(ApplicationManager * pApp) : Action(pApp)
{}

//Execute the action
void ActionHelp::Execute()
{
	GUI* pGUI = pManager->GetGUI();
	pGUI->PrintMessage("You want to open help.");
	string cmd0("cd\\");
	string cmd("start \"\" /max \"c:\\PaintFiles\\UserManual.pdf\"");
	system(cmd0.c_str());
	system(cmd.c_str());
	
}
