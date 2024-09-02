#include "link.h"
#include <stdio.h>


int main(int argc, const char *argv[])
{
	LinkNode *ptmp = NULL;
	LinkList *plist  = create_link();
	if (NULL == plist)
	{
		return -1;
	}
	
	push_head_link(plist, 1);
	push_head_link(plist, 2);
	push_head_link(plist, 3);
	push_head_link(plist, 4);
	push_head_link(plist, 4);
	push_head_link(plist, 4);

	push_tail_link(plist,4);
	push_tail_link(plist,5);
	push_tail_link(plist,6);

	link_for_each(plist);

	pop_head_link(plist);
	
	pop_tail_link(plist);

	link_for_each(plist);

	ptmp = find_link(plist, 3);
	if (ptmp != NULL)
	{
		printf("find node = %d\n", ptmp->data);
	}
	else
	{
		printf("not find this node\n");
	}
	
	change_link(plist, 2, 10);
	
	link_for_each(plist);

	
	ptmp = find_mid_node(plist);
	if (ptmp != NULL)
	{
		printf("Mid node = %d\n", ptmp->data);
	}

	ptmp = find_last_k_node(plist, 3);
	if (ptmp != NULL)
	{
		printf("Last k node = %d\n", ptmp->data);
	}
	link_for_each(plist);
	pop_point_link(plist, 4);

	link_for_each(plist);

	reverse_link(plist);

	link_for_each(plist);
	
	insert_sort_link(plist);
	link_for_each(plist);


	destroy_link(plist);


	return 0;
}
