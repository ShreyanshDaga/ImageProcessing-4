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
//File: Problem_2.cpp
//////////////////////////////////////////////////

#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include<iostream>
#include<list>
#include<algorithm>
#include<fstream>

#include"HW_4.h"
#include"Pixel.h"
#include"Image.h"
#include"Misc.h"
#include"Histogram.h"
#include"Matrix.h";

using namespace std;

int** SegmentCharachters(Image *pimBin, list<int> *plistLabels);
Image* ExtractCharachter(int **iaLabels,int iRows, int iCols, int iLabel);
Feature* ComputeFeatures(Image *pimCharachter);
int CompareBitQuad_Q0(int iaWin[2][2]);
int CompareBitQuad_Q1(int iaWin[2][2]);
int CompareBitQuad_Q2(int iaWin[2][2]);
int CompareBitQuad_Q3(int iaWin[2][2]);
int CompareBitQuad_Q4(int iaWin[2][2]);
int CompareBitQuad_QD(int iaWin[2][2]);
char DecisionTreeChar(Image *pimChar);
char DecisionTreeInt(Image *pimChar);
void WriteFeatureFile(Feature **pfFeatureSet, int iNum, char strFileName[30]);

Feature *pTrain[29];

void Problem_2_A()
{
	string strName("training-bill.raw");
	Image imTrainingBill(strName,300,600,3), *pimGray, *pimBin;
	int iThresh, iRows = 300, iCols = 600;

	imTrainingBill.AllocImageMem();
	imTrainingBill.ReadImageData();
	
	pimGray = imTrainingBill.Convert2Gray();

	pimGray->WriteImageData();
	pimGray->PlotHistogram();

	cout<<"\n Enter Threshold for Binary Conversion: ";
	cin>>iThresh;

	pimBin = pimGray->Convert2Bin(iThresh);

	pimBin->WriteImageData();

	//Charachter Segmentation
	int **iaLabels, iLabelCount;
	list<int> plistLabels;

	cout<<"\n* Segmenting Training Charachters..";
	iaLabels = SegmentCharachters(pimBin,&plistLabels);

	//Paint Labeled Image
	for(int i = 0;i<iRows;i++)
	{
		for(int j = 0;j<iCols;j++)
		{
			Pixel pxP;

			if(iaLabels[i][j] == 0)
			{
				pxP.iBW = (255);
			}
			else
			{
				pxP.iBW = (iaLabels[i][j]);
			}

			pimGray->SetPixel(i,j,pxP);
		}
	}

	cout<<"\n Labelled Image: ";
	pimGray->WriteImageData();

	//Charachter Seperation
	cout<<"\n* Extracting Charachters..";
	int i = 1;
	Image *pimCharachter[29];
	int iaLabelArr[29];

	for(list<int>::iterator it = plistLabels.begin();it != plistLabels.end();++it)
	{
		int iLabel = *it;		
		
		pimCharachter[i-1] = ExtractCharachter(iaLabels, 300, 600, iLabel);
		iaLabelArr[i-1] = iLabel;

		string strName;
		char szName[30];
		sprintf(szName,"Character_%d.raw",i);		
		strName = string::basic_string(szName);
		pimCharachter[i-1]->SetImageName(strName);

		pimCharachter[i-1]->WriteImageData();
		i++;				
	}

	cout<<"\n*Total Number of Charachters in Training image: "<<i-1;

	//Features
	//Feature *dfFeatures[29];
	for(int j = 0;j<i-1;j++)
	{
		pTrain[j] =  ComputeFeatures(pimCharachter[j]);
		pTrain[j]->iLabel = iaLabelArr[j];
	}
	
	//CSV File
	WriteFeatureFile(pTrain,i,"P2A_Training.csv");

	cout<<"\n Press 'C' to continue..";
	getch();
}

