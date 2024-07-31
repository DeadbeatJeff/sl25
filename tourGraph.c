/*******************************************************************************
 * TourGraph.c
 *
 * This file contains code for performing a depth-first search of the Cayley 
 * graph of SL(2,5) with respect to the generators S = [1,-1;1,0] and T = 
 * [-1,0;-1,-1] and creates a list of words in the generators for each vertex.
 *
 * Author:        Jeffrey Rolland
 * Creation Date: 05/18/2007
 * Modifications: none
 *         
*******************************************************************************/

/*******************************************************************************
 * 
 * Header inclusions
 * 
*******************************************************************************/

#include <stdio.h>
#include "MatrixOps.h"

#include "TourGraph.h"

/*******************************************************************************
 * void TourGraph(void)
 *
 * This function tours the Cayley graph of SL(2,5) with respect to S and T and 
 * creates a list of words in the generators for each vertex.
 * 
*******************************************************************************/
 
int TourGraph(void)
{
	Matrix I, S, T;
	ListNode *newListNodePtr = (ListNode *)NULL,
		*currentListPtr = (ListNode *)NULL,
		*disposableListPtr = (ListNode *)NULL,
		*rootSearchListPtr = (ListNode *)NULL,
		*endSearchListPtr = (ListNode *)NULL,
		*rootOutputListPtr = (ListNode *)NULL;
	
	I.elt11 = 1;
	I.elt12 = 0;
	I.elt21 = 0;
	I.elt22 = 1;
	
	S.elt11 = 1;
	S.elt12 = 4;
	S.elt21 = 1;
	S.elt22 = 0;
	
	T.elt11 = 4;
	T.elt12 = 0;
	T.elt21 = 4;
	T.elt22 = 4;
	
/* Starting the Output List with I and the Search List with S and T will greatly save on special case checking in insertion function, as we don't want "I" in our word string for any elements except I */
	
	/* Start the Output List */
	newListNodePtr = MakeListNode(I, "I");
	rootOutputListPtr = newListNodePtr;
	
	/* Start the Search List with S */
	newListNodePtr = MakeListNode(S, "S");
	rootSearchListPtr = newListNodePtr;
	
	/* Append T to Search List */
	newListNodePtr = MakeListNode(T, "T");
	endSearchListPtr = newListNodePtr;
	rootSearchListPtr->Child = endSearchListPtr;
	endSearchListPtr->Parent = rootSearchListPtr;
	
	/* Begin the main loop */
	while (rootSearchListPtr != (ListNode *)NULL)
	{
		currentListPtr = rootSearchListPtr;
		
		/* Begin the once-around loop */
		while (currentListPtr != (ListNode *)NULL)
		{
			if (IsInOutputList(currentListPtr, &rootOutputListPtr) == 
				FALSE)
			{
				/* Insert into output list */
				newListNodePtr = MakeListNode(currentListPtr->MatrixElt,
					currentListPtr->Word);
				InsertIntoOutputList(newListNodePtr, &rootOutputListPtr);
				
				/* Generate S child and put at end of search list */
				newListNodePtr = 
					MakeListNode(MatrixMult(currentListPtr->MatrixElt,
					S), currentListPtr->WordPtr);
				strcat(newListNodePtr->WordPtr, "S");
				AppendToSearchList(newListNodePtr, &endSearchListPtr);
				 
				/* Generate T child and put at end of search list */
				newListNodePtr = 
					MakeListNode(MatrixMult(currentListPtr->MatrixElt,
					T), currentListPtr->WordPtr);
				strcat(newListNodePtr->WordPtr, "T");
				AppendToSearchList(newListNodePtr, &endSearchListPtr);
				
				/* Move to the next record in the search list */
				currentListPtr = currentListPtr->Child;
			}
			
			else
			{
				disposableListPtr = currentListPtr;
				
				currentListPtr = currentListPtr->Child;
				
				RemoveFromSearchList(disposableListPtr, 
					&rootSearchListPtr, &endSearchListPtr);
				
			}
		}
	}
	
	WriteOutputListToFile(&rootOutputListPtr);
	
	/* Delete the output list */
	while (rootOutputListPtr != (ListNode *)NULL)
	{
		RemoveFromOutputList(&rootOutputListPtr);
	}
	
	return 0;
}

/*******************************************************************************
 * ListNode *MakeListNode(Matrix A, char *w)
 *
 * This function attempts to create a list node, and, if there is no error in 
 * attempting this, returns the list node; in case of error, it returns NULL.
 * 
*******************************************************************************/
 
