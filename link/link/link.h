#ifndef __LINK_H__
#define __LINK_H__

typedef int DataType;

typedef struct node
{
	DataType data;
	struct node *pnext;
}LinkNode;

typedef struct list
{
	LinkNode *phead;
	int clen;
}LinkList;

extern LinkList *create_link();
extern int push_head_link(LinkList *plist, DataType data);
extern void link_for_each(LinkList *plist);
extern int push_tail_link(LinkList *plist, DataType data);
extern int is_empty_link(LinkList *plist);
extern int pop_head_link(LinkList *plist);
extern int pop_tail_link(LinkList *plist);
extern LinkNode *find_link(LinkList *plist, int key);
extern int change_link(LinkList *plist, int key, DataType newdata);
extern void destroy_link(LinkList *plist);
extern LinkNode *find_mid_node(LinkList *plist);
extern LinkNode *find_last_k_node(LinkList *plist, int k);
extern int pop_point_link(LinkList *plist, int key);
extern void reverse_link(LinkList *plist);
extern void insert_sort_link(LinkList *plist);

#endif
