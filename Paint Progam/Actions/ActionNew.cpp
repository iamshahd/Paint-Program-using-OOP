#include "ActionNew.h"

#include "..\ApplicationManager.h"

#include "..\GUI\GUI.h"

ActionNew::ActionNew(ApplicationManager * pApp) :Action(pApp)
{}

//Execute the action
void ActionNew::Execute()
{
	GUI* pGUI = pManager->GetGUI();
	pGUI->PrintMessage("You want to create a new sketch.");

	if ((pManager->IsDrawAreaEmpty()) || (!pManager->IsDrawAreaEmpty() && pManager->IsGraphSaved())) { //if the drawing area is empty or graph already saved
		pManager->ToNew();; //new
	}
	else if (!pManager->IsDrawAreaEmpty() && !pManager->IsGraphSaved()){ //if the drawing area is not empty and graph is not already saved
		pGUI->PrintMessage("Your file is not saved. Do you want to save it before creating a new sketch? Type Y for yes and N for no.");
		string saveresponse = pGUI->GetString();
		if (saveresponse == "Y") { //if yes
			//save
			GUI* pGUI = pManager->GetGUI();
			pGUI->PrintMessage("You want to Save. Enter file name.");
			string filename = pGUI->GetString();
			ofstream outfile(filename);
			pManager->SaveAll(outfile);
			outfile.close();
			pGUI->PrintMessage("Project saved in file " + filename);
			//new
			pManager->ToNew();
		}
		else if (saveresponse == "N") { //if no
			pManager->ToNew(); //new
		}
		else //if user enters any other keyboard input
		{
			pGUI->PrintMessage("Unidentified input.");
		}
	}

}
