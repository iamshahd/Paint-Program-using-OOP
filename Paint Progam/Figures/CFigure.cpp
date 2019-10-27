#include "CFigure.h"

CFigure::CFigure()
{
	Selected = false;
	Shown = true;
}


CFigure::CFigure(GfxInfo FigureGfxInfo)
{ 
	FigGfxInfo = FigureGfxInfo;	//Default status is non-filled.
	Selected = false;
	Shown = true;
}


bool CFigure::IsSelected() const
{	return Selected; }

bool CFigure::IsShown() const
{	return Shown;	}

bool CFigure::IsFilled()
{
	return FigGfxInfo.isFilled;
}

color CFigure::GetDrawClr() const
{
	return FigGfxInfo.DrawClr;
}

color CFigure::GetFillClr() const
{
	return FigGfxInfo.FillClr;
}

void CFigure::SetSelected(bool s)
{
	Selected = s;
}

void CFigure::SetShown(bool s)
{
	Shown = s;
}

void CFigure::ChngDrawClr(color Dclr)
{	FigGfxInfo.DrawClr = Dclr; }

void CFigure::ChngFillClr(color Fclr)
{	
	FigGfxInfo.isFilled = true;
	FigGfxInfo.FillClr = Fclr; 
}

void CFigure::SetID(int FigID) {
	ID = FigID;
}
