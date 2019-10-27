#include "ApplicationManager.h"
#include "Actions\ActionAddSquare.h"
#include "Actions\ActionAddElps.h"
#include "Actions\ActionAddHex.h"
#include "Actions\ActionBkClr.h"
#include "Actions\ActionFillClr.h"
#include "Actions\ActionDrawClr.h"
#include "Actions\ActionDel.h"
#include "Actions\ActionExit.h"
#include "Actions\ActionLoad.h"
#include "Actions\ActionResize.h"
#include "Actions\ActionSave.h"
#include "Actions\ActionToBack.h"
#include "Actions\ActionToFront.h"
#include "Actions\ActionToPlay.h"
#include "Actions\ActionHelp.h"
#include "Actions\ActionInfo.h"

#include "Actions\ActionSelect.h"

#include "Actions\ActionFigType.h"
#include "Actions\ActionFigFill.h"
#include "Actions\ActionFigTypeFill.h"
#include "Actions\ActionRestart.h"
#include "Actions\ActionToDraw.h"

#include "Actions\ActionMove.h"
#include "Actions\ActionUndo.h"
#include "Actions\ActionRedo.h"
#include "Actions\ActionNew.h"

//Constructor
ApplicationManager::ApplicationManager()
{
	//Create Input and output
	pGUI = new GUI;	
	
	FigCount = 0;
		
	//Create an array of figure pointers and set them to NULL		
	for(int i=0; i<MaxFigCount; i++)
		FigList[i] = NULL;	
}

void ApplicationManager::Run()
{
	srand(time(0));
	ActionType ActType;
	do
	{		
		//1- Read user action
		ActType = pGUI->MapInputToActionType();
		pGUI->PrintMessage("The last point clicked is: ( "
			+ to_string(pGUI->LastClickedPoint.x) + ", "
			+ to_string(pGUI->LastClickedPoint.y) + " ).");

		//2-A- Create the corresponding Action
		Action *pAct = CreateAction(ActType);

		//2-B-Save State before Executing
		if (ActType != UNDO && ActType != REDO && ActType!=EXIT
			&& ActType!=DRAWING_AREA && ActType!=LOAD && ActType!=SAVE
			&& ActType!=NEW && ActType!=TO_DRAW && ActType!=TO_PLAY
			&& ActType!=HELP && ActType!=INFO) {
			ofstream outfile("Log\\" + to_string(NumberOfActions % 100) + ".txt");
			SaveAll(outfile);
			outfile.close();
			NumberOfActions++;
			UndoCtr = 1;
		}
		else if (ActType == UNDO) {
			ofstream outfile("Log2\\" + to_string(UndoCtr) + ".txt");
			SaveAll(outfile);
			outfile.close();
		}
		//3- Execute the action
		ExecuteAction(pAct);

		//4- Update the interface
		UpdateInterface();	

	}while(ActType != EXIT && chkexit==false);
	
}


//==================================================================================//
//								Actions Related Functions							//
//==================================================================================//
//Creates an action
Action* ApplicationManager::CreateAction(ActionType ActType) 
{
	Action* newAct = NULL;
	
	//According to Action Type, create the corresponding action object
	switch (ActType)
	{
		case DRAW_SQUARE:
			newAct = new ActionAddSquare(this);
			break;

		case DRAW_ELPS:
	    	newAct = new ActionAddElps(this);
			break;

		case DRAW_HEX:
			newAct = new ActionAddHex(this);
			break;

		case CHNG_DRAW_CLR:
			newAct = new ActionDrawClr(this);
			break;

		case CHNG_FILL_CLR:
			newAct = new ActionFillClr(this);
			break;

		case CHNG_BK_CLR:
			newAct = new ActionBkClr(this);
			break;

		case DEL:
			newAct = new ActionDel(this);
			break;

		case RESIZE:
			newAct = new ActionResize(this);
			break;

		case SEND_BACK:
			newAct = new ActionToBack(this);
			break;

		case BRNG_FRNT:
			newAct = new ActionToFront(this);
			break;

		case SAVE:
			newAct = new ActionSave(this);
			break;

		case LOAD:
			newAct = new ActionLoad(this);
			break;

		case TO_PLAY:
			newAct = new ActionToPlay(this);
			break;

		case TO_DRAW:
			newAct = new ActionToDraw(this);
			break;

		case FIG_TYPE:
			newAct = new ActionFigType(this);
			break;

		case FIG_FILL:
			newAct = new ActionFigFill(this);
			break;

		case FIG_TYPE_FILL:
			newAct = new ActionFigTypeFill(this);
			break;
				
		case MOVE:
			newAct = new ActionMove(this);
			break;

		case UNDO:
			newAct = new ActionUndo(this);
			break;

		case REDO:
			newAct = new ActionRedo(this);
			break;

		case EXIT:
			newAct = new ActionExit(this);
			break;

		case STATUS:	//a click on the status bar ==> no action
			return NULL;
			break;

		case DRAWING_AREA:
			newAct = new ActionSelect(this);
			break;

		case RESTART:
			newAct = new ActionRestart(this);
			break;

		case NEW:
			newAct = new ActionNew(this);
			break;
		case HELP:
			newAct = new ActionHelp(this);
			break;
		case INFO:
			newAct = new ActionInfo(this);
			break;
	}	
	return newAct;
}
//////////////////////////////////////////////////////////////////////
//Executes the created Action
void ApplicationManager::ExecuteAction(Action* &pAct) 
{	
	//Execute the created action
	if(pAct != NULL)
	{
		pAct->Execute();//Execute
		delete pAct;	//Action is not needed any more ==> delete it
		pAct = NULL;
	}
}
//==================================================================================//
//						Figures Management Functions								//
//==================================================================================//

