#ifndef CHEXAGON_H
#define CHEXAGON_H

#include "CFigure.h"
#include <fstream>
class CHexagon : public CFigure
{
private:
	Point center;
	Point end;
	double radius;
public:
	const int iVertices = 6;
	double const PI = 3.14159265;
	CHexagon(Point, Point, GfxInfo FigureGfxInfo);
	CHexagon(ifstream &infile);
	virtual void DrawMe(GUI* pOut) const;
	virtual int* gethexpointsy(Point, Point) const;
	virtual int* gethexpointsx(Point, Point) const;
	virtual bool IsInside(Point P);
	virtual void Save(ofstream &OutFile);
	virtual void Load(ifstream &Infile);
	virtual void Resize(double resfactor);
	virtual int GetType() const;
	virtual string FigureInfo() const;
	virtual void MoveFromTo(Point p, Point pMoveTo);
	//Checks whether figure is inside drawing area borders
	virtual bool IsFigInsideBorders(int x1, int x2, int y1, int y2) const;
};

#endif
