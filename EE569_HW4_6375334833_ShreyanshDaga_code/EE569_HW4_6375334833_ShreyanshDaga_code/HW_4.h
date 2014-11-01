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
//File: HW_4.h
//////////////////////////////////////////////////

#ifndef HW_3_H
#define HW_3_H

#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<iostream>

#include"HW_4.h"
#include"Pixel.h"
#include"Image.h"
#include"Histogram.h"
#include"Misc.h"
#include"Feature.h";
#include"LabelTable.h";

int PrintMenu();

void Problem_1_A();		
void Problem_1_B();		
void Problem_1_C();		

void Problem_2_A();
void Problem_2_B();
void Problem_2_C();

void Problem_3_A();
void Problem_3_B();
void Problem_3_C();

//Matrix Functions Used from 
void MatrixInversion(double **A, int order, double **Y);
int GetMinor(double **src, double **dest, int row, int col, int order);
double CalcDeterminant( double **mat, int order);

#endif