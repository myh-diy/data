#ifndef __TREE_H__
#define __TREE_H__


typedef char TreeDataType;

typedef struct node
{
	TreeDataType data;
	struct node *pl;
	struct node *pr;
}TreeNode;


extern TreeNode *create_bin_tree();
extern void pre_order(TreeNode *proot);
extern void mid_order(TreeNode *proot);
extern void pos_order(TreeNode *proot);
extern int get_tree_node_cnt(TreeNode *proot);
extern int get_tree_layer_cnt(TreeNode *proot);
extern void destroy_tree(TreeNode *proot);
extern void layer_order(TreeNode *proot);
	

#endif