void Problem_2_B()
{
	string strName("testOCR-bill1.raw");
	Image imTrainingBill(strName,82,272,3), *pimGray, *pimBin;
	int iThresh, iRows = 82, iCols = 272;

	imTrainingBill.AllocImageMem();
	imTrainingBill.ReadImageData();
	
	pimGray = imTrainingBill.Convert2Gray();

	pimGray->WriteImageData();
	pimGray->PlotHistogram();

	cout<<"\n Enter Threshold for Binary Conversion: ";
	cin>>iThresh;

	pimBin = pimGray->Convert2Bin(iThresh);

	pimBin->WriteImageData();

	//Charachter Segmentation
	int **iaLabels, iLabelCount;
	list<int> plistLabels;

	cout<<"\n* Segmenting Test Charachters..";
	iaLabels = SegmentCharachters(pimBin,&plistLabels);

	//Paint Labeled Image
	for(int i = 0;i<iRows;i++)
	{
		for(int j = 0;j<iCols;j++)
		{
			Pixel pxP;

			if(iaLabels[i][j] == 0)
			{
				pxP.iBW = (255);
			}
			else
			{
				pxP.iBW = (iaLabels[i][j]);
			}

			pimGray->SetPixel(i,j,pxP);
		}
	}

	pimGray->WriteImageData();

	//Charachter Seperation
	cout<<"\n* Extracting Test Charachters..";
	int i = 1;
	Image *pimCharachter[60];
	int *iaLabelArr = new int[60];

	for(list<int>::iterator it = plistLabels.begin();it != plistLabels.end();++it)
	{
		int iLabel = *it;		
		
		pimCharachter[i-1] = ExtractCharachter(iaLabels, iRows, iCols, iLabel);
		iaLabelArr[i-1] = iLabel;

		string strName;
		char szName[30];
		sprintf(szName,"Test_1Char_%d.raw",i);		
		strName = string::basic_string(szName);
		pimCharachter[i-1]->SetImageName(strName);

		pimCharachter[i-1]->WriteImageData();
		i++;				
	}

	cout<<"\n*Total Number of Charachters in Test1 image: "<<i-1;

	//Features
	Feature *dfFeatures[60];
	for(int j = 0;j<i-1;j++)
	{
		dfFeatures[j] =  ComputeFeatures(pimCharachter[j]);
		dfFeatures[j]->iLabel = iaLabelArr[j];
	}

	//CSV File
	WriteFeatureFile(dfFeatures,i-1,"P2A_FeatureSet_test1.csv");

	//Identify T and L
	char cT;
	bool fT = false;
	bool fL = false;
	bool fO = false;
	Image *pimChar;
	int iXmin,iXmax,iYmin,iYmax;
	list<int> pLabelList;
	bool bDone = false;

	for(int i = 0;i<iRows;i++)
	{
		for(int j = 0;j<iCols;j++)
		{
			int iCurrLabel = iaLabels[i][j];
			if(iCurrLabel == 0)
				continue;

			//if label done before
			for(list<int>::iterator it1 = pLabelList.begin();it1 != pLabelList.end();it1++)
			{
				if(*it1 == iCurrLabel)
				{
					bDone = true;
					break;
				}
			}

			if(bDone == true)
			{
				bDone = false;
				continue;
			}
			else
			{
				pLabelList.push_back(iCurrLabel);
			}

			pimChar = ExtractCharachter(iaLabels, iRows, iCols, iCurrLabel);
			
			cT = DecisionTreeChar(pimChar);
			
			if(cT == 'T')
			{
				cout<<"T("<<iCurrLabel<<") ";
				fT = true;
			}
			if(cT == 'O')
			{
				cout<<"O("<<iCurrLabel<<") ";
				fO = true;
			}

			if(cT == 'L')
			{
				cout<<"L("<<iCurrLabel<<") ";
				fL = true;
			}

			if(( fL && fT && fO) == true)
			{
				iXmin = i - 2;
				iYmin = j+ pimChar->GetImageCols() + 1;

				iXmax = iXmin + pimChar->GetImageRows() + 2;				

				break;
			}
		}
		if(( fL && fT && fO) == true)
		{
			break;
		}
	}

	cout<<"\n*Ammount:\n";
	pLabelList.clear();

	for(int i = iXmin;i<iXmax;i++)
	{
		for(int j = iYmin;j<iCols;j++)
		{
			int iCurrLabel = iaLabels[i][j];

			if(iCurrLabel == 0)
				continue;

			//Check for repeat label
			for(list<int>::iterator it1 = pLabelList.begin();it1 != pLabelList.end();it1++)
			{
				if(*it1 == iCurrLabel)
				{
					bDone = true;
					break;
				}
			}

			if(bDone == true)
			{
				bDone = false;
				continue;
			}
			else
			{
				pLabelList.push_back(iCurrLabel);
			}

			pimChar = ExtractCharachter(iaLabels, iRows, iCols, iCurrLabel);
			
			cT = DecisionTreeInt(pimChar);
			
			if(cT == '\n')
				continue;

			cout<<cT<<"("<<iCurrLabel<<")";
		}
	}

	cout<<"\n Press 'C' to continue..";
	getch();
}

