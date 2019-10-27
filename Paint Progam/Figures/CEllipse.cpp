#include "CEllipse.h"

CEllipse::CEllipse(Point Point1, Point Point2, GfxInfo FigureGfxInfo) :CFigure(FigureGfxInfo)
{
	P1 = Point1;
	P2 = Point2;
}

CEllipse::CEllipse(ifstream &infile):CFigure() {
	Load(infile);
}

void CEllipse::DrawMe(GUI* pGUI) const
{
	if (this->Shown) {
		//Call Output::DrawEllipse to draw a Ellipse on the screen	
		pGUI->DrawEllipse(P1, P2, FigGfxInfo, Selected);
	}
	
}

bool CEllipse::isIn(CFigure* ToCheck)
{
	return 0;
}

bool CEllipse::IsInside(Point P)
{
	bool isin = false;
	double hsq = pow(abs(P2.x - P1.x) / 2.0 , 2); //horizontal axis squared
	horizax = sqrt(hsq);
	double vsq = pow(abs(P2.y - P1.y) / 2.0 , 2); //vertical axis squared
	vertax = sqrt(vsq);
	center.x = (P1.x + P2.x) / 2;
	center.y = (P1.y + P2.y) / 2;

	if (
		(P.x <= (center.x + pow(hsq*(1 - (pow(P.y - center.y, 2) / vsq)),0.5)))
		&& (P.x >= (center.x - pow(hsq*(1 - (pow(P.y - center.y, 2) / vsq)), 0.5)))
		&& (P.y <= (center.y + pow(vsq*(1 - (pow(P.x - center.x, 2) / hsq)), 0.5)))
		&& (P.y >= (center.y - pow(vsq*(1 - (pow(P.x - center.x, 2) / hsq)), 0.5)))
		)
	{ isin = true;}
	return isin;
}
void CEllipse::Save(ofstream &outfile) {
	color DrawColor = FigGfxInfo.DrawClr;

	outfile << "2\t"
		<< ID << "\t"
		<< P1.x << "\t"
		<< P1.y << "\t"
		<< P2.x << "\t"
		<< P2.y << "\t"
		<< int(DrawColor.ucRed) << "\t" << int(DrawColor.ucGreen) << "\t" << int(DrawColor.ucBlue) << "\t";
	if (FigGfxInfo.isFilled) {
		color FillColor = FigGfxInfo.FillClr;
		outfile << int(FillColor.ucRed) << "\t" << int(FillColor.ucGreen) << "\t" << int(FillColor.ucBlue) << "\t";
	}
	else
		outfile << -1 << "\t";
	outfile << FigGfxInfo.BorderWdth << endl;
}

void CEllipse::Load(ifstream &infile) {
	infile >> ID;
	infile >> P1.x
		>> P1.y
		>> P2.x
		>> P2.y;
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

void CEllipse::Resize(double resfactor) {
	double horizax1 = horizax;
	double vertax1 = vertax;
	double area1 = PI*(horizax1)*(vertax1);
	double area2 = area1*resfactor;
	double horizax2 = horizax1*sqrt(area2 / area1);
	double vertax2 = vertax1*sqrt(area2 / area1);
	horizax = horizax2;
	vertax = vertax2;
	if (P2.x < P1.x)
	{
		P2.x = int(- 2 * horizax + P1.x);
	}
	else
	{
		P2.x = int(2 * horizax + P1.x);
	}
	if (P2.y < P1.y)
	{
		P2.y = int(- 2 * vertax + P1.y);
	}
	else
	{
		P2.y = int(2 * vertax + P1.y);
	}
	
}

//1 for square, 2 for ellipse, 3 for hexagon
int CEllipse::GetType() const{
	return 2;
}

string CEllipse::FigureInfo() const {

	double area = PI*horizax*vertax;
	std::string cx = std::to_string(center.x);
	std::string cy = std::to_string(center.y);
	std::string h = std::to_string((int)horizax);
	std::string v = std::to_string((int)vertax);
	std::string id = std::to_string(ID);
	std::string a = std::to_string(area);
	std::string info = "Elipse Selected. Center: (";
	info.append(cx);
	info.append(", ");
	info.append(cy);
	info.append("). Horizontal Axis: ");
	info.append(h);
	info.append(". Vertical Axis: ");
	info.append(v);
	info.append(". Area: ");
	info.append(a);
	info.append(". ID: ");
	info.append(id);

	return info;
}

void CEllipse::MoveFromTo(Point p, Point pMoveTo){

	int DeltaX = (pMoveTo.x - p.x);
	int DeltaY = (pMoveTo.y - p.y);

	P1.x += DeltaX;
	P1.y += DeltaY;
	P2.x += DeltaX;
	P2.y += DeltaY;

}

bool CEllipse::IsFigInsideBorders(int x1, int x2, int y1, int y2) const {
	bool isInside = (P1.x >= x1) && (P1.y >= y1)
		&& (P2.x <= x2) && (P2.y <= y2);
	return isInside;
}