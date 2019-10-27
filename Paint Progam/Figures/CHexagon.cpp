#include "CHexagon.h"

CHexagon::CHexagon(Point P1, Point P2, GfxInfo FigureGfxInfo) :CFigure(FigureGfxInfo)
{
	center = P1;
	end = P2;
	radius = sqrt(pow((P2.x - P1.x), 2) + pow((P2.y - P1.y), 2));
}

CHexagon::CHexagon(ifstream &infile) :CFigure() {
	Load(infile);
}
void CHexagon::DrawMe(GUI* pGUI) const
{
	if (this->Shown) {
		//Call Output::DrawHex to draw a Hexagon on the screen	 ///make get points 
		int *ppts6x = gethexpointsx(center, end);
		int *ppts6y = gethexpointsy(center, end);
		pGUI->DrawHex(ppts6x, ppts6y, FigGfxInfo, Selected);
	}
}

int ipY[6];
int ipX[6];

int* CHexagon::gethexpointsy(Point P1, Point P2) const
{
	ipY[0] = int(radius * sin(2 * PI * 0 / iVertices) + P1.y);
	ipY[1] = int(radius * sin(2 * PI * 1 / iVertices) + P1.y);
	ipY[2] = int(radius * sin(2 * PI * 2 / iVertices) + P1.y);
	ipY[3] = int(radius * sin(2 * PI * 3 / iVertices) + P1.y);
	ipY[4] = int(radius * sin(2 * PI * 4 / iVertices) + P1.y);
	ipY[5] = int(radius * sin(2 * PI * 5 / iVertices) + P1.y);
	//ipY[6] = { pt1y, pt2y, pt3y, pt4y, pt5y, pt6y };
	//int* ppts6y;
	//ppts6y = ipY;
	//return ppts6y;
	return ipY;
}

int* CHexagon::gethexpointsx(Point P1, Point P2) const
{
	ipX[0] = int(radius * cos(2 * PI * 0 / iVertices) + P1.x);
	ipX[1] = int(radius * cos(2 * PI * 1 / iVertices) + P1.x);
	ipX[2] = int(radius * cos(2 * PI * 2 / iVertices) + P1.x);
	ipX[3] = int(radius * cos(2 * PI * 3 / iVertices) + P1.x);
	ipX[4] = int(radius * cos(2 * PI * 4 / iVertices) + P1.x);
	ipX[5] = int(radius * cos(2 * PI * 5 / iVertices) + P1.x);
	//int ipX[6] = { pt1x, pt2x, pt3x, pt4x, pt5x, pt6x };
	//int* ppts6x;
	//ppts6x = ipX;
	//return ppts6x;
	return ipX;
}


bool CHexagon::IsInside(Point P)
{
	bool isin = false;
	int* ipY = new int[6];
	int* ipX = new int[6];
	ipY = gethexpointsy(center, end);
	ipX = gethexpointsx(center, end);

	double m23, m34, m01, m05;
	double c23, c34, c01, c05;
	m23 = double(ipY[3] - ipY[4]) / double(ipX[3] - ipX[4]);
	m34 = double(ipY[2] - ipY[3]) / double(ipX[2] - ipX[3]);
	m01 = double(ipY[5] - ipY[0]) / double(ipX[5] - ipX[0]);
	m05 = double(ipY[1] - ipY[0]) / double(ipX[1] - ipX[0]);

	c23 = ipY[4] - m23 * ipX[4];
	c34 = ipY[3] - m34 * ipX[3];
	c01 = ipY[5] - m01 * ipX[5];
	c05 = ipY[1] - m05 * ipX[1];



	if (
		((P.y < ipY[0]) && (P.y > ipY[5]) && (P.x < (P.y - c01) / m01) && (P.x >(P.y - c23) / m23)) || ((P.y < ipY[1]) && (P.y > ipY[0]) && (P.x > (P.y - c34) / m34) && (P.x < (P.y - c05) / m05))
		)
	{
		isin = true;
	}
	return isin;
}

void CHexagon::Save(ofstream &outfile) {
	color DrawColor = FigGfxInfo.DrawClr;

	outfile << "3\t"
		<< ID << "\t"
		<< center.x << "\t"
		<< center.y << "\t"
		<< end.x << "\t"
		<< end.y << "\t"
		<< int(DrawColor.ucRed) << "\t" << int(DrawColor.ucGreen) << "\t" << int(DrawColor.ucBlue) << "\t";
	if (FigGfxInfo.isFilled) {
		color FillColor = FigGfxInfo.FillClr;
		outfile << int(FillColor.ucRed) << "\t" << int(FillColor.ucGreen) << "\t" << int(FillColor.ucBlue) << "\t";
	}
	else
	{
		outfile << -1 << "\t";
	}
	outfile << FigGfxInfo.BorderWdth << endl;
}

void CHexagon::Load(ifstream &infile) {
	infile >> ID;
	infile >> center.x
		>> center.y
		>> end.x
		>> end.y;
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
	radius = sqrt(pow((center.x - end.x), 2) + pow((center.y - end.y), 2));
}


void CHexagon::Resize(double resfactor) {
	double radius1 = radius;
	double area1 = PI*pow(radius1, 2);
	double area2 = resfactor*area1;
	double radius2 = sqrt((pow(radius1,2)*area2)/area1);
	end.x = int(end.x*radius2 / radius1);
	end.y = int(end.y*radius2 / radius1);
	radius = radius2;
}

//1 for square, 2 for ellipse, 3 for hexagon
int CHexagon::GetType() const{
	return 3;
}

string CHexagon::FigureInfo() const {

	int area = int(6*0.5*radius*radius*sin(PI/3));
	std::string cx = std::to_string(center.x);
	std::string cy = std::to_string(center.y);
	std::string r = std::to_string(radius);
	std::string id = std::to_string(ID);
	std::string a = std::to_string(area);
	std::string info = "Hexagon Selected. Center: (";
	info.append(cx);
	info.append(", ");
	info.append(cy);
	info.append("). Radius: ");
	info.append(r);
	info.append(". Area: ");
	info.append(a);
	info.append(". ID: ");
	info.append(id);

	return info;
}

void CHexagon::MoveFromTo(Point p, Point pMoveTo){

	int DeltaX = (pMoveTo.x - p.x);
	int DeltaY = (pMoveTo.y - p.y);

	center.x += DeltaX;
	center.y += DeltaY;
	end.x += DeltaX;
	end.y += DeltaY;

}

bool CHexagon::IsFigInsideBorders(int x1, int x2, int y1, int y2) const {
	int* ipY = new int[6];
	int* ipX = new int[6];
	ipY = gethexpointsy(center, end);
	ipX = gethexpointsx(center, end);
	bool isInside = (ipX[3] >= x1) && (ipX[0] <= x2) && (ipY[5] >= y1) && (ipY[1]<=y2);
	return isInside;
}