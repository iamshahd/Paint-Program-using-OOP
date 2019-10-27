#include "CSquare.h"

CSquare::CSquare(Point P1, int len, GfxInfo FigureGfxInfo):CFigure(FigureGfxInfo)
{
	TopLeftCorner = P1;
	length = len;
	Point P2;
	P2.x = P1.x + length;
	P2.y = P1.y + length;
	Point2 = P2;
}

CSquare::CSquare(ifstream &infile):CFigure()
{
	Load(infile);
}

bool CSquare::IsInside(Point P)
{
	bool isin = 0;
	if(P.x < (this->TopLeftCorner.x + this->length)
		&& P.x > this->TopLeftCorner.x
		&& P.y<(this->TopLeftCorner.y+this->length)
		&& P.y > this->TopLeftCorner.y) {
		isin = 1;
	}
	return isin;

}

void CSquare::DrawMe(GUI* pGUI) const
{
	if (this->Shown) {
		//Call Output::DrawRect to draw a Square on the screen	
		pGUI->DrawSquare(TopLeftCorner, Point2, FigGfxInfo, Selected);
	}
}

void CSquare::Save(ofstream &outfile) {
	
	color DrawColor = FigGfxInfo.DrawClr;
	outfile << "1\t"
		<< ID << "\t"
		<< TopLeftCorner.x << "\t"
		<< TopLeftCorner.y << "\t"
		<< length << "\t"
		<< int(DrawColor.ucRed) << "\t" << int(DrawColor.ucGreen) << "\t" << int(DrawColor.ucBlue) << "\t";
	if (FigGfxInfo.isFilled) {
		color FillColor = FigGfxInfo.FillClr;
		outfile << int(FillColor.ucRed) << "\t" << int(FillColor.ucGreen) << "\t" << int(FillColor.ucBlue) << "\t";
	}
	else
		outfile << -1 << "\t";
	outfile << FigGfxInfo.BorderWdth<<endl;
}

void CSquare::Load(ifstream &infile) {
	infile >> ID;
	infile >> TopLeftCorner.x >> TopLeftCorner.y >> length;
	Point2.x = TopLeftCorner.x + length;
	Point2.y = TopLeftCorner.y + length;
	int temp;
	infile >> temp;
	FigGfxInfo.DrawClr.ucRed = static_cast<char>(temp);
	infile >> temp;
	FigGfxInfo.DrawClr.ucGreen = static_cast<char>(temp);
	infile >> temp;
	FigGfxInfo.DrawClr.ucBlue = static_cast<char>(temp);

	int filled;
	infile >> filled;
	if (filled == -1)
		FigGfxInfo.isFilled = false;
	else {
		FigGfxInfo.isFilled = true;
		FigGfxInfo.FillClr.ucRed = static_cast<char>(filled);
		infile >> temp;
		FigGfxInfo.FillClr.ucGreen = static_cast<char>(temp);
		infile >> temp;
		FigGfxInfo.FillClr.ucBlue = static_cast<char>(temp);
	}
	infile >> FigGfxInfo.BorderWdth;
}


void CSquare::Resize(double resfactor) {
	double length1 = length;
	double area1 = pow(length1, 2);
	double area2 = resfactor*area1;
	double length2 = sqrt((pow(length1, 2)*area2) / area1);
	length = int(length2);
	Point2.x = TopLeftCorner.x + length;
	Point2.y = TopLeftCorner.y + length;
}

//1 for square, 2 for ellpise, 3 for hexagon
int CSquare::GetType() const {
	return 1;
}

string CSquare::FigureInfo() const {
	int area = int(pow(length, 2));
	std::string x = std::to_string(TopLeftCorner.x);
	std::string y = std::to_string(TopLeftCorner.y);
	std::string l = std::to_string(length);
	std::string id = std::to_string(ID);
	std::string a = std::to_string(area);
	std::string info = "Square Selected. Top Left Corner: (";
	info.append(x);
	info.append(", ");
	info.append(y);
	info.append("). Side length: ");
	info.append(l);
	info.append(". Area: ");
	info.append(a);
	info.append(". ID: ");
	info.append(id);

	return info;
}

void CSquare::MoveFromTo(Point p, Point pMoveTo){
	int DeltaX = (pMoveTo.x - p.x);
	int DeltaY = (pMoveTo.y - p.y);

	TopLeftCorner.x += DeltaX;
	TopLeftCorner.y += DeltaY;

	Point2.x = TopLeftCorner.x + length;
	Point2.y = TopLeftCorner.y + length;

}

bool CSquare::IsFigInsideBorders(int x1, int x2, int y1, int y2) const {
	bool isInside = (TopLeftCorner.x>=x1)&&(TopLeftCorner.y>=y1)
		&&(Point2.x<=x2)&&(Point2.y<=y2);
	return isInside;
}