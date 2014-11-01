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
//File: LabelTable.cpp
//////////////////////////////////////////////////

#include"LabelTable.h"

LabelTable::LabelTable()
{
	this->dR = 0;
	this->dG =0;
	this->dB = 0;

	this->iCount = 0;
}

LabelTable::LabelTable(double dR1, double dG1, double dB1, int iCount, int iLabel)
{
	this->dR = dR1;
	this->dG = dG1;
	this->dB = dB1;

	this->iCount = iCount;
	this->iLabel = iLabel;
}

int LabelTable::GetLabelCount()
{
	return this->iCount;
}

int LabelTable::GetLabel()
{
	return this->iLabel;
}

double LabelTable::GetR()
{
	return this->dR;
}

double LabelTable::GetG()
{
	return this->dG;
}

double LabelTable::GetB()
{
	return this->dB;
}