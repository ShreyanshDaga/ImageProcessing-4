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
//File: Problem_1.cpp
//////////////////////////////////////////////////

#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<iostream>
#include<string.h>

#include"HW_4.h"
#include"Pixel.h"
#include"Image.h"
#include"Histogram.h"
#include"Misc.h"
#include"Matrix.h"

using namespace std;
void Problem_1_C_b();

Matrix** FindTransMatrix(Point ptaIp[8][3], Point ptaOp[8][3], int iTriangleNumber);

void Problem_1_A()
{
	Image imDrew, imBabyDrew, imBabyDrewA, imDrewA, *pimResult = new Image();
	string szNames[4] = {"old_drew.raw","young_drew.raw","babydrewA.raw","drewA.raw"};
	int iRows = 350, iCols = 300;

	InitImage(&imDrew,szNames[0],iRows,iCols,3);
	InitImage(&imBabyDrew,szNames[1],iRows,iCols,3);
	InitImage(&imBabyDrewA,szNames[2],iRows,iCols,3);
	InitImage(&imDrewA,szNames[3],iRows,iCols,3);
	InitImage(pimResult,string::basic_string(""),iRows,iCols,3);

	imDrew.ReadImageData();
	imBabyDrew.ReadImageData();

	//Align Images

	//Baby
	//Control Points
	Point ptC1(0,0),ptC2(0,299),ptC3(349,299), ptC4(349,0), ptC5(169,150), ptC6(289,73), ptC7(289,233), ptC8(246,124),ptC9(243,172),ptC10(172,177), ptC11(172,224), ptC12(162,202), ptC13(179,202), ptC14(140,209);//old
	Point ptB1(0,0),ptB2(0,299),ptB3(349,299), ptB4(349,0), ptB5(175,145), ptB6(291,65), ptB7(289,231), ptB8(240,116),ptB9(240,175),ptB10(180,178), ptB11(179,230), ptB12(167,202), ptB13(190,202), ptB14(153,216);	//baby
	Point ptA1(ptC1),ptA2(ptC2),ptA3(ptC3), ptA4(ptC4), ptA5(172,147.5), ptA6(290,69), ptA7(289,232), ptA8(243,120),ptA9(241.5,173.5),ptA10(176,177.5), ptA11(175.5,227), ptA12(164.5,202), ptA13(184.5,202), ptA14(146.5,212.5);	//Align
	//Triangle Points
	Point ptaIP_Old[22][3] = {{ptC1,ptC2,ptC5},{ptC1,ptC6,ptC4},{ptC1,ptC5,ptC6},{ptC6,ptC5,ptC8},{ptC8,ptC5,ptC9},{ptC9,ptC5,ptC7},{ptC5,ptC10,ptC7},{ptC5,ptC2,ptC10},{ptC10,ptC2,ptC14},{ptC14,ptC2,ptC11},{ptC11,ptC2,ptC3},{ptC10,ptC12,ptC11},{ptC13,ptC12,ptC11},{ptC10,ptC13,ptC7},{ptC13,ptC11,ptC7},{ptC7,ptC11,ptC3},{ptC6,ptC8,ptC9},{ptC6,ptC9,ptC7},{ptC4,ptC6,ptC3},{ptC6,ptC7,ptC3},{ptC10,ptC14,ptC13},{ptC13,ptC14,ptC11}};
	Point ptaIP_Baby[22][3] = {{ptB1,ptB2,ptB5},{ptB1,ptB6,ptB4},{ptB1,ptB5,ptB6},{ptB6,ptB5,ptB8},{ptB8,ptB5,ptB9},{ptB9,ptB5,ptB7},{ptB5,ptB10,ptB7},{ptB5,ptB2,ptB10},{ptB10,ptB2,ptB14},{ptB14,ptB2,ptB11},{ptB11,ptB2,ptB3},{ptB10,ptB12,ptB11},{ptB13,ptB12,ptB11},{ptB10,ptB13,ptB7},{ptB13,ptB11,ptB7},{ptB7,ptB11,ptB3},{ptB6,ptB8,ptB9},{ptB6,ptB9,ptB7},{ptB4,ptB6,ptB3},{ptB6,ptB7,ptB3},{ptB10,ptB14,ptB13},{ptB13,ptB14,ptB11}};
	Point ptaOP[22][3] = {{ptA1,ptA2,ptA5},{ptA1,ptA6,ptA4},{ptA1,ptA5,ptA6},{ptA6,ptA5,ptA8},{ptA8,ptA5,ptA9},{ptA9,ptA5,ptA7},{ptA5,ptA10,ptA7},{ptA5,ptA2,ptA10},{ptA10,ptA2,ptA14},{ptA14,ptA2,ptA11},{ptA11,ptA2,ptA3},{ptA10,ptA12,ptA11},{ptA13,ptA12,ptA11},{ptA10,ptA13,ptA7},{ptA13,ptA11,ptA7},{ptA7,ptA11,ptA3},{ptA6,ptA8,ptA9},{ptA6,ptA9,ptA7},{ptA4,ptA6,ptA3},{ptA6,ptA7,ptA3},{ptA10,ptA14,ptA13},{ptA13,ptA14,ptA11}};

	Matrix **pMatTrans_Old = FindTransMatrix(ptaIP_Old,ptaOP,22);
	Matrix **pMatTrans_Baby = FindTransMatrix(ptaIP_Baby,ptaOP,22);

	//Warp Baby Image
	for(int i = 0;i<iRows;i++)
	{
		for(int j = 0;j<iCols;j++)
		{
			double dU = (double)(i); ///350.00;
			double dV = (double)(j); ///300.00;
			double dX_1, dY_1, dX_2,dY_2;
			Point ptP(dU,dV);			
									
			Matrix *pmatIp_Old, *pmatIp_Baby;
			Matrix matOp(3,1);
			
			matOp.SetElement(0,0,1.00);
			matOp.SetElement(1,0,ptP.iX);
			matOp.SetElement(2,0,ptP.iY);

			if(ptP.LiesWithinTriangle(ptaOP[1]))
			{
				//Check for Triangle_1								
				pmatIp_Old = Matrix::MatrixMultiply(*pMatTrans_Old[1],matOp);
				pmatIp_Baby = Matrix::MatrixMultiply(*pMatTrans_Baby[1],matOp);
				
				dX_1 = pmatIp_Old->GetElement(0,0);
				dY_1 = pmatIp_Old->GetElement(1,0);

				dX_2 = pmatIp_Baby->GetElement(0,0);
				dY_2 = pmatIp_Baby->GetElement(1,0);

				pmatIp_Old->FreeMemory();
				pmatIp_Baby->FreeMemory();
				delete pmatIp_Baby;
				delete pmatIp_Old;
			}
			else if(ptP.LiesWithinTriangle(ptaOP[2]))
			{
				//Check for Triangle_2
				pmatIp_Old = Matrix::MatrixMultiply(*pMatTrans_Old[2],matOp);
				pmatIp_Baby = Matrix::MatrixMultiply(*pMatTrans_Baby[2],matOp);
				
				dX_1 = pmatIp_Old->GetElement(0,0);
				dY_1 = pmatIp_Old->GetElement(1,0);

				dX_2 = pmatIp_Baby->GetElement(0,0);
				dY_2 = pmatIp_Baby->GetElement(1,0);

				pmatIp_Old->FreeMemory();
				pmatIp_Baby->FreeMemory();
				delete pmatIp_Baby;
				delete pmatIp_Old;
			}
			else if(ptP.LiesWithinTriangle(ptaOP[3]))
			{
				//Check for Triangle_2
				pmatIp_Old = Matrix::MatrixMultiply(*pMatTrans_Old[3],matOp);
				pmatIp_Baby = Matrix::MatrixMultiply(*pMatTrans_Baby[3],matOp);
				
				dX_1 = pmatIp_Old->GetElement(0,0);
				dY_1 = pmatIp_Old->GetElement(1,0);

				dX_2 = pmatIp_Baby->GetElement(0,0);
				dY_2 = pmatIp_Baby->GetElement(1,0);

				pmatIp_Old->FreeMemory();
				pmatIp_Baby->FreeMemory();
				delete pmatIp_Baby;
				delete pmatIp_Old;
			}
			else if(ptP.LiesWithinTriangle(ptaOP[4]))
			{
				//Check for Triangle_2
				pmatIp_Old = Matrix::MatrixMultiply(*pMatTrans_Old[4],matOp);
				pmatIp_Baby = Matrix::MatrixMultiply(*pMatTrans_Baby[4],matOp);
				
				dX_1 = pmatIp_Old->GetElement(0,0);
				dY_1 = pmatIp_Old->GetElement(1,0);

				dX_2 = pmatIp_Baby->GetElement(0,0);
				dY_2 = pmatIp_Baby->GetElement(1,0);

				pmatIp_Old->FreeMemory();
				pmatIp_Baby->FreeMemory();
				delete pmatIp_Baby;
				delete pmatIp_Old;
			}
			else if(ptP.LiesWithinTriangle(ptaOP[5]))
			{
				//Check for Triangle_2
				pmatIp_Old = Matrix::MatrixMultiply(*pMatTrans_Old[5],matOp);
				pmatIp_Baby = Matrix::MatrixMultiply(*pMatTrans_Baby[5],matOp);
				
				dX_1 = pmatIp_Old->GetElement(0,0);
				dY_1 = pmatIp_Old->GetElement(1,0);

				dX_2 = pmatIp_Baby->GetElement(0,0);
				dY_2 = pmatIp_Baby->GetElement(1,0);

				pmatIp_Old->FreeMemory();
				pmatIp_Baby->FreeMemory();
				delete pmatIp_Baby;
				delete pmatIp_Old;
			}
			else if(ptP.LiesWithinTriangle(ptaOP[6]))
			{
				//Check for Triangle_2
				pmatIp_Old = Matrix::MatrixMultiply(*pMatTrans_Old[6],matOp);
				pmatIp_Baby = Matrix::MatrixMultiply(*pMatTrans_Baby[6],matOp);
				
				dX_1 = pmatIp_Old->GetElement(0,0);
				dY_1 = pmatIp_Old->GetElement(1,0);

				dX_2 = pmatIp_Baby->GetElement(0,0);
				dY_2 = pmatIp_Baby->GetElement(1,0);

				pmatIp_Old->FreeMemory();
				pmatIp_Baby->FreeMemory();
				delete pmatIp_Baby;
				delete pmatIp_Old;
			}
			else if(ptP.LiesWithinTriangle(ptaOP[7]))
			{
				//Check for Triangle_2
				pmatIp_Old = Matrix::MatrixMultiply(*pMatTrans_Old[7],matOp);
				pmatIp_Baby = Matrix::MatrixMultiply(*pMatTrans_Baby[7],matOp);
				
				dX_1 = pmatIp_Old->GetElement(0,0);
				dY_1 = pmatIp_Old->GetElement(1,0);

				dX_2 = pmatIp_Baby->GetElement(0,0);
				dY_2 = pmatIp_Baby->GetElement(1,0);

				pmatIp_Old->FreeMemory();
				pmatIp_Baby->FreeMemory();
				delete pmatIp_Baby;
				delete pmatIp_Old;
			}
			else if(ptP.LiesWithinTriangle(ptaOP[8]))
			{
				//Check for Triangle_2
				pmatIp_Old = Matrix::MatrixMultiply(*pMatTrans_Old[8],matOp);
				pmatIp_Baby = Matrix::MatrixMultiply(*pMatTrans_Baby[8],matOp);
				
				dX_1 = pmatIp_Old->GetElement(0,0);
				dY_1 = pmatIp_Old->GetElement(1,0);

				dX_2 = pmatIp_Baby->GetElement(0,0);
				dY_2 = pmatIp_Baby->GetElement(1,0);

				pmatIp_Old->FreeMemory();
				pmatIp_Baby->FreeMemory();
				delete pmatIp_Baby;
				delete pmatIp_Old;
			}
			else if(ptP.LiesWithinTriangle(ptaOP[9]))
			{
				//Check for Triangle_2
				pmatIp_Old = Matrix::MatrixMultiply(*pMatTrans_Old[9],matOp);
				pmatIp_Baby = Matrix::MatrixMultiply(*pMatTrans_Baby[9],matOp);
				
				dX_1 = pmatIp_Old->GetElement(0,0);
				dY_1 = pmatIp_Old->GetElement(1,0);

				dX_2 = pmatIp_Baby->GetElement(0,0);
				dY_2 = pmatIp_Baby->GetElement(1,0);

				pmatIp_Old->FreeMemory();
				pmatIp_Baby->FreeMemory();
				delete pmatIp_Baby;
				delete pmatIp_Old;
			}
			else if(ptP.LiesWithinTriangle(ptaOP[10]))
			{
				//Check for Triangle_2
				pmatIp_Old = Matrix::MatrixMultiply(*pMatTrans_Old[10],matOp);
				pmatIp_Baby = Matrix::MatrixMultiply(*pMatTrans_Baby[10],matOp);
				
				dX_1 = pmatIp_Old->GetElement(0,0);
				dY_1 = pmatIp_Old->GetElement(1,0);

				dX_2 = pmatIp_Baby->GetElement(0,0);
				dY_2 = pmatIp_Baby->GetElement(1,0);

				pmatIp_Old->FreeMemory();
				pmatIp_Baby->FreeMemory();
				delete pmatIp_Baby;
				delete pmatIp_Old;
			}
			else if(ptP.LiesWithinTriangle(ptaOP[11]))
			{
				//Check for Triangle_2
				pmatIp_Old = Matrix::MatrixMultiply(*pMatTrans_Old[11],matOp);
				pmatIp_Baby = Matrix::MatrixMultiply(*pMatTrans_Baby[11],matOp);
				
				dX_1 = pmatIp_Old->GetElement(0,0);
				dY_1 = pmatIp_Old->GetElement(1,0);

				dX_2 = pmatIp_Baby->GetElement(0,0);
				dY_2 = pmatIp_Baby->GetElement(1,0);

				pmatIp_Old->FreeMemory();
				pmatIp_Baby->FreeMemory();
				delete pmatIp_Baby;
				delete pmatIp_Old;
			}
			else if(ptP.LiesWithinTriangle(ptaOP[12]))
			{
				//Check for Triangle_2
				pmatIp_Old = Matrix::MatrixMultiply(*pMatTrans_Old[12],matOp);
				pmatIp_Baby = Matrix::MatrixMultiply(*pMatTrans_Baby[12],matOp);
				
				dX_1 = pmatIp_Old->GetElement(0,0);
				dY_1 = pmatIp_Old->GetElement(1,0);

				dX_2 = pmatIp_Baby->GetElement(0,0);
				dY_2 = pmatIp_Baby->GetElement(1,0);

				pmatIp_Old->FreeMemory();
				pmatIp_Baby->FreeMemory();
				delete pmatIp_Baby;
				delete pmatIp_Old;
			}
			else if(ptP.LiesWithinTriangle(ptaOP[13]))
			{
				//Check for Triangle_2
				pmatIp_Old = Matrix::MatrixMultiply(*pMatTrans_Old[13],matOp);
				pmatIp_Baby = Matrix::MatrixMultiply(*pMatTrans_Baby[13],matOp);
				
				dX_1 = pmatIp_Old->GetElement(0,0);
				dY_1 = pmatIp_Old->GetElement(1,0);

				dX_2 = pmatIp_Baby->GetElement(0,0);
				dY_2 = pmatIp_Baby->GetElement(1,0);

				pmatIp_Old->FreeMemory();
				pmatIp_Baby->FreeMemory();
				delete pmatIp_Baby;
				delete pmatIp_Old;
			}
			else if(ptP.LiesWithinTriangle(ptaOP[14]))
			{
				//Check for Triangle_2
				pmatIp_Old = Matrix::MatrixMultiply(*pMatTrans_Old[14],matOp);
				pmatIp_Baby = Matrix::MatrixMultiply(*pMatTrans_Baby[14],matOp);
				
				dX_1 = pmatIp_Old->GetElement(0,0);
				dY_1 = pmatIp_Old->GetElement(1,0);

				dX_2 = pmatIp_Baby->GetElement(0,0);
				dY_2 = pmatIp_Baby->GetElement(1,0);

				pmatIp_Old->FreeMemory();
				pmatIp_Baby->FreeMemory();
				delete pmatIp_Baby;
				delete pmatIp_Old;
			}
			else if(ptP.LiesWithinTriangle(ptaOP[15]))
			{
				//Check for Triangle_2
				pmatIp_Old = Matrix::MatrixMultiply(*pMatTrans_Old[15],matOp);
				pmatIp_Baby = Matrix::MatrixMultiply(*pMatTrans_Baby[15],matOp);
				
				dX_1 = pmatIp_Old->GetElement(0,0);
				dY_1 = pmatIp_Old->GetElement(1,0);

				dX_2 = pmatIp_Baby->GetElement(0,0);
				dY_2 = pmatIp_Baby->GetElement(1,0);

				pmatIp_Old->FreeMemory();
				pmatIp_Baby->FreeMemory();
				delete pmatIp_Baby;
				delete pmatIp_Old;
			}
			else if(ptP.LiesWithinTriangle(ptaOP[16]))
			{
				//Check for Triangle_2
				pmatIp_Old = Matrix::MatrixMultiply(*pMatTrans_Old[16],matOp);
				pmatIp_Baby = Matrix::MatrixMultiply(*pMatTrans_Baby[16],matOp);
				
				dX_1 = pmatIp_Old->GetElement(0,0);
				dY_1 = pmatIp_Old->GetElement(1,0);

				dX_2 = pmatIp_Baby->GetElement(0,0);
				dY_2 = pmatIp_Baby->GetElement(1,0);

				pmatIp_Old->FreeMemory();
				pmatIp_Baby->FreeMemory();
				delete pmatIp_Baby;
				delete pmatIp_Old;
			}
			else if(ptP.LiesWithinTriangle(ptaOP[17]))
			{
				//Check for Triangle_2
				pmatIp_Old = Matrix::MatrixMultiply(*pMatTrans_Old[17],matOp);
				pmatIp_Baby = Matrix::MatrixMultiply(*pMatTrans_Baby[17],matOp);
				
				dX_1 = pmatIp_Old->GetElement(0,0);
				dY_1 = pmatIp_Old->GetElement(1,0);

				dX_2 = pmatIp_Baby->GetElement(0,0);
				dY_2 = pmatIp_Baby->GetElement(1,0);

				pmatIp_Old->FreeMemory();
				pmatIp_Baby->FreeMemory();
				delete pmatIp_Baby;
				delete pmatIp_Old;
			}
			else if(ptP.LiesWithinTriangle(ptaOP[18]))
			{
				//Check for Triangle_2
				pmatIp_Old = Matrix::MatrixMultiply(*pMatTrans_Old[18],matOp);
				pmatIp_Baby = Matrix::MatrixMultiply(*pMatTrans_Baby[18],matOp);
				
				dX_1 = pmatIp_Old->GetElement(0,0);
				dY_1 = pmatIp_Old->GetElement(1,0);

				dX_2 = pmatIp_Baby->GetElement(0,0);
				dY_2 = pmatIp_Baby->GetElement(1,0);

				pmatIp_Old->FreeMemory();
				pmatIp_Baby->FreeMemory();
				delete pmatIp_Baby;
				delete pmatIp_Old;
			}
			else if(ptP.LiesWithinTriangle(ptaOP[19]))
			{
				//Check for Triangle_2
				pmatIp_Old = Matrix::MatrixMultiply(*pMatTrans_Old[19],matOp);
				pmatIp_Baby = Matrix::MatrixMultiply(*pMatTrans_Baby[19],matOp);
				
				dX_1 = pmatIp_Old->GetElement(0,0);
				dY_1 = pmatIp_Old->GetElement(1,0);

				dX_2 = pmatIp_Baby->GetElement(0,0);
				dY_2 = pmatIp_Baby->GetElement(1,0);

				pmatIp_Old->FreeMemory();
				pmatIp_Baby->FreeMemory();
				delete pmatIp_Baby;
				delete pmatIp_Old;
			}
			else if(ptP.LiesWithinTriangle(ptaOP[20]))
			{
				//Check for Triangle_2
				pmatIp_Old = Matrix::MatrixMultiply(*pMatTrans_Old[20],matOp);
				pmatIp_Baby = Matrix::MatrixMultiply(*pMatTrans_Baby[20],matOp);
				
				dX_1 = pmatIp_Old->GetElement(0,0);
				dY_1 = pmatIp_Old->GetElement(1,0);

				dX_2 = pmatIp_Baby->GetElement(0,0);
				dY_2 = pmatIp_Baby->GetElement(1,0);

				pmatIp_Old->FreeMemory();
				pmatIp_Baby->FreeMemory();
				delete pmatIp_Baby;
				delete pmatIp_Old;
			}
			else if(ptP.LiesWithinTriangle(ptaOP[21]))
			{
				//Check for Triangle_2
				pmatIp_Old = Matrix::MatrixMultiply(*pMatTrans_Old[21],matOp);
				pmatIp_Baby = Matrix::MatrixMultiply(*pMatTrans_Baby[21],matOp);
				
				dX_1 = pmatIp_Old->GetElement(0,0);
				dY_1 = pmatIp_Old->GetElement(1,0);

				dX_2 = pmatIp_Baby->GetElement(0,0);
				dY_2 = pmatIp_Baby->GetElement(1,0);

				pmatIp_Old->FreeMemory();
				pmatIp_Baby->FreeMemory();
				delete pmatIp_Baby;
				delete pmatIp_Old;
			}
			else if(ptP.LiesWithinTriangle(ptaOP[0]))
			{
				//Check for Triangle_2
				pmatIp_Old = Matrix::MatrixMultiply(*pMatTrans_Old[0],matOp);
				pmatIp_Baby = Matrix::MatrixMultiply(*pMatTrans_Baby[0],matOp);
				
				dX_1 = pmatIp_Old->GetElement(0,0);
				dY_1 = pmatIp_Old->GetElement(1,0);

				dX_2 = pmatIp_Baby->GetElement(0,0);
				dY_2 = pmatIp_Baby->GetElement(1,0);

				pmatIp_Old->FreeMemory();
				pmatIp_Baby->FreeMemory();
				delete pmatIp_Baby;
				delete pmatIp_Old;
			}
			
			Pixel *pxP_1 = imBabyDrew.GetPixel(dX_2,dY_2);
			Pixel *pxP_2 = imDrew.GetPixel(dX_1,dY_1);
			
			imBabyDrewA.SetPixel(i,j,*pxP_1);
			imDrewA.SetPixel(i,j,*pxP_2);

			delete pxP_1, pxP_2;
		}		
	}

	imBabyDrewA.WriteImageData();
	imDrewA.WriteImageData();
	
	//Transition
	for(float alpha = 0.00;alpha<=1.09;alpha += 0.025)
	{
		string strResult;
		char szResult[20];
		sprintf(szResult,"Result_Drew_%d.raw",(int)(alpha*40));
		strResult = string::basic_string(szResult);
		pimResult->SetImageName(strResult);

		for(int i = 0;i<iRows;i++)
		{
			for(int j = 0;j<iCols;j++)
			{				
				int cR, cB, cG;

				cR = (1 - alpha)*imDrewA.GetRed(i,j) + alpha*imBabyDrewA.GetRed(i,j);
				cG = (1 - alpha)*imDrewA.GetGreen(i,j) + alpha*imBabyDrewA.GetGreen(i,j);
				cB = (1 - alpha)*imDrewA.GetBlue(i,j) + alpha*imBabyDrewA.GetBlue(i,j);

				Pixel pxPResult(cR,cG,cB,i,j);

				pimResult->SetPixel(i,j,pxPResult);
			}
		}

		pimResult->WriteImageData();
	}

	cout<<"\n Press 'C' to continue..";
	getch();
}