//Add a figure to the list of figures
void ApplicationManager::AddFigure(CFigure* pFig)
{
	if (FigCount < MaxFigCount)
		FigList[FigCount++] = pFig;
	else
		pGUI->PrintMessage("Cannot draw more than 200 figures in one graph.");

	ResetIDs();
	SetGraphSaved(false);
}
////////////////////////////////////////////////////////////////////////////////////
CFigure *ApplicationManager::GetFigure(int x, int y) const
{
	//If a figure is found return a pointer to it.
	//if this point (x,y) does not belong to any figure return NULL


	///Add your code here to search for a figure given a point x,y	

	return NULL;
}

void ApplicationManager::SelectFigure(Point LastClickedPoint) //Select a figure given last clicked point
{
	// Loop on figures from front to back
	for (int i=FigCount-1; i>=0; i--){
		// Check if last clicked point is inside  figure by calling its virtual fn IsInside
		if (FigList[i]->IsInside(LastClickedPoint)) {
			// Select/Unselect
			FigList[i]->SetSelected(!FigList[i]->IsSelected());
			// Print figure info if figure is selected
			if (FigList[i]->IsSelected()){
				// FigureInfo is a virtual function
				pGUI->PrintMessage(FigList[i]->FigureInfo());
			}
			break;
		}
	}
}

void ApplicationManager::DeleteSelectedFigures() //Delete selected figures
{
	
	if (GetSelectedCount() == 0)
	{
		pGUI->PrintMessage("No figure is selected. Please select at least a figure to delete.");
	}
	else
	{
		// Loop on all figures to find selected figures and delete them
		for (int i = FigCount - 1; i >= 0; i--) {
			if (FigList[i]->IsSelected()) {
				delete FigList[i]; // clean up memory
				FigList[i] = NULL;
				/*Shift elements above in FigList so there are no "holes" where
				the figure was deleted*/
				for (int j = i + 1; j < FigCount; j++)
				{
					FigList[j - 1] = FigList[j];
				}
				FigCount--; //Decrement count of figures by 1 after deleting each figure
			}
		}
		SetGraphSaved(false); // Graph state is now not saved
		ResetIDs(); // Re-assign IDs
		pGUI->PrintMessage("Figure(s) deleted.");
	}
}

void ApplicationManager::BringToFront(int FigIndex) //Bring 1 figure to front
{
	if (FigIndex == FigCount - 1) { return; } //figure already in front
	CFigure* FigToMove = FigList[FigIndex]; //temporarily hold the figure
	//Shift backward all elements in front of said figure 
	for (int i = FigIndex; i < FigCount - 1; i++) {
		FigList[i] = FigList[i + 1];
	}
	//Insert FigToMove at the end of the figure list
	FigList[FigCount - 1] = FigToMove;
}

