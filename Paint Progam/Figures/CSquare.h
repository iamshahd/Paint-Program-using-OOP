#ifndef CSQUARE_H
#define CSQUARE_H

#include "CFigure.h"
#include <fstream>
class CSquare : public CFigure
{
private:
	Point TopLeftCorner;	
	int length;
	Point Point2;

public:
	CSquare(Point , int, GfxInfo FigureGfxInfo );
	CSquare(ifstream &infile);
	virtual void DrawMe(GUI* pOut) const;
	virtual bool IsInside(Point P);
	virtual void Save(ofstream &OutFile);
	virtual void Load(ifstream &Infile);
	virtual void Resize(double resfactor);
	virtual int GetType() const; //returns 1
	virtual string FigureInfo() const;
	virtual void MoveFromTo(Point p, Point pMoveTo);
	virtual bool IsFigInsideBorders(int x1, int x2, int y1, int y2) const; //Checks whether figure is inside drawing area borders
};

#endif