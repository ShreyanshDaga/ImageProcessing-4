//////////////////////////////////////////////////
//EE 569 Homework #3
//
//Date:			November 3, 2013
//Name:		Shreyansh Dnyanesh Daga
//ID:				6375-3348-33	
//Email:		sdaga@usc.edu
//
//Compiled and build on Visual Studio 2012
//OS: Windows 8
//File: Feature.cpp	
//////////////////////////////////////////////////
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
//File Name: Feature.cpp
////////////////////////////////////////////////

#include"Image.h"
#include"HW_4.h"
#include"Feature.h"

Feature::Feature()
{
	this->iEuler = 0;
	this->dArea = 0;
	this->dPeri = 0;
	this->dCirc = 0;
	this->ptCen.iX = 0;
	this->ptCen.iY = 0;
	this->dAS = 0;
	this->dHSym = 0;
	this->dVSym = 0;
	this->iCols = 0;
	this->iRows = 0;
}