void ApplicationManager::BringSelectedFiguresToFront() //Bring all selected figures to front
{
	
	if (GetSelectedCount() == 0)
	{
		pGUI->PrintMessage("No figure is selected. Please select a figure to bring to front.");
	}
	else
	{
		/* Brings each selected figure to front. We start from 0 to FigCount-1
		in order to preserve relative order */
		for (int i = 0; i < FigCount; i++) {
			if (FigList[i]->IsSelected()) {
				BringToFront(i);
			}
		}
		SetGraphSaved(false); // Graph is now not saved
		ResetIDs(); // Re-assign IDs (unnecessary)
		pGUI->PrintMessage("Figure(s) brough to front.");
		DeselectAllFigures();
	}
}

void ApplicationManager::SendToBack(int FigIndex) //Send 1 figure to back
{
	if (FigIndex == 0) { return; } //figure already at the back
	CFigure* FigToMove = FigList[FigIndex]; //temporarily hold the figure
	//Shift forward all elements behind said figure 
	for (int i = FigIndex - 1; i >= 0; i--) {
		FigList[i + 1] = FigList[i];
	}
	//Insert FigToMove at the head of the figure list
	FigList[0] = FigToMove;
}

void ApplicationManager::SendSelectedFiguresToBack() //Send all selected figures to back
{
	if (GetSelectedCount() == 0)
	{
		pGUI->PrintMessage("No figure is selected. Please select a figure to send to back.");
	}
	else
	{
		/* Sends each selected figure to back. We start from FigCount-1 to 0
		in order to preserve relative order */
		for (int i = FigCount - 1; i >= 0; i--) {
			if (FigList[i]->IsSelected()) {
				SendToBack(i);
			}
		}
		SetGraphSaved(false); // Graph is now not saved
		ResetIDs(); // Re-assign IDs (unnecessary)
		pGUI->PrintMessage("Figure(s) sent to back.");
		DeselectAllFigures();
	}
}

void ApplicationManager::SaveAll(ofstream &outfile) //Save 
{
	//First, save GUI information
	color DrawColor = pGUI->getCrntDrawColor();
	outfile << int(DrawColor.ucRed) << "\t" << int(DrawColor.ucGreen) << "\t" << int(DrawColor.ucBlue) << "\n";
	color FillColor = pGUI->getCrntFillColor();
	outfile << int(FillColor.ucRed) << "\t" << int(FillColor.ucGreen) << "\t" << int(FillColor.ucBlue) << "\n";
	color BkGrndColor = pGUI->getCrntBkGrndColor();
	outfile<< int(BkGrndColor.ucRed) << "\t" << int(BkGrndColor.ucGreen) << "\t" << int(BkGrndColor.ucBlue) << "\n";
	outfile << FigCount << endl;
	//Pass the output file stream to each figure so it saves its own information
	for (int i = 0; i < FigCount; i++) {
		FigList[i]->Save(outfile); //virtual fn
	}
	SetGraphSaved(true); // Graph is now saved
}

void ApplicationManager::SetGraphSaved(bool s){
	saved = s;
}

bool ApplicationManager::IsGraphSaved(){
	return saved;
}

void ApplicationManager::ToLoad(){
	pGUI->PrintMessage("You want to load a file. Enter file name. ");

	string filename = pGUI->GetString();
	NumberOfActions = 0; //Do not allow undo of a load operation
	ToLoadWithName(filename);
}

void ApplicationManager::ToLoadWithName(string filename) {

	ifstream infile(filename + ".txt");

	if (!infile) {
		pGUI->PrintMessage("Error opening file name. Please contact the Developer.");
	}
	else {
		// Load data in the same order it is saved
		int temp;
		color DrawColor;
		infile >> temp;
		DrawColor.ucRed = static_cast<char>(temp);
		infile >> temp;
		DrawColor.ucGreen = static_cast<char>(temp);
		infile >> temp;
		DrawColor.ucBlue = static_cast<char>(temp);
		pGUI->setDrawColor(DrawColor);

		color FillColor;
		infile >> temp;
		FillColor.ucRed = static_cast<char>(temp);
		infile >> temp;
		FillColor.ucGreen = static_cast<char>(temp);
		infile >> temp;
		FillColor.ucBlue = static_cast<char>(temp);
		pGUI->setFillColor(FillColor);

		color BkGrndColor;
		infile >> temp;
		BkGrndColor.ucRed = static_cast<char>(temp);
		infile >> temp;
		BkGrndColor.ucGreen = static_cast<char>(temp);
		infile >> temp;
		BkGrndColor.ucBlue = static_cast<char>(temp);
		pGUI->setBkGrndColor(BkGrndColor);

		int count; // Figure count
		infile >> count;

		LoadAll(infile, count);
		infile.close();
		SetGraphSaved(true);
	}
}

