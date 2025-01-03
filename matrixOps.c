/*******************************************************************************
 * MatrixOps.c
 *
 * This file contains some routines for working with 2x2 matrices mod 5.
 *
 * Author:        Jeffrey Rolland
 * Creation Date: 05/16/2007
 * Modifications: none
 *         
*******************************************************************************/

/*******************************************************************************
 * 
 * Header inclusions
 * 
*******************************************************************************/

#include "matrixOps.h"

/*******************************************************************************
 * Matrix MatrixMult(Matrix A, Matrix B)
 *
 * This function takes two 2x2 mod 5 matrices and mutliplies them mod 5.
 * 
*******************************************************************************/
 
Matrix MatrixMult(Matrix A, Matrix B)
{
	Matrix C;
	
	C.elt11 = ((A.elt11*B.elt11) + (A.elt12*B.elt21)) % 5;
	C.elt12 = ((A.elt11*B.elt12) + (A.elt12*B.elt22)) % 5;
	C.elt21 = ((A.elt21*B.elt11) + (A.elt22*B.elt21)) % 5;
	C.elt22 = ((A.elt21*B.elt12) + (A.elt22*B.elt22)) % 5;
	
	return C;
}

/*******************************************************************************
 * int MatrixDet(Matrix A)
 *
 * This function computes the mod 5 determinant of a 2x2 mod 5 matrix.
 * 
*******************************************************************************/

int MatrixDet(Matrix A)
{
	int d;
	
    d = (A.elt11*A.elt22 - A.elt12*A.elt21) % 5;
    
    return d;
}

/*******************************************************************************
 * Matrix MatrixInv(Matrix A)
 *
 * This function computes the mod 5 inverse of a 2x2 mod 5 matrix, if the 
 * inverse exists.
 * 
*******************************************************************************/

Matrix MatrixInv(Matrix A)
{
	int detA;
	Matrix B;
	
	detA = MatrixDet(A);
	
    if (detA == 0)
    {
    	B.elt11 = 0;
    	B.elt12 = 0;
    	B.elt21 = 0;
    	B.elt22 = 0;
    }
    
    else
    {
    	B.elt11 = (A.elt22/detA) % 5;
    	B.elt22 = (A.elt11/detA) % 5;
    	B.elt12 = ((-A.elt12)/detA) % 5;
    	B.elt21 = ((-A.elt21)/detA) % 5;
    }
    
    return B;
}

/*******************************************************************************
 * int MatrixCompare(Matrix A, Matrix B)
 *
 * This function computes the relative lexocographical order of two 2x2 mod 5 
 * matrices.
 * 
*******************************************************************************/

int MatrixCompare(Matrix A, Matrix B)
{
	if (A.elt11 < B.elt11)
	{
		return LESSTHAN;
	}
		
	else if (A.elt11 > B.elt11)
	{
		return GREATERTHAN;
	}
	
	else if (A.elt12 < B.elt12)
	{
		return LESSTHAN;
	}
	
	else if (A.elt12 > B.elt12)
	{
		return GREATERTHAN;
	}
	
	else if (A.elt21 < B.elt21)
	{
		return LESSTHAN;
	}
	
	else if (A.elt21 > B.elt21)
	{
		return GREATERTHAN;
	}
	
	else if (A.elt22 < B.elt22)
	{
		return LESSTHAN;
	}
	
	else if (A.elt22 > B.elt22)
	{
		return GREATERTHAN;
	}
	
	else
	{
		return EQUAL;
	}
}