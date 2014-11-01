//////////////////////////////////////////////////
//EE 569 Homework #4
//
//Date:			December 1st, 2013
//Name:		Shreyansh Dnyanesh Daga
//ID:				6375-3348-33	
//Email:		sdaga@usc.edu
//
//Compiled and build on Visual Studio 2012
//OS: Windows 8
//File: Pixel.cpp
//////////////////////////////////////////////////

#include"Pixel.h"
#include<math.h>

Pixel::Pixel()
{
	this->iB = -1;
	this->iG = -1;
	this->iR = -1;
	this->iBW = -1;

	this->iX = -1;
	this->iY = -1;
}

Pixel::Pixel(int R, int G, int B)
{
	this->iR = R;
	this->iG = G;
	this->iB = B;

	this->iBW = (0.299*R + 0.587*G + B*0.114);

	this->iX = -1;
	this->iY = -1;
}

Pixel::Pixel(int R, int G , int B , int X, int Y)
{
	this->iR = R;
	this->iG = G;
	this->iB = B;	

	this->iBW =  ((0.299*iR + 0.587*iG + 0.114*iB) + 0.5);

	this->iX = X;
	this->iY = Y;
}

Pixel::Pixel(int R, int G, int B, int X, int Y, int Z)
{
	this->iR = R;
	this->iG = G;
	this->iB = B;	

	this->iBW =  ((0.299*iR + 0.587*iG + 0.114*iB) + 0.5);

	this->iX = X;
	this->iY = Y;
	this->iZ = Z;
}

Pixel::Pixel(int BW)
{
	this->iBW = BW;
}

Pixel::Pixel(int BW,int X, int Y, bool bDum)
{
	this->iBW = BW;

	this->iX = X;
	this->iY = Y;
}

Pixel::Pixel(int BW, int X, int Y, int Z, bool bDum)
{
	this->iBW = BW;

	this->iX = X;
	this->iY = Y;
	this->iZ = Z;
}

Pixel::~Pixel()
{
}

int Pixel::GetRed()
{
	return this->iR;
}

int Pixel::GetGreen()
{
	return this->iG;
}

int Pixel::GetBlue()
{
	return this->iB;
}

int Pixel::GetBW()
{
	return this->iBW;
}

int Pixel::GetPixelX()
{
	return this->iX;
}

int Pixel::GetPixelY()
{
	return this->iY;
}

float Pixel::DistanceTo(Pixel pxP)
{
	float fDist;
	int iX1,iX2,iY1,iY2;

	iX1 = this->GetPixelX();
	iX2 = pxP.GetPixelX();
	iY1 = this->GetPixelY();
	iY2 = pxP.GetPixelY();

	fDist = sqrtf(pow((float)(iX2 - iX1),2) + pow((float)(iY2 - iY1),2));

	return fDist;
}

float Pixel::DistanceFrom(Pixel pxP)
{
	float fDist;
	int iX1,iX2,iY1,iY2;

	iX1 = this->GetPixelX();
	iX2 = pxP.GetPixelX();
	iY1 = this->GetPixelY();
	iY2 = pxP.GetPixelY();

	fDist = sqrtf(pow((float)(iX1 - iX2),2) + pow((float)(iY1 - iY2),2));

	return fDist;
}

Pixel Pixel::operator- (Pixel & pxArg)
{
	Pixel pxTemp(this->GetRed() - pxArg.GetRed(),this->GetGreen() - pxArg.GetGreen(),this->GetBlue() - pxArg.GetBlue());

	return pxTemp;
}

bool Pixel::operator==(Pixel &pxArg)
{
	if(this->GetRed() == pxArg.GetRed() && this->GetRed() == pxArg.GetRed() && this->GetRed() == pxArg.GetRed())
		return true;
	else
		return false;
}

Pixel Pixel::operator + (Pixel &pxArg)
{
	Pixel pxTemp(this->GetRed() + pxArg.GetRed(),this->GetGreen() + pxArg.GetGreen(),this->GetBlue() + pxArg.GetBlue());

	return pxTemp;
}

void Pixel::operator = (Pixel &pxArg)
{
	this->iR = pxArg.GetRed();
	this->iG = pxArg.GetGreen();
	this->iB = pxArg.GetBlue();

	this->iBW = pxArg.GetBW();
	this->iX = pxArg.GetPixelX();
	this->iY = pxArg.GetPixelY();
}

Point::Point()
{
	this->iX = 0.00;
	this->iY = 0.00;
	this->iVal = 0.00;
}

void Point::SetPoint(double iX, double iY)
{
	this->iX = iX;
	this->iY = iY;
}

void Point::Cart2Pol(double dXo, double dYo)
{
	double dRad, dTheta;

	if(this->iY == 0.00 && this->iX == 0.50)
	{
		dTheta = 270.00;
		dRad = 0.500;
	}
	else if(this->iY == 1.00 && this->iX == 0.50)
	{
		dTheta = 90.00;
		dRad = 0.50;
	}
	else if(this->iX == 0.00 && this->iY == 0.50)
	{
		dTheta = 180.00;
		dRad = 0.500;
	}
	else if(this->iX == 1.00 && this->iY == 0.50)
	{
		dTheta = 0.00;
		dRad = 0.500;
	}
	else 
	{
		dRad = sqrt((this->iX - dXo)*(this->iX - dXo) + (this->iY - dYo)*(this->iY - dYo));
		dTheta = 2*atan((this->iY - dYo)/((this->iX - dXo) + dRad))*180/3.14159;
	}

	this->iRad = dRad;
	if(dTheta < 0.00)
		dTheta += 360.00;
	this->iTheta = dTheta;
}

