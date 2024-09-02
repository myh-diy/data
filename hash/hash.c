#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

HashNode *HashTable[HASH_SIZE] = {NULL};

int hash_function(char key)
{
	if (key >= 'a' && key <= 'z')
	{
		return key - 'a';
	}
	else if (key >= 'A' && key <= 'Z')
	{
		return key - 'A';
	}
	else
	{
		return HASH_SIZE-1;
	}
}
int insert_hash_table(DataType data)
{
	HashNode *pnode = malloc(sizeof(HashNode));
	if (NULL == pnode)
	{
		perror("fail malloc");
		return -1;
	}
	pnode->data = data;
	pnode->pnext = NULL;

	int addr = hash_function(data.name[0]);
	
	//phead ===>HashTable[addr]
	
	pnode->pnext = HashTable[addr];
	HashTable[addr] = pnode;
	
	return 0;
}

void hash_for_each()
{
	HashNode *ptmp = NULL;
	int i = 0;
	for (i = 0 ; i < HASH_SIZE; i++)
	{
		ptmp = HashTable[i];
		while (ptmp != NULL)
		{
			printf("%s %s\n", ptmp->data.name, ptmp->data.tel);
			ptmp = ptmp->pnext;
		}
		printf("\n");
	}
}


HashNode *find_hash_table(char *name)
{
	int addr = hash_function(name[0]);

	HashNode *ptmp = HashTable[addr];
	while (ptmp)
	{
		if (!strcmp(ptmp->data.name, name))
		{
			return ptmp;
		}
		ptmp = ptmp->pnext;
	}
	
	return NULL;
}

void destroy_hash_table()
{
	int i = 0;
	HashNode *ptmp = NULL;
	for (i = 0; i < HASH_SIZE; i++)
	{
		while (HashTable[i] != NULL)
		{
			ptmp = HashTable[i];
			HashTable[i] = ptmp->pnext;
			free(ptmp);
		}
	}
}






