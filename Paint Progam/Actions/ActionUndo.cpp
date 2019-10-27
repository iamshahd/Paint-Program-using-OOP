#include "ActionUndo.h"

#include "..\ApplicationManager.h"

#include "..\GUI\GUI.h"

ActionUndo::ActionUndo(ApplicationManager * pApp) :Action(pApp)
{}

//Execute the action
void ActionUndo::Execute()
{
	GUI* pGUI = pManager->GetGUI();
	pGUI->PrintMessage("You want to Undo.");

	if (pManager->UndoCtr <= pManager->NumberOfActions)
		/* ie. the number of undo's possible must be less than
		or equal to the number of actions.*/
	{
		pManager->ToLoadWithName("Log\\" + to_string((pManager->NumberOfActions - pManager->UndoCtr) % 100));
		/*loading from the folder Log, which is created for saving actions for the Undo only. 
		We load the file number (Number of Actions - Number of Undos -1) 
		NB: ( UndoCtr = Number of Undos +1)*/

		pManager->UndoCtr++; //increment the undo counter to decrement number of possible undos

		pManager->SetGraphSaved(false); //To not change the Save state of the user by saving for undo.
	}
	else {
		pGUI->PrintMessage("No More Undo's Available");
	}
}