void Problem_1_C_b()
{
	Image imBruce, imHulk, *pimBruceA, *pimHulkA, *pimResult = new Image(), imBruceA;
	int iRows = 400, iCols = 400;
	string strName[5] = {"bruce_banner.raw","hulk.raw","bruceA.raw","hulkA.raw","Result.raw"};

	InitImage(&imBruce,strName[0],iRows,iCols,3);
	InitImage(&imHulk,strName[1],iRows,iCols,3);
	InitImage(&imBruceA,strName[2],iRows,iCols,3);
	InitImage(pimResult,string::basic_string(""),iRows,iCols,3);

	imBruce.ReadImageData();
	imHulk.ReadImageData();

	//Alignment
	Point ptaPts_B[7], ptaPts_H[7], ptaPtf_BW[7], ptaPtf_HW[7];
	
	//Control Points for Hulk
	ptaPts_H[0].SetPoint(0,0);
	ptaPts_H[1].SetPoint(0,399);
	ptaPts_H[2].SetPoint(399,399);
	ptaPts_H[3].SetPoint(399,0);
	ptaPts_H[4].SetPoint(176,195);
	ptaPts_H[5].SetPoint(340,90);
	ptaPts_H[6].SetPoint(328,322);	

	//Triangles
	Point ptaTr_H[8][3] =  {	{ptaPts_H[0], ptaPts_H[1], ptaPts_H[4]},
											{ptaPts_H[3], ptaPts_H[0], ptaPts_H[5]},
											{ptaPts_H[5], ptaPts_H[0], ptaPts_H[4]},
											{ptaPts_H[5], ptaPts_H[4], ptaPts_H[6]},
											{ptaPts_H[4], ptaPts_H[1], ptaPts_H[6]},
											{ptaPts_H[6], ptaPts_H[1], ptaPts_H[2]},
											{ptaPts_H[3], ptaPts_H[5], ptaPts_H[2]},
											{ptaPts_H[5], ptaPts_H[6], ptaPts_H[2]},
										};

	//Control Points for Bruce Banner
	ptaPts_B[0].SetPoint(0,0);
	ptaPts_B[1].SetPoint(0,399);
	ptaPts_B[2].SetPoint(399,399);
	ptaPts_B[3].SetPoint(399,0);
	ptaPts_B[4].SetPoint(168,192);
	ptaPts_B[5].SetPoint(338,104);
	ptaPts_B[6].SetPoint(340,304);	
	
	//Triangles
	Point ptaTr_B[8][3] =   {	{ptaPts_B[0], ptaPts_B[1], ptaPts_B[4]},
											{ptaPts_B[3], ptaPts_B[0], ptaPts_B[5]},
											{ptaPts_B[5], ptaPts_B[0], ptaPts_B[4]},
											{ptaPts_B[5], ptaPts_B[4], ptaPts_B[6]},
											{ptaPts_B[4], ptaPts_B[1], ptaPts_B[6]},
											{ptaPts_B[6], ptaPts_B[1], ptaPts_B[2]},
											{ptaPts_B[3], ptaPts_B[5], ptaPts_B[2]},
											{ptaPts_B[5], ptaPts_B[6], ptaPts_B[2]},
										};

	//Warping
	Matrix **pMatTransHW, **pMatTransBW;
	double alpha = 0.00;

	for(int i = 0;i<=20;i++)
	{
		double dX, dY;
		for(int j = 0;j<7;j++)//7 Points
		{
			dX = ptaPts_H[j].iX - ptaPts_B[j].iX;
			dY = ptaPts_H[j].iY - ptaPts_B[j].iY;
			ptaPtf_BW[j].iX = ptaPts_B[j].iX + dX*i/20;
			ptaPtf_BW[j].iY = ptaPts_B[j].iY + dY*i/20;

			dX = ptaPts_B[j].iX - ptaPts_H[j].iX;
			dY = ptaPts_B[j].iY - ptaPts_H[j].iY;
			ptaPtf_HW[j].iX = ptaPts_B[j].iX - dX*i/20;
			ptaPtf_HW[j].iY = ptaPts_B[j].iY - dY*i/20;
		}

		//Triangles for Bruce Warped 8 triangles
		Point ptaTr_BW[8][3] = {	{ptaPtf_BW[0], ptaPtf_BW[1], ptaPtf_BW[4]},
											{ptaPtf_BW[3], ptaPtf_BW[0], ptaPtf_BW[5]},
											{ptaPtf_BW[5], ptaPtf_BW[0], ptaPtf_BW[4]},
											{ptaPtf_BW[5], ptaPtf_BW[4], ptaPtf_BW[6]},
											{ptaPtf_BW[4], ptaPtf_BW[1], ptaPtf_BW[6]},
											{ptaPtf_BW[6], ptaPtf_BW[1], ptaPtf_BW[2]},
											{ptaPtf_BW[3], ptaPtf_BW[5], ptaPtf_BW[2]},
											{ptaPtf_BW[5], ptaPtf_BW[6], ptaPtf_BW[2]},										
											};
		Point ptaTr_HW[8][3] = {	{ptaPtf_HW[0], ptaPtf_HW[1], ptaPtf_HW[4]},
											{ptaPtf_HW[3], ptaPtf_HW[0], ptaPtf_HW[5]},
											{ptaPtf_HW[5], ptaPtf_HW[0], ptaPtf_HW[4]},
											{ptaPtf_HW[5], ptaPtf_HW[4], ptaPtf_HW[6]},
											{ptaPtf_HW[4], ptaPtf_HW[1], ptaPtf_HW[6]},
											{ptaPtf_HW[6], ptaPtf_HW[1], ptaPtf_HW[2]},
											{ptaPtf_HW[3], ptaPtf_HW[5], ptaPtf_HW[2]},
											{ptaPtf_HW[5], ptaPtf_HW[6], ptaPtf_HW[2]},										
											};

		pMatTransBW = FindTransMatrix(ptaTr_B,ptaTr_BW,8);
		pMatTransHW = FindTransMatrix(ptaTr_H,ptaTr_HW,8);

		for(int a = 0;a<iRows;a++)
		{
			for(int b = 0;b<iCols;b++)
			{
				double dU = (double)(a); ///350.00;
				double dV = (double)(b); ///300.00;
				double dX_1, dY_1, dX_2,dY_2;
				Point ptP(dU,dV);			
										
				Matrix *pmatIp_B;
				Matrix matOp(3,1);
				
				matOp.SetElement(0,0,1.00);
				matOp.SetElement(1,0,ptP.iX);
				matOp.SetElement(2,0,ptP.iY);
							
				dX_1 = -1;
				dY_1 = -1;

				dX_2 = -1;
				dY_2 = -1;
				
				for(int t = 0;t<8;t++)
				{
					if(ptP.LiesWithinTriangle(ptaTr_BW[t]))
					{
						//Check for Triangle_1								
						pmatIp_B = Matrix::MatrixMultiply(*pMatTransBW[t],matOp);				
						
						dX_1 = pmatIp_B->GetElement(0,0);
						dY_1 = pmatIp_B->GetElement(1,0);						

						pmatIp_B->FreeMemory();						
						delete pmatIp_B;						
						//break;
					}
					
					if(ptP.LiesWithinTriangle(ptaTr_HW[t]))
					{
						//Check for Triangle_1								
						pmatIp_B = Matrix::MatrixMultiply(*pMatTransHW[t],matOp);				
						
						dX_2 = pmatIp_B->GetElement(0,0);
						dY_2 = pmatIp_B->GetElement(1,0);						

						pmatIp_B->FreeMemory();						
						delete pmatIp_B;						
						//break;
					}
				}
								
				if((dX_1 < 0 && dY_1 < 0) || (dX_1 > 400 || dY_1 > 400) || (dX_2 < 0 && dY_2 < 0) || (dX_2 > 400 || dY_2 > 400))
				{
					Pixel pxPB(0);
					imBruceA.SetPixel(a,b,pxPB);
				}
				else
				{
					Pixel *pxP_1 = imBruce.GetPixel(dX_1,dY_1);
					Pixel *pxP_2 = imHulk.GetPixel(dX_2,dY_2);

					int cR, cB, cG;

					cR = (1 - alpha)*pxP_1->GetRed() + alpha*pxP_2->GetRed();
					cG = (1 - alpha)*pxP_1->GetGreen() + alpha*pxP_2->GetGreen();
					cB = (1 - alpha)*pxP_1->GetBlue() + alpha*pxP_2->GetBlue();

					Pixel pxPResult(cR,cG,cB,a,b);					
					imBruceA.SetPixel(a,b,pxPResult);
					delete pxP_1;
					delete pxP_2;
				}			
			}
		}

		string strBW;
		char szBW[30];
		sprintf(szBW,"Result_BW_7Point_%d.raw",i);

		strBW = string::basic_string(szBW);
		imBruceA.SetImageName(strBW);
		imBruceA.WriteImageData();

		alpha = (double)i/20.00*1.00;
//		pMatTransBW[i]->FreeMemory();
	//	pMatTransHW[i]->FreeMemory();
	}
	
	//Matrix **pMatTransBH = FindTransMatrix(ptaTr_B,ptaTr_H,63);
	//
	////Warp Bruce Image Image
	//for(int i = 0;i<iRows;i++)
	//{
	//	for(int j = 0;j<iCols;j++)
	//	{
	//		double dU = (double)(i); ///350.00;
	//		double dV = (double)(j); ///300.00;
	//		double dX_1, dY_1, dX_2,dY_2;
	//		Point ptP(dU,dV);			
	//								
	//		Matrix *pmatIp_B;
	//		Matrix matOp(3,1);
	//		
	//		matOp.SetElement(0,0,1.00);
	//		matOp.SetElement(1,0,ptP.iX);
	//		matOp.SetElement(2,0,ptP.iY);
	//					
	//		dX_1 = -1;
	//		dY_1 = -1;
	//		
	//		for(int t = 0;t<63;t++)
	//		{
	//			if(ptP.LiesWithinTriangle(ptaTr_H[t]))
	//			{
	//				//Check for Triangle_1								
	//				pmatIp_B = Matrix::MatrixMultiply(*pMatTransBH[t],matOp);				
	//				
	//				dX_1 = pmatIp_B->GetElement(0,0);
	//				dY_1 = pmatIp_B->GetElement(1,0);
	//
	//				//dX_2 = pmatIp_Baby->GetElement(0,0);
	//				//dY_2 = pmatIp_Baby->GetElement(1,0);
	//
	//				pmatIp_B->FreeMemory();
	//				//pmatIp_Baby->FreeMemory();
	//				delete pmatIp_B;
	//				//delete pmatIp_Old;
	//				break;
	//			}
	//			
	//		}
	//		
	//		//cout<<"\ni:  "<<i<<"   j:  "<<j;
	//		if((dX_1 < 0 && dY_1 < 0) || (dX_1 > 400 || dY_1 > 400))
	//		{
	//			Pixel pxPB(125);				
	//			imBruceA.SetPixel(i,j,pxPB);
	//		}
	//		else
	//		{
	//			Pixel *pxP_1 = imBruce.GetPixel(dX_1,dY_1);
	//			imBruceA.SetPixel(i,j,*pxP_1);
	//			delete pxP_1;
	//		}			
	//	}
	//}
	//
	//imBruceA.WriteImageData();

	//Transition
	//for(float alpha = 0.00;alpha<=1.09;alpha += 0.025)
	//{
	//	string strResult;
	//	char szResult[20];
	//	sprintf(szResult,"Result_BH_%d.raw",(int)(alpha*40));
	//	strResult = string::basic_string(szResult);
	//	pimResult->SetImageName(strResult);
	//
	//	for(int i = 0;i<iRows;i++)
	//	{
	//		for(int j = 0;j<iCols;j++)
	//		{				
	//			int cR, cB, cG;
	//
	//			cR = (1 - alpha)*imBruceA.GetRed(i,j) + alpha*imHulk.GetRed(i,j);
	//			cG = (1 - alpha)*imBruceA.GetGreen(i,j) + alpha*imHulk.GetGreen(i,j);
	//			cB = (1 - alpha)*imBruceA.GetBlue(i,j) + alpha*imHulk.GetBlue(i,j);
	//
	//			Pixel pxPResult(cR,cG,cB,i,j);
	//
	//			pimResult->SetPixel(i,j,pxPResult);
	//		}
	//	}
	//
	//	pimResult->WriteImageData();
	//}

	cout<<"\n Press 'C' to continue..";
	getch();	
}

