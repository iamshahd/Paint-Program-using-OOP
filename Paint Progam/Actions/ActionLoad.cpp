#include "ActionLoad.h"

#include "..\ApplicationManager.h"

#include "..\GUI\GUI.h"

ActionLoad::ActionLoad(ApplicationManager * pApp):Action(pApp)
{}

//Execute the action
void ActionLoad::Execute()
{
	GUI* pGUI = pManager->GetGUI();

	if ((pManager->IsDrawAreaEmpty()) || (!pManager->IsDrawAreaEmpty() && pManager->IsGraphSaved())) { //if the drawing area is empty or graph already saved
		pManager->ToLoad(); //load
	}
	else if (!pManager->IsDrawAreaEmpty() && !pManager->IsGraphSaved()){ //if the drawing area is not empty and graph is not already saved
		pGUI->PrintMessage("Your file is not saved. Do you want to save it before loading? Type Y for yes and N for no.");
		string saveresponse = pGUI->GetString();
		if (saveresponse == "Y") { //if yes
			//save
			GUI* pGUI = pManager->GetGUI();
			pGUI->PrintMessage("You want to Save. Enter file name.");
			string filename = pGUI->GetString();
			ofstream outfile(filename + ".txt");
			pManager->SaveAll(outfile);
			outfile.close();
			pGUI->PrintMessage("Project saved in file " + filename+".txt");
			//load
			pManager->ToLoad();
		}
		else if (saveresponse == "N") { //if no
			pManager->ToLoad(); //load
		}
		else //if user enters any other keyboard input
		{
			pGUI->PrintMessage("Unidentified input.");
		}
	}



}