ListNode *MakeListNode(Matrix A, char *w)
{
	ListNode *newListNodePtr = (ListNode *)NULL;
	
	newListNodePtr = (ListNode *)malloc(sizeof(ListNode));
	
	if (newListNodePtr != (ListNode *)NULL)
	{
		newListNodePtr->MatrixElt = A;
		newListNodePtr->Word[0] = '\0';
		newListNodePtr->WordPtr = &(newListNodePtr->Word[0]);
		strcpy(newListNodePtr->WordPtr, w);
		newListNodePtr->Parent = (ListNode *)NULL;
		newListNodePtr->Child = (ListNode *)NULL;
	}
	
	/* Returns NULL if ListNode was not allocated */
	/* Return actual newListNodePtr if ListNode was allocated */
	
	return newListNodePtr;
}

/*******************************************************************************
 * int IsInOutputList(ListNode *newListNodePtr, ListNode **rootOutputListPtr)
 *
 * This function tests to see if a node in the search list is already in the 
 * output list. The function returns TRUE if the node is already in the output 
 * list and FALSE otherwise.
 * 
*******************************************************************************/
 
int IsInOutputList(ListNode *newListNodePtr, ListNode **rootOutputListPtr)
{
	ListNode *currentListNodePtr;
	
	currentListNodePtr = *rootOutputListPtr;
	
	while (currentListNodePtr != (ListNode *)NULL)
	{
		if ((MatrixCompare(newListNodePtr->MatrixElt,
			currentListNodePtr->MatrixElt) == LESSTHAN)
			||
			(MatrixCompare(newListNodePtr->MatrixElt,
			currentListNodePtr->MatrixElt) == EQUAL))
		{
			if (MatrixCompare(newListNodePtr->MatrixElt,
				currentListNodePtr->MatrixElt) == EQUAL)
			{
				return TRUE;
			}
			
			else
			{
				return FALSE;
			}
		}
		
		currentListNodePtr = currentListNodePtr->Child;
	}
	
	return FALSE;
}

/*******************************************************************************
 * void InsertIntoOutputList(ListNode *newListNodePtr, ListNode 
 * 		**rootOutputListPtrPtr)
 *
 * This function inserts a newly discovered matrix into its proper spot in the 
 * output list.
 * 
*******************************************************************************/
 
void InsertIntoOutputList(ListNode *newListNodePtr, ListNode 
	**rootOutputListPtrPtr)
{
	ListNode *currentListNodePtr;
	int doneFlag = FALSE;
	
	currentListNodePtr = *rootOutputListPtrPtr;
	
	while ((currentListNodePtr->Child != (ListNode *)NULL) || (!(doneFlag)))
	{
		if (MatrixCompare(newListNodePtr->MatrixElt, 
			currentListNodePtr->MatrixElt) == LESSTHAN)
		{
			/* Inserting at the beginning */
			
			if (currentListNodePtr == *rootOutputListPtrPtr)
			{
				newListNodePtr->Child = currentListNodePtr;
				currentListNodePtr->Parent = newListNodePtr;
				*rootOutputListPtrPtr = newListNodePtr;
				
				return;
			}
			
			/* Inserting not at the beginning and not at the end */
			
			else if (!(doneFlag))
			{
				currentListNodePtr->Parent->Child = newListNodePtr;
				newListNodePtr->Parent = currentListNodePtr->Parent;
				newListNodePtr->Child = currentListNodePtr;
				currentListNodePtr->Parent = newListNodePtr;
				
				return;
			}
		}
		
		/* Test to see if we are at the last node */
		
		if (currentListNodePtr->Child != (ListNode *)NULL)
		{
			/* Not at the last node - move through the list */
			
			currentListNodePtr = currentListNodePtr->Child;
		}
		
		else
		{
			/* At the last node - pop the flag; we'll have to insert at the 
				end */
				
			doneFlag = TRUE;
		}
	}
	
	/* Inserting at the end */
	
	currentListNodePtr->Child = newListNodePtr;
	newListNodePtr->Parent = currentListNodePtr;
	newListNodePtr->Child = (ListNode *)NULL;
	
	return;
}

/*******************************************************************************
 * void AppendToSearchList(ListNode *newListNodePtr, ListNode 
 * 		**endSearchListPtrPtr)
 *
 * This function inserts a newly created vertex to the end of the search list.
 * 
*******************************************************************************/
 
