#include "link.h"
#include <stdlib.h>
#include <stdio.h>


LinkList *create_link()
{
	LinkList *plist = malloc(sizeof(LinkList));
	if (NULL == plist)
	{

		perror("fail malloc");
		return NULL;
	}
	
	plist->phead = NULL;
	plist->clen = 0;

	return plist;

}

int push_head_link(LinkList *plist, DataType data)
{
	LinkNode *pnode = malloc(sizeof(LinkNode));
	if (NULL ==pnode)
	{
		perror("fail malloc");
		return -1;
	}
	pnode->data = data;
	pnode->pnext = NULL;

	pnode->pnext = plist->phead;
	plist->phead = pnode;
	
	plist->clen++;

	return 0;
}

void link_for_each(LinkList *plist)
{
	LinkNode *ptmp = plist->phead;

	while (ptmp != NULL)
	{
		printf("%d ", ptmp->data);
		ptmp = ptmp->pnext;
	}

	printf("\n");
}

int is_empty_link(LinkList *plist)
{
	if (NULL == plist->phead)
	{
		return 1;
	}
	return 0;
}

int push_tail_link(LinkList *plist, DataType data)
{
	LinkNode *plast = NULL;
	LinkNode *pnode = malloc(sizeof(LinkNode));
	if (NULL == pnode)
	{
		perror("fail malloc");
		return -1;
	}
	pnode->data = data;
	pnode->pnext = NULL;

	if (is_empty_link(plist))
	{
		plist->phead = pnode;
	}
	else
	{
		plast = plist->phead;
		while (plast->pnext != NULL)
		{
			plast = plast->pnext;
		}
		plast->pnext = pnode;
	}
	plist->clen++;

	return 0;
}

/*****
 *功能:
 *参数:
 *返回值：
 *		0
 *		1
 *		-1
 ***************/
int pop_head_link(LinkList *plist)
{
	if (is_empty_link(plist))
	{
		return 1;
	}
	
	LinkNode *pfree = plist->phead;

	plist->phead = pfree->pnext;
	free(pfree);
	plist->clen--;

	return 0;
}


int pop_tail_link(LinkList *plist)
{
	LinkNode *ptmp = NULL;

	if (is_empty_link(plist))
	{
		return 1;
	}
	if (1 == plist->clen)
	{
		pop_head_link(plist);
	}
	else
	{
		ptmp = plist->phead;
		while (ptmp->pnext->pnext != NULL)
		{
			ptmp = ptmp->pnext;
		}
		free(ptmp->pnext);
		ptmp->pnext = NULL;
		plist->clen--;
	}

	return 0;
}

LinkNode *find_link(LinkList *plist, int key)
{
	LinkNode *ptmp = plist->phead;

	while (ptmp)
	{
		if (ptmp->data == key)
		{
			return ptmp;
		}
		ptmp = ptmp->pnext;
	}

	return NULL;
}


int change_link(LinkList *plist, int key, DataType newdata)
{
	LinkNode *ptmp = NULL;

	ptmp = find_link(plist, key);
	if (ptmp != NULL)
	{
		ptmp->data = newdata;
		return 0;
	}
	else
	{
		return -1;
	}
}

void destroy_link(LinkList *plist)
{
	while (!is_empty_link(plist))
	{
		pop_head_link(plist);
	}
	free(plist);
}

LinkNode *find_mid_node(LinkList *plist)
{
	LinkNode *pslow = NULL;
	LinkNode *pfast = NULL;
	
	pfast = plist->phead;
	pslow = pfast;
	
	while (pfast != NULL)
	{
		pfast = pfast->pnext;
		if (NULL == pfast)
		{
			break;
		}
		pfast = pfast->pnext;
		pslow = pslow->pnext;
	}
	
	return pslow;
}


LinkNode *find_last_k_node(LinkList *plist, int k)
{
	LinkNode *pfast = NULL;
	LinkNode *pslow = NULL;
	int i = 0;

	pfast = plist->phead;
	pslow = pfast;

	for (i = 0; i < k; i++)
	{
		if ( NULL == pfast)
		{
			return NULL;
		}
		pfast = pfast->pnext;
	}
	
	while(pfast != NULL)
	{
		pfast = pfast->pnext;
		pslow = pslow->pnext;
	}

	return pslow;
}


int pop_point_link(LinkList *plist, int key)
{
	if (is_empty_link(plist))
	{
		return 1;
	}
	LinkNode *ptmp = NULL;
	LinkNode *ppre = NULL;

	ptmp = plist->phead;
	while (ptmp != NULL)
	{
		if (ptmp->data == key)
		{
			if (ptmp == plist->phead)
			{
				plist->phead = ptmp->pnext;
				free(ptmp);
				ptmp = plist->phead;
			}
			else
			{
				ppre->pnext = ptmp->pnext;
				free(ptmp);
				ptmp = ppre->pnext;
			}
			plist->clen--;
		//	return 0;
		}
		else
		{
			ppre = ptmp;
			ptmp = ptmp->pnext;
		}
	}

	return 1;
}


void reverse_link(LinkList *plist)
{
	LinkNode *pinsert = NULL;
	LinkNode *ptmp = plist->phead;

	plist->phead = NULL;

	while (ptmp != NULL)
	{
		pinsert = ptmp;
		ptmp = ptmp->pnext;
		
		pinsert->pnext = plist->phead;
		plist->phead = pinsert;
	}
}


void insert_sort_link(LinkList *plist)
{
	if (is_empty_link(plist) || 1 == plist->clen)
	{
		return ;
	}
	
	LinkNode *p = NULL;
	LinkNode *pinsert = NULL;
	LinkNode *ptmp = plist->phead->pnext;
	plist->phead->pnext = NULL;

	while (ptmp != NULL)
	{
		pinsert = ptmp;
		ptmp = ptmp->pnext;

		if (pinsert->data <= plist->phead->data)
		{
			pinsert->pnext = plist->phead;
			plist->phead = pinsert;
		}
		else
		{
			p = plist->phead;
			while (p->pnext != NULL && p->pnext->data < pinsert->data)
			{
				p = p->pnext;
			}
			pinsert->pnext = p->pnext;
			p->pnext = pinsert;
		}
	}
}




