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
//File: Pixel.h	
//////////////////////////////////////////////////

#ifndef PIXEL_H
#define PIXEL_H

class Pixel
{
	public:
		int iR;
		int iG;
		int iB;
		int iBW;			//GreyLevel
		int iX;
		int iY;
		int iZ;

	public:
		Pixel();
		Pixel(int R, int G, int B);
		Pixel(int R, int G, int B, int X, int Y);
		Pixel(int R, int G, int B, int X, int Y, int Z);
		Pixel(int iBW);
		Pixel(int iBW, int X, int Y, bool bDum);
		Pixel(int iBW, int X, int Y, int Z, bool bDum);
		~Pixel();
		int GetRed();
		int GetBlue();
		int GetGreen();
		int GetBW();
		int GetPixelX();
		int GetPixelY();
		float DistanceTo(Pixel pxP);
		float DistanceFrom(Pixel pxP);	

		Pixel operator - (Pixel &pxArg);
		Pixel operator + (Pixel &pxArg);
		void operator = (Pixel &pxArg);
		bool operator == (Pixel &pxArg);
};

class Point
{
	public:
		double iX;
		double iY;		
		double iRad;
		double iTheta;
		double iVal;

	public:
		Point();
		Point(double iX, double iY);
		Point(double iX, double iY, double iVal);
		void SetPoint(double iX, double iY);
		void Cart2Pol(double dXo, double dYo);
		void Pol2Cart(double dXo, double dYo);
		double FindDistanceFromSq();
		bool LiesWithinTriangle(Point pt1, Point pt2, Point pt3);
		bool LiesWithinTriangle(Point ptaT[3]);
		bool LiesWithinQuarterCircle(double dRadius, int iQuadrant);
};

#endif