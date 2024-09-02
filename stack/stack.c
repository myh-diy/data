#include "stack.h"
#include <stdlib.h>
#include <stdio.h>

StackList *create_stack()
{
	StackList *pstack = malloc(sizeof(StackList));
	if (NULL == pstack)
	{
		perror("fail malloc");
		return NULL;
	}
	pstack->ptop = NULL;
	pstack->clen = 0;

	return pstack;
}
int is_empty_stack(StackList *pstack)
{
	if (NULL == pstack->ptop)
	{
		return 1;
	}
	return 0;
}
int push_stack(StackList *pstack, DataType data)
{
	StackNode *pnode = malloc(sizeof(StackNode));
	if (NULL == pnode)
	{
		perror("fail malloc");
		return -1;
	}
	pnode->data = data;
	pnode->pnext = NULL;

	pnode->pnext = pstack->ptop;
	pstack->ptop = pnode;

	pstack->clen++;

	return 0;
}
int pop_stack(StackList *pstack, DataType *pdata)
{
	if (is_empty_stack(pstack))
	{
		return 1;
	}
	
	StackNode *pfree = pstack->ptop;
	pstack->ptop = pfree->pnext;
	if (pdata != NULL)
	{
		*pdata = pfree->data;
	}
	free(pfree);
	pstack->clen--;
	
	return 0;
}
void clear_stack(StackList * pstack)
{
	while (!is_empty_stack(pstack))
	{
		pop_stack(pstack, NULL);
	}
}
void destaroy_stack(StackList *pstack)
{
	clear_stack(pstack);
	free(pstack);
}
int get_stack_top(StackList *pstack, DataType *pdata)
{
	if (is_empty_stack(pstack))
	{
		return 1;
	}
	*pdata = pstack->ptop->data;
	return 0;
}
