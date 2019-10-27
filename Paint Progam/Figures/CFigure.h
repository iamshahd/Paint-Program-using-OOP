#ifndef CFIGURE_H
#define CFIGURE_H

#include "..\defs.h"
#include "..\GUI\GUI.h"

//Base class for all figures
class CFigure
{
protected:
	int ID;		//Each figure has an ID
	bool Selected;	//true if the figure is selected.
	bool Shown; //true if the figure is shown.
	GfxInfo FigGfxInfo;	//Figure graphis info

public:
	//Constructors
	CFigure();
	CFigure(GfxInfo FigureGfxInfo);
	//========================================================================================

	//Getter Methods

	bool IsSelected() const;	//check whether fig is selected
	bool IsShown() const;		//check whether figure is shown
	color GetFillClr() const;
	color GetDrawClr() const;
	bool IsFilled();
	
	//========================================================================================

	//Setter Methods

	void SetSelected(bool s);	//select/unselect the figure
	void SetShown(bool s);		//Hide or show figure
	void ChngDrawClr(color Dclr);	//changes the figure's drawing color
	void ChngFillClr(color Fclr);	//changes the figure's filling color
	void SetID(int FigID);

	//========================================================================================

	// Virtual Functions

	virtual void DrawMe(GUI*) const  = 0 ;		//Draw the figure
	virtual bool IsInside(Point P)=0; //Checks whether the point is inside or not

	//Checks whether figure is inside drawing area borders, given borders
	virtual bool IsFigInsideBorders(int x1, int x2, int y1, int y2) const = 0;
	
	virtual string FigureInfo() const = 0;
	virtual int GetType() const = 0; //1 for square, 2 for ellipse, 3 for hexagon
	virtual void Resize(double resfactor) = 0;	//Resize the figure
	virtual void MoveFromTo(Point p, Point pMoveTo) = 0; //Moves Figure from point p to point pMoveTo

	virtual void Save(ofstream &outfile) = 0;	//Save the figure parameters to the file
	virtual void Load(ifstream &Infile) = 0;	//Load the figure parameters to the file

};

#endif