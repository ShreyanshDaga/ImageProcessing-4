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
//File: Misc.cpp
//////////////////////////////////////////////////

#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include<iostream>

#include"HW_4.h"
#include"Pixel.h"
#include"Image.h"
#include"Histogram.h"
#include"Misc.h"

using namespace std;

void InitImage(Image *pimImage,string strName, int iRows, int iCols, int iColorFormat)
{
	pimImage->SetImageName(strName);
	pimImage->SetImageRows(iRows);
	pimImage->SetImageCols(iCols);
	pimImage->SetImageColorFormat(iColorFormat);
	pimImage->AllocImageMem();
}

Point** DelaunayTriangulation(Point *ptaControlPoints, int iPointCount)
{
	Point **ptaTriangles;

	return ptaTriangles;
}

int FindMin(int N, int NW, int NE, int W)
{
	int a[4] = {N,NW,NE,W};
	int iM;
	int i = 0;

	if(N != 0)
		a[i++] = N;
	else if(NW != 0)
		a[i++] = NW;
	else if(NE != 0)
		a[i++] = NE;
	else if(W != 0)
		a[i++] = W;
	
	for (int k = 1; k < i; k++)
	{
		for (int j = 0; j <i -1 - k; j++)
		{
			if (a[j] > a[j +1])
			{
				int temp = a[j];			
				a[j] = a[j + 1];
				a[j + 1] = temp;
			}
		}
	}

	return a[0];
}

/// Matrix Inversion Code Taken from http://chi3x10.wordpress.com/2008/05/28/calculate-matrix-inversion-in-c/
//   Author: Yu-Tseh Jason Chi
/// matrix inversion

// the result is put in Y
void MatrixInversion(double **A, int order, double **Y)
{
    // get the determinant of a
    double det = 1.0/CalcDeterminant(A,order);
 
    // memory allocation
    double *temp = new double[(order-1)*(order-1)];
    double **minor = new double*[order-1];
    for(int i=0;i<order-1;i++)
        minor[i] = temp+(i*(order-1));
 
    for(int j=0;j<order;j++)
    {
        for(int i=0;i<order;i++)
        {
            // get the co-factor (matrix) of A(j,i)
            GetMinor(A,minor,j,i,order);
            Y[i][j] = det*CalcDeterminant(minor,order-1);
            if( (i+j)%2 == 1)
                Y[i][j] = -Y[i][j];
        }
    }
 
    // release memory
    //delete [] minor[0];
    delete [] temp;
    delete [] minor;
}
 
// calculate the cofactor of element (row,col)
int GetMinor(double **src, double **dest, int row, int col, int order)
{
    // indicate which col and row is being copied to dest
    int colCount=0,rowCount=0;
 
    for(int i = 0; i < order; i++ )
    {
        if( i != row )
        {
            colCount = 0;
            for(int j = 0; j < order; j++ )
            {
                // when j is not the element
                if( j != col )
                {
                    dest[rowCount][colCount] = src[i][j];
                    colCount++;
                }
            }
            rowCount++;
        }
    }
 
    return 1;
}
 
// Calculate the determinant recursively.
double CalcDeterminant( double **mat, int order)
{
    // order must be >= 0
    // stop the recursion when matrix is a single element
    if( order == 1 )
        return mat[0][0];
 
    // the determinant value
    double det = 0;
 
    // allocate the cofactor matrix
    double **minor;
    minor = new double*[order-1];
    for(int i=0;i<order-1;i++)
        minor[i] = new double[order-1];
 
    for(int i = 0; i < order; i++ )
    {
        // get minor of element (0,i)
        GetMinor( mat, minor, 0, i , order);
        // the recusion is here!
 
        det += (i%2==1?-1.0:1.0) * mat[0][i] * CalcDeterminant(minor,order-1);       
    }
 
    // release memory
    for(int i=0;i<order-1;i++)
        delete [] minor[i];
    delete [] minor;
 
    return det;
}

