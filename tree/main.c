#include <stdio.h>
#include "tree.h"


int main(int argc, const char *argv[])
{
	TreeNode *proot = create_bin_tree();	
	if (NULL == proot)
	{
		return -1;
	}

	pre_order(proot);
	printf("\n");

	mid_order(proot);
	printf("\n");
	pos_order(proot);
	printf("\n");

	layer_order(proot);
	printf("\n");

	printf("node : %d\n", get_tree_node_cnt(proot));
	printf("layer : %d\n", get_tree_layer_cnt(proot));

	destroy_tree(proot);
	return 0;
}
