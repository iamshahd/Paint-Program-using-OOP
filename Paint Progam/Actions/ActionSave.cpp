#include "ActionSave.h"

#include "..\ApplicationManager.h"

#include "..\GUI\GUI.h"

ActionSave::ActionSave(ApplicationManager * pApp):Action(pApp)
{}

//Execute the action
void ActionSave::Execute() 
{
	GUI* pGUI = pManager->GetGUI();
	pGUI->PrintMessage("You want to Save. Enter file name.");

	string filename = pGUI->GetString();
	ofstream outfile(filename + ".txt");

	pManager->SaveAll(outfile);
	outfile.close();
	pGUI->PrintMessage("Project saved in file "+filename+".txt");
}