void ApplicationManager::LoadAll(ifstream &infile, int FigureCount) //Load
{
	// Delete current sketch
	for (int i = 0; i < FigCount; i++) {
		delete FigList[i];
		FigList[i] = NULL;
	}
	FigCount = 0; // Re-set FigCount
	UpdateInterface(); // Drawing Area is now clear

	int FigType; //1 for square, 2 for ellipse, 3 for hexagon
	for (int i = 0; i < FigureCount; i++) {
		infile >> FigType;
		switch (FigType) {
		case 1: //square
		{
			// Create a square object and let it load its data
			CSquare* S = new CSquare(infile);
			//Add figure to FigList
			AddFigure(S);
		}
		break;
		case 2: //ellipse
		{
			// Create an ellipse object and let it load its data
			CEllipse * E = new CEllipse(infile);
			//Add figure to FigList
			AddFigure(E);
		}
		break;
		case 3: //hexagon
		{
			// Create a hexagon object and let it load its data
			CHexagon * H = new CHexagon(infile);
			//Add figure to FigList
			AddFigure(H);
		}
		break;
		}
	}
	
}

void ApplicationManager::ShowAllFigures()
{
	for (int i = 0; i < FigCount; i++)
		FigList[i]->SetShown(true);
}

void ApplicationManager::DeselectAllFigures()
{
	for (int i = 0; i < FigCount; i++)
		FigList[i]->SetSelected(false);
}

void ApplicationManager::SelectAllFigures()
{
	for (int i = 0; i < FigCount; i++)
		FigList[i]->SetSelected(true);
}

bool ApplicationManager::IsDrawAreaEmpty(){
	//returns true if no figures are drawn
	if (FigCount == 0)
		return true;
	else
		return false;
}

void ApplicationManager::ToNew(){
	// New sketch
	SetGraphSaved(false);
	SelectAllFigures();
	DeleteSelectedFigures();
	pGUI->setDrawColor(BLUE);	//Default drawing color
	pGUI->setFillColor(GREEN);	//Default filling color
	pGUI->setBkGrndColor(LIGHTGOLDENRODYELLOW);	//Default background color
	NumberOfActions = 0; //Do not allow undo of a New Sketch operation
	pGUI->PrintMessage("New sketch created.");
}

void ApplicationManager::SetExitTrue(){
	//clean up dynamically allocated memory
	for (int i = 0; i < FigCount; i++)
	{
		delete FigList[i];
		FigList[i] = NULL;
	}
	FigCount = 0;
	// set exit check to true
	chkexit = true;
}

void ApplicationManager::ToResize()
{
	if (GetSelectedCount() == 0)
	{
		pGUI->PrintMessage("No figure is selected. Please select at least one figure to resize.");
	}
	else
	{
		GUI* pGUI = GetGUI();
		pGUI->pWind->DrawImage("images\\Other\\ResizeFactors.jpg", ITM_RESIZE * UI.MenuItemWidth, UI.ToolBarHeight, 208, 46); //draws an image at (x, y).  The width and height parameters can be used to scale the image.
		pGUI->PrintMessage("Choose the ratio you want to resize to");
		int x, y;
		pGUI->pWind->WaitMouseClick(x, y);	//Get the coordinates of the user click
		pGUI->LastClickedPoint.x = x;
		pGUI->LastClickedPoint.y = y;

		double resfactor;

		if (x >= ITM_RESIZE * UI.MenuItemWidth && x <= ITM_RESIZE * UI.MenuItemWidth + 52 && y >= UI.ToolBarHeight && y <= UI.ToolBarHeight + 46)
		{
			resfactor = 0.25;
		}
		else if (x >= ITM_RESIZE * UI.MenuItemWidth + 52 && x <= ITM_RESIZE * UI.MenuItemWidth + 104 && y >= UI.ToolBarHeight && y <= UI.ToolBarHeight + 46)
		{
			resfactor = 0.5;
		}
		else if (x >= ITM_RESIZE * UI.MenuItemWidth + 104 && x <= ITM_RESIZE * UI.MenuItemWidth + 156 && y >= UI.ToolBarHeight && y <= UI.ToolBarHeight + 46)
		{
			resfactor = 2;
		}
		else if (x >= ITM_RESIZE * UI.MenuItemWidth + 156 && x <= ITM_RESIZE * UI.MenuItemWidth + 208 && y >= UI.ToolBarHeight && y <= UI.ToolBarHeight + 46)
		{
			resfactor = 4;
		}
		pGUI->PrintMessage("You want to resize by " + to_string(resfactor));
		int fignum = FigCount;
		CFigure* pFig;
		// Resize all selected figures
		for (int i = 0; i < fignum; i++)
		{
			pFig = FigList[i];
			if (pFig->IsSelected())
			{
				pFig->Resize(resfactor);
				// Check to see if figure is inside borders after resizing
				if (!pFig->IsFigInsideBorders(0, UI.width - 10, UI.ToolBarHeight, UI.height - UI.StatusBarHeight + 3)) {
					pGUI->PrintMessage("Cannot resize figure beyond Drawing Area");
					pFig->Resize(1 / resfactor); //bring back to original size
				}
				else {
					pGUI->PrintMessage("Figure resized by "+to_string(resfactor));
					SetGraphSaved(false);
				}
			}
		}
	}
	
	
}

