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
//File: Misc.h
//////////////////////////////////////////////////

#ifndef MISC_H
#define MISC_H

#include<string.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include<iostream>

#include"Pixel.h"
#include"Image.h"
#include"HW_4.h"
#include"Histogram.h"

using namespace std;

void InitImage(Image *pimImage, string strName, int iRows, int iCols, int iColorFormat);
int* K_Means(double **data, int n, int m, int k, double t, double **centroids);
int FindMin(int N, int NW, int NE, int W);

#endif