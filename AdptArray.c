//  נעזרתי בפיתרון של מועד א 2023 בתכנות מערכות 1
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "AdptArray.h"

typedef struct AdptArray_
{
	int ArrSize;
	PElement* pElemArr;
	DEL_FUNC delFunc;
	COPY_FUNC copyFunc;
    PRINT_FUNC printFunc;
} AdptArray, *PAdptArray;

PAdptArray CreateAdptArray(COPY_FUNC copyF, DEL_FUNC delF , PRINT_FUNC printF)
{
    PAdptArray pArr = (PAdptArray)malloc(sizeof(AdptArray));
	if (pArr == NULL)
		return NULL;
	pArr->ArrSize = 0;
	pArr->pElemArr = NULL;
	pArr->delFunc = delF;
	pArr->copyFunc = copyF;
    pArr->printFunc = printF;
	return pArr;
}

void DeleteAdptArray(PAdptArray pArr)
{
	int i;
	if (pArr == NULL)
		return;
	for(i = 0; i < pArr->ArrSize; i++)
	{
        if( (pArr->pElemArr)[i] != NULL)
		    pArr->delFunc((pArr->pElemArr)[i]);
	}
	free(pArr->pElemArr);
	free(pArr);
}

Result SetAdptArrayAt(PAdptArray pArr, int idx, PElement pNewElem)
{
	PElement* newpElemArr;
	if (pArr == NULL)
		return FAIL;

	if (idx >= pArr->ArrSize)
	{
		
// Extend Array
		if ((newpElemArr = (PElement*)calloc((idx + 1), sizeof(PElement))) == NULL)
			return FAIL;
		memcpy(newpElemArr, pArr->pElemArr, (pArr->ArrSize) * sizeof(PElement));
		free(pArr->pElemArr);
		pArr->pElemArr = newpElemArr;
	}

	// Delete Previous Elem
    if( pArr->pElemArr[idx] != NULL)
	    pArr->delFunc(pArr->pElemArr[idx]);
	(pArr->pElemArr)[idx] = pArr->copyFunc(pNewElem);

	// Update Array Size
	pArr->ArrSize = (idx >= pArr->ArrSize) ? (idx + 1) : pArr->ArrSize;
	return SUCCESS;
}

PElement GetAdptArrayAt(PAdptArray pArr, int idx)
{
    if (idx > pArr->ArrSize-1 )
        return NULL;
    if (pArr->pElemArr[idx] == NULL )
        return NULL;
    PElement copyElem = pArr->copyFunc(pArr->pElemArr[idx]);
    return copyElem;
}

int GetAdptArraySize(PAdptArray pArr)
{
    if (pArr == NULL)
        return -1;
    return pArr->ArrSize;
}

void PrintDB(PAdptArray pArr)
{
    if (pArr == NULL)
        return;
    for (int i = 0; i<pArr->ArrSize; i++)
    {
        if(pArr->pElemArr[i] != NULL)
            pArr->printFunc(pArr->pElemArr[i]);
    }
            
}
