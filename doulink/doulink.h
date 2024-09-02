#ifndef __DOULINK_H__
#define __DOULINK_H__

typedef struct stu
{
	int id;
	char name[32];
	int score;
}DataType;

typedef struct node
{
	DataType data;
	struct node *ppre;
	struct node *pnext;
}DouNode;

typedef struct list
{
	DouNode *phead;
	int clen;
}DouList;


extern DouList *create_dou_link();
extern int is_empty_dou_link(DouList *plist);
extern int push_head_dou_link(DouList *plist,DataType data);
extern void dou_link_for_each(DouList *plist, int dir);
extern int push_tail_dou_link(DouList *plist, DataType data);
extern int pop_head_dou_link(DouList *plist);
extern int pop_tail_dou_link(DouList *plist);
extern void destroy_dou_link(DouList *plist);
extern DouNode *Joseph_loop(DouList *plist);


#endif
