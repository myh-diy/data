#include "doulink.h"
#include <stdlib.h>
#include <stdio.h>

DouList *create_dou_link()
{
	DouList *plist = (DouList *)malloc(sizeof(DouList));
	if (NULL == plist)
	{
		perror("fail malloc");
		return NULL;
	}
		
	plist->phead = NULL;
	plist->clen = 0;

	return plist;
}

int is_empty_dou_link(DouList *plist)
{
	if (NULL == plist->phead)
	{
		return 1;
	}
	return 0;
}


int push_head_dou_link(DouList *plist,DataType data)
{
	DouNode *pnode = malloc(sizeof(DouNode));
	if (NULL == pnode)
	{
		perror("fail malloc");
		return -1;
	}
	pnode->data = data;
	pnode->pnext = NULL;
	pnode->ppre = NULL;

	if (is_empty_dou_link(plist))
	{
		plist->phead = pnode;
	}
	else
	{
		pnode->pnext = plist->phead;
		plist->phead->ppre = pnode;
		plist->phead = pnode;
	}
	plist->clen++;
	
	return 0;
}


void dou_link_for_each(DouList *plist, int dir)
{
	if (is_empty_dou_link(plist))
	{
		return ;
	}
	DouNode *ptmp = plist->phead;
	if (dir)
	{
		while (ptmp)
		{
			printf("%d %s %d\n", ptmp->data.id, ptmp->data.name, ptmp->data.score);
			ptmp = ptmp->pnext;
		}
	}
	else
	{
		while (ptmp->pnext)
		{
			ptmp = ptmp->pnext;
		}

		while (ptmp)
		{
			printf("%d %s %d\n", ptmp->data.id, ptmp->data.name, ptmp->data.score);
			ptmp = ptmp->ppre;
		}
	}
	printf("\n");
}


int push_tail_dou_link(DouList *plist, DataType data)
{
	DouNode *ptmp = NULL;
	DouNode *pnode = malloc(sizeof(DouNode));
	if (NULL == pnode)
	{
		perror("fail malloc");
		return -1;
	}
	pnode->data = data;
	pnode->pnext = NULL;
	pnode->ppre = NULL;

	if (is_empty_dou_link(plist))
	{
		plist->phead = pnode;
	}
	else
	{
		ptmp = plist->phead;
		while (ptmp->pnext)
		{
			ptmp = ptmp->pnext;
		}
		ptmp->pnext = pnode;
		pnode->ppre = ptmp;
	}
	plist->clen++;

	return 0;
}

int pop_head_dou_link(DouList *plist)
{
	if (is_empty_dou_link(plist))
	{
		return 1;
	}
	
	DouNode *pfree = plist->phead;
	
	plist->phead = pfree->pnext;
	if (plist->phead != NULL)
	{
		plist->phead->ppre = NULL;
	}
	free(pfree);

	plist->clen--;

	return 0;
}

int pop_tail_dou_link(DouList *plist)
{
	if (is_empty_dou_link(plist))
	{
		return 1;
	}
	
	DouNode *pfree = plist->phead;

	while (pfree->pnext)
	{
		pfree = pfree->pnext;
	}
	
	if (pfree->ppre != NULL)
	{
		pfree->ppre->pnext = NULL;
	}
	else
	{
		plist->phead = NULL;
	}

	free(pfree);
	plist->clen--;

	return 0;
}


void destroy_dou_link(DouList *plist)
{
	while (!is_empty_dou_link(plist))
	{
		pop_head_dou_link(plist);
	}
	free(plist);
}

DouNode *Joseph_loop(DouList *plist)
{
	DouNode *ptmp = plist->phead;
	DouNode *pfree = NULL;

	while (plist->clen > 1)
	{
		pfree = ptmp;

		pfree = pfree->pnext->pnext;
		pfree->ppre->pnext = pfree->pnext;
		pfree->pnext->ppre = pfree->ppre;

		ptmp = pfree->pnext;
		free(pfree);
	//	printf("%d\n", plist->clen);
		plist->clen--;
	}

	return ptmp;
}




