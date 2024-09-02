#include "hash.h"
#include <stdio.h>

int main(int argc, const char *argv[])
{
	DataType pers[]	 = {{"zhangsan", "110"},
		{"lisi", "120"}, {"wanger", "119"},
		{"zhaowu", "114"}, {"lihua", "10086"}};

	
	insert_hash_table(pers[0]);
	insert_hash_table(pers[1]);
	insert_hash_table(pers[2]);
	insert_hash_table(pers[3]);
	insert_hash_table(pers[4]);

	hash_for_each();
	
	HashNode *ptmp = find_hash_table("zhangsan");
	if (ptmp != NULL)
	{
		printf("find : %s %s\n", ptmp->data.name, ptmp->data.tel);
	}

	destroy_hash_table();
	return 0;
}