///////////////////////////////////////////

int ApplicationManager::GetSelectedCount(){
	//returns count of selected figures
	int counter = 0;
	for (int i = 0; i < FigCount; i++){
		if (FigList[i]->IsSelected()){
			counter++;
		}
	}
	return counter;
}

///////////////////////////////////////////

bool ApplicationManager::MoveSelected(Point p, Point pMoveTo)
//moves selected figures from point p to pMoveTo
{
	//returns 1 if move is successful and 0 if not
	bool success = 1;
	CFigure* pFig;
	for (int i = 0; i < FigCount; i++)
	{
		pFig = FigList[i];
		if (pFig->IsSelected())
		{
			pFig->MoveFromTo(p, pMoveTo);
			//makes sure figure is inside borders
			if (!pFig->IsFigInsideBorders(0, UI.width-10, UI.ToolBarHeight, UI.height - UI.StatusBarHeight+3))
			{
				//if figure is outside borders, move it back to point p
				pGUI->PrintMessage("Cannot drag figure beyond Drawing Area borders.");
				pFig->MoveFromTo(pMoveTo, p);
				success= 0;
			}
			SetGraphSaved(false);
		}
	}
	return success;
}

///////////////////////////////////////////

void ApplicationManager::ResetIDs() {
	// re-assigns IDs
	for (int i = 0; i < FigCount; i++)
		FigList[i]->SetID(i+1);
}

//==================================================================================//
//							Play Mode Functions						             	//
//==================================================================================//

void ApplicationManager::PlayFigType()
{
	if (PlayedWithAllFigs())
		return;

	int FigIndex = rand() % FigCount; //choose a random figure from FigList
	while (!FigList[FigIndex]->IsShown()) {
		FigIndex = rand() % FigCount; //choose a shown random figure from FigList
	}
	int type = FigList[FigIndex]->GetType(); //get type of randomly chosen figure
	//prepare message to display
	string message = "Click on all ";
	switch (type) {
	case 1: { message += "squares."; break; }
	case 2: { message += "ellipses."; break; }
	case 3: { message += "hexagons."; break; }
	}
	//count all figures of the same type
	int SameTypeCount = 0;
	for (int i = 0; i < FigCount; i++) {
		if (!FigList[i]->IsShown())
			continue;
		if (FigList[i]->GetType() == type) {
			SameTypeCount++;
		}
	}
	pGUI->PrintMessage(message);

	int correct = 0; //correct clicks
	int incorrect = 0; //incorrect clicks
	std::string msg;
	std::string strCorrect;
	std::string strIncorrect;

	while (correct < SameTypeCount)
	{
		int x, y;
		pGUI->pWind->WaitMouseClick(x,y);
		pGUI->LastClickedPoint.x = x;
		pGUI->LastClickedPoint.y = y;
		
		for (int i = FigCount - 1; i >= 0; i--) {
			if ((FigList[i]->IsInside(pGUI->LastClickedPoint)) && (FigList[i]->IsShown())) {
				//correct pick
				if (FigList[i]->GetType() == type) {
					correct++;
					FigList[i]->SetShown(false); //hide figure
					UpdateInterface();
					break;
				}
				//incorrect pick
				else {
					incorrect++;
					break;
				}
			}
		}
		msg = "Correct picks : ";
		strCorrect = std::to_string(correct);
		strIncorrect = std::to_string(incorrect);
		msg.append(strCorrect);
		msg.append(", Incorrect picks : ");
		msg.append(strIncorrect);
		
		pGUI->PrintMessage(msg);
	}
	
	std::string msg2 = "You have finished! Your total score is: \t\t";
	msg2.append(msg);
	
	pGUI->PrintMessage(msg2);
}