void Problem_2_B_b()
{
	string strName("testOCR-bill2.raw");
	Image imTrainingBill(strName,316,901,3), *pimGray, *pimBin;
	int iThresh, iRows = 316, iCols = 901;

	cout<<"\n\n ** ** ** ** ** ** ** ** ** ** ** ** **\n";
	cout<<"\n Test IMage 2: \n";	

	imTrainingBill.AllocImageMem();
	imTrainingBill.ReadImageData();
	
	pimGray = imTrainingBill.Convert2Gray();

	pimGray->WriteImageData();
	pimGray->PlotHistogram();
		
	cout<<"\n Enter Threshold for Binary Conversion: ";
	cin>>iThresh;

	pimBin = pimGray->Convert2Bin(iThresh);

	pimBin->WriteImageData();

	//Charachter Segmentation
	int **iaLabels, iLabelCount;
	list<int> plistLabels;

	cout<<"\n* Segmenting Test Charachters..";
	iaLabels = SegmentCharachters(pimBin,&plistLabels);

	//Paint Labeled Image
	for(int i = 0;i<iRows;i++)
	{
		for(int j = 0;j<iCols;j++)
		{
			Pixel pxP;

			if(iaLabels[i][j] == 0)
			{
				pxP.iBW = (255);
			}
			else
			{
				pxP.iBW = (iaLabels[i][j]);
			}

			pimGray->SetPixel(i,j,pxP);
		}
	}

	pimGray->WriteImageData();

	//Charachter Seperation
	
	cout<<"\n* Extracting Test Charachters..";
	int i = 1;
	Image *pimCharachter[60];
	int *iaLabelArr = new int[60];

	for(list<int>::iterator it = plistLabels.begin();it != plistLabels.end();++it)
	{
		int iLabel = *it;		
		
		pimCharachter[i-1] = ExtractCharachter(iaLabels, iRows, iCols, iLabel);
		iaLabelArr[i-1] = iLabel;

		string strName;
		char szName[30];
		sprintf(szName,"Test_2Char_%d.raw",i);		
		strName = string::basic_string(szName);
		pimCharachter[i-1]->SetImageName(strName);

		pimCharachter[i-1]->WriteImageData();
		i++;				
	}

	cout<<"\n*Total Number of Charachters in Test2 image: "<<i-1;

	//Features
	Feature *dfFeatures[60];
	for(int j = 0;j<i-1;j++)
	{
		dfFeatures[j] =  ComputeFeatures(pimCharachter[j]);
		dfFeatures[j]->iLabel = iaLabelArr[j];
	}

	//CSV File
	WriteFeatureFile(dfFeatures,i-1,"P2A_FeatureSet_test1.csv");

	//Identify T and L
	char cT;
	bool fT = false;
	bool fL = false;
	bool fO = false;
	Image *pimChar;
	int iXmin,iXmax,iYmin,iYmax;
	list<int> pLabelList;
	bool bDone = false;

	for(int i = 0;i<iRows;i++)
	{
		for(int j = 0;j<iCols;j++)
		{
			int iCurrLabel = iaLabels[i][j];
			if(iCurrLabel == 0)
				continue;

			//if label done before
			for(list<int>::iterator it1 = pLabelList.begin();it1 != pLabelList.end();it1++)
			{
				if(*it1 == iCurrLabel)
				{
					bDone = true;
					break;
				}
			}

			if(bDone == true)
			{
				bDone = false;
				continue;
			}
			else
			{
				pLabelList.push_back(iCurrLabel);
			}

			pimChar = ExtractCharachter(iaLabels, iRows, iCols, iCurrLabel);
			
			cT = DecisionTreeChar(pimChar);
			
			if(cT == 'T')
			{
				cout<<"T("<<iCurrLabel<<") ";
				fT = true;
			}
			if(cT == 'O')
			{
				cout<<"O ";
				fO = true;
			}

			if(cT == 'L')
			{
				cout<<"L("<<iCurrLabel<<") ";
				fL = true;
			}

			if(( fL && fT && fO) == true)
			{
				iXmin = i - 2;
				iYmin = j+ pimChar->GetImageCols() + 1;

				iXmax = iXmin + pimChar->GetImageRows() + 2;				

				break;
			}
		}
		if(( fL && fT && fO) == true)
		{
			break;
		}
	}

	cout<<"\n*Ammount:\n";
	pLabelList.clear();

	for(int i = iXmin;i<iXmax;i++)
	{
		for(int j = iYmin;j<iCols;j++)
		{
			int iCurrLabel = iaLabels[i][j];

			if(iCurrLabel == 0)
				continue;

			//Check for repeat label
			for(list<int>::iterator it1 = pLabelList.begin();it1 != pLabelList.end();it1++)
			{
				if(*it1 == iCurrLabel)
				{
					bDone = true;
					break;
				}
			}

			if(bDone == true)
			{
				bDone = false;
				continue;
			}
			else
			{
				pLabelList.push_back(iCurrLabel);
			}

			pimChar = ExtractCharachter(iaLabels, iRows, iCols, iCurrLabel);
			
			cT = DecisionTreeInt(pimChar);
			
			if(cT == '\n')
				continue;

			cout<<cT<<"("<<iCurrLabel<<")";
		}
	}

	cout<<"\n Press 'C' to continue..";
	getch();
}

void Problem_2_C()
{
	cout<<"\n Press 'C' to continue..";
	getch();
}

