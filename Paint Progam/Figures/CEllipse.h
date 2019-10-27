#ifndef CEllipse_H
#define CEllipse_H

#include "CFigure.h"

#include <fstream>
class CEllipse : public CFigure
{
private:
	Point P1, P2;
	double horizax, vertax;
	Point center;
public:
	CEllipse(Point, Point, GfxInfo FigureGfxInfo);
	CEllipse(ifstream &infile);
	virtual void DrawMe(GUI* pOut) const;
	virtual bool isIn(CFigure* ToCheck);
	virtual bool IsInside(Point P);
	virtual void Save(ofstream &outfile);
	virtual void Load(ifstream &Infile);
	virtual void Resize(double resfactor);
	double const PI = 3.14159265;
	virtual int GetType() const; //returns 2
	virtual string FigureInfo() const;
	virtual void MoveFromTo(Point p, Point pMoveTo);
	virtual bool IsFigInsideBorders(int x1, int x2, int y1, int y2) const; //Checks whether figure is inside drawing area borders
};

#endif