#ifndef __KERLIST_H__
#define __KERLIST_H__

typedef struct node 
{
	struct node *pnext;
}linknode;

extern linknode *createkerlist(void);
extern int insertheadkerlist(linknode *phead, void *pdata);
extern int foreachkerlist(linknode *phead, int (*pfun)(void *pnode));
extern int deletekerlist(linknode *phead, int (*pcom)(void *pnode));
extern int destroykerlist(linknode **pphead);
extern int execcomkerlist(linknode *phead, int (*pcom)(void *pnode), int (*pfun)(void *pnode));

#endif
