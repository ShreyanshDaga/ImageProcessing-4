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
//File: Problem_3.cpp
//////////////////////////////////////////////////

#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<iostream>
#include<fstream>
#include<list>

#include"HW_4.h"
#include"Pixel.h"
#include"Image.h"
#include"Histogram.h"
#include"Matrix.h"
#include"Misc.h"

using namespace std;

void Problem_3_A_b();

void Problem_3_A()
{
	Image imSeg[3], imResult[3];
	string strNames[3] = {"seg1.raw","seg2.raw","seg3.raw"};
	string strResNames[3] = {"seg1_Op.raw","seg2_Op.raw","seg3_Op.raw"};
	int iRows = 321, iCols = 481;
	int iK = 3;	

	for(int i = 0;i<3;i++)
	{
		InitImage(&imSeg[i],strNames[i],iRows,iCols,3);
		InitImage(&imResult[i],strResNames[i],iRows,iCols,3);
		imSeg[i].ReadImageData();
	}


	//Segmentation IMage 
	double **dFeature = new double*[iRows*iCols];
	for(int i = 0;i<iRows*iCols;i++)
	{
		dFeature[i] = new double[3];
	}

	int iaK[5] = {3,4,7,10,12};

	for(int l = 1;l<2;l++)
	{
		iK = 12;

		for(int p = 2;p < 3;p++)
		{
			for(int i = 0;i<iRows;i++)
			{
				for(int j = 0;j<iCols;j++)
				{
					Pixel *pxP = imSeg[p].GetPixel(i,j);
					
					dFeature[i*iCols + j][0] = pxP->GetRed();
					dFeature[i*iCols + j][1] = pxP->GetGreen();
					dFeature[i*iCols + j][2] = pxP->GetBlue();
				}
			}

			//k-Means
			double **daCentroid = new double*[iK];
			for(int i = 0;i<10;i++)
			{
				daCentroid[i] = new double[3];
			}

			int *pLabel = K_Means(dFeature,iRows*iCols,3,iK,0.0001,daCentroid);

			//OutputImage
			for(int i = 0;i<iRows;i++)
			{
				for(int j = 0;j<iCols;j++)
				{
					Pixel pxP;
					int iVal = pLabel[i*iCols + j];								

					pxP.iR = daCentroid[iVal][0];
					pxP.iG = daCentroid[iVal][1];
					pxP.iB = daCentroid[iVal][2];

					imResult[p].SetPixel(i,j,pxP);
				}
			}

			string strName;
			char szName[30];
			sprintf(szName,"Result_Seg_%d_K_%d.raw",p,iK);

			strName = string::basic_string(szName);
			imResult[p].SetImageName(strName);
			imResult[p].WriteImageData();	
		}
	}
	cout<<"\n Press 'C' to continue..";
	getch();
}

void Problem_3_A_b()
{
	Image imSeg[3], imResult[3];
	string strNames[3] = {"seg1.raw","seg2.raw","seg3.raw"};
	string strResNames[3] = {"seg1_Op.raw","seg2_Op.raw","seg3_Op.raw"};
	int iRows = 321, iCols = 481;
	int iK;


	for(int i = 0;i<3;i++)
	{
		InitImage(&imSeg[i],strNames[i],iRows,iCols,3);
		InitImage(&imResult[i],strResNames[i],iRows,iCols,3);
		imSeg[i].ReadImageData();
	}


	//Segmentation IMage 
	double **dFeature = new double*[iRows*iCols];
	for(int i = 0;i<iRows*iCols;i++)
	{
		dFeature[i] = new double[5];
	}
	Image *pimSegEx;

	int iaK[5] = { 3,4,7,10,12};

	for(int p = 0;p < 3;p++)
	{
		if(p == 0)
			iK = 4;
		else if(p == 1)
			iK = 6;
		else 
			iK = 12;

		pimSegEx = imSeg[p].ImageExtend(2);

		for(int i = 2;i<iRows+2;i++)
		{
			for(int j = 2;j<iCols+2;j++)
			{								
				dFeature[(i-2)*iCols + j-2][0] = pimSegEx->GetRed(i,j);
				dFeature[(i-2)*iCols + j-2][1] = pimSegEx->GetGreen(i,j);
				dFeature[(i-2)*iCols + j-2][2] = pimSegEx->GetBlue(i,j);
				dFeature[(i-2)*iCols + j-2][3] = pimSegEx->GetBW(i,j);

				double dInt = 0;

				for(int l = 0;l<5;l++)
				{
					for(int m = 0;m<5;m++)
					{
						int iBW = pimSegEx->GetBW(i + (l - 2), j + (m - 2));
						dInt += iBW;
					}
				}
				dInt /= 25;

				dFeature[(i-2)*iCols + j-2][4] = dInt;//Intensity;
			}
		}

		//k-Means
		double **daCentroid = new double*[iK];
		for(int i = 0;i<iK;i++)
		{
			daCentroid[i] = new double[5];
		}

		int *pLabel = K_Means(dFeature,iRows*iCols,5,iK,0.0001,daCentroid);

		//OutputImage
		for(int i = 0;i<iRows;i++)
		{
			for(int j = 0;j<iCols;j++)
			{
				Pixel pxP;
				int iVal = pLabel[i*iCols + j];
				
				//if(iVal == 0)
				//{
				//	//pxP.iR = daCentroid[0][0];
				//	//pxP.iG = daCentroid[1][0];
				//	//pxP.iB = daCentroid[2][0];
				//	//
				//	pxP.iR = daCentroid[0][0];
				//	pxP.iG = daCentroid[0][1];
				//	pxP.iB = daCentroid[0][2];
				//}
				//else if(iVal == 1)
				//{
				//	pxP.iR = daCentroid[0][1];
				//	pxP.iG = daCentroid[1][1];
				//	pxP.iB = daCentroid[2][1];
				//
				//	pxP.iR = daCentroid[1][0];
				//	pxP.iG = daCentroid[1][1];
				//	pxP.iB = daCentroid[1][2];
				//}
				//else if(iVal == 2)
				//{
				//	pxP.iR = daCentroid[0][2];
				//	pxP.iG = daCentroid[1][2];
				//	pxP.iB = daCentroid[2][2];
				//
				//	pxP.iR = daCentroid[2][0];
				//	pxP.iG = daCentroid[2][1];
				//	pxP.iB = daCentroid[2][2];
				//}

				pxP.iR = daCentroid[iVal][0];
				pxP.iG = daCentroid[iVal][1];
				pxP.iB = daCentroid[iVal][2];

				imResult[p].SetPixel(i,j,pxP);
			}
		}

		imResult[p].WriteImageData();

		//for(int i = 0;i<iRows*iCols;i++)
		//	delete [] dFeature[i];
		//
		//delete [] dFeature;
	}
	cout<<"\n Press 'C' to continue..";
	getch();
}

