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
//File: Matrix.h
//////////////////////////////////////////////////

#ifndef MATRIX_H
#define MATRIX_H

#include<string.h>
#include<conio.h>
#include<stdlib.h>
#include<iostream>

#include"Pixel.h"
#include"Histogram.h"

using namespace std;

class Matrix
{
	private:
		double **daMat;
		int iM,iN;

	public:
		//Matrix Functions
		Matrix();
		~Matrix();
		void FreeMemory();
		Matrix(int iM, int iN);
		Matrix(int iM);
		void AllocMatrixMem();
		void SetM(int iM);
		void SetN(int iN);	
		void SetElements(double daElems[]);
		void SetElement(int i, int j, double dElem);
		void SetElement(Point ptP, double dElem);
		void SetElement(Point ptP);
		int GetM();
		int GetN();		
		double GetElement(int i, int j);
		double GetElement(Point ptP);
		Matrix* MatrixTranspose();
		double FindDet();
		Matrix GetMinor(int iRow, int iCol);
		void PrintMatrix();
		Matrix* InverseMatrix();

		//Static Functions
		static Matrix* MatrixMultiply(Matrix M1, Matrix M2);
		static Matrix* MatrixAdd(Matrix M1, Matrix M2);
		static Matrix* MatrixSubtract(Matrix M1, Matrix M2);
		static Matrix* IdentityMatrix(int iSize);
		static Matrix* FindMatrixA(Matrix matU, Matrix matV, int iOrder);	
		static Matrix* MergeByRow(Matrix matM1, Matrix matM2);
		static Matrix* MergeByCol(Matrix matM1, Matrix matM2);
};

#endif