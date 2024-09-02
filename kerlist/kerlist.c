#include <stdio.h>
#include <stdlib.h>
#include "kerlist.h"

linknode *createkerlist(void)
{
	linknode *ptmpnode = NULL;

	ptmpnode = malloc(sizeof(linknode));
	if (NULL == ptmpnode)
	{
		printf("malloc failed!\n");
		return NULL;
	}
	
	ptmpnode->pnext = NULL;

	return ptmpnode;
}

int insertheadkerlist(linknode *phead, void *pdata)
{
	linknode *ptmpnode = pdata;
	
	ptmpnode->pnext = phead->pnext;
	phead->pnext = ptmpnode;

	return 0;
}

int foreachkerlist(linknode *phead, int (*pfun)(void *pnode))
{
	linknode *ptmpnode = NULL;

	ptmpnode = phead->pnext;
	while (ptmpnode != NULL)
	{
		pfun(ptmpnode);
		ptmpnode = ptmpnode->pnext;
	}

	return 0;
}

int deletekerlist(linknode *phead, int (*pcom)(void *pnode))
{
	linknode *ptmpnode = NULL;
	linknode *pprenode = NULL;

	pprenode = phead;
	ptmpnode = phead->pnext;
	while (ptmpnode != NULL)
	{
		if (pcom(ptmpnode))
		{
			pprenode->pnext = ptmpnode->pnext;
			ptmpnode = pprenode->pnext;
		}
		else 
		{
			ptmpnode = ptmpnode->pnext;
			pprenode = pprenode->pnext;
		}
	}

	return 0;
}

int destroykerlist(linknode **pphead)
{
	free(*pphead);
	*pphead = NULL;

	return 0;
}

int execcomkerlist(linknode *phead, int (*pcom)(void *pnode), int (*pfun)(void *pnode))
{
	linknode *ptmpnode = NULL;

	ptmpnode = phead->pnext;
	while (ptmpnode != NULL)
	{
		if (pcom(ptmpnode))
		{
			pfun(ptmpnode);	
		}
		ptmpnode = ptmpnode->pnext;
	}

	return 0;
}