void Problem_3_B()
{
	Image imSeg[3], imResult[3];
	string strNames[3] = {"seg1.raw","seg2.raw","seg3.raw"};
	string strResNames[3] = {"seg1_Op.raw","seg2_Op.raw","seg3_Op.raw"};
	int iRows = 321, iCols = 481;

	for(int i = 0;i<3;i++)
	{
		InitImage(&imSeg[i],strNames[i],iRows,iCols,3);
		InitImage(&imResult[i],strResNames[i],iRows,iCols,3);
		imSeg[i].ReadImageData();
	}

	int dSigS = 20, dSigR = 25;

	int iWinSize = 6*dSigS + 1;
	int iWinIndex = (iWinSize - 1)/2;
	for(int im = 0;im<3;im++)
	{
		Image *pimExSeg = imSeg[im].ImageExtend((iWinIndex));

		for(int i = iWinIndex; i< iRows + iWinIndex;i++)
		{
			cout<<"\n Row Number: "<<i - iWinIndex;
			for(int j = iWinIndex; j < iCols + iWinIndex;j++)
			{
				Pixel *pxX = pimExSeg->GetPixel(i,j);			
				
				double dYR = pxX->GetRed();
				double dYG = pxX->GetGreen();
				double dYB = pxX->GetBlue();

				double dCYThisR = 0;
				double dCYThisG = 0;
				double dCYThisB = 0;				

				int iIt = 0;
				bool bFlag = false;
				double dMSE = 0;
				
				while(!bFlag)
				{								
					double dWThisR = 0;
					double dWThisG = 0;
					double dWThisB = 0;

					double dYThisR = 0;
					double dYThisG = 0;
					double dYThisB = 0;

					double dYAccR = 0;
					double dYAccG = 0;
					double dYAccB = 0;

					double dCYThisR = 0;
					double dCYThisG = 0;
					double dCYThisB = 0;				

					for(int l = 0;l<iWinSize;l++)
					{
						for(int m = 0;m<iWinSize;m++)
						{						
							double dXThisR = pimExSeg->GetRed(i + (l - iWinIndex),j + (m - iWinIndex));
							double dXThisG = pimExSeg->GetGreen(i + (l - iWinIndex),j + (m - iWinIndex));
							double dXThisB = pimExSeg->GetBlue(i + (l - iWinIndex),j + (m - iWinIndex));

							//Spatial Kernal
							double dSpatialKernal = exp(-1*((l - iWinIndex)*(l - iWinIndex) + (m - iWinIndex)*(m - iWinIndex))/(2*dSigS*dSigS));
							
							//Intensity Kernal
							double dDiffYR = abs(dYR - dXThisR);
							double dDiffYB = abs(dYB - dXThisB);
							double dDiffYG = abs(dYG - dXThisG);
							
							//Intensity Kernal = R*R + G*G + B*B / 2dSigR
							double dIntensityKernal = ((dDiffYR*dDiffYR) + (dDiffYG*dDiffYG) + (dDiffYB*dDiffYB)/2*dSigR*dSigR);
							dWThisR = dSpatialKernal*exp(-1*(dDiffYR*dDiffYR)/(2*dSigR*dSigR))*dDiffYR;
							dWThisG = dSpatialKernal*exp(-1*(dDiffYG*dDiffYG)/(2*dSigR*dSigR))*dDiffYG;
							dWThisB = dSpatialKernal*exp(-1*(dDiffYB*dDiffYB)/(2*dSigR*dSigR))*dDiffYB;
							
							//C
							dCYThisR += dWThisR;
							dCYThisG += dWThisG;
							dCYThisB += dWThisB;

							dYAccR += dXThisR*dWThisR;
							dYAccG += dXThisG*dWThisG;
							dYAccB += dXThisB*dWThisB;
						}
					}

					dYThisR = dYAccR/dCYThisR;
					dYThisG = dYAccG/dCYThisG;
					dYThisB = dYAccB/dCYThisB;

					dMSE = ( (dYThisR - dYR)*(dYThisR - dYR) + (dYThisG - dYG)*(dYThisG - dYG) + (dYThisB - dYB)*(dYThisB - dYB) )/3.0;

					if(iIt > 20 || dMSE < 0.1)
					{
						bFlag = true;
						dYR = dYThisR;
						dYG = dYThisG;
						dYB = dYThisB;
					}
					else
					{
						dYR = dYThisR;
						dYG = dYThisG;
						dYB = dYThisB;
						iIt++;
					}
				}
				
				Pixel pxPYk(dYR,dYG,dYB);
				imResult[im].SetPixel(i - iWinIndex,j-iWinIndex,pxPYk);
			}
		}

		imResult[im].WriteImageData();		
	}

	cout<<"\n Press 'C' to continue..";
	getch();
}

