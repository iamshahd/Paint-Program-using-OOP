#ifndef APPLICATION_MANAGER_H
#define APPLICATION_MANAGER_H

#include "DEFS.h"
#include "Figures\CFigure.h"
#include "Figures\CSquare.h"
#include "Figures\CEllipse.h"
#include "Figures\CHexagon.h"

#include <ctime>

class Action;	//Forward Declaration


//Main class that manages everything in the application.
class ApplicationManager
{
	enum { MaxFigCount = 200 };	//Max no of figures
public:
	bool isplay = 0;		//true if play mode, false if draw mode
	int NumberOfActions = 0; //number of actions made so far in the program
	int UndoCtr;		//counter for undo
	int FigCount;		//Actual number of figures
	CFigure* FigList[MaxFigCount];	//List of all figures (Array of pointers)
	bool saved = false;		//indicates whether graph has been saved or not
	bool chkexit = false;	//Exit check

private:
	
	//Pointers to Input and Output classes
	GUI* pGUI;

public:	
	ApplicationManager(); 
	~ApplicationManager();

	void Run();		//to run the application
	
	// -- Action-Related Functions
	Action* CreateAction(ActionType);
	void ExecuteAction(Action*&) ; //Execute an action
	
	// -- Figures Management Functions
	void AddFigure(CFigure* pFig); //Adds a new figure to the FigList
	CFigure *GetFigure(int x, int y) const; //Search for a figure given a point inside the figure

	void SelectFigure(Point LastClickedPoint); //Select a figure given last clicked point 
	int GetSelectedCount(); //Returns number of selected Figures
	void DeselectAllFigures(); //Deselect all figures
	void SelectAllFigures(); //select all figures

	void DeleteSelectedFigures(); //Delete Selected Figures

	void BringToFront(int FigIndex); //Brings 1 selected figure to front
	void BringSelectedFiguresToFront(); //Brings all selected figures to front

	void SendToBack(int FigIndex); // Sends 1 selected figure to back
	void SendSelectedFiguresToBack(); //Sends all selected figures to back

	void ShowAllFigures(); //Show all figures
	
	void SaveAll(ofstream &outfile); //Save
	
	void SetGraphSaved(bool s);		//sets save state
	bool IsGraphSaved();			//returs save state

	bool IsDrawAreaEmpty();			//returns true if graph has no figures

	void ToLoad();
	void ToLoadWithName(string filename);
	void LoadAll(ifstream &infile, int FigureCount); //Load

	void ToResize();				//resize

	void ToNew();					//new sketch

	
	void SetExitTrue();				//sets exit check to true
	
	//Move the selected figure. returns 1 if move is successful and 0 if not
	bool MoveSelected(Point p, Point pMoveTo);
	

	void ResetIDs();			//re-assigns Figure IDs

	// -- Play Mode Functions
	void PlayFigType();
	void PlayFigFill();
	void PlayFigTypeFill();
	bool PlayedWithAllFigs();
	void ToPlay();		//switch to play mode
	void ToRestart();

	// -- Interface Management Functions	
	GUI *GetGUI() const; //Return pointer to the interface
	void UpdateInterface();	//Redraws all the drawing window	
	void OurOwnUpdateInterface(); // Redraws DrawingArea only

};

#endif