int** SegmentCharachters(Image *pimBin, list<int> *plistLabels)
{
	int iRows = pimBin->GetImageRows();
	int iCols = pimBin->GetImageCols();

	//Charachter Segmentation
	int **iaLabels = new int*[iRows];
	int **iaBinIm = new int*[iRows];
	for(int i = 0;i<iRows;i++)
	{
		iaLabels[i] = new int[iCols];
		iaBinIm[i] = new int[iCols];
	}

	//Init Labels
	Pixel *pxP;
	for(int i = 0;i<iRows;i++)
	{
		for(int j = 0;j<iCols;j++)
		{
			iaLabels[i][j] = 0;
			pxP = pimBin->GetPixel(i,j);
			if(pxP->GetBW() == 0)	//If Foregound
				iaBinIm[i][j] = 1;
			else
				iaBinIm[i][j] = 0;

			delete pxP;
		}
	}

	int iLabel = 1;	
	list<int> listEqList[300];	//Equvivalence List

	for(int i = 1;i<iRows;i++)
	{
		for(int j = 1;j<iCols;j++)
		{
			//cout<<"\n "<<i<<"  "<<j;
			if(iaBinIm[i][j] == 1)
			{
				//Check 4 neighbours
				int NW = iaLabels[i-1][j-1];
				int N = iaLabels[i-1][j];
				int NE = iaLabels[i-1][j+1];
				int W = iaLabels[i][j-1];

				if((W == 0) && (NW == 0) && (N == 0) && (NE == 0))
				{
					iaLabels[i][j] = iLabel;
					listEqList[iLabel].push_back(iLabel);					
					iLabel++;
					//cout<<"\n label: "<<iLabel;
				}
				else
				{
					int L = FindMin(NW, N , NE, W);
					
					iaLabels[i][j] = L;
										
					if(L != NW && NW != 0)
					{
						listEqList[L].push_back(NW);
						listEqList[NW].push_back(L);

						listEqList[NW].sort();						
						listEqList[NW].unique();
					}
					if(L != NE && NE != 0)
					{
						listEqList[L].push_back(NE);
						listEqList[NE].push_back(L);
						
						listEqList[NE].sort();						
						listEqList[NE].unique();
					}
					if(L != N && N != 0)
					{
						listEqList[L].push_back(N);
						listEqList[N].push_back(L);
						
						listEqList[N].sort();						
						listEqList[N].unique();
					}
					if(L != W && W != 0)
					{
						listEqList[L].push_back(W);
						listEqList[W].push_back(L);
						
						listEqList[W].sort();						
						listEqList[W].unique();
					}

					listEqList[L].sort();
					listEqList[L].unique();
				}
			}
		}
	}

	for(int i = 1;i<iLabel;i++)
	{
		list<int>::iterator it = listEqList[i].begin();
		
		for(it;it != listEqList[i].end();++it)
		{
			if(*it == i)
				continue;

			list<int>::iterator it1 = listEqList[*it].begin();
			for(it1;it1 != listEqList[*it].end();++it1)
			{
				if(*it1 == i)
					continue;
				listEqList[i].push_back(*it1);
				listEqList[i].sort();
				listEqList[i].unique();
			}			
		}
		listEqList[i].sort();
		listEqList[i].unique();
	}

	//Again
	for(int i = 1;i<iLabel;i++)
	{
		list<int>::iterator it = listEqList[i].begin();
		
		for(it;it != listEqList[i].end();++it)
		{
			if(*it == i)
				continue;

			list<int>::iterator it1 = listEqList[*it].begin();
			for(it1;it1 != listEqList[*it].end();++it1)
			{
				if(*it1 == i)
					continue;
				listEqList[i].push_back(*it1);
				listEqList[i].sort();
				listEqList[i].unique();
			}			
		}
		listEqList[i].sort();
		listEqList[i].unique();
	}

	list<int> labels;
	//Second Pass
	for(int i = 1;i<iRows;i++)
	{
		for(int j = 1;j<iCols;j++)
		{
			int id = iaLabels[i][j];
			
			if(id == 0)			
				continue;			
			
			//listEqList[id].sort();
			list<int>::iterator it = listEqList[id].begin();
			iaLabels[i][j] = *it;
			plistLabels->push_back(*it);
		}

		plistLabels->sort();
		plistLabels->unique();
	}

	plistLabels->sort();
	plistLabels->unique();

	int iLabelNumb = 1;
	
	for(int i = 0;i<iRows;i++)
	{
		for(int j = 0;j<iCols;j++)
		{
			if(iaLabels[i][j] == 0)
				continue;			
					
		}
	}

	//for(int i = 0;i<iRows;i++)
	//{
	//	for(int j = 0;j<iCols;j++)
	//	{
	//		if(iaLabels[i][j] == 0)
	//		{
	//			pimBin->SetPixel(i,j,*(new Pixel(255)));
	//		}
	//		else
	//		{
	//			pimBin->SetPixel(i,j,*(new Pixel(iaLabels[i][j])));
	//		}
	//	}
	//}

	//Free Memory
	for(int i = 0;i<iRows;i++)
		delete [] iaBinIm[i];


	delete [] iaBinIm;

	//*plistLabels = labels;
	return iaLabels;
}