void Problem_3_C()
{
	Image imSeg[3], imResult[3];
	string strNames[3] = {"seg1_Op.raw","seg2_Op.raw","seg3_Op.raw"};
	string strResNames[3] = {"seg1_Op_3C.raw","seg2_Op_3C.raw","seg3_Op_3C.raw"};
	int iRows = 321, iCols = 481;

	for(int i = 0;i<3;i++)
	{
		InitImage(&imSeg[i],strNames[i],iRows,iCols,3);
		InitImage(&imResult[i],strResNames[i],iRows,iCols,3);
		imSeg[i].ReadImageData();
	}

	double **daImLabels = new double *[iRows];
	for(int i = 0;i<iRows;i++)
		daImLabels[i] = new double[iCols];

	for(int i = 0;i<iRows;i++)
	{
		for(int j =0 ;j<iCols;j++)
		{
			daImLabels[0];
		}
	}

	//Start Traversing
	for(int im = 0;im<3;im++)
	{
		list<LabelTable> listTable;
		int iLabel = 1;
		bool bFlag = false;

		for(int i = 0;i<iRows;i++)
		{
			for(int j = 0;j<iCols;j++)
			{
				double dR,dG,dB;

				dR = imSeg[im].GetRed(i,j);
				dG = imSeg[im].GetGreen(i,j);
				dB = imSeg[im].GetBlue(i,j);

				if(listTable.empty())
				{
					LabelTable ltEntry(dR,dG,dB,iLabel,1);

					listTable.push_back(ltEntry);
					daImLabels[i][j] = iLabel;
					continue;
				}

				bFlag = false;

				for(list<LabelTable>::iterator l = listTable.begin(); l != listTable.end(); l++)
				{
					int iCurrentLabel = l->iLabel;
					int iCurrentLabelCount = l->iCount;

					double dR1 = l->dR;
					double dG1 = l->dG;
					double dB1 = l->dB;

					double dEDist = sqrt((dR - dR1)*(dR - dR1) + (dG - dG1)*(dG - dG1) + (dB - dB1)*(dB - dB1));

					if(dEDist <= 100.00)
					{
						//Assign Current Label
						daImLabels[i][j] = iCurrentLabel;

						iCurrentLabelCount++;
						l->iCount = iCurrentLabelCount;

						l->dR = (dR1*(iCurrentLabelCount-1) + dR )/iCurrentLabelCount;
						l->dG = (dG1*(iCurrentLabelCount-1) + dG )/iCurrentLabelCount;
						l->dB = (dB1*(iCurrentLabelCount-1) + dB )/iCurrentLabelCount;

						bFlag = true;
						break;
					}				
				}
				
				if(bFlag == false)
				{
					//New Label
					iLabel++;
					LabelTable ltEntry(dR,dG,dB,1,iLabel);
					listTable.push_back(ltEntry);

					daImLabels[i][j] = iLabel;
				}
			}
		}

		cout<<"\n Total Number oF Labels: "<<iLabel;
		for(int i = 0;i<iRows;i++)
		{
			for(int j = 0;j<iCols;j++)
			{
				int iLabel = daImLabels[i][j];

				for(list<LabelTable>::iterator l = listTable.begin(); l != listTable.end(); l++)
				{
					if(l->iLabel == iLabel)
					{
						Pixel pxP(l->dR,l->dG,l->dB);

						imResult[im].SetPixel(i,j,pxP);
						break;
					}
				}
			}
		}

		imResult[im].WriteImageData();
	}
	cout<<"\n Press 'C' to continue..";
	getch();
}