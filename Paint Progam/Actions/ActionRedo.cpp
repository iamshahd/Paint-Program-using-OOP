#include "ActionRedo.h"

#include "..\ApplicationManager.h"

#include "..\GUI\GUI.h"

ActionRedo::ActionRedo(ApplicationManager * pApp) :Action(pApp)
{}

//Execute the action
void ActionRedo::Execute()
{
	GUI* pGUI = pManager->GetGUI();
	pGUI->PrintMessage("You want to Redo.");

	if (pManager->UndoCtr > 1)
		/*for any possible redo, the undo counter must be greater than
		1 since it starts from 1 (ie. number of possible redos is equal
		to the number of performed undos.*/

	{
		pManager->ToLoadWithName("Log2\\" + to_string(pManager->UndoCtr - 1));
		//loading from the folder Log2, which is created for saving sketches for the Redo only. 
		pManager->UndoCtr--;// decrement undo counter to decrement number of possible redos.
	}
	else { pGUI->PrintMessage("No More Redo's Available"); }

	pManager->SetGraphSaved(false); //To not change the Save state of the user by saving for redo.

}