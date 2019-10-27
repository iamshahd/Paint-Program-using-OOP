#include "ActionSelect.h"

#include "..\ApplicationManager.h"

#include "..\GUI\GUI.h"

ActionSelect::ActionSelect(ApplicationManager * pApp) :Action(pApp)
{}

//Execute the action
void ActionSelect::Execute()
{
	GUI* pGUI = pManager->GetGUI();
	pGUI->PrintMessage("You want to Select/Deselect.");

	pManager->SelectFigure(pGUI->LastClickedPoint);
}
