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
//File: LabelTable.h
//////////////////////////////////////////////////

#ifndef LABEL_H
#define LABEL_H

class LabelTable
{
	public:
		double dR,dG,dB;
		int iCount;
		int iLabel;

	LabelTable();
	LabelTable(double dR, double dG, double dB, int iCount, int iLabel);

	int GetLabelCount();
	int GetLabel();
	double GetR();
	double GetG();
	double GetB();
};

#endif;