/*****
** kmeans.c
** - a simple k-means clustering routine
** - returns the cluster labels of the data points in an array
** - here's an example
**   extern int *k_means(double**, int, int, int, double, double**);
**   ...
**   int *c = k_means(data_points, num_points, dim, 20, 1e-4, 0);
**   for (i = 0; i < num_points; i++) {
**      printf("data point %d is in cluster %d\n", i, c[i]);
**   }
**   ...
**   free(c);
** Parameters
** - array of data points (double **data)
** - number of data points (int n)
** - dimension (int m)
** - desired number of clusters (int k)
** - error tolerance (double t)
**   - used as the stopping criterion, i.e. when the sum of
**     squared euclidean distance (standard error for k-means)
**     of an iteration is within the tolerable range from that
**     of the previous iteration, the clusters are considered
**     "stable", and the function returns
**   - a suggested value would be 0.0001
** - output address for the final centroids (double **centroids)
**   - user must make sure the memory is properly allocated, or
**     pass the null pointer if not interested in the centroids
** References
** - J. MacQueen, "Some methods for classification and analysis
**   of multivariate observations", Fifth Berkeley Symposium on
**   Math Statistics and Probability, 281-297, 1967.
** - I.S. Dhillon and D.S. Modha, "A data-clustering algorithm
**   on distributed memory multiprocessors",
**   Large-Scale Parallel Data Mining, 245-260, 1999.
** Notes
** - this function is provided as is with no warranty.
** - the author is not responsible for any damage caused
**   either directly or indirectly by using this function.
** - anybody is free to do whatever he/she wants with this
**   function as long as this header section is preserved.
** Created on 2005-04-12 by
** - Roger Zhang (rogerz@cs.dal.ca)
** Modifications
** -
** Last compiled under Linux with gcc-3
*/
int* K_Means(double **data, int n, int m, int k, double t, double **centroids)
{
   /* output cluster label for each data point */
   int *labels = (int*)calloc(n, sizeof(int));

   int h, i, j; /* loop counters, of course :) */
   int *counts = (int*)calloc(k, sizeof(int)); /* size of each cluster */
   double old_error, error = DBL_MAX; /* sum of squared euclidean distance */
   double **c = centroids ? centroids : (double**)calloc(k, sizeof(double*));
   double **c1 = (double**)calloc(k, sizeof(double*)); /* temp centroids */

   assert(data && k > 0 && k <= n && m > 0 && t >= 0); /* for debugging */

   /****
   ** initialization */

   for (h = i = 0; i < k; h += n / k, i++) 
   {
      c1[i] = (double*)calloc(m, sizeof(double));
      
	  if (!centroids) 
	  {
         c[i] = (double*)calloc(m, sizeof(double));
      }
      /* pick k points as initial centroids */
      for (j = m; j-- > 0; c[i][j] = data[h][j]);
   }

   /****
   ** main loop */

   do 
   {
      /* save error from last step */
      old_error = error, error = 0;

      /* clear old counts and temp centroids */
      for (i = 0; i < k; counts[i++] = 0) 
	  {
         for (j = 0; j < m; c1[i][j++] = 0);
      }

      for (h = 0; h < n; h++) 
	  {
         /* identify the closest cluster */
         double min_distance = DBL_MAX;
         for (i = 0; i < k; i++) 
		 {
            double distance = 0;
            for (j = m; j-- > 0; distance += pow(data[h][j] - c[i][j], 2));
            if (distance < min_distance) 
			{
               labels[h] = i;
               min_distance = distance;
            }
         }
         /* update size and temp centroid of the destination cluster */
         for (j = m; j-- > 0; c1[labels[h]][j] += data[h][j]);
			counts[labels[h]]++;
         /* update standard error */
         error += min_distance;
      }

      for (i = 0; i < k; i++) 
	  { /* update all centroids */
         for (j = 0; j < m; j++) 
		 {
            c[i][j] = counts[i] ? c1[i][j] / counts[i] : c1[i][j];
         }
      }

   } while (fabs(error - old_error) > t);

   /****
   ** housekeeping */

   for (i = 0; i < k; i++) 
   {
      if (!centroids) 
	  {
         free(c[i]);
      }
      free(c1[i]);
   }

   if (!centroids) 
   {
      free(c);
   }
   free(c1);

   free(counts);

   return labels;
}
