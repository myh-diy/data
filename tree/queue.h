#ifndef __QUEUE_H__
#define __QUEUE_H__

#include "tree.h"

typedef TreeNode* DataType;

typedef struct que_node
{
	DataType data;
	struct que_node *pnext;
}QueNode;

typedef struct que_list
{
	QueNode *pfront;
	QueNode *prear;
	int clen;
}QueList;


extern QueList *create_queue();
extern int push_queue(QueList *, DataType );
extern int pop_queue(QueList *, DataType *);
extern int get_queue_front(QueList *, DataType *);
extern void destroy_queue(QueList *);
extern void clear_queue(QueList *);
extern int is_empty_queue(QueList *pque);

#endif