void Problem_1_B()
{
	//Drew Old to Young Improved
	Image imBruce, imHulk, *pimBruceA, *pimHulkA, *pimResult = new Image(), imBruceA;
	int iRows = 350, iCols = 300;
	string strName[5] = {"old_drew.raw","young_drew.raw","oldA.raw","youngA.raw","Result.raw"};

	InitImage(&imBruce,strName[0],iRows,iCols,3);
	InitImage(&imHulk,strName[1],iRows,iCols,3);
	InitImage(&imBruceA,strName[2],iRows,iCols,3);
	InitImage(pimResult,string::basic_string(""),iRows,iCols,3);

	imBruce.ReadImageData();
	imHulk.ReadImageData();

	//Alignment
	Point ptaPts_B[36], ptaPts_H[36], ptaPtf_BW[36], ptaPtf_HW[36];
	
	//Control Points for Young
	ptaPts_H[0].SetPoint(0,0);
	ptaPts_H[1].SetPoint(0,299);
	ptaPts_H[2].SetPoint(349,299);
	ptaPts_H[3].SetPoint(349,0);
	ptaPts_H[4].SetPoint(159,148);
	ptaPts_H[5].SetPoint(318,89);
	ptaPts_H[6].SetPoint(309,220);
	ptaPts_H[7].SetPoint(263,105);
	ptaPts_H[8].SetPoint(268,190);
	ptaPts_H[9].SetPoint(233,118);
	ptaPts_H[10].SetPoint(236,176);
	ptaPts_H[11].SetPoint(262,145);
	ptaPts_H[12].SetPoint(272,146);
	ptaPts_H[13].SetPoint(272,146);
	ptaPts_H[14].SetPoint(282,147);
	ptaPts_H[15].SetPoint(338,127);
	ptaPts_H[16].SetPoint(334,187);
	ptaPts_H[17].SetPoint(349,149);
	ptaPts_H[18].SetPoint(181,178);
	ptaPts_H[19].SetPoint(180,120);
	ptaPts_H[20].SetPoint(180,234);
	ptaPts_H[21].SetPoint(176,73);
	ptaPts_H[22].SetPoint(189,97);
	ptaPts_H[23].SetPoint(193,202);
	ptaPts_H[24].SetPoint(157,21);
	ptaPts_H[25].SetPoint(161,277);
	ptaPts_H[26].SetPoint(197,15);
	ptaPts_H[27].SetPoint(203,279);
	ptaPts_H[28].SetPoint(192,42);
	ptaPts_H[29].SetPoint(200,255);
	ptaPts_H[30].SetPoint(243,254);
	ptaPts_H[31].SetPoint(235,39);
	ptaPts_H[32].SetPoint(279,239);
	ptaPts_H[33].SetPoint(287,62);
	ptaPts_H[34].SetPoint(158,98);
	ptaPts_H[35].SetPoint(156,205);
	//Triangles
	Point ptaTr_H[63][3] = {	{ptaPts_H[1-1], ptaPts_H[2-1], ptaPts_H[5-1]},
											{ptaPts_H[1-1], ptaPts_H[5-1], ptaPts_H[35-1]},
											{ptaPts_H[1-1], ptaPts_H[35-1], ptaPts_H[22-1]},
											{ptaPts_H[1-1], ptaPts_H[22-1], ptaPts_H[25-1]},
											{ptaPts_H[1-1], ptaPts_H[25-1], ptaPts_H[27-1]},
											{ptaPts_H[1-1], ptaPts_H[27-1], ptaPts_H[4-1]},
											{ptaPts_H[22-1], ptaPts_H[35-1], ptaPts_H[20-1]},
											{ptaPts_H[22-1], ptaPts_H[20-1], ptaPts_H[23-1]},
											{ptaPts_H[25-1], ptaPts_H[22-1], ptaPts_H[23-1]},
											{ptaPts_H[25-1], ptaPts_H[23-1], ptaPts_H[29-1]},
											{ptaPts_H[32-1], ptaPts_H[25-1], ptaPts_H[29-1]},
											{ptaPts_H[27-1], ptaPts_H[25-1], ptaPts_H[32-1]},
											{ptaPts_H[4-1], ptaPts_H[27-1], ptaPts_H[32-1]},
											{ptaPts_H[35-1], ptaPts_H[5-1], ptaPts_H[20-1]},
											{ptaPts_H[20-1], ptaPts_H[5-1], ptaPts_H[10-1]},
											{ptaPts_H[23-1], ptaPts_H[20-1], ptaPts_H[10-1]},
											{ptaPts_H[29-1], ptaPts_H[23-1], ptaPts_H[10-1]},
											{ptaPts_H[29-1], ptaPts_H[10-1], ptaPts_H[8-1]},
											{ptaPts_H[32-1], ptaPts_H[29-1], ptaPts_H[8-1]},
											{ptaPts_H[32-1], ptaPts_H[8-1], ptaPts_H[34-1]},
											{ptaPts_H[4-1], ptaPts_H[32-1], ptaPts_H[34-1]},
											{ptaPts_H[10-1], ptaPts_H[5-1], ptaPts_H[11-1]},
											{ptaPts_H[10-1], ptaPts_H[11-1], ptaPts_H[12-1]},
											{ptaPts_H[8-1], ptaPts_H[10-1], ptaPts_H[12-1]},
											{ptaPts_H[8-1], ptaPts_H[12-1], ptaPts_H[13-1]},
											{ptaPts_H[8-1], ptaPts_H[14-1], ptaPts_H[15-1]},
											{ptaPts_H[6-1], ptaPts_H[8-1], ptaPts_H[15-1]},
											{ptaPts_H[34-1], ptaPts_H[8-1], ptaPts_H[6-1]},
											{ptaPts_H[4-1], ptaPts_H[34-1], ptaPts_H[6-1]},
											{ptaPts_H[16-1], ptaPts_H[15-1], ptaPts_H[17-1]},
											{ptaPts_H[6-1], ptaPts_H[15-1], ptaPts_H[16-1]},
											{ptaPts_H[4-1], ptaPts_H[6-1], ptaPts_H[16-1]},
											{ptaPts_H[4-1], ptaPts_H[16-1], ptaPts_H[18-1]},
											{ptaPts_H[16-1], ptaPts_H[17-1], ptaPts_H[18-1]},
											{ptaPts_H[18-1], ptaPts_H[17-1], ptaPts_H[3-1]},
											{ptaPts_H[17-1], ptaPts_H[7-1], ptaPts_H[3-1]},
											{ptaPts_H[15-1], ptaPts_H[7-1], ptaPts_H[17-1]},
											{ptaPts_H[15-1], ptaPts_H[9-1], ptaPts_H[7-1]},
											{ptaPts_H[7-1], ptaPts_H[33-1], ptaPts_H[3-1]},
											{ptaPts_H[9-1], ptaPts_H[33-1], ptaPts_H[7-1]},
											{ptaPts_H[9-1], ptaPts_H[31-1], ptaPts_H[33-1]},
											{ptaPts_H[33-1], ptaPts_H[31-1], ptaPts_H[3-1]},
											{ptaPts_H[12-1], ptaPts_H[11-1], ptaPts_H[9-1]},
											{ptaPts_H[11-1], ptaPts_H[30-1], ptaPts_H[9-1]},
											{ptaPts_H[9-1], ptaPts_H[30-1], ptaPts_H[31-1]},
											{ptaPts_H[5-1], ptaPts_H[19-1], ptaPts_H[11-1]},
											{ptaPts_H[11-1], ptaPts_H[19-1], ptaPts_H[24-1]},
											{ptaPts_H[11-1], ptaPts_H[24-1], ptaPts_H[30-1]},
											{ptaPts_H[5-1], ptaPts_H[36-1], ptaPts_H[19-1]},
											{ptaPts_H[19-1], ptaPts_H[36-1], ptaPts_H[21-1]},
											{ptaPts_H[19-1], ptaPts_H[21-1], ptaPts_H[24-1]},
											{ptaPts_H[24-1], ptaPts_H[21-1], ptaPts_H[26-1]},
											{ptaPts_H[24-1], ptaPts_H[26-1], ptaPts_H[30-1]},
											{ptaPts_H[30-1], ptaPts_H[26-1], ptaPts_H[31-1]},
											{ptaPts_H[26-1], ptaPts_H[28-1], ptaPts_H[31-1]},
											{ptaPts_H[31-1], ptaPts_H[28-1], ptaPts_H[3-1]},
											{ptaPts_H[5-1], ptaPts_H[2-1], ptaPts_H[36-1]},
											{ptaPts_H[36-1], ptaPts_H[2-1], ptaPts_H[21-1]},
											{ptaPts_H[21-1], ptaPts_H[2-1], ptaPts_H[26-1]},
											{ptaPts_H[26-1], ptaPts_H[2-1], ptaPts_H[28-1]},
											{ptaPts_H[28-1], ptaPts_H[2-1], ptaPts_H[3-1]},
											{ptaPts_H[13-1], ptaPts_H[12-1], ptaPts_H[9-1]},
											{ptaPts_H[14-1], ptaPts_H[9-1], ptaPts_H[15-1]},
										};

	//Control Points for Old
	ptaPts_B[0].SetPoint(0,0);
	ptaPts_B[1].SetPoint(0,299);
	ptaPts_B[2].SetPoint(349,299);
	ptaPts_B[3].SetPoint(349,0);
	ptaPts_B[4].SetPoint(167,150);
	ptaPts_B[5].SetPoint(321,99);
	ptaPts_B[6].SetPoint(317,206);
	ptaPts_B[7].SetPoint(272,110);
	ptaPts_B[8].SetPoint(270,191);
	ptaPts_B[9].SetPoint(241,124);
	ptaPts_B[10].SetPoint(240,177);
	ptaPts_B[11].SetPoint(266,151);
	ptaPts_B[12].SetPoint(276,151);
	ptaPts_B[13].SetPoint(276,151);
	ptaPts_B[14].SetPoint(298,152);
	ptaPts_B[15].SetPoint(339,130);
	ptaPts_B[16].SetPoint(329,193);
	ptaPts_B[17].SetPoint(349,149);
	ptaPts_B[18].SetPoint(174,174);
	ptaPts_B[19].SetPoint(179,123);
	ptaPts_B[20].SetPoint(171,231);
	ptaPts_B[21].SetPoint(177,69);
	ptaPts_B[22].SetPoint(187,99);
	ptaPts_B[23].SetPoint(182,204);
	ptaPts_B[24].SetPoint(164,24);
	ptaPts_B[25].SetPoint(139,269);
	ptaPts_B[26].SetPoint(199,35);
	ptaPts_B[27].SetPoint(187,272);
	ptaPts_B[28].SetPoint(195,49);
	ptaPts_B[29].SetPoint(181,254);
	ptaPts_B[30].SetPoint(225,253);
	ptaPts_B[31].SetPoint(231,53);
	ptaPts_B[32].SetPoint(268,239);
	ptaPts_B[33].SetPoint(278,66);
	ptaPts_B[34].SetPoint(160,97);
	ptaPts_B[35].SetPoint(156,262);
	//Triangles
	Point ptaTr_B[63][3] = {	{ptaPts_B[1-1], ptaPts_B[2-1], ptaPts_B[5-1]},
											{ptaPts_B[1-1], ptaPts_B[5-1], ptaPts_B[35-1]},
											{ptaPts_B[1-1], ptaPts_B[35-1], ptaPts_B[22-1]},
											{ptaPts_B[1-1], ptaPts_B[22-1], ptaPts_B[25-1]},
											{ptaPts_B[1-1], ptaPts_B[25-1], ptaPts_B[27-1]},
											{ptaPts_B[1-1], ptaPts_B[27-1], ptaPts_B[4-1]},
											{ptaPts_B[22-1], ptaPts_B[35-1], ptaPts_B[20-1]},
											{ptaPts_B[22-1], ptaPts_B[20-1], ptaPts_B[23-1]},
											{ptaPts_B[25-1], ptaPts_B[22-1], ptaPts_B[23-1]},
											{ptaPts_B[25-1], ptaPts_B[23-1], ptaPts_B[29-1]},
											{ptaPts_B[32-1], ptaPts_B[25-1], ptaPts_B[29-1]},
											{ptaPts_B[27-1], ptaPts_B[25-1], ptaPts_B[32-1]},
											{ptaPts_B[4-1], ptaPts_B[27-1], ptaPts_B[32-1]},
											{ptaPts_B[35-1], ptaPts_B[5-1], ptaPts_B[20-1]},
											{ptaPts_B[20-1], ptaPts_B[5-1], ptaPts_B[10-1]},
											{ptaPts_B[23-1], ptaPts_B[20-1], ptaPts_B[10-1]},
											{ptaPts_B[29-1], ptaPts_B[23-1], ptaPts_B[10-1]},
											{ptaPts_B[29-1], ptaPts_B[10-1], ptaPts_B[8-1]},
											{ptaPts_B[32-1], ptaPts_B[29-1], ptaPts_B[8-1]},
											{ptaPts_B[32-1], ptaPts_B[8-1], ptaPts_B[34-1]},
											{ptaPts_B[4-1], ptaPts_B[32-1], ptaPts_B[34-1]},
											{ptaPts_B[10-1], ptaPts_B[5-1], ptaPts_B[11-1]},
											{ptaPts_B[10-1], ptaPts_B[11-1], ptaPts_B[12-1]},
											{ptaPts_B[8-1], ptaPts_B[10-1], ptaPts_B[12-1]},
											{ptaPts_B[8-1], ptaPts_B[12-1], ptaPts_B[13-1]},
											{ptaPts_B[8-1], ptaPts_B[14-1], ptaPts_B[15-1]},
											{ptaPts_B[6-1], ptaPts_B[8-1], ptaPts_B[15-1]},
											{ptaPts_B[34-1], ptaPts_B[8-1], ptaPts_B[6-1]},
											{ptaPts_B[4-1], ptaPts_B[34-1], ptaPts_B[6-1]},
											{ptaPts_B[16-1], ptaPts_B[15-1], ptaPts_B[17-1]},
											{ptaPts_B[6-1], ptaPts_B[15-1], ptaPts_B[16-1]},
											{ptaPts_B[4-1], ptaPts_B[6-1], ptaPts_B[16-1]},
											{ptaPts_B[4-1], ptaPts_B[16-1], ptaPts_B[18-1]},
											{ptaPts_B[16-1], ptaPts_B[17-1], ptaPts_B[18-1]},
											{ptaPts_B[18-1], ptaPts_B[17-1], ptaPts_B[3-1]},
											{ptaPts_B[17-1], ptaPts_B[7-1], ptaPts_B[3-1]},
											{ptaPts_B[15-1], ptaPts_B[7-1], ptaPts_B[17-1]},
											{ptaPts_B[15-1], ptaPts_B[9-1], ptaPts_B[7-1]},
											{ptaPts_B[7-1], ptaPts_B[33-1], ptaPts_B[3-1]},
											{ptaPts_B[9-1], ptaPts_B[33-1], ptaPts_B[7-1]},
											{ptaPts_B[9-1], ptaPts_B[31-1], ptaPts_B[33-1]},
											{ptaPts_B[33-1], ptaPts_B[31-1], ptaPts_B[3-1]},
											{ptaPts_B[12-1], ptaPts_B[11-1], ptaPts_B[9-1]},
											{ptaPts_B[11-1], ptaPts_B[30-1], ptaPts_B[9-1]},
											{ptaPts_B[9-1], ptaPts_B[30-1], ptaPts_B[31-1]},
											{ptaPts_B[5-1], ptaPts_B[19-1], ptaPts_B[11-1]},
											{ptaPts_B[11-1], ptaPts_B[19-1], ptaPts_B[24-1]},
											{ptaPts_B[11-1], ptaPts_B[24-1], ptaPts_B[30-1]},
											{ptaPts_B[5-1], ptaPts_B[36-1], ptaPts_B[19-1]},
											{ptaPts_B[19-1], ptaPts_B[36-1], ptaPts_B[21-1]},
											{ptaPts_B[19-1], ptaPts_B[21-1], ptaPts_B[24-1]},
											{ptaPts_B[24-1], ptaPts_B[21-1], ptaPts_B[26-1]},
											{ptaPts_B[24-1], ptaPts_B[26-1], ptaPts_B[30-1]},
											{ptaPts_B[30-1], ptaPts_B[26-1], ptaPts_B[31-1]},
											{ptaPts_B[26-1], ptaPts_B[28-1], ptaPts_B[31-1]},
											{ptaPts_B[31-1], ptaPts_B[28-1], ptaPts_B[3-1]},
											{ptaPts_B[5-1], ptaPts_B[2-1], ptaPts_B[36-1]},
											{ptaPts_B[36-1], ptaPts_B[2-1], ptaPts_B[21-1]},
											{ptaPts_B[21-1], ptaPts_B[2-1], ptaPts_B[26-1]},
											{ptaPts_B[26-1], ptaPts_B[2-1], ptaPts_B[28-1]},
											{ptaPts_B[28-1], ptaPts_B[2-1], ptaPts_B[3-1]},
											{ptaPts_B[13-1], ptaPts_B[12-1], ptaPts_B[9-1]},
											{ptaPts_B[14-1], ptaPts_B[9-1], ptaPts_B[15-1]},
										};

	//Warping
	Matrix **pMatTransHW, **pMatTransBW;
	double alpha = 0.00;

	for(int i = 0;i<=60;i++)
	{
		double dX, dY;
		for(int j = 0;j<36;j++)//36 Points
		{
			dX = ptaPts_H[j].iX - ptaPts_B[j].iX;
			dY = ptaPts_H[j].iY - ptaPts_B[j].iY;
			ptaPtf_BW[j].iX = ptaPts_B[j].iX + dX*i/60;
			ptaPtf_BW[j].iY = ptaPts_B[j].iY + dY*i/60;

			dX = ptaPts_B[j].iX - ptaPts_H[j].iX;
			dY = ptaPts_B[j].iY - ptaPts_H[j].iY;
			ptaPtf_HW[j].iX = ptaPts_B[j].iX - dX*i/60;
			ptaPtf_HW[j].iY = ptaPts_B[j].iY - dY*i/60;
		}

		//Triangles for Bruce Warped 63 triangles
		Point ptaTr_BW[63][3] = {	{ptaPtf_BW[1-1], ptaPtf_BW[2-1], ptaPtf_BW[5-1]},
												{ptaPtf_BW[1-1], ptaPtf_BW[5-1], ptaPtf_BW[35-1]},
												{ptaPtf_BW[1-1], ptaPtf_BW[35-1], ptaPtf_BW[22-1]},
												{ptaPtf_BW[1-1], ptaPtf_BW[22-1], ptaPtf_BW[25-1]},
												{ptaPtf_BW[1-1], ptaPtf_BW[25-1], ptaPtf_BW[27-1]},
												{ptaPtf_BW[1-1], ptaPtf_BW[27-1], ptaPtf_BW[4-1]},
												{ptaPtf_BW[22-1], ptaPtf_BW[35-1], ptaPtf_BW[20-1]},
												{ptaPtf_BW[22-1], ptaPtf_BW[20-1], ptaPtf_BW[23-1]},
												{ptaPtf_BW[25-1], ptaPtf_BW[22-1], ptaPtf_BW[23-1]},
												{ptaPtf_BW[25-1], ptaPtf_BW[23-1], ptaPtf_BW[29-1]},
												{ptaPtf_BW[32-1], ptaPtf_BW[25-1], ptaPtf_BW[29-1]},
												{ptaPtf_BW[27-1], ptaPtf_BW[25-1], ptaPtf_BW[32-1]},
												{ptaPtf_BW[4-1], ptaPtf_BW[27-1], ptaPtf_BW[32-1]},
												{ptaPtf_BW[35-1], ptaPtf_BW[5-1], ptaPtf_BW[20-1]},
												{ptaPtf_BW[20-1], ptaPtf_BW[5-1], ptaPtf_BW[10-1]},
												{ptaPtf_BW[23-1], ptaPtf_BW[20-1], ptaPtf_BW[10-1]},
												{ptaPtf_BW[29-1], ptaPtf_BW[23-1], ptaPtf_BW[10-1]},
												{ptaPtf_BW[29-1], ptaPtf_BW[10-1], ptaPtf_BW[8-1]},
												{ptaPtf_BW[32-1], ptaPtf_BW[29-1], ptaPtf_BW[8-1]},
												{ptaPtf_BW[32-1], ptaPtf_BW[8-1], ptaPtf_BW[34-1]},
												{ptaPtf_BW[4-1], ptaPtf_BW[32-1], ptaPtf_BW[34-1]},
												{ptaPtf_BW[10-1], ptaPtf_BW[5-1], ptaPtf_BW[11-1]},
												{ptaPtf_BW[10-1], ptaPtf_BW[11-1], ptaPtf_BW[12-1]},
												{ptaPtf_BW[8-1], ptaPtf_BW[10-1], ptaPtf_BW[12-1]},
												{ptaPtf_BW[8-1], ptaPtf_BW[12-1], ptaPtf_BW[13-1]},
												{ptaPtf_BW[8-1], ptaPtf_BW[14-1], ptaPtf_BW[15-1]},
												{ptaPtf_BW[6-1], ptaPtf_BW[8-1], ptaPtf_BW[15-1]},
												{ptaPtf_BW[34-1], ptaPtf_BW[8-1], ptaPtf_BW[6-1]},
												{ptaPtf_BW[4-1], ptaPtf_BW[34-1], ptaPtf_BW[6-1]},
												{ptaPtf_BW[16-1], ptaPtf_BW[15-1], ptaPtf_BW[17-1]},
												{ptaPtf_BW[6-1], ptaPtf_BW[15-1], ptaPtf_BW[16-1]},
												{ptaPtf_BW[4-1], ptaPtf_BW[6-1], ptaPtf_BW[16-1]},
												{ptaPtf_BW[4-1], ptaPtf_BW[16-1], ptaPtf_BW[18-1]},
												{ptaPtf_BW[16-1], ptaPtf_BW[17-1], ptaPtf_BW[18-1]},
												{ptaPtf_BW[18-1], ptaPtf_BW[17-1], ptaPtf_BW[3-1]},
												{ptaPtf_BW[17-1], ptaPtf_BW[7-1], ptaPtf_BW[3-1]},
												{ptaPtf_BW[15-1], ptaPtf_BW[7-1], ptaPtf_BW[17-1]},
												{ptaPtf_BW[15-1], ptaPtf_BW[9-1], ptaPtf_BW[7-1]},
												{ptaPtf_BW[7-1], ptaPtf_BW[33-1], ptaPtf_BW[3-1]},
												{ptaPtf_BW[9-1], ptaPtf_BW[33-1], ptaPtf_BW[7-1]},
												{ptaPtf_BW[9-1], ptaPtf_BW[31-1], ptaPtf_BW[33-1]},
												{ptaPtf_BW[33-1], ptaPtf_BW[31-1], ptaPtf_BW[3-1]},
												{ptaPtf_BW[12-1], ptaPtf_BW[11-1], ptaPtf_BW[9-1]},
												{ptaPtf_BW[11-1], ptaPtf_BW[30-1], ptaPtf_BW[9-1]},
												{ptaPtf_BW[9-1], ptaPtf_BW[30-1], ptaPtf_BW[31-1]},
												{ptaPtf_BW[5-1], ptaPtf_BW[19-1], ptaPtf_BW[11-1]},
												{ptaPtf_BW[11-1], ptaPtf_BW[19-1], ptaPtf_BW[24-1]},
												{ptaPtf_BW[11-1], ptaPtf_BW[24-1], ptaPtf_BW[30-1]},
												{ptaPtf_BW[5-1], ptaPtf_BW[36-1], ptaPtf_BW[19-1]},
												{ptaPtf_BW[19-1], ptaPtf_BW[36-1], ptaPtf_BW[21-1]},
												{ptaPtf_BW[19-1], ptaPtf_BW[21-1], ptaPtf_BW[24-1]},
												{ptaPtf_BW[24-1], ptaPtf_BW[21-1], ptaPtf_BW[26-1]},
												{ptaPtf_BW[24-1], ptaPtf_BW[26-1], ptaPtf_BW[30-1]},
												{ptaPtf_BW[30-1], ptaPtf_BW[26-1], ptaPtf_BW[31-1]},
												{ptaPtf_BW[26-1], ptaPtf_BW[28-1], ptaPtf_BW[31-1]},
												{ptaPtf_BW[31-1], ptaPtf_BW[28-1], ptaPtf_BW[3-1]},
												{ptaPtf_BW[5-1], ptaPtf_BW[2-1], ptaPtf_BW[36-1]},
												{ptaPtf_BW[36-1], ptaPtf_BW[2-1], ptaPtf_BW[21-1]},
												{ptaPtf_BW[21-1], ptaPtf_BW[2-1], ptaPtf_BW[26-1]},
												{ptaPtf_BW[26-1], ptaPtf_BW[2-1], ptaPtf_BW[28-1]},
												{ptaPtf_BW[28-1], ptaPtf_BW[2-1], ptaPtf_BW[3-1]},
												{ptaPtf_BW[13-1], ptaPtf_BW[12-1], ptaPtf_BW[9-1]},
												{ptaPtf_BW[14-1], ptaPtf_BW[9-1], ptaPtf_BW[15-1]},
											};
		Point ptaTr_HW[63][3] = {	{ptaPtf_HW[1-1], ptaPtf_HW[2-1], ptaPtf_HW[5-1]},
												{ptaPtf_HW[1-1], ptaPtf_HW[5-1], ptaPtf_HW[35-1]},
												{ptaPtf_HW[1-1], ptaPtf_HW[35-1], ptaPtf_HW[22-1]},
												{ptaPtf_HW[1-1], ptaPtf_HW[22-1], ptaPtf_HW[25-1]},
												{ptaPtf_HW[1-1], ptaPtf_HW[25-1], ptaPtf_HW[27-1]},
												{ptaPtf_HW[1-1], ptaPtf_HW[27-1], ptaPtf_HW[4-1]},
												{ptaPtf_HW[22-1], ptaPtf_HW[35-1], ptaPtf_HW[20-1]},
												{ptaPtf_HW[22-1], ptaPtf_HW[20-1], ptaPtf_HW[23-1]},
												{ptaPtf_HW[25-1], ptaPtf_HW[22-1], ptaPtf_HW[23-1]},
												{ptaPtf_HW[25-1], ptaPtf_HW[23-1], ptaPtf_HW[29-1]},
												{ptaPtf_HW[32-1], ptaPtf_HW[25-1], ptaPtf_HW[29-1]},
												{ptaPtf_HW[27-1], ptaPtf_HW[25-1], ptaPtf_HW[32-1]},
												{ptaPtf_HW[4-1], ptaPtf_HW[27-1], ptaPtf_HW[32-1]},
												{ptaPtf_HW[35-1], ptaPtf_HW[5-1], ptaPtf_HW[20-1]},
												{ptaPtf_HW[20-1], ptaPtf_HW[5-1], ptaPtf_HW[10-1]},
												{ptaPtf_HW[23-1], ptaPtf_HW[20-1], ptaPtf_HW[10-1]},
												{ptaPtf_HW[29-1], ptaPtf_HW[23-1], ptaPtf_HW[10-1]},
												{ptaPtf_HW[29-1], ptaPtf_HW[10-1], ptaPtf_HW[8-1]},
												{ptaPtf_HW[32-1], ptaPtf_HW[29-1], ptaPtf_HW[8-1]},
												{ptaPtf_HW[32-1], ptaPtf_HW[8-1], ptaPtf_HW[34-1]},
												{ptaPtf_HW[4-1], ptaPtf_HW[32-1], ptaPtf_HW[34-1]},
												{ptaPtf_HW[10-1], ptaPtf_HW[5-1], ptaPtf_HW[11-1]},
												{ptaPtf_HW[10-1], ptaPtf_HW[11-1], ptaPtf_HW[12-1]},
												{ptaPtf_HW[8-1], ptaPtf_HW[10-1], ptaPtf_HW[12-1]},
												{ptaPtf_HW[8-1], ptaPtf_HW[12-1], ptaPtf_HW[13-1]},
												{ptaPtf_HW[8-1], ptaPtf_HW[14-1], ptaPtf_HW[15-1]},
												{ptaPtf_HW[6-1], ptaPtf_HW[8-1], ptaPtf_HW[15-1]},
												{ptaPtf_HW[34-1], ptaPtf_HW[8-1], ptaPtf_HW[6-1]},
												{ptaPtf_HW[4-1], ptaPtf_HW[34-1], ptaPtf_HW[6-1]},
												{ptaPtf_HW[16-1], ptaPtf_HW[15-1], ptaPtf_HW[17-1]},
												{ptaPtf_HW[6-1], ptaPtf_HW[15-1], ptaPtf_HW[16-1]},
												{ptaPtf_HW[4-1], ptaPtf_HW[6-1], ptaPtf_HW[16-1]},
												{ptaPtf_HW[4-1], ptaPtf_HW[16-1], ptaPtf_HW[18-1]},
												{ptaPtf_HW[16-1], ptaPtf_HW[17-1], ptaPtf_HW[18-1]},
												{ptaPtf_HW[18-1], ptaPtf_HW[17-1], ptaPtf_HW[3-1]},
												{ptaPtf_HW[17-1], ptaPtf_HW[7-1], ptaPtf_HW[3-1]},
												{ptaPtf_HW[15-1], ptaPtf_HW[7-1], ptaPtf_HW[17-1]},
												{ptaPtf_HW[15-1], ptaPtf_HW[9-1], ptaPtf_HW[7-1]},
												{ptaPtf_HW[7-1], ptaPtf_HW[33-1], ptaPtf_HW[3-1]},
												{ptaPtf_HW[9-1], ptaPtf_HW[33-1], ptaPtf_HW[7-1]},
												{ptaPtf_HW[9-1], ptaPtf_HW[31-1], ptaPtf_HW[33-1]},
												{ptaPtf_HW[33-1], ptaPtf_HW[31-1], ptaPtf_HW[3-1]},
												{ptaPtf_HW[12-1], ptaPtf_HW[11-1], ptaPtf_HW[9-1]},
												{ptaPtf_HW[11-1], ptaPtf_HW[30-1], ptaPtf_HW[9-1]},
												{ptaPtf_HW[9-1], ptaPtf_HW[30-1], ptaPtf_HW[31-1]},
												{ptaPtf_HW[5-1], ptaPtf_HW[19-1], ptaPtf_HW[11-1]},
												{ptaPtf_HW[11-1], ptaPtf_HW[19-1], ptaPtf_HW[24-1]},
												{ptaPtf_HW[11-1], ptaPtf_HW[24-1], ptaPtf_HW[30-1]},
												{ptaPtf_HW[5-1], ptaPtf_HW[36-1], ptaPtf_HW[19-1]},
												{ptaPtf_HW[19-1], ptaPtf_HW[36-1], ptaPtf_HW[21-1]},
												{ptaPtf_HW[19-1], ptaPtf_HW[21-1], ptaPtf_HW[24-1]},
												{ptaPtf_HW[24-1], ptaPtf_HW[21-1], ptaPtf_HW[26-1]},
												{ptaPtf_HW[24-1], ptaPtf_HW[26-1], ptaPtf_HW[30-1]},
												{ptaPtf_HW[30-1], ptaPtf_HW[26-1], ptaPtf_HW[31-1]},
												{ptaPtf_HW[26-1], ptaPtf_HW[28-1], ptaPtf_HW[31-1]},
												{ptaPtf_HW[31-1], ptaPtf_HW[28-1], ptaPtf_HW[3-1]},
												{ptaPtf_HW[5-1], ptaPtf_HW[2-1], ptaPtf_HW[36-1]},
												{ptaPtf_HW[36-1], ptaPtf_HW[2-1], ptaPtf_HW[21-1]},
												{ptaPtf_HW[21-1], ptaPtf_HW[2-1], ptaPtf_HW[26-1]},
												{ptaPtf_HW[26-1], ptaPtf_HW[2-1], ptaPtf_HW[28-1]},
												{ptaPtf_HW[28-1], ptaPtf_HW[2-1], ptaPtf_HW[3-1]},
												{ptaPtf_HW[13-1], ptaPtf_HW[12-1], ptaPtf_HW[9-1]},
												{ptaPtf_HW[14-1], ptaPtf_HW[9-1], ptaPtf_HW[15-1]},
											};

		pMatTransBW = FindTransMatrix(ptaTr_B,ptaTr_BW,63);
		pMatTransHW = FindTransMatrix(ptaTr_H,ptaTr_HW,63);

		for(int a = 0;a<iRows;a++)
		{
			for(int b = 0;b<iCols;b++)
			{
				double dU = (double)(a); ///350.00;
				double dV = (double)(b); ///300.00;
				double dX_1, dY_1, dX_2,dY_2;
				Point ptP(dU,dV);			
										
				Matrix *pmatIp_B;
				Matrix matOp(3,1);
				
				matOp.SetElement(0,0,1.00);
				matOp.SetElement(1,0,ptP.iX);
				matOp.SetElement(2,0,ptP.iY);
							
				dX_1 = -1;
				dY_1 = -1;

				dX_2 = -1;
				dY_2 = -1;
				
				for(int t = 0;t<63;t++)
				{
					if(ptP.LiesWithinTriangle(ptaTr_BW[t]))
					{
						//Check for Triangle_1								
						pmatIp_B = Matrix::MatrixMultiply(*pMatTransBW[t],matOp);				
						
						dX_1 = pmatIp_B->GetElement(0,0);
						dY_1 = pmatIp_B->GetElement(1,0);						

						pmatIp_B->FreeMemory();						
						delete pmatIp_B;						
						//break;
					}
					
					if(ptP.LiesWithinTriangle(ptaTr_HW[t]))
					{
						//Check for Triangle_1								
						pmatIp_B = Matrix::MatrixMultiply(*pMatTransHW[t],matOp);				
						
						dX_2 = pmatIp_B->GetElement(0,0);
						dY_2 = pmatIp_B->GetElement(1,0);						

						pmatIp_B->FreeMemory();						
						delete pmatIp_B;						
						//break;
					}
				}
								
				if((dX_1 < 0 && dY_1 < 0) || (dX_1 > 400 || dY_1 > 400) || (dX_2 < 0 && dY_2 < 0) || (dX_2 > 400 || dY_2 > 400))
				{
					Pixel pxPB(0);
					imBruceA.SetPixel(a,b,pxPB);
				}
				else
				{
					Pixel *pxP_1 = imBruce.GetPixel(dX_1,dY_1);
					Pixel *pxP_2 = imHulk.GetPixel(dX_2,dY_2);

					int cR, cB, cG;

					cR = (1 - alpha)*pxP_1->GetRed() + alpha*pxP_2->GetRed();
					cG = (1 - alpha)*pxP_1->GetGreen() + alpha*pxP_2->GetGreen();
					cB = (1 - alpha)*pxP_1->GetBlue() + alpha*pxP_2->GetBlue();

					Pixel pxPResult(cR,cG,cB,a,b);					
					imBruceA.SetPixel(a,b,pxPResult);
					delete pxP_1;
					delete pxP_2;
				}			
			}
		}

		string strBW;
		char szBW[30];
		sprintf(szBW,"Result_Drew_Warped_%d.raw",i);

		strBW = string::basic_string(szBW);
		imBruceA.SetImageName(strBW);
		imBruceA.WriteImageData();

		alpha = (double)i/60.00*1.00;
		pMatTransBW[i]->FreeMemory();
		pMatTransHW[i]->FreeMemory();
	}	

	//Transition
	//for(float alpha = 0.00;alpha<=1.09;alpha += 0.025)
	//{
	//	string strResult;
	//	char szResult[20];
	//	sprintf(szResult,"Result_OY_%d.raw",(int)(alpha*40));
	//	strResult = string::basic_string(szResult);
	//	pimResult->SetImageName(strResult);
	//
	//	for(int i = 0;i<iRows;i++)
	//	{
	//		for(int j = 0;j<iCols;j++)
	//		{				
	//			int cR, cB, cG;
	//
	//			cR = (1 - alpha)*imBruceA.GetRed(i,j) + alpha*imHulk.GetRed(i,j);
	//			cG = (1 - alpha)*imBruceA.GetGreen(i,j) + alpha*imHulk.GetGreen(i,j);
	//			cB = (1 - alpha)*imBruceA.GetBlue(i,j) + alpha*imHulk.GetBlue(i,j);
	//
	//			Pixel pxPResult(cR,cG,cB,i,j);
	//
	//			pimResult->SetPixel(i,j,pxPResult);
	//		}
	//	}
	//
	//	pimResult->WriteImageData();
	//}

	cout<<"\n Press 'C' to continue..";
	getch();
}