void ApplicationManager::PlayFigFill()
{
	if (PlayedWithAllFigs())
		return;

	int FigIndex = rand() % FigCount; //choose a random figure from FigList
	while (!FigList[FigIndex]->IsShown())
	{
		FigIndex = rand() % FigCount; //choose a shown random figure from FigList
	}
	color fillclr;
	int SameFillCount = 0; //counts figures of selected fill

	if (FigList[FigIndex]->IsFilled()) {
		fillclr = FigList[FigIndex]->GetFillClr(); //get fill clr of randomly chosen figure
	}

	unsigned char R, G, B;

	//prepare message to display
	string message = "Click on all ";
	if (!FigList[FigIndex]->IsFilled())
	{
		message += "not filled shapes.";
	}
	else
	{
		R = fillclr.ucRed;
		G = fillclr.ucGreen;
		B = fillclr.ucBlue;

		if (R == 255 && G == 255 && B == 255)
		{
			message += "white";
		}
		else if (R == 251 && G == 226 && B == 1)
		{
			message += "yellow";
		}
		else if (R == 255 && G == 90 && B == 0)
		{
			message += "orange";
		}
		else if (R == 216 && G == 9 && B == 15)
		{
			message += "red";
		}
		else if (R == 239 && G == 63 && B == 172)
		{
			message += "pink";
		}
		else if (R == 156 && G == 36 && B == 63)
		{
			message += "burgundy";
		}
		else if (R == 0 && G == 158 && B == 221)
		{
			message += "cyan";
		}
		else if (R == 1 && G == 37 && B == 149)
		{
			message += "blue";
		}
		else if (R == 73 && G == 20 && B == 160)
		{
			message += "violet";
		}
		else if (R == 0 && G == 117 && B == 0)
		{
			message += "dark green";
		}
		else if (R == 0 && G == 210 && B == 0)
		{
			message += "light green";
		}
		else if (R == 87 && G == 61 && B == 24)
		{
			message += "brown";
		}
		else if (R == 99 && G == 100 && B == 102)
		{
			message += "dark grey";
		}
		else if (R == 153 && G == 153 && B == 153)
		{
			message += "light grey";
		}
		else if (R == 254 && G == 255 && B == 179)
		{
			message += "cream";
		}
		else if (R == 0 && G == 0 && B == 0)
		{
			message += "black";
		}

		message += " colored shapes.";
	}

	for (int i = 0; i < FigCount; i++){
		color left = FigList[i]->GetFillClr();
		color right = fillclr;
		if (!FigList[i]->IsShown())
			continue;
		if (FigList[FigIndex]->IsFilled())
		{
			if (left.ucRed == right.ucRed && left.ucGreen == right.ucGreen && left.ucBlue == right.ucBlue)
			{
				SameFillCount++;
			}
		}
		else
		{
			if (!FigList[i]->IsFilled())
			{
				SameFillCount++;
			}
		}
	}

	pGUI->PrintMessage(message);

	int correct = 0;
	int incorrect = 0;
	std::string msg;
	std::string strCorrect;
	std::string strIncorrect;

	while (correct < SameFillCount)
	{
		int x, y;
		pGUI->pWind->WaitMouseClick(x, y);	//Get the coordinates of the user click
		pGUI->LastClickedPoint.x = x;
		pGUI->LastClickedPoint.y = y;

		for (int i = FigCount - 1; i >= 0; i--){
			color left = FigList[i]->GetFillClr();
			color right = fillclr;
			if (FigList[i]->IsInside(pGUI->LastClickedPoint) && FigList[i]->IsShown()) {
				if (FigList[FigIndex]->IsFilled())
				{
					if (left.ucRed == right.ucRed && left.ucGreen == right.ucGreen && left.ucBlue == right.ucBlue)
					{
						correct++;
						FigList[i]->SetShown(false); //hide figure
						UpdateInterface();
						break;
					}
					else if (left.ucRed != right.ucRed || left.ucGreen != right.ucGreen || left.ucBlue != right.ucBlue)
					{
						incorrect++;
						break;
					}
				}
				else
				{
					if (!FigList[i]->IsFilled())
					{
						correct++;
						FigList[i]->SetShown(false); //hide figure
						UpdateInterface();
						break;
					}
					else
					{
						incorrect++;
						break;
					}

				}
			}
		}
		msg = "Correct picks : ";
		strCorrect = std::to_string(correct);
		strIncorrect = std::to_string(incorrect);
		msg.append(strCorrect);
		msg.append(", Incorrect picks : ");
		msg.append(strIncorrect);
		pGUI->PrintMessage(msg);
	}
	std::string msg2 = "You have finished! Your total score is: \t";
	msg2.append(msg);
	pGUI->PrintMessage(msg2);
}

