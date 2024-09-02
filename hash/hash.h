#ifndef __HASH_H__
#define __HASH_H__

#define HASH_SIZE 27

typedef struct per
{
	char name[32];
	char tel[32];
}DataType;

typedef struct hashnode
{
	DataType data;
	struct hashnode *pnext;
}HashNode;
	

extern int insert_hash_table(DataType data);

extern void hash_for_each();
extern HashNode *find_hash_table(char *name);
extern void destroy_hash_table();

#endif