void Problem_1_C()
{
	Image imBruce, imHulk, *pimBruceA, *pimHulkA, *pimResult = new Image(), imBruceA;
	int iRows = 400, iCols = 400;
	string strName[5] = {"bruce_banner.raw","hulk.raw","bruceA.raw","hulkA.raw","Result.raw"};

	InitImage(&imBruce,strName[0],iRows,iCols,3);
	InitImage(&imHulk,strName[1],iRows,iCols,3);
	InitImage(&imBruceA,strName[2],iRows,iCols,3);
	InitImage(pimResult,string::basic_string(""),iRows,iCols,3);

	imBruce.ReadImageData();
	imHulk.ReadImageData();

	//Alignment
	Point ptaPts_B[36], ptaPts_H[36], ptaPtf_BW[36], ptaPtf_HW[36];
	
	//Control Points for Hulk
	ptaPts_H[0].SetPoint(0,0);
	ptaPts_H[1].SetPoint(0,399);
	ptaPts_H[2].SetPoint(399,399);
	ptaPts_H[3].SetPoint(399,0);
	ptaPts_H[4].SetPoint(167,198);
	ptaPts_H[5].SetPoint(344,101);
	ptaPts_H[6].SetPoint(333,312);
	ptaPts_H[7].SetPoint(291,128);
	ptaPts_H[8].SetPoint(286,272);
	ptaPts_H[9].SetPoint(230,159);
	ptaPts_H[10].SetPoint(221,234);
	ptaPts_H[11].SetPoint(259,195);
	ptaPts_H[12].SetPoint(281,197);
	ptaPts_H[13].SetPoint(281,197);
	ptaPts_H[14].SetPoint(313,201);
	ptaPts_H[15].SetPoint(380,160);
	ptaPts_H[16].SetPoint(374,255);
	ptaPts_H[17].SetPoint(399,202);
	ptaPts_H[18].SetPoint(184,243);
	ptaPts_H[19].SetPoint(182,149);
	ptaPts_H[20].SetPoint(166,325);
	ptaPts_H[21].SetPoint(166,77);
	ptaPts_H[22].SetPoint(190,118);
	ptaPts_H[23].SetPoint(190,281);
	ptaPts_H[24].SetPoint(124,32);
	ptaPts_H[25].SetPoint(125,369);
	ptaPts_H[26].SetPoint(167,16);
	ptaPts_H[27].SetPoint(167,383);
	ptaPts_H[28].SetPoint(167,47);
	ptaPts_H[29].SetPoint(172,355);
	ptaPts_H[30].SetPoint(210,361);
	ptaPts_H[31].SetPoint(208,35);
	ptaPts_H[32].SetPoint(279,359);
	ptaPts_H[33].SetPoint(292,48);
	ptaPts_H[34].SetPoint(150,117);
	ptaPts_H[35].SetPoint(147,292);
	//Triangles
	Point ptaTr_H[63][3] = {	{ptaPts_H[1-1], ptaPts_H[2-1], ptaPts_H[5-1]},
											{ptaPts_H[1-1], ptaPts_H[5-1], ptaPts_H[35-1]},
											{ptaPts_H[1-1], ptaPts_H[35-1], ptaPts_H[22-1]},
											{ptaPts_H[1-1], ptaPts_H[22-1], ptaPts_H[25-1]},
											{ptaPts_H[1-1], ptaPts_H[25-1], ptaPts_H[27-1]},
											{ptaPts_H[1-1], ptaPts_H[27-1], ptaPts_H[4-1]},
											{ptaPts_H[22-1], ptaPts_H[35-1], ptaPts_H[20-1]},
											{ptaPts_H[22-1], ptaPts_H[20-1], ptaPts_H[23-1]},
											{ptaPts_H[25-1], ptaPts_H[22-1], ptaPts_H[23-1]},
											{ptaPts_H[25-1], ptaPts_H[23-1], ptaPts_H[29-1]},
											{ptaPts_H[32-1], ptaPts_H[25-1], ptaPts_H[29-1]},
											{ptaPts_H[27-1], ptaPts_H[25-1], ptaPts_H[32-1]},
											{ptaPts_H[4-1], ptaPts_H[27-1], ptaPts_H[32-1]},
											{ptaPts_H[35-1], ptaPts_H[5-1], ptaPts_H[20-1]},
											{ptaPts_H[20-1], ptaPts_H[5-1], ptaPts_H[10-1]},
											{ptaPts_H[23-1], ptaPts_H[20-1], ptaPts_H[10-1]},
											{ptaPts_H[29-1], ptaPts_H[23-1], ptaPts_H[10-1]},
											{ptaPts_H[29-1], ptaPts_H[10-1], ptaPts_H[8-1]},
											{ptaPts_H[32-1], ptaPts_H[29-1], ptaPts_H[8-1]},
											{ptaPts_H[32-1], ptaPts_H[8-1], ptaPts_H[34-1]},
											{ptaPts_H[4-1], ptaPts_H[32-1], ptaPts_H[34-1]},
											{ptaPts_H[10-1], ptaPts_H[5-1], ptaPts_H[11-1]},
											{ptaPts_H[10-1], ptaPts_H[11-1], ptaPts_H[12-1]},
											{ptaPts_H[8-1], ptaPts_H[10-1], ptaPts_H[12-1]},
											{ptaPts_H[8-1], ptaPts_H[12-1], ptaPts_H[13-1]},
											{ptaPts_H[8-1], ptaPts_H[14-1], ptaPts_H[15-1]},
											{ptaPts_H[6-1], ptaPts_H[8-1], ptaPts_H[15-1]},
											{ptaPts_H[34-1], ptaPts_H[8-1], ptaPts_H[6-1]},
											{ptaPts_H[4-1], ptaPts_H[34-1], ptaPts_H[6-1]},
											{ptaPts_H[16-1], ptaPts_H[15-1], ptaPts_H[17-1]},
											{ptaPts_H[6-1], ptaPts_H[15-1], ptaPts_H[16-1]},
											{ptaPts_H[4-1], ptaPts_H[6-1], ptaPts_H[16-1]},
											{ptaPts_H[4-1], ptaPts_H[16-1], ptaPts_H[18-1]},
											{ptaPts_H[16-1], ptaPts_H[17-1], ptaPts_H[18-1]},
											{ptaPts_H[18-1], ptaPts_H[17-1], ptaPts_H[3-1]},
											{ptaPts_H[17-1], ptaPts_H[7-1], ptaPts_H[3-1]},
											{ptaPts_H[15-1], ptaPts_H[7-1], ptaPts_H[17-1]},
											{ptaPts_H[15-1], ptaPts_H[9-1], ptaPts_H[7-1]},
											{ptaPts_H[7-1], ptaPts_H[33-1], ptaPts_H[3-1]},
											{ptaPts_H[9-1], ptaPts_H[33-1], ptaPts_H[7-1]},
											{ptaPts_H[9-1], ptaPts_H[31-1], ptaPts_H[33-1]},
											{ptaPts_H[33-1], ptaPts_H[31-1], ptaPts_H[3-1]},
											{ptaPts_H[12-1], ptaPts_H[11-1], ptaPts_H[9-1]},
											{ptaPts_H[11-1], ptaPts_H[30-1], ptaPts_H[9-1]},
											{ptaPts_H[9-1], ptaPts_H[30-1], ptaPts_H[31-1]},
											{ptaPts_H[5-1], ptaPts_H[19-1], ptaPts_H[11-1]},
											{ptaPts_H[11-1], ptaPts_H[19-1], ptaPts_H[24-1]},
											{ptaPts_H[11-1], ptaPts_H[24-1], ptaPts_H[30-1]},
											{ptaPts_H[5-1], ptaPts_H[36-1], ptaPts_H[19-1]},
											{ptaPts_H[19-1], ptaPts_H[36-1], ptaPts_H[21-1]},
											{ptaPts_H[19-1], ptaPts_H[21-1], ptaPts_H[24-1]},
											{ptaPts_H[24-1], ptaPts_H[21-1], ptaPts_H[26-1]},
											{ptaPts_H[24-1], ptaPts_H[26-1], ptaPts_H[30-1]},
											{ptaPts_H[30-1], ptaPts_H[26-1], ptaPts_H[31-1]},
											{ptaPts_H[26-1], ptaPts_H[28-1], ptaPts_H[31-1]},
											{ptaPts_H[31-1], ptaPts_H[28-1], ptaPts_H[3-1]},
											{ptaPts_H[5-1], ptaPts_H[2-1], ptaPts_H[36-1]},
											{ptaPts_H[36-1], ptaPts_H[2-1], ptaPts_H[21-1]},
											{ptaPts_H[21-1], ptaPts_H[2-1], ptaPts_H[26-1]},
											{ptaPts_H[26-1], ptaPts_H[2-1], ptaPts_H[28-1]},
											{ptaPts_H[28-1], ptaPts_H[2-1], ptaPts_H[3-1]},
											{ptaPts_H[13-1], ptaPts_H[12-1], ptaPts_H[9-1]},
											{ptaPts_H[14-1], ptaPts_H[9-1], ptaPts_H[15-1]},
										};

	//Control Points for Bruce Banner
	ptaPts_B[0].SetPoint(0,0);
	ptaPts_B[1].SetPoint(0,399);
	ptaPts_B[2].SetPoint(399,399);
	ptaPts_B[3].SetPoint(399,0);
	ptaPts_B[4].SetPoint(158,192);
	ptaPts_B[5].SetPoint(336,100);
	ptaPts_B[6].SetPoint(321,317);
	ptaPts_B[7].SetPoint(309,146);
	ptaPts_B[8].SetPoint(302,257);
	ptaPts_B[9].SetPoint(256,162);
	ptaPts_B[10].SetPoint(252,234);
	ptaPts_B[11].SetPoint(291,203);
	ptaPts_B[12].SetPoint(308,204);
	ptaPts_B[13].SetPoint(308,204);
	ptaPts_B[14].SetPoint(335,204);
	ptaPts_B[15].SetPoint(388,175);
	ptaPts_B[16].SetPoint(385,244);
	ptaPts_B[17].SetPoint(399,199);
	ptaPts_B[18].SetPoint(172,223);
	ptaPts_B[19].SetPoint(173,168);
	ptaPts_B[20].SetPoint(160,289);
	ptaPts_B[21].SetPoint(169,97);
	ptaPts_B[22].SetPoint(193,128);
	ptaPts_B[23].SetPoint(185,258);
	ptaPts_B[24].SetPoint(145,33);
	ptaPts_B[25].SetPoint(116,374);
	ptaPts_B[26].SetPoint(184,36);
	ptaPts_B[27].SetPoint(168,372);
	ptaPts_B[28].SetPoint(179,60);
	ptaPts_B[29].SetPoint(171,344);
	ptaPts_B[30].SetPoint(229,343);
	ptaPts_B[31].SetPoint(230,62);
	ptaPts_B[32].SetPoint(287,333);
	ptaPts_B[33].SetPoint(293,75);
	ptaPts_B[34].SetPoint(142,134);
	ptaPts_B[35].SetPoint(135,254);
	//Triangles
	Point ptaTr_B[63][3] = {	{ptaPts_B[1-1], ptaPts_B[2-1], ptaPts_B[5-1]},
											{ptaPts_B[1-1], ptaPts_B[5-1], ptaPts_B[35-1]},
											{ptaPts_B[1-1], ptaPts_B[35-1], ptaPts_B[22-1]},
											{ptaPts_B[1-1], ptaPts_B[22-1], ptaPts_B[25-1]},
											{ptaPts_B[1-1], ptaPts_B[25-1], ptaPts_B[27-1]},
											{ptaPts_B[1-1], ptaPts_B[27-1], ptaPts_B[4-1]},
											{ptaPts_B[22-1], ptaPts_B[35-1], ptaPts_B[20-1]},
											{ptaPts_B[22-1], ptaPts_B[20-1], ptaPts_B[23-1]},
											{ptaPts_B[25-1], ptaPts_B[22-1], ptaPts_B[23-1]},
											{ptaPts_B[25-1], ptaPts_B[23-1], ptaPts_B[29-1]},
											{ptaPts_B[32-1], ptaPts_B[25-1], ptaPts_B[29-1]},
											{ptaPts_B[27-1], ptaPts_B[25-1], ptaPts_B[32-1]},
											{ptaPts_B[4-1], ptaPts_B[27-1], ptaPts_B[32-1]},
											{ptaPts_B[35-1], ptaPts_B[5-1], ptaPts_B[20-1]},
											{ptaPts_B[20-1], ptaPts_B[5-1], ptaPts_B[10-1]},
											{ptaPts_B[23-1], ptaPts_B[20-1], ptaPts_B[10-1]},
											{ptaPts_B[29-1], ptaPts_B[23-1], ptaPts_B[10-1]},
											{ptaPts_B[29-1], ptaPts_B[10-1], ptaPts_B[8-1]},
											{ptaPts_B[32-1], ptaPts_B[29-1], ptaPts_B[8-1]},
											{ptaPts_B[32-1], ptaPts_B[8-1], ptaPts_B[34-1]},
											{ptaPts_B[4-1], ptaPts_B[32-1], ptaPts_B[34-1]},
											{ptaPts_B[10-1], ptaPts_B[5-1], ptaPts_B[11-1]},
											{ptaPts_B[10-1], ptaPts_B[11-1], ptaPts_B[12-1]},
											{ptaPts_B[8-1], ptaPts_B[10-1], ptaPts_B[12-1]},
											{ptaPts_B[8-1], ptaPts_B[12-1], ptaPts_B[13-1]},
											{ptaPts_B[8-1], ptaPts_B[14-1], ptaPts_B[15-1]},
											{ptaPts_B[6-1], ptaPts_B[8-1], ptaPts_B[15-1]},
											{ptaPts_B[34-1], ptaPts_B[8-1], ptaPts_B[6-1]},
											{ptaPts_B[4-1], ptaPts_B[34-1], ptaPts_B[6-1]},
											{ptaPts_B[16-1], ptaPts_B[15-1], ptaPts_B[17-1]},
											{ptaPts_B[6-1], ptaPts_B[15-1], ptaPts_B[16-1]},
											{ptaPts_B[4-1], ptaPts_B[6-1], ptaPts_B[16-1]},
											{ptaPts_B[4-1], ptaPts_B[16-1], ptaPts_B[18-1]},
											{ptaPts_B[16-1], ptaPts_B[17-1], ptaPts_B[18-1]},
											{ptaPts_B[18-1], ptaPts_B[17-1], ptaPts_B[3-1]},
											{ptaPts_B[17-1], ptaPts_B[7-1], ptaPts_B[3-1]},
											{ptaPts_B[15-1], ptaPts_B[7-1], ptaPts_B[17-1]},
											{ptaPts_B[15-1], ptaPts_B[9-1], ptaPts_B[7-1]},
											{ptaPts_B[7-1], ptaPts_B[33-1], ptaPts_B[3-1]},
											{ptaPts_B[9-1], ptaPts_B[33-1], ptaPts_B[7-1]},
											{ptaPts_B[9-1], ptaPts_B[31-1], ptaPts_B[33-1]},
											{ptaPts_B[33-1], ptaPts_B[31-1], ptaPts_B[3-1]},
											{ptaPts_B[12-1], ptaPts_B[11-1], ptaPts_B[9-1]},
											{ptaPts_B[11-1], ptaPts_B[30-1], ptaPts_B[9-1]},
											{ptaPts_B[9-1], ptaPts_B[30-1], ptaPts_B[31-1]},
											{ptaPts_B[5-1], ptaPts_B[19-1], ptaPts_B[11-1]},
											{ptaPts_B[11-1], ptaPts_B[19-1], ptaPts_B[24-1]},
											{ptaPts_B[11-1], ptaPts_B[24-1], ptaPts_B[30-1]},
											{ptaPts_B[5-1], ptaPts_B[36-1], ptaPts_B[19-1]},
											{ptaPts_B[19-1], ptaPts_B[36-1], ptaPts_B[21-1]},
											{ptaPts_B[19-1], ptaPts_B[21-1], ptaPts_B[24-1]},
											{ptaPts_B[24-1], ptaPts_B[21-1], ptaPts_B[26-1]},
											{ptaPts_B[24-1], ptaPts_B[26-1], ptaPts_B[30-1]},
											{ptaPts_B[30-1], ptaPts_B[26-1], ptaPts_B[31-1]},
											{ptaPts_B[26-1], ptaPts_B[28-1], ptaPts_B[31-1]},
											{ptaPts_B[31-1], ptaPts_B[28-1], ptaPts_B[3-1]},
											{ptaPts_B[5-1], ptaPts_B[2-1], ptaPts_B[36-1]},
											{ptaPts_B[36-1], ptaPts_B[2-1], ptaPts_B[21-1]},
											{ptaPts_B[21-1], ptaPts_B[2-1], ptaPts_B[26-1]},
											{ptaPts_B[26-1], ptaPts_B[2-1], ptaPts_B[28-1]},
											{ptaPts_B[28-1], ptaPts_B[2-1], ptaPts_B[3-1]},
											{ptaPts_B[13-1], ptaPts_B[12-1], ptaPts_B[9-1]},
											{ptaPts_B[14-1], ptaPts_B[9-1], ptaPts_B[15-1]},
										};

	//Warping
	Matrix **pMatTransHW, **pMatTransBW;
	double alpha = 0.00;

	for(int i = 0;i<=60;i++)
	{
		double dX, dY;
		for(int j = 0;j<36;j++)//36 Points
		{
			dX = ptaPts_H[j].iX - ptaPts_B[j].iX;
			dY = ptaPts_H[j].iY - ptaPts_B[j].iY;
			ptaPtf_BW[j].iX = ptaPts_B[j].iX + dX*i/60;
			ptaPtf_BW[j].iY = ptaPts_B[j].iY + dY*i/60;

			dX = ptaPts_B[j].iX - ptaPts_H[j].iX;
			dY = ptaPts_B[j].iY - ptaPts_H[j].iY;
			ptaPtf_HW[j].iX = ptaPts_B[j].iX - dX*i/60;
			ptaPtf_HW[j].iY = ptaPts_B[j].iY - dY*i/60;
		}

		//Triangles for Bruce Warped 63 triangles
		Point ptaTr_BW[63][3] = {	{ptaPtf_BW[1-1], ptaPtf_BW[2-1], ptaPtf_BW[5-1]},
												{ptaPtf_BW[1-1], ptaPtf_BW[5-1], ptaPtf_BW[35-1]},
												{ptaPtf_BW[1-1], ptaPtf_BW[35-1], ptaPtf_BW[22-1]},
												{ptaPtf_BW[1-1], ptaPtf_BW[22-1], ptaPtf_BW[25-1]},
												{ptaPtf_BW[1-1], ptaPtf_BW[25-1], ptaPtf_BW[27-1]},
												{ptaPtf_BW[1-1], ptaPtf_BW[27-1], ptaPtf_BW[4-1]},
												{ptaPtf_BW[22-1], ptaPtf_BW[35-1], ptaPtf_BW[20-1]},
												{ptaPtf_BW[22-1], ptaPtf_BW[20-1], ptaPtf_BW[23-1]},
												{ptaPtf_BW[25-1], ptaPtf_BW[22-1], ptaPtf_BW[23-1]},
												{ptaPtf_BW[25-1], ptaPtf_BW[23-1], ptaPtf_BW[29-1]},
												{ptaPtf_BW[32-1], ptaPtf_BW[25-1], ptaPtf_BW[29-1]},
												{ptaPtf_BW[27-1], ptaPtf_BW[25-1], ptaPtf_BW[32-1]},
												{ptaPtf_BW[4-1], ptaPtf_BW[27-1], ptaPtf_BW[32-1]},
												{ptaPtf_BW[35-1], ptaPtf_BW[5-1], ptaPtf_BW[20-1]},
												{ptaPtf_BW[20-1], ptaPtf_BW[5-1], ptaPtf_BW[10-1]},
												{ptaPtf_BW[23-1], ptaPtf_BW[20-1], ptaPtf_BW[10-1]},
												{ptaPtf_BW[29-1], ptaPtf_BW[23-1], ptaPtf_BW[10-1]},
												{ptaPtf_BW[29-1], ptaPtf_BW[10-1], ptaPtf_BW[8-1]},
												{ptaPtf_BW[32-1], ptaPtf_BW[29-1], ptaPtf_BW[8-1]},
												{ptaPtf_BW[32-1], ptaPtf_BW[8-1], ptaPtf_BW[34-1]},
												{ptaPtf_BW[4-1], ptaPtf_BW[32-1], ptaPtf_BW[34-1]},
												{ptaPtf_BW[10-1], ptaPtf_BW[5-1], ptaPtf_BW[11-1]},
												{ptaPtf_BW[10-1], ptaPtf_BW[11-1], ptaPtf_BW[12-1]},
												{ptaPtf_BW[8-1], ptaPtf_BW[10-1], ptaPtf_BW[12-1]},
												{ptaPtf_BW[8-1], ptaPtf_BW[12-1], ptaPtf_BW[13-1]},
												{ptaPtf_BW[8-1], ptaPtf_BW[14-1], ptaPtf_BW[15-1]},
												{ptaPtf_BW[6-1], ptaPtf_BW[8-1], ptaPtf_BW[15-1]},
												{ptaPtf_BW[34-1], ptaPtf_BW[8-1], ptaPtf_BW[6-1]},
												{ptaPtf_BW[4-1], ptaPtf_BW[34-1], ptaPtf_BW[6-1]},
												{ptaPtf_BW[16-1], ptaPtf_BW[15-1], ptaPtf_BW[17-1]},
												{ptaPtf_BW[6-1], ptaPtf_BW[15-1], ptaPtf_BW[16-1]},
												{ptaPtf_BW[4-1], ptaPtf_BW[6-1], ptaPtf_BW[16-1]},
												{ptaPtf_BW[4-1], ptaPtf_BW[16-1], ptaPtf_BW[18-1]},
												{ptaPtf_BW[16-1], ptaPtf_BW[17-1], ptaPtf_BW[18-1]},
												{ptaPtf_BW[18-1], ptaPtf_BW[17-1], ptaPtf_BW[3-1]},
												{ptaPtf_BW[17-1], ptaPtf_BW[7-1], ptaPtf_BW[3-1]},
												{ptaPtf_BW[15-1], ptaPtf_BW[7-1], ptaPtf_BW[17-1]},
												{ptaPtf_BW[15-1], ptaPtf_BW[9-1], ptaPtf_BW[7-1]},
												{ptaPtf_BW[7-1], ptaPtf_BW[33-1], ptaPtf_BW[3-1]},
												{ptaPtf_BW[9-1], ptaPtf_BW[33-1], ptaPtf_BW[7-1]},
												{ptaPtf_BW[9-1], ptaPtf_BW[31-1], ptaPtf_BW[33-1]},
												{ptaPtf_BW[33-1], ptaPtf_BW[31-1], ptaPtf_BW[3-1]},
												{ptaPtf_BW[12-1], ptaPtf_BW[11-1], ptaPtf_BW[9-1]},
												{ptaPtf_BW[11-1], ptaPtf_BW[30-1], ptaPtf_BW[9-1]},
												{ptaPtf_BW[9-1], ptaPtf_BW[30-1], ptaPtf_BW[31-1]},
												{ptaPtf_BW[5-1], ptaPtf_BW[19-1], ptaPtf_BW[11-1]},
												{ptaPtf_BW[11-1], ptaPtf_BW[19-1], ptaPtf_BW[24-1]},
												{ptaPtf_BW[11-1], ptaPtf_BW[24-1], ptaPtf_BW[30-1]},
												{ptaPtf_BW[5-1], ptaPtf_BW[36-1], ptaPtf_BW[19-1]},
												{ptaPtf_BW[19-1], ptaPtf_BW[36-1], ptaPtf_BW[21-1]},
												{ptaPtf_BW[19-1], ptaPtf_BW[21-1], ptaPtf_BW[24-1]},
												{ptaPtf_BW[24-1], ptaPtf_BW[21-1], ptaPtf_BW[26-1]},
												{ptaPtf_BW[24-1], ptaPtf_BW[26-1], ptaPtf_BW[30-1]},
												{ptaPtf_BW[30-1], ptaPtf_BW[26-1], ptaPtf_BW[31-1]},
												{ptaPtf_BW[26-1], ptaPtf_BW[28-1], ptaPtf_BW[31-1]},
												{ptaPtf_BW[31-1], ptaPtf_BW[28-1], ptaPtf_BW[3-1]},
												{ptaPtf_BW[5-1], ptaPtf_BW[2-1], ptaPtf_BW[36-1]},
												{ptaPtf_BW[36-1], ptaPtf_BW[2-1], ptaPtf_BW[21-1]},
												{ptaPtf_BW[21-1], ptaPtf_BW[2-1], ptaPtf_BW[26-1]},
												{ptaPtf_BW[26-1], ptaPtf_BW[2-1], ptaPtf_BW[28-1]},
												{ptaPtf_BW[28-1], ptaPtf_BW[2-1], ptaPtf_BW[3-1]},
												{ptaPtf_BW[13-1], ptaPtf_BW[12-1], ptaPtf_BW[9-1]},
												{ptaPtf_BW[14-1], ptaPtf_BW[9-1], ptaPtf_BW[15-1]},
											};
		Point ptaTr_HW[63][3] = {	{ptaPtf_HW[1-1], ptaPtf_HW[2-1], ptaPtf_HW[5-1]},
												{ptaPtf_HW[1-1], ptaPtf_HW[5-1], ptaPtf_HW[35-1]},
												{ptaPtf_HW[1-1], ptaPtf_HW[35-1], ptaPtf_HW[22-1]},
												{ptaPtf_HW[1-1], ptaPtf_HW[22-1], ptaPtf_HW[25-1]},
												{ptaPtf_HW[1-1], ptaPtf_HW[25-1], ptaPtf_HW[27-1]},
												{ptaPtf_HW[1-1], ptaPtf_HW[27-1], ptaPtf_HW[4-1]},
												{ptaPtf_HW[22-1], ptaPtf_HW[35-1], ptaPtf_HW[20-1]},
												{ptaPtf_HW[22-1], ptaPtf_HW[20-1], ptaPtf_HW[23-1]},
												{ptaPtf_HW[25-1], ptaPtf_HW[22-1], ptaPtf_HW[23-1]},
												{ptaPtf_HW[25-1], ptaPtf_HW[23-1], ptaPtf_HW[29-1]},
												{ptaPtf_HW[32-1], ptaPtf_HW[25-1], ptaPtf_HW[29-1]},
												{ptaPtf_HW[27-1], ptaPtf_HW[25-1], ptaPtf_HW[32-1]},
												{ptaPtf_HW[4-1], ptaPtf_HW[27-1], ptaPtf_HW[32-1]},
												{ptaPtf_HW[35-1], ptaPtf_HW[5-1], ptaPtf_HW[20-1]},
												{ptaPtf_HW[20-1], ptaPtf_HW[5-1], ptaPtf_HW[10-1]},
												{ptaPtf_HW[23-1], ptaPtf_HW[20-1], ptaPtf_HW[10-1]},
												{ptaPtf_HW[29-1], ptaPtf_HW[23-1], ptaPtf_HW[10-1]},
												{ptaPtf_HW[29-1], ptaPtf_HW[10-1], ptaPtf_HW[8-1]},
												{ptaPtf_HW[32-1], ptaPtf_HW[29-1], ptaPtf_HW[8-1]},
												{ptaPtf_HW[32-1], ptaPtf_HW[8-1], ptaPtf_HW[34-1]},
												{ptaPtf_HW[4-1], ptaPtf_HW[32-1], ptaPtf_HW[34-1]},
												{ptaPtf_HW[10-1], ptaPtf_HW[5-1], ptaPtf_HW[11-1]},
												{ptaPtf_HW[10-1], ptaPtf_HW[11-1], ptaPtf_HW[12-1]},
												{ptaPtf_HW[8-1], ptaPtf_HW[10-1], ptaPtf_HW[12-1]},
												{ptaPtf_HW[8-1], ptaPtf_HW[12-1], ptaPtf_HW[13-1]},
												{ptaPtf_HW[8-1], ptaPtf_HW[14-1], ptaPtf_HW[15-1]},
												{ptaPtf_HW[6-1], ptaPtf_HW[8-1], ptaPtf_HW[15-1]},
												{ptaPtf_HW[34-1], ptaPtf_HW[8-1], ptaPtf_HW[6-1]},
												{ptaPtf_HW[4-1], ptaPtf_HW[34-1], ptaPtf_HW[6-1]},
												{ptaPtf_HW[16-1], ptaPtf_HW[15-1], ptaPtf_HW[17-1]},
												{ptaPtf_HW[6-1], ptaPtf_HW[15-1], ptaPtf_HW[16-1]},
												{ptaPtf_HW[4-1], ptaPtf_HW[6-1], ptaPtf_HW[16-1]},
												{ptaPtf_HW[4-1], ptaPtf_HW[16-1], ptaPtf_HW[18-1]},
												{ptaPtf_HW[16-1], ptaPtf_HW[17-1], ptaPtf_HW[18-1]},
												{ptaPtf_HW[18-1], ptaPtf_HW[17-1], ptaPtf_HW[3-1]},
												{ptaPtf_HW[17-1], ptaPtf_HW[7-1], ptaPtf_HW[3-1]},
												{ptaPtf_HW[15-1], ptaPtf_HW[7-1], ptaPtf_HW[17-1]},
												{ptaPtf_HW[15-1], ptaPtf_HW[9-1], ptaPtf_HW[7-1]},
												{ptaPtf_HW[7-1], ptaPtf_HW[33-1], ptaPtf_HW[3-1]},
												{ptaPtf_HW[9-1], ptaPtf_HW[33-1], ptaPtf_HW[7-1]},
												{ptaPtf_HW[9-1], ptaPtf_HW[31-1], ptaPtf_HW[33-1]},
												{ptaPtf_HW[33-1], ptaPtf_HW[31-1], ptaPtf_HW[3-1]},
												{ptaPtf_HW[12-1], ptaPtf_HW[11-1], ptaPtf_HW[9-1]},
												{ptaPtf_HW[11-1], ptaPtf_HW[30-1], ptaPtf_HW[9-1]},
												{ptaPtf_HW[9-1], ptaPtf_HW[30-1], ptaPtf_HW[31-1]},
												{ptaPtf_HW[5-1], ptaPtf_HW[19-1], ptaPtf_HW[11-1]},
												{ptaPtf_HW[11-1], ptaPtf_HW[19-1], ptaPtf_HW[24-1]},
												{ptaPtf_HW[11-1], ptaPtf_HW[24-1], ptaPtf_HW[30-1]},
												{ptaPtf_HW[5-1], ptaPtf_HW[36-1], ptaPtf_HW[19-1]},
												{ptaPtf_HW[19-1], ptaPtf_HW[36-1], ptaPtf_HW[21-1]},
												{ptaPtf_HW[19-1], ptaPtf_HW[21-1], ptaPtf_HW[24-1]},
												{ptaPtf_HW[24-1], ptaPtf_HW[21-1], ptaPtf_HW[26-1]},
												{ptaPtf_HW[24-1], ptaPtf_HW[26-1], ptaPtf_HW[30-1]},
												{ptaPtf_HW[30-1], ptaPtf_HW[26-1], ptaPtf_HW[31-1]},
												{ptaPtf_HW[26-1], ptaPtf_HW[28-1], ptaPtf_HW[31-1]},
												{ptaPtf_HW[31-1], ptaPtf_HW[28-1], ptaPtf_HW[3-1]},
												{ptaPtf_HW[5-1], ptaPtf_HW[2-1], ptaPtf_HW[36-1]},
												{ptaPtf_HW[36-1], ptaPtf_HW[2-1], ptaPtf_HW[21-1]},
												{ptaPtf_HW[21-1], ptaPtf_HW[2-1], ptaPtf_HW[26-1]},
												{ptaPtf_HW[26-1], ptaPtf_HW[2-1], ptaPtf_HW[28-1]},
												{ptaPtf_HW[28-1], ptaPtf_HW[2-1], ptaPtf_HW[3-1]},
												{ptaPtf_HW[13-1], ptaPtf_HW[12-1], ptaPtf_HW[9-1]},
												{ptaPtf_HW[14-1], ptaPtf_HW[9-1], ptaPtf_HW[15-1]},
											};

		pMatTransBW = FindTransMatrix(ptaTr_B,ptaTr_BW,63);
		pMatTransHW = FindTransMatrix(ptaTr_H,ptaTr_HW,63);

		for(int a = 0;a<iRows;a++)
		{
			for(int b = 0;b<iCols;b++)
			{
				double dU = (double)(a); ///350.00;
				double dV = (double)(b); ///300.00;
				double dX_1, dY_1, dX_2,dY_2;
				Point ptP(dU,dV);			
										
				Matrix *pmatIp_B;
				Matrix matOp(3,1);
				
				matOp.SetElement(0,0,1.00);
				matOp.SetElement(1,0,ptP.iX);
				matOp.SetElement(2,0,ptP.iY);
							
				dX_1 = -1;
				dY_1 = -1;

				dX_2 = -1;
				dY_2 = -1;
				
				for(int t = 0;t<63;t++)
				{
					if(ptP.LiesWithinTriangle(ptaTr_BW[t]))
					{
						//Check for Triangle_1								
						pmatIp_B = Matrix::MatrixMultiply(*pMatTransBW[t],matOp);				
						
						dX_1 = pmatIp_B->GetElement(0,0);
						dY_1 = pmatIp_B->GetElement(1,0);						

						pmatIp_B->FreeMemory();						
						delete pmatIp_B;						
						//break;
					}
					
					if(ptP.LiesWithinTriangle(ptaTr_HW[t]))
					{
						//Check for Triangle_1								
						pmatIp_B = Matrix::MatrixMultiply(*pMatTransHW[t],matOp);				
						
						dX_2 = pmatIp_B->GetElement(0,0);
						dY_2 = pmatIp_B->GetElement(1,0);						

						pmatIp_B->FreeMemory();						
						delete pmatIp_B;						
						//break;
					}
				}
								
				if((dX_1 < 0 && dY_1 < 0) || (dX_1 > 400 || dY_1 > 400) || (dX_2 < 0 && dY_2 < 0) || (dX_2 > 400 || dY_2 > 400))
				{
					Pixel pxPB(0);
					imBruceA.SetPixel(a,b,pxPB);
				}
				else
				{
					Pixel *pxP_1 = imBruce.GetPixel(dX_1,dY_1);
					Pixel *pxP_2 = imHulk.GetPixel(dX_2,dY_2);

					int cR, cB, cG;

					cR = (1 - alpha)*pxP_1->GetRed() + alpha*pxP_2->GetRed();
					cG = (1 - alpha)*pxP_1->GetGreen() + alpha*pxP_2->GetGreen();
					cB = (1 - alpha)*pxP_1->GetBlue() + alpha*pxP_2->GetBlue();

					Pixel pxPResult(cR,cG,cB,a,b);					
					imBruceA.SetPixel(a,b,pxPResult);
					delete pxP_1;
					delete pxP_2;
				}			
			}
		}

		string strBW;
		char szBW[30];
		sprintf(szBW,"Result_BW_%d.raw",i);

		strBW = string::basic_string(szBW);
		imBruceA.SetImageName(strBW);
		imBruceA.WriteImageData();

		alpha = (double)i/60.00*1.00;
		pMatTransBW[i]->FreeMemory();
		pMatTransHW[i]->FreeMemory();
	}
	
	//Matrix **pMatTransBH = FindTransMatrix(ptaTr_B,ptaTr_H,63);
	//
	////Warp Bruce Image Image
	//for(int i = 0;i<iRows;i++)
	//{
	//	for(int j = 0;j<iCols;j++)
	//	{
	//		double dU = (double)(i); ///350.00;
	//		double dV = (double)(j); ///300.00;
	//		double dX_1, dY_1, dX_2,dY_2;
	//		Point ptP(dU,dV);			
	//								
	//		Matrix *pmatIp_B;
	//		Matrix matOp(3,1);
	//		
	//		matOp.SetElement(0,0,1.00);
	//		matOp.SetElement(1,0,ptP.iX);
	//		matOp.SetElement(2,0,ptP.iY);
	//					
	//		dX_1 = -1;
	//		dY_1 = -1;
	//		
	//		for(int t = 0;t<63;t++)
	//		{
	//			if(ptP.LiesWithinTriangle(ptaTr_H[t]))
	//			{
	//				//Check for Triangle_1								
	//				pmatIp_B = Matrix::MatrixMultiply(*pMatTransBH[t],matOp);				
	//				
	//				dX_1 = pmatIp_B->GetElement(0,0);
	//				dY_1 = pmatIp_B->GetElement(1,0);
	//
	//				//dX_2 = pmatIp_Baby->GetElement(0,0);
	//				//dY_2 = pmatIp_Baby->GetElement(1,0);
	//
	//				pmatIp_B->FreeMemory();
	//				//pmatIp_Baby->FreeMemory();
	//				delete pmatIp_B;
	//				//delete pmatIp_Old;
	//				break;
	//			}
	//			
	//		}
	//		
	//		//cout<<"\ni:  "<<i<<"   j:  "<<j;
	//		if((dX_1 < 0 && dY_1 < 0) || (dX_1 > 400 || dY_1 > 400))
	//		{
	//			Pixel pxPB(125);				
	//			imBruceA.SetPixel(i,j,pxPB);
	//		}
	//		else
	//		{
	//			Pixel *pxP_1 = imBruce.GetPixel(dX_1,dY_1);
	//			imBruceA.SetPixel(i,j,*pxP_1);
	//			delete pxP_1;
	//		}			
	//	}
	//}
	//
	//imBruceA.WriteImageData();

	//Transition
	for(float alpha = 0.00;alpha<=1.09;alpha += 0.025)
	{
		string strResult;
		char szResult[20];
		sprintf(szResult,"Result_BH_%d.raw",(int)(alpha*40));
		strResult = string::basic_string(szResult);
		pimResult->SetImageName(strResult);

		for(int i = 0;i<iRows;i++)
		{
			for(int j = 0;j<iCols;j++)
			{				
				int cR, cB, cG;

				cR = (1 - alpha)*imBruceA.GetRed(i,j) + alpha*imHulk.GetRed(i,j);
				cG = (1 - alpha)*imBruceA.GetGreen(i,j) + alpha*imHulk.GetGreen(i,j);
				cB = (1 - alpha)*imBruceA.GetBlue(i,j) + alpha*imHulk.GetBlue(i,j);

				Pixel pxPResult(cR,cG,cB,i,j);

				pimResult->SetPixel(i,j,pxPResult);
			}
		}

		pimResult->WriteImageData();
	}

	cout<<"\n Press 'C' to continue..";
	getch();
}

