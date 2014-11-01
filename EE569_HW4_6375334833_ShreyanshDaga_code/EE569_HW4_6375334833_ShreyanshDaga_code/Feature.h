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
//File: Feature.h
//////////////////////////////////////////////////

#ifndef FEATURE_H
#define FEATURE_H

#include<string.h>
#include<conio.h>
#include<stdlib.h>
#include<iostream>

#include"Pixel.h"


class Feature
{
	public:
		int iEuler;
		double dArea;
		double dPeri;
		double dCirc;
		double dAS;
		double dVSym;
		double dHSym;
		int iRows;
		int iCols;
		Point ptCen;
		int iLabel;
		int iHCut;
		int iVCut;

		Feature();
};

#endif