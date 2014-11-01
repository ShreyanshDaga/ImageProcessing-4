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
//File: HW_4.cpp
//////////////////////////////////////////////////

#include<stdio.h>
#include<list>
#include<algorithm>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#include<iostream>

using namespace std;

#include"HW_4.h"

void Problem_1_C_b();
void Problem_3_A_b();
void Problem_2_B_b();

int PrintMenu();
void TestFunction();

void main()
{
	int iCh = 0;

	while(1)
	{
		iCh = PrintMenu();			
		switch(iCh)
		{				
			case 1:
				Problem_1_A();				
			break;
		
			case 2:			
				Problem_1_B();					
			break;
		
			case 3:
				Problem_1_C();
				//Problem_1_C_b();
			break;			

			case 4:
				Problem_2_A();
			break;

			case 5:
				Problem_2_B();
			break;

			case 6:
				Problem_2_C();
			break;

			case 7:
				Problem_3_A();
			break;

			case 8:
				Problem_3_B();
			break;

			case 9:
				Problem_3_C();
			break;

			case 10:
				exit(0);
			break;

			case 0:
				TestFunction();
		}
	}
}

int PrintMenu()
{
	int iCh = 0;

	while(1)
	{
		system("CLS");		
		cout<<"\t\t\t\t\t\tShreyansh Daga, USCID 6375334833\n";
		cout<<"******* Home work 4 ********\n";		
		cout<<"*Problem 1:Face Warping\n";
		cout<<"1.\tQ1(a) Back to Baby\n";
		cout<<"2.\tQ1(b) Face Morphing\n";
		cout<<"3.\tQ1(c) Advanced Morphing: From Bruce Banner to Hulk\n\n";		
		cout<<"*Problem 2:Optical Charachter Recognition\n";
		cout<<"4.\tQ2(a) OCR Segmentation and Training\n";
		cout<<"5.\tQ2(b) OCR Testing\n";
		cout<<"6.\tQ2(c) OCR Testing on \"Restaurant\" bill \n\n";
		cout<<"*Problem 3:Image Segmentation\n";
		cout<<"7.\tQ3(a) Image Segmentation using K-means\n";
		cout<<"8.\tQ3(b) Image Segmentation using mean shift filtering\n";
		cout<<"9.\tQ3(c) Image Segmentation using mean shift clustering\n";
		cout<<"10.\tExit\n";
		cout<<"0.\tTestFunction\n";
		cout<<"\n Enter your choice: ";
		cin>>iCh;

		if(iCh > 13)
		{
			cout<<"\n\n!! Please enter valid choice !!\n\n";
			getch();
			iCh = 0;
		}
		else
		{
			break;
		}
	}
	return iCh;
}

void TestFunction()
{
	list<int> l1[4];

	l1[0].push_back(1);
	l1[0].push_back(2);
	l1[0].push_back(2);

	l1[1].push_back(2);
	l1[1].push_back(3);
	l1[1].push_back(3);

	l1[2].push_back(1);
	l1[2].push_back(2);
	l1[2].push_back(3);
	
}