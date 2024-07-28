/******************************************************************************
 * main.c
 *
 * This file calls calls the major function, TourGraph.
 *
 * Author:        Jeffrey Rolland
 * Creation Date: 05/16/2006
 * Modifications: None
 *         
******************************************************************************/

/******************************************************************************
 * 
 * Header inclusions
 * 
******************************************************************************/

#include "MatrixOps.h"
#include "TourGraph.h"

/******************************************************************************
 * int main(void)
 *
 * This is the main function. It calls a function to tour the Cayley graph of 
 * SL(2,5) with respect to the generators S = [1,-1;1,0] and T = [-1,0;-1,-1] 
 * and creates a list of words in the generators for each vertex.
 * 
******************************************************************************/
 
int main(void)
{
	TourGraph();

	return 0;
}