Image* ExtractCharachter(int **iaLabels, int iRows, int iCols, int iLabel)
{
	Image *pImage = new Image();

	int iXmax = 0, iYmax = 0, iXmin = iRows, iYmin = iCols;

	for(int i = 0;i<iRows;i++)
	{
		for(int j = 0;j<iCols;j++)
		{
			if(iaLabels[i][j] == iLabel)
			{
				if(iXmax < i)
					iXmax = i;
				if(iXmin > i)
					iXmin = i;

				if(iYmax < j)
					iYmax = j;
				if(iYmin > j)
					iYmin = j;
			}
		}
	}

	int icRows = iXmax - iXmin + 1, icCols = iYmax - iYmin + 1;

	InitImage(pImage,string::basic_string(""),icRows+2, icCols+2,1);

	for(int i = 0;i<icRows+2;i++)
	{
		for(int j = 0;j<icCols+2;j++)
		{
			Pixel pxPW(255);

			pImage->SetPixel(i,j,pxPW);
		}
	}
	
	for(int i = iXmin-1;i<=iXmax+1;i++)
	{
		for(int j = iYmin-1;j<=iYmax+1;j++)
		{
			Pixel pxPB(0);
			Pixel pxPW(255);

			if(iaLabels[i][j] == iLabel)
				pImage->SetPixel(i - (iXmin - 1),j - (iYmin - 1), pxPB);	
			else
				pImage->SetPixel(i - (iXmin - 1),j - (iYmin - 1), pxPW);			
		}
	}

	return pImage;
}

Feature* ComputeFeatures(Image *pimCharachter)
{
	Feature *pFeat = new Feature();
	double **daImage = pimCharachter->GetDoubleArray(false);
	int iRows = pimCharachter->GetImageRows();
	int iCols = pimCharachter->GetImageCols();

	//Feature 1 Area
	double dA = 0;
	for(int i = 0;i<iRows;i++)
	{
		for(int j = 0;j<iCols;j++)
		{
			Pixel *pxP = pimCharachter->GetPixel(i,j);

			if(pxP->GetBW() == 0)
				dA++;
			delete pxP;
		}
	}	
	pFeat->dArea = dA/((iRows-2)*(iCols-2));

	//Perimeter
	int iaBitQuadWin[2][2];
	double nQ0 = 0, nQ1 = 0, nQ2 = 0, nQ3 = 0, nQ4 = 0, nQD = 0;
	for(int i = 1;i<iRows;i++)
	{
		for(int j = 1;j<iCols;j++)
		{
			//First Bit Quad
			iaBitQuadWin[0][0] = daImage[i-1][j-1];
			iaBitQuadWin[0][1] = daImage[i-1][j];
			iaBitQuadWin[1][0] = daImage[i][j-1];
			iaBitQuadWin[1][1] = daImage[i][j];

			if(CompareBitQuad_Q0(iaBitQuadWin))
				nQ0++;
			if(CompareBitQuad_Q1(iaBitQuadWin))
				nQ1++;
			if(CompareBitQuad_Q2(iaBitQuadWin))
				nQ2++;
			if(CompareBitQuad_Q3(iaBitQuadWin))
				nQ3++;
			if(CompareBitQuad_Q4(iaBitQuadWin))
				nQ4++;
			if(CompareBitQuad_QD(iaBitQuadWin))
				nQD++;

			//Second Bit Quad
			//iaBitQuadWin[0][0] = daImage[i-1][j];
			//iaBitQuadWin[0][1] = daImage[i-1][j+1];
			//iaBitQuadWin[1][0] = daImage[i][j];
			//iaBitQuadWin[1][1] = daImage[i][j+1];
			//
			//if(CompareBitQuad_Q0(iaBitQuadWin))
			//	nQ0++;
			//if(CompareBitQuad_Q1(iaBitQuadWin))
			//	nQ1++;
			//if(CompareBitQuad_Q2(iaBitQuadWin))
			//	nQ2++;
			//if(CompareBitQuad_Q3(iaBitQuadWin))
			//	nQ3++;
			//if(CompareBitQuad_Q4(iaBitQuadWin))
			//	nQ4++;
			//if(CompareBitQuad_QD(iaBitQuadWin))
			//	nQD++;
			//
			////Third Bit Quad
			//iaBitQuadWin[0][0] = daImage[i][j];
			//iaBitQuadWin[0][1] = daImage[i][j+1];
			//iaBitQuadWin[1][0] = daImage[i+1][j];
			//iaBitQuadWin[1][1] = daImage[i+1][j+1];
			//
			//if(CompareBitQuad_Q0(iaBitQuadWin))
			//	nQ0++;
			//if(CompareBitQuad_Q1(iaBitQuadWin))
			//	nQ1++;
			//if(CompareBitQuad_Q2(iaBitQuadWin))
			//	nQ2++;
			//if(CompareBitQuad_Q3(iaBitQuadWin))
			//	nQ3++;
			//if(CompareBitQuad_Q4(iaBitQuadWin))
			//	nQ4++;
			//if(CompareBitQuad_QD(iaBitQuadWin))
			//	nQD++;
			//
			////Fourth Bit Quad
			//iaBitQuadWin[0][0] = daImage[i][j-1];
			//iaBitQuadWin[0][1] = daImage[i][j];
			//iaBitQuadWin[1][0] = daImage[i+1][j-1];
			//iaBitQuadWin[1][1] = daImage[i+1][j];
			//
			//if(CompareBitQuad_Q0(iaBitQuadWin))
			//	nQ0++;
			//if(CompareBitQuad_Q1(iaBitQuadWin))
			//	nQ1++;
			//if(CompareBitQuad_Q2(iaBitQuadWin))
			//	nQ2++;
			//if(CompareBitQuad_Q3(iaBitQuadWin))
			//	nQ3++;
			//if(CompareBitQuad_Q4(iaBitQuadWin))
			//	nQ4++;
			//if(CompareBitQuad_QD(iaBitQuadWin))
			//	nQD++;
		}
	}
	double dPeri = nQ2 + 0.707*(nQ1 + nQ3 + 2*nQD);
	//dPeri = nQ1 + nQ2 + nQ3 + 2*nQD;
	dA = 0.25*nQ1 + 0.5*nQ2 + 7.00/8.00*nQ3 + nQ4 + 0.74*nQD;
	pFeat->dArea = dA/((iRows-2)*(iCols-2));
	pFeat->dPeri = dPeri/((iRows-2)*(iCols-2));

	//Euler Number
	double dE = 0.25*(nQ1 - nQ3 - 2*nQD);

	pFeat->iEuler = dE;

	//Circularity
	double dC = 4.00*3.14159*dA/(dPeri*dPeri);
	pFeat->dCirc = dC;

	//Aspect Ratio
	double dAS = (double) iCols/(double) iRows;
	pFeat->dAS = dAS;
	
	//iRows iCols
	pFeat->iRows = iRows;
	pFeat->iCols = iCols;

	//HSym
	int iUpperCount = 0, iLowerCount = 0;
	for(int i = 0;i<iRows/2;i++)
	{
		for(int j = 0;j<iCols;j++)
		{
			if(daImage[i][j] == 0)
				iUpperCount++;

			if(daImage[iRows - i - 1][j] == 0)
				iLowerCount++;
		}
	}
	double dDiffH = (double)abs(iUpperCount - iLowerCount)/(double)iRows;
	pFeat->dHSym = dDiffH;
	
	//VSym
	int iRightCount = 0, iLeftCount = 0;
	for(int i = 0;i<iRows;i++)
	{
		for(int j = 0;j<iCols/2;j++)
		{
			if(daImage[i][iCols - j - 1] == 0)
				iRightCount++;

			if(daImage[i][j] == 0)
				iLeftCount++;
		}
	}	
	dDiffH = (double)abs(iRightCount - iLeftCount)/(double)iCols;
	pFeat->dVSym = dDiffH;

	//Cen
	double dcX = 0, dcY = 0;
	for(int i = 0;i<iRows;i++)
	{
		for(int j = 0;j<iCols;j++)
		{
			if(daImage[i][j] == 0)
			{
				dcX += 1;
				dcY += 1;
			}
			else
			{
				dcX += 0;
				dcY += 0;
			}
		}
	}

	dcX /= (double) (iRows-2);
	dcY /= (double) (iCols-2);

	Point ptCen(dcX,dcY);

	pFeat->ptCen = ptCen;

	//HCut
	int iHCut = 0;
	int i = iRows/2;
	for(int j = 0;j<iCols-1;j++)
	{
		if(daImage[i][j] == 255 && daImage[i][j+1] == 0)
			iHCut++;
	}
	pFeat->iHCut = iHCut;

	//VCut
	int iVCut = 0;
	int j = iCols/2;
	for(int i = 0;i<iRows-1;i++)
	{
		if(daImage[i][j] == 255 && daImage[i+1][j] == 0)
			iVCut++;
	}
	pFeat->iVCut = iVCut;

	return pFeat;
}