Matrix** FindTransMatrix(Point ptaIp[22][3], Point ptaOp[22][3], int iTriangleNumber)
{
	Matrix matU(3,1), matV(3,1);
	Matrix matX(3,1), matY(3,1);

	Matrix *pmatTransUX, *pmatTransUX_Inv;
	Matrix **pMatTrans = new Matrix*[iTriangleNumber];

	for(int i = 0;i<iTriangleNumber;i++)
	{				
		double dU[3] = {ptaOp[i][0].iX, ptaOp[i][1].iX, ptaOp[i][2].iX};//{0.173,0.00,0.500};
		double dV[3] = {ptaOp[i][0].iY, ptaOp[i][1].iY, ptaOp[i][2].iY};//{0.2625,0.500,0.500};
		double dX[3] = {ptaIp[i][0].iX, ptaIp[i][1].iX, ptaIp[i][2].iX};//{0.00,0.00,0.500};
		double dY[3] = {ptaIp[i][0].iY, ptaIp[i][1].iY, ptaIp[i][2].iY};//{0.00,0.50,0.500};
		
		matU.SetElements(dU);	
		matV.SetElements(dV);
		matX.SetElements(dX);
		matY.SetElements(dY);
		
		pmatTransUX = Matrix::FindMatrixA(matU,matV,1);
		pmatTransUX_Inv = pmatTransUX->InverseMatrix();

		Matrix *pmatA, *pmatB;

		pmatA = Matrix::MatrixMultiply(*pmatTransUX_Inv,matX);
		pmatB = Matrix::MatrixMultiply(*pmatTransUX_Inv,matY);

		pMatTrans[i] = Matrix::MergeByRow(*pmatA->MatrixTranspose(),*pmatB->MatrixTranspose());

		delete pmatA;
		delete pmatB;
		pmatTransUX->FreeMemory();
		pmatTransUX_Inv->FreeMemory();
	}

	return pMatTrans;
}