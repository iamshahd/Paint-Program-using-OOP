#include "ActionInfo.h"

#include "..\ApplicationManager.h"

#include "..\GUI\GUI.h"
#include <string>

using namespace std;

ActionInfo::ActionInfo(ApplicationManager * pApp) : Action(pApp)
{}

//Execute the action
void ActionInfo::Execute()
{
	GUI* pGUI = pManager->GetGUI();
	pGUI->PrintMessage("You want to open info.");
	string cmd0("cd\\");
	//string cmd("start \"\" /max \"c:\\PaintFiles\\Info.pdf\"");
	string cmd("c:\\PaintFiles\\Info.txt");
	system(cmd0.c_str());
	system(cmd.c_str());

}