int CompareBitQuad_Q0(int iaWin[2][2])
{
	if(iaWin[0][0] == 255 && iaWin[0][1] == 255 && iaWin[1][0] == 255 && iaWin[1][1] == 255)
		return 1;
	else 
		return 0;
}

int CompareBitQuad_Q1(int iaWin[2][2])
{
	if(iaWin[0][0] == 0 && iaWin[0][1] == 255 && iaWin[1][0] == 255 && iaWin[1][1] == 255)
		return 1;
	if(iaWin[0][0] == 255 && iaWin[0][1] == 0 && iaWin[1][0] == 255 && iaWin[1][1] == 255)
		return 1;
	if(iaWin[0][0] == 255 && iaWin[0][1] == 255 && iaWin[1][0] == 0 && iaWin[1][1] == 255)
		return 1;
	if(iaWin[0][0] == 255 && iaWin[0][1] == 255 && iaWin[1][0] == 255 && iaWin[1][1] == 0)
		return 1;

	return 0;
}

int CompareBitQuad_Q2(int iaWin[2][2])
{
	if(iaWin[0][0] == 0 && iaWin[0][1] == 0 && iaWin[1][0] == 255 && iaWin[1][1] == 255)
		return 1;
	if(iaWin[0][0] == 255 && iaWin[0][1] == 0 && iaWin[1][0] == 255 && iaWin[1][1] == 0)
		return 1;
	if(iaWin[0][0] == 255 && iaWin[0][1] == 255 && iaWin[1][0] == 0 && iaWin[1][1] == 0)
		return 1;
	if(iaWin[0][0] == 0 && iaWin[0][1] == 255 && iaWin[1][0] == 0 && iaWin[1][1] == 255)
		return 1;

	return 0;
}

