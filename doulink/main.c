#include <stdio.h>
#include "doulink.h"


int main(int argc, const char *argv[])
{
	
	DouNode *ptmp = NULL;

	DataType stus[10] = {{1, "zhangsan", 90},
		{2, "lisi", 88}, {3, "wanger", 56},
		{4, "zhaowu", 85}, {5, "maliu", 77},
		{6, "xxx",99}, 
		{
			.id = 7,
		}, 
		{
			.id = 8,
		}, 
		{
			.id = 9,	
		},
		{
			.id = 10,
		}};

	DouList *plist = create_dou_link();	
	if (NULL == plist)
	{
		return -1;
	}
	
	int i = 0;
	for (i = 0; i < sizeof(stus) / sizeof(stus[0]); i++)
	{
		push_tail_dou_link(plist, stus[i]);
	}

#if 0	
	push_head_dou_link(plist, stus[0]);
	push_head_dou_link(plist, stus[1]);
	push_head_dou_link(plist, stus[2]);

	push_tail_dou_link(plist, stus[3]);
	push_tail_dou_link(plist, stus[4]);

	dou_link_for_each(plist, 1);
	dou_link_for_each(plist, 0);

	pop_head_dou_link(plist);
	pop_tail_dou_link(plist);


	dou_link_for_each(plist, 1);
	dou_link_for_each(plist, 0);

//	destroy_dou_link(plist);

#endif
	ptmp = plist->phead;
	while (ptmp->pnext != NULL)
	{
		ptmp = ptmp->pnext;
	}
	ptmp->pnext = plist->phead;
	plist->phead->ppre = ptmp;
	
	
	ptmp = Joseph_loop(plist);
	printf("last one = %d\n", ptmp->data.id);




	return 0;
}