void ApplicationManager::PlayFigTypeFill()
{
	if (PlayedWithAllFigs())
		return;

	int FigIndex = rand() % FigCount; //choose a random figure from FigList
	while (!FigList[FigIndex]->IsShown())
	{
		FigIndex = rand() % FigCount; //choose a shown random figure from FigList
	}
	color fillclr;
	int type = FigList[FigIndex]->GetType(); //1 for square, 2 for ellipse, 3 for hexagon
	int SameTypeFillCount = 0; //counts figures of selected type

	if (FigList[FigIndex]->IsFilled()) {
		fillclr = FigList[FigIndex]->GetFillClr(); //get fill clr of randomly chosen figure
	}

	unsigned char R, G, B;

	//prepare message to display
	string message = "Click on all ";
	if (!FigList[FigIndex]->IsFilled())
	{
		message += "not filled ";
	}
	else
	{
		R = fillclr.ucRed;
		G = fillclr.ucGreen;
		B = fillclr.ucBlue;

		if (R == 255 && G == 255 && B == 255)
		{
			message += "white";
		}
		else if (R == 251 && G == 226 && B == 1)
		{
			message += "yellow";
		}
		else if (R == 255 && G == 90 && B == 0)
		{
			message += "orange";
		}
		else if (R == 216 && G == 9 && B == 15)
		{
			message += "red";
		}
		else if (R == 239 && G == 63 && B == 172)
		{
			message += "pink";
		}
		else if (R == 156 && G == 36 && B == 63)
		{
			message += "burgundy";
		}
		else if (R == 0 && G == 158 && B == 221)
		{
			message += "cyan";
		}
		else if (R == 1 && G == 37 && B == 149)
		{
			message += "blue";
		}
		else if (R == 73 && G == 20 && B == 160)
		{
			message += "violet";
		}
		else if (R == 0 && G == 117 && B == 0)
		{
			message += "dark green";
		}
		else if (R == 0 && G == 210 && B == 0)
		{
			message += "light green";
		}
		else if (R == 87 && G == 61 && B == 24)
		{
			message += "brown";
		}
		else if (R == 99 && G == 100 && B == 102)
		{
			message += "dark grey";
		}
		else if (R == 153 && G == 153 && B == 153)
		{
			message += "light grey";
		}
		else if (R == 254 && G == 255 && B == 179)
		{
			message += "cream";
		}
		else if (R == 0 && G == 0 && B == 0)
		{
			message += "black";
		}

		message += "-colored ";
	}
	switch (type) {
	case 1: { message += "squares."; break; }
	case 2: { message += "ellipses."; break; }
	case 3: { message += "hexagons."; break; }
	}

	//Loop on all figures to find count of figures with the same fill and type
	for (int i = 0; i < FigCount; i++) {
		if (!FigList[i]->IsShown())
			continue;
		color c = FigList[i]->GetFillClr();
		int t = FigList[i]->GetType();
		//Check if same type
		if (t == type) {
			//if same type, check if same fill
			if (FigList[FigIndex]->IsFilled())
			{
				if (c.ucRed == fillclr.ucRed && c.ucGreen == fillclr.ucGreen
					&& c.ucBlue == fillclr.ucBlue)
				{
					SameTypeFillCount++;
				}
			}
			else
			{
				if (!FigList[i]->IsFilled())
				{
					SameTypeFillCount++;
				}
			}
		}
		
	}

	pGUI->PrintMessage(message);

	int correct = 0;
	int incorrect = 0;
	std::string msg;
	std::string strCorrect;
	std::string strIncorrect;

	while (correct < SameTypeFillCount)
	{
		int x, y;
		pGUI->pWind->WaitMouseClick(x, y);	//Get the coordinates of the user click
		pGUI->LastClickedPoint.x = x;
		pGUI->LastClickedPoint.y = y;

		for (int i = FigCount - 1; i >= 0; i--) {
			
			if (FigList[i]->IsInside(pGUI->LastClickedPoint) && FigList[i]->IsShown()) {
				//Get color and type of clicked figure
				color c = FigList[i]->GetFillClr();
				int t = FigList[i]->GetType();
				//Check type of clicked figure
				if (t == type) {
					//If correct type, check fill
					if (FigList[FigIndex]->IsFilled())
					{
						if (c.ucRed == fillclr.ucRed && c.ucGreen == fillclr.ucGreen
							&& c.ucBlue == fillclr.ucBlue)
						{
							correct++;
							FigList[i]->SetShown(false); //hide figure
							UpdateInterface();
							break;
						}
						else
						{
							incorrect++;
							break;
						}
					}
					else
					{
						if (!FigList[i]->IsFilled())
						{
							correct++;
							FigList[i]->SetShown(false); //hide figure
							UpdateInterface();
							break;
						}
						else
						{
							incorrect++;
							break;
						}

					}
				}
				else {
					incorrect++;
					break;
				}
				
			}
		}
		msg = "Correct picks : ";
		strCorrect = std::to_string(correct);
		strIncorrect = std::to_string(incorrect);
		msg.append(strCorrect);
		msg.append(", Incorrect picks : ");
		msg.append(strIncorrect);
		pGUI->PrintMessage(msg);
	}
	std::string msg2 = "You have finished! Your total score is: \t";
	msg2.append(msg);
	pGUI->PrintMessage(msg2);
}