int CompareBitQuad_Q3(int iaWin[2][2])
{
	if(iaWin[0][0] == 0 && iaWin[0][1] == 0 && iaWin[1][0] == 0 && iaWin[1][1] == 255)
		return 1;
	if(iaWin[0][0] == 255 && iaWin[0][1] == 0 && iaWin[1][0] == 0 && iaWin[1][1] == 0)
		return 1;
	if(iaWin[0][0] == 0 && iaWin[0][1] == 255 && iaWin[1][0] == 0 && iaWin[1][1] == 0)
		return 1;
	if(iaWin[0][0] == 0 && iaWin[0][1] == 0 && iaWin[1][0] == 255 && iaWin[1][1] == 0)
		return 1;

	return 0;
}

int CompareBitQuad_Q4(int iaWin[2][2])
{
	if(iaWin[0][0] == 0 && iaWin[0][1] == 0 && iaWin[1][0] == 0 && iaWin[1][1] == 0)
		return 1;
	else
		return 0;
}

int CompareBitQuad_QD(int iaWin[2][2])
{
	if(iaWin[0][0] == 0 && iaWin[0][1] == 255 && iaWin[1][0] == 255 && iaWin[1][1] == 0)
		return 1;
	if(iaWin[0][0] == 255 && iaWin[0][1] == 0 && iaWin[1][0] == 0 && iaWin[1][1] == 255)
		return 1;

	return 0;
}

char DecisionTreeInt(Image *pimChar)
{	
	Feature *pTF = ComputeFeatures(pimChar);
	
	//First Level
	// Euler Number 
	if(pTF->iEuler == 0)
	{
		//Characters 4 6 9 0
				
		for(int i = 0;i<29;i++)
		{
			// For 4
			if(pTrain[i]->iLabel == 10)
			{
				//Pass Perimeter
				if(pTF->dPeri >= pTrain[i]->dPeri*0.9 || pTF->dPeri <= pTrain[i]->dPeri*1.1)
				{
				}
			}

			//For 6
			if(pTrain[i]->iLabel == 4)
			{				
			}

			//For 9
			if(pTrain[i]->iLabel == 6)
			{
			}

			//For 0
			if(pTrain[i]->iLabel == 7)
			{
				if(pTF->iHCut == 2 && pTF->iVCut == 2)
				{
					if(pTF->dHSym <= 0.1 && pTF->dVSym <= 0.25)
					{
						if(pTF->dAS >= 0.65 && pTF->dAS <= 1.00)
						{
									return '0';
						}
					}
				}
			}
		}
	}
	
	if(pTF->iEuler == -1)
	{
		//Characters 8 B

		for(int i = 0;i<29;i++)
		{
			//For 8
			if(pTrain[i]->iLabel == 5)
			{
				if(pTF->iVCut == 3 && pTF->dVSym <= 0.10)
				{
					//cout<<", 8";
				}
			}

			//For B
			if(pTrain[i]->iLabel == 96)
			{
				if(pTF->iVCut == 3 & pTF->dVSym <= 1.5 && pTF->dHSym <= 0.05)
				{
					//cout<<", B";
				}
			}

			//for

		}
	}

	if(pTF->iEuler== 1)
	{
		//Numbers 1 2 3 5 7 .

		//For 1
		for(int i = 0;i<29;i++)
		{
			// For 1
			if(pTrain[i]->iLabel == 1)
			{
				if(pTF->iHCut == 1 && pTF->iVCut == 1)
				{
					if(pTF->dArea >= 0.39 && pTF->dCirc <= 0.45)
					{
						if(pTF->dAS >= 0.39 && pTF->dAS <= 0.63)
						{
									return '1';
						}
					}
				}
			}

			//For 2
			if(pTrain[i]->iLabel == 2)
			{
				if(pTF->iHCut == 1 && pTF->iVCut == 3)
				{
					if(pTF->dArea >= 0.40 && pTF->dArea <= 0.50)
					{
						if(pTF->dCirc >= 0.13 && pTF->dCirc <= 0.176)
						{
									return '2';
						}
					}
				}
			}

			//For 5
			if(pTrain[i]->iLabel == 11)
			{
				if(pTF->iHCut == 2 && pTF->iVCut == 3)
				{
					if(pTF->dArea >= 0.40 && pTF->dArea <= 0.50)
					{
						if(pTF->dCirc >= 0.13 && pTF->dCirc <= 0.16)
						{
									return '5';
						}
					}
				}
			}

			//For 3
			if(pTrain[i]->iLabel == 3)
			{
				if(pTF->iVCut == 3)
				{
					if(pTF->dHSym <= 0.30)
					{
						//cout<<", 3";
					}
				}
			}

			//For 7
			if(pTrain[i]->iLabel == 13)
			{
				if(pTF->iHCut == 1 && pTF->iVCut == 2)
				{
					if(pTF->dCirc <= 0.20)
					{
						//cout<<", 7";
					}
				}
			}

			//for .

			if(pTrain[i]->iLabel == 43)
			{
				if(pTF->iHCut == 1 && pTF->iVCut == 1)
				{
					if(pTF->dArea >= 0.850 && pTF->dArea <= 1.0)
					{
						if(pTF->dCirc >= 0.85 && pTF->dCirc <= 1.00)
						{
									return '.';
						}
					}
				}
			}
			//Charachters
		}
	}

	return '\n';
}

