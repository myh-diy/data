#ifndef __STACK_H__
#define __STACK_H__

typedef int DataType;

typedef struct stk_node
{
	DataType data;
	struct stk_node *pnext;
}StackNode;

typedef struct Stack
{
	StackNode *ptop;
	int clen;
}StackList;


StackList *create_stack();
int is_empty_stack(StackList *);
int push_stack(StackList *, DataType );
int pop_stack(StackList *, DataType *);
void clear_stack(StackList *);
void destaroy_stack(StackList *);
int get_stack_top(StackList *, DataType *);


#endif