void ApplicationManager::ToRestart() {
	ShowAllFigures();
	pGUI->PrintMessage("Graph restarted. Select the game you want to play.");
}

bool ApplicationManager::PlayedWithAllFigs() {
	//Check if there is at least one shown figure
	string errorMsg = "You have played with all figures. Click restart to restore graph.";
	for (int i = 0; i < FigCount; i++) {
		if (FigList[i]->IsShown())
			return 0;
	}
	pGUI->PrintMessage(errorMsg);
	return 1;
}

void ApplicationManager::ToPlay()
{
	if (IsDrawAreaEmpty()) {
		pGUI->PrintMessage("You must draw at least one figure to go into Play Mode.");
	}
	else {
		isplay = true;
		DeselectAllFigures();
	}
}

//==================================================================================//
//							Interface Management Functions							//
//==================================================================================//

//Draw all figures on the user interface
void ApplicationManager::UpdateInterface()
{
	
	if (isplay)
	{
		pGUI->CreatePlayToolBar();
		pGUI->ClearDrawArea();
		for (int i = 0; i < FigCount; i++)
		{
			FigList[i]->DrawMe(pGUI); //Call Draw function (virtual member fn)
		}
	}
	else
	{
		pGUI->CreateDrawToolBar();
		pGUI->ClearDrawArea();
		
		for (int i = 0; i < FigCount; i++)
		{
			FigList[i]->DrawMe(pGUI); //Call Draw function (virtual member fn)
		}
	}
}

void ApplicationManager::OurOwnUpdateInterface() {

	pGUI->ClearDrawArea();

	for (int i = 0; i < FigCount; i++)
	{
		FigList[i]->DrawMe(pGUI); //Call Draw function (virtual member fn)
	}
	// Uses a whole picture to reduce lagging effect
	pGUI->pWind->DrawImage("images\\Other\\header.jpg", 0, 0, 1236, UI.ToolBarHeight + 2);

	pGUI->pWind->DrawImage("images\\Other\\footer.jpg", 0, 600, 1236, 35);

	pGUI->pWind->SetPen(RED, 3);
	pGUI->pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);

}


GUI *ApplicationManager::GetGUI() const
{	return pGUI; }
////////////////////////////////////////////////////////////////////////////////////
//Destructor
ApplicationManager::~ApplicationManager()
{
	for(int i=0; i<FigCount; i++)
		delete FigList[i];
	delete pGUI;
	
}
