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
//File: Image.h	
//////////////////////////////////////////////////

#ifndef IMAGE_H
#define IMAGE_H

#include<string.h>
#include<conio.h>
#include<stdlib.h>
#include<iostream>

#include"Pixel.h"
#include"Histogram.h"

using namespace std;

class Image
{
	public:		
		int iPixelCount;
		Histogram hHist;

	private:		
		unsigned char **pImageDate;
		int iRows;
		int iCols;
		int iColorFormat;
		string szImageName;		

	public:
		Image();
		~Image();
		Image(string ImageName, int Rows, int Cols, int ColorFormat);
		string GetImageName();		
		int GetImageRows();
		int GetImageCols();
		int GetImageColorFormat();
		void SetImageRows(int iRows);
		void SetImageCols(int iCols);
		void SetImageColorFormat(int iColorFormat);
		void SetImageName(string szName);
		void SetPixel(int X,int Y, Pixel pxP);
		void DrawLine(int X1, int Y1, int X2, int Y2, Pixel pxP);
		Pixel* GetPixel(int X, int Y);
		Pixel* GetPixel(int X, int Y, int Z);
		Pixel* GetPixel(double dX, double dY);
		Pixel* GetNBPixel(Pixel pxP, int idX, int idY);
		int GetBW(int X, int Y);
		int GetRed(int X, int Y);
		int GetGreen(int X, int Y);
		int GetBlue(int X, int Y);
		void ReadImageInfo();
		void WriteImageData();
		void ReadImageData();
		void AllocImageMem();
		void PlotHistogram();
		void PlotCumHistogram();
		void FreeResources();
		Image* ImageExtend(int iSize);
		Image* Convert2RGB();
		Image* Convert2Gray();
		Image* Convert2YUV();
		Image* Convert2YCrCb();
		Image* Convert2Bin(int iThresh);
		void Convert2BMP();
		int** GetIntArray();
		double** GetDoubleArray(bool bIsNormalised);
		void SetIntArray(int **piaImage);
		void SetDoubleArray(double **piaImage, bool bIsNormalised);
		void FillColor(unsigned char cCol);
};

#endif