/******************************************************************************
 * TourGraph.h
 *
 * This file contains prototypes and declarations used in Calculator.c. Include 
 * this file if you need the functionality provided by Calculator.c
 *
 * Author:        Jeffrey Rolland
 * Creation Date: 05/18/2007
 * Modifications: None
 *          *****************************************************************************/

/******************************************************************************
 *
 * Note that the "includes guards" technique is incorporated into all 
 * (non-system) header files, to eliminate the need to be concerned about 
 * multiple inclusions of a given header and unneccessary program overhead.
 * 
******************************************************************************/

#ifndef TOUR_GRAPH_H

	#define TOUR_GRAPH_H   /* Null declaration */
	
	#include <stdio.h>
	
	/***************************************************************************
	*
	* Literal Declarations
	*
	* Literals are defined in the header file for easy reference and 	
	* updating.
	*
	***************************************************************************/
	
	#define MAX_WORD_LEN 500
	
	enum Boolean {FALSE=0, TRUE};
    
	/***************************************************************************
	*
	* Struct Declarations
	*
	* Structures are defined in the header file for easy reference and 	
	* updating.
	*
	***************************************************************************/
	
	typedef struct node 
	{
	    Matrix MatrixElt;
	    char Word[MAX_WORD_LEN+1];
	    char *WordPtr;
	    struct node *Parent;
	    struct node *Child;
	} ListNode;
    
    /***************************************************************************
	*
	* Function Prototypes
	*
	***************************************************************************/

	void TourGraph(void);
	ListNode *MakeListNode(Matrix A, char *w);
	int IsInOutputList(ListNode *newListNodePtr, ListNode **rootOutputListPtr);
	void InsertIntoOutputList(ListNode *newListNodePtr, ListNode 
		**rootOutputListPtrPtr);
	void AppendToSearchList(ListNode *newListNodePtr, ListNode 
		**endSearchListPtrPtr);
	void RemoveFromSearchList(ListNode *disposableSearchListPtr, ListNode 
		**rootSearchListPtrPtr, ListNode **endSearchListPtrPtr);
	void RemoveFromOutputList(ListNode **rootOutputListPtrPtr);
	void PrintRecord(FILE *fp, ListNode *listNodePtr);
	void WriteOutputListToFile(ListNode **rootOutputListPtrPtr);
	
#endif