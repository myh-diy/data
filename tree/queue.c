#include "queue.h"
#include <stdlib.h>
#include <stdio.h>


QueList *create_queue()
{
	QueList *pque = malloc(sizeof(QueList));
	if (NULL == pque)
	{
		perror("fail malloc");
		return NULL;
	}
	pque->pfront = NULL;
	pque->prear = NULL;
	pque->clen = 0;

	return pque;
}

int is_empty_queue(QueList *pque)
{
	if (NULL == pque->pfront)
	{
		return 1;
	}
	return 0;
}

int push_queue(QueList *pque, DataType data)
{
	QueNode *pnode = malloc(sizeof(QueNode));
	if (NULL == pnode)
	{
		perror("fail malloc");
		return -1;
	}
	pnode->data = data;
	pnode->pnext = NULL;
	
	if (is_empty_queue(pque))
	{
		pque->pfront = pnode;
		pque->prear = pnode;
	}
	else
	{
		pque->prear->pnext = pnode;
		pque->prear = pnode;
	}
	pque->clen++;

	return 0;
}
int pop_queue(QueList *pque, DataType *pdata)
{
	if (is_empty_queue(pque))
	{
		return 1;
	}
	
	QueNode *pfree = pque->pfront;
	pque->pfront = pfree->pnext;
	if (pdata != NULL)
	{
		*pdata = pfree->data;
	}
	free(pfree);
	pque->clen--;
	if (NULL == pque->pfront)
	{
		pque->prear = NULL;
	}
	return 0;
}
int get_queue_front(QueList *pque, DataType *pdata)
{
	if (is_empty_queue(pque))
	{
		return -1;
	}
	*pdata = pque->pfront->data;

	return 0;
}
void destroy_queue(QueList *pque)
{
	clear_queue(pque);
	free(pque);
}
void clear_queue(QueList *pque)
{
	while (!is_empty_queue(pque))
	{
		pop_queue(pque, NULL);
	}
}



