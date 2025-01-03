/******************************************************************************
 * MatrixOps.h
 *
 * This file contains prototypes and declarations used in Calculator.c. Include 
 * this file if you need the functionality provided by Calculator.c
 *
 * Author:        Jeffrey Rolland
 * Creation Date: 05/16/2007
 * Modifications: None
 *          *****************************************************************************/

/******************************************************************************
 *
 * Note that the "includes guards" technique is incorporated into all 
 * (non-system) header files, to eliminate the need to be concerned about 
 * multiple inclusions of a given header and unneccessary program overhead.
 * 
******************************************************************************/

#ifndef MATRIXOPS_H

	#define MATRIXOPS_H   /* Null declaration */
	
	/***************************************************************************
	*
	* Literal Declarations
	*
	* Literals are defined in the header file for easy reference and 	
	* updating.
	*
	***************************************************************************/

    enum Order {LESSTHAN, EQUAL, GREATERTHAN};
    
	/***************************************************************************
	*
	* Struct Declarations
	*
	* Structures are defined in the header file for easy reference and 	
	* updating.
	*
	***************************************************************************/
    
    typedef struct
	{
	    int elt11;
	    int elt12;
	    int elt21;
	    int elt22;
	} Matrix;

    
	/***************************************************************************
	*
	* Function Prototypes
	*
	***************************************************************************/

	Matrix MatrixMult(Matrix A, Matrix B);
	int MatrixDet(Matrix A);
	Matrix MatrixInv(Matrix A);
	int MatrixCompare(Matrix A, Matrix B);
	
#endif