char DecisionTreeChar(Image *pimChar)
{
	Feature *pTF = ComputeFeatures(pimChar);

	//First Level

	//Euler Number
	if(pTF->iEuler == 0)
	{
		//O and o A a

		for(int i = 0;i<29;i++)
		{
			//for O
			if(pTrain[i]->iLabel == 92)
			{
				if(pTF->iHCut == 2 && pTF->iVCut == 2)
				{
					if(pTF->dCirc >= 0.11 && pTF->dCirc <= 0.17)
					{
						if(pTF->dAS >= 0.90 && pTF->dAS <= 1.00)
						{
									return 'O';
						}
					}
				}
			}

			//for o
			if(pTrain[i]->iLabel == 52)
			{
			}

			//for A
			if(pTrain[i]->iLabel ==98)
			{
			}

			//for a
			if(pTrain[i]->iLabel == 53)
			{
			}
		}
	}
	else if(pTF->iEuler == -1)
	{

	}
	else if(pTF->iEuler == 1)
	{
		// T t L l
		for(int i = 0;i<29;i++)
		{
			//for T
			if(pTrain[i]->iLabel == 46)
			{
				if(pTF->iHCut == 1 && pTF->iVCut == 1)
				{
					if(pTF->dCirc >= 0.21 && pTF->dCirc <= 0.33)
					{
						if(pTF->dAS >= 0.72 && pTF->dAS <= 0.93)
						{
							if(pTF->dArea >= 0.25*0.9 && pTF->dArea <= 0.34)
							{
								if(pTF->dVSym <= 0.1)
									return 'T';
							}
						}
					}
				}
			}

			//for t
			if(pTrain[i]->iLabel == 50)
			{
				if(pTF->iHCut == 1 && pTF->iVCut == 1)
				{
					if(pTF->dCirc >= 0.265*0.9 && pTF->dCirc <= 0.265*1.1)
					{
						if(pTF->dAS >= 0.375*0.9 && pTF->dAS <= 0.375*1.1)
						{
							if(pTF->dArea >= 0.44*0.9 && pTF->dArea <= 0.44*1.1)
							{								
									return 't';
							}
						}
					}
				}
			}

			//for L
			if(pTrain[i]->iLabel == 99)
			{
				if(pTF->iHCut == 1 && pTF->iVCut == 1)
				{
					if(pTF->dCirc >= 0.21*0.9 && pTF->dCirc <= 0.33*1.1)
					{
						if(pTF->dAS >= 0.65*0.9 && pTF->dAS <= 0.85*1.1)
						{
							if(pTF->dArea >= 0.28*0.9 && pTF->dArea <= 0.36*1.1)
							{
								return 'L';
							}
						}
					}
				}
			}

			//for l
			if(pTrain[i]->iLabel == 47)
			{
			}
		}
	}
}

void WriteFeatureFile(Feature **pfFeatureSet, int iNum, char strFileName[30])
{
	//CSV File
	fstream fpFeature;

	fpFeature.open(strFileName,ios::out);

	fpFeature<<"Charachter , Area , Perimiter , Euler No , Circularity , Centroid_X , Centroid_Y , Aspect Ratio, HSym, VSym , HCut , VCut , iRows , iCols , Label\n";
	
	for(int j = 0;j<iNum-1;j++)
	{
		fpFeature<<"Charachter_"<<j+1<<","<<pfFeatureSet[j]->dArea<<","<<pfFeatureSet[j]->dPeri<<","<<pfFeatureSet[j]->iEuler<<","<<pfFeatureSet[j]->dCirc<<","<<pfFeatureSet[j]->ptCen.iX<<","<<pfFeatureSet[j]->ptCen.iY<<","<<pfFeatureSet[j]->dAS<<","<<pfFeatureSet[j]->dHSym<<","<<pfFeatureSet[j]->dVSym<<","<<pfFeatureSet[j]->iHCut<<" , "<<pfFeatureSet[j]->iVCut<<" , "<<pfFeatureSet[j]->iRows<<","<<pfFeatureSet[j]->iCols<<" , "<<pfFeatureSet[j]->iLabel;
		fpFeature<<"\n";
	}
	
	fpFeature.close();
}