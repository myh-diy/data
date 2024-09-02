#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
/**
        A
       / \
      B   D
     / \  / \
    E   F G  C
         /
          H
           \
            I
 */
char tree[] = {"ABE##F##DGH#I###C##"};
int idx = 0;

TreeNode *create_bin_tree()
{
	TreeDataType data = tree[idx++];
	if ('#' == data)
	{
		return NULL;
	}
	TreeNode *pnode = malloc(sizeof(TreeNode));
	if (NULL == pnode)
	{
		perror("fail malloc");
		return NULL;
	}
	pnode->data = data;
	pnode->pl = create_bin_tree();
	pnode->pr = create_bin_tree();
	
	return pnode;
}


void pre_order(TreeNode *proot)
{
	if (NULL == proot)
	{
		return ;
	}
	printf("%c", proot->data);
	pre_order(proot->pl);
	pre_order(proot->pr);

}


void mid_order(TreeNode *proot)
{
	if (NULL == proot)
	{
		return ;
	}
	mid_order(proot->pl);
	printf("%c", proot->data);
	mid_order(proot->pr);
}

void pos_order(TreeNode *proot)
{
	if (NULL == proot)
	{
		return ;
	}
	pos_order(proot->pl);
	pos_order(proot->pr);
	printf("%c", proot->data);
}
// 获取根节点个数
int get_tree_node_cnt(TreeNode *proot)
{
	if (NULL == proot)
	{
		return 0;
	}
	return 1+get_tree_node_cnt(proot->pl)+get_tree_node_cnt(proot->pr);
}
// 获取层数
int get_tree_layer_cnt(TreeNode *proot)
{
	if (NULL == proot)
	{
		return 0;
	}
	int cntl = get_tree_layer_cnt(proot->pl);
	int cntr = get_tree_layer_cnt(proot->pr);

	return cntl > cntr ? cntl+1 : cntr+1;
}


void destroy_tree(TreeNode *proot)
{
	if (NULL == proot)
	{
		return ;
	}
	destroy_tree(proot->pl);
	destroy_tree(proot->pr);
	free(proot);
}

void layer_order(TreeNode *proot)
{
	DataType outdata;
	QueList *pque = create_queue();	
	if (NULL == pque)
	{
		return ;
	}
	
	push_queue(pque, proot);

	while (!is_empty_queue(pque))
	{
		pop_queue(pque, &outdata);
		printf("%c", outdata->data);
		if (outdata->pl != NULL)
		{
			push_queue(pque, outdata->pl);
		}
		if (outdata->pr != NULL)
		{
			push_queue(pque, outdata->pr);
		}
	}
	
	destroy_queue(pque);
}