void AppendToSearchList(ListNode *newListNodePtr, ListNode 
	**endSearchListPtrPtr)
{
	ListNode *currentListNodePtr;
	
	currentListNodePtr = *endSearchListPtrPtr;
	
	currentListNodePtr->Child = newListNodePtr;
	newListNodePtr->Parent = currentListNodePtr;
	
	*endSearchListPtrPtr = newListNodePtr;
	
	return;
}

/*******************************************************************************
 * void RemoveFromSearchList(ListNode *disposableListNodePtr, ListNode 
 *		**rootSearchListPtrPtr, ListNode **endSearchListPtrPtr)
 *
 * This function removes an already discovered matrix from the search list.
 * 
*******************************************************************************/
 
void RemoveFromSearchList(ListNode *disposableListNodePtr, ListNode 
	**rootSearchListPtrPtr, ListNode **endSearchListPtrPtr)
{
	/* Check for one element in list */
	if ((disposableListNodePtr == *rootSearchListPtrPtr)
		&&
		(disposableListNodePtr == *endSearchListPtrPtr))
	{
		*rootSearchListPtrPtr = (ListNode *)NULL;
		*endSearchListPtrPtr = (ListNode *)NULL;
	}
	
	else 
	{
		if (disposableListNodePtr == *rootSearchListPtrPtr)
		{
			*rootSearchListPtrPtr = disposableListNodePtr->Child;
			(*rootSearchListPtrPtr)->Parent = (ListNode *)NULL;
		}
		
		else
		{
			disposableListNodePtr->Parent->Child = 
				disposableListNodePtr->Child;
		}
		
		if (disposableListNodePtr == *endSearchListPtrPtr)
		{
			*endSearchListPtrPtr = disposableListNodePtr->Parent;
			(*endSearchListPtrPtr)->Child = (ListNode *)NULL;
		}
		
		else
		{
			disposableListNodePtr->Child->Parent = 
				disposableListNodePtr->Parent;
		}
	}
	
	free(disposableListNodePtr);
	
	return;
}

/*******************************************************************************
 * void RemoveFromOutputList(ListNode **rootOutputListPtrPtr)
 *
 * This function removes an output list node from the output list.
 * 
*******************************************************************************/
 
void RemoveFromOutputList(ListNode **rootOutputListPtrPtr)
{
	ListNode *disposableListNodePtr;
	
	
	if ((*rootOutputListPtrPtr)->Child != (ListNode *)NULL)
		{
			disposableListNodePtr = *rootOutputListPtrPtr;
			*rootOutputListPtrPtr = (*rootOutputListPtrPtr)->Child;
			(*rootOutputListPtrPtr)->Parent = (ListNode *)NULL;
		}
		
		else
		{
			disposableListNodePtr = *rootOutputListPtrPtr;
			*rootOutputListPtrPtr = (*rootOutputListPtrPtr)->Child;
		}
		
		free(disposableListNodePtr);
}

/*******************************************************************************
 * void PrintRecord(FILE *fp, ListNode *listNodePtr)
 *
 * This function prints a node struct to a file.
 * 
*******************************************************************************/
 
void PrintRecord(FILE *fp, ListNode *listNodePtr)
{
	fprintf(fp, "[%d,%d;%d,%d] = %s\n", 
				listNodePtr->MatrixElt.elt11, 
				listNodePtr->MatrixElt.elt12, 
				listNodePtr->MatrixElt.elt21, 
				listNodePtr->MatrixElt.elt22, 
				listNodePtr->WordPtr);
				
	return;
}

/*******************************************************************************
 * void WriteOutputListToFile(ListNode **rootOutputListPtrPtr)
 *
 * This function writes the output list to a file.
 * 
*******************************************************************************/
 
void WriteOutputListToFile(ListNode **rootOutputListPtrPtr)
{
	ListNode *currentListNodePtr;
	FILE *fp;
	
	fp = fopen("out.txt", "w");
	
	if(fp == NULL)
	{
		printf("Couldn't open out.txt");
		exit(1);
	}
	else
	{
		currentListNodePtr = *rootOutputListPtrPtr;
		
		while (currentListNodePtr != (ListNode *)NULL)
		{
			PrintRecord(fp, currentListNodePtr);
			
			currentListNodePtr = currentListNodePtr->Child;
		}
		
		fclose(fp);
	}
	
	return;
}