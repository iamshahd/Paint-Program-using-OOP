#include "ActionResize.h"

#include "..\ApplicationManager.h"

#include "..\GUI\GUI.h"

ActionResize::ActionResize(ApplicationManager * pApp) :Action(pApp)
{}

//Execute the action
void ActionResize::Execute()
{
	pManager->ToResize();
}