void Point::Pol2Cart(double dXo, double dYo)
{
	double dX, dY;

	dX = this->iRad*cos(this->iTheta/180*3.14159) + dXo;
	dY = this->iRad*sin(this->iTheta/180*3.14159) + dYo;

	this->iX = dX;
	this->iY = dY;
}

double Point::FindDistanceFromSq()
{
	double dTheta = this->iTheta;
	double dDist = 0;

	double dSlope = (0.499 - this->iY)/(0.499 - this->iX);
	double dC = (0.499 - dSlope*0.499);

	if(dTheta > 0 && dTheta < 45)
	{		
		double dY = dSlope*1.00 + dC;
		dDist = sqrt(pow(dY - 0.499,2) + pow(1.00 - 0.499,2));
		return dDist;
	}

	if(dTheta > 45 && dTheta < 90)
	{		
		double dX = (1.0 - dC)/dSlope;	
		dDist = sqrt(pow(1.00 - 0.499,2) + pow(dX - 0.499,2));
		return dDist;
	}

	if(dTheta > 90 && dTheta < 135)
	{
		double dX = (1.0 - dC)/dSlope;	
		dDist = sqrt(pow(1.00 - 0.499,2) + pow(dX - 0.499,2));
		return dDist;
	}

	if(dTheta >135 && dTheta < 180)
	{		
		double dY = dSlope*0.00 + dC;
		dDist = sqrt(pow(dY - 0.499,2) + pow(0.00 - 0.499,2));
		return dDist;
	}

	if(dTheta >180 && dTheta < 225)
	{		
		double dY = dSlope*0.00 + dC;
		dDist = sqrt(pow(dY - 0.499,2) + pow(0.00 - 0.499,2));
		return dDist;
	}

	if(dTheta >225 && dTheta <270)
	{
		double dX = (0.0 - dC)/dSlope;	
		dDist = sqrt(pow(1.00 - 0.499,2) + pow(dX - 0.499,2));
		return dDist;
	}

	if(dTheta >270 && dTheta <315)
	{
		double dX = (0.0 - dC)/dSlope;	
		dDist = sqrt(pow(1.00 - 0.499,2) + pow(dX - 0.499,2));
		return dDist;
	}

	if(dTheta >315 && dTheta <360)
	{		
		double dY = dSlope*1.00 + dC;
		dDist = sqrt(pow(dY - 0.499,2) + pow(1.00 - 0.499,2));
		return dDist;
	}	

	if(dTheta == 0 || dTheta == 360 || dTheta == 90 || dTheta == 180 || dTheta == 270)
	{
		dDist = 0.499;
	}

	if(dTheta == 45 || dTheta == 135 || dTheta == 225 ||dTheta == 315)
	{
		dDist =  0.499*1.414;
	}	

	return dDist;
}

Point::Point(double iX, double iY)
{
	this->iX = iX;
	this->iY = iY;
	this->iRad = 0;
	this->iTheta = 0;
	this->iVal = 0.00;
}

Point::Point(double iX, double iY, double iVal)
{
	this->iX = iX;
	this->iY = iY;
	this->iRad = 0;
	this->iTheta = 0;
	this->iVal = iVal;
}

bool Point::LiesWithinTriangle(Point pt1, Point pt2, Point pt3)
{
	double dAlpha, dBeta, dGamma;

	dAlpha = ((pt2.iY - pt3.iY)*(this->iX - pt3.iX) + (pt3.iX - pt2.iX)*(this->iY - pt3.iY))/((pt2.iY - pt3.iY)*(pt1.iX - pt3.iX) + (pt3.iX - pt2.iX)*(pt1.iY - pt3.iY));
	
	dBeta = ((pt3.iY - pt1.iY)*(this->iX - pt3.iX) + (pt1.iX - pt3.iX)*(this->iY - pt3.iY))/((pt2.iY - pt3.iY)*(pt1.iX - pt3.iX) + (pt3.iX - pt2.iX)*(pt1.iY - pt3.iY));
	
	dGamma = 1.0f - dAlpha - dBeta;

	if(dAlpha >= 0.00 && dBeta >= 0.00 && dGamma >= 0.00)
		return true;
	else
		return false;
}

bool Point::LiesWithinTriangle(Point ptaT[3])
{
	Point pt1 = ptaT[0];
	Point pt2 = ptaT[1];
	Point pt3 = ptaT[2];

	double dAlpha, dBeta, dGamma;

	dAlpha = ((pt2.iY - pt3.iY)*(this->iX - pt3.iX) + (pt3.iX - pt2.iX)*(this->iY - pt3.iY))/((pt2.iY - pt3.iY)*(pt1.iX - pt3.iX) + (pt3.iX - pt2.iX)*(pt1.iY - pt3.iY));
	
	dBeta = ((pt3.iY - pt1.iY)*(this->iX - pt3.iX) + (pt1.iX - pt3.iX)*(this->iY - pt3.iY))/((pt2.iY - pt3.iY)*(pt1.iX - pt3.iX) + (pt3.iX - pt2.iX)*(pt1.iY - pt3.iY));
	
	dGamma = 1.0f - dAlpha - dBeta;

	if(dAlpha >= 0.00 && dBeta >= 0.00 && dGamma >= 0.00)
		return true;
	else
		return false;

}

bool Point::LiesWithinQuarterCircle(double dRadius, int iQuadrant)
{
	double dDist;

	dDist = sqrt(pow(this->iX - 0.5,2.0) + pow(this->iY - 0.5,2.0));

	if(dDist <= 0.500)
		return true;
	else
		return false;
}