#include <stdio.h>
#include "kerlist.h"
/*
 * offsetof()
 *
*/
typedef struct student 
{
	linknode node;
	char name[32];
	char sex;
	int age;
	int score;
}stu_t;

int shownode(void *pnode)
{
	stu_t *pdata = NULL;
	
	pdata = pnode;
	printf("姓名:%s\n", pdata->name);
	printf("性别:%c\n", pdata->sex);
	printf("年龄:%d\n", pdata->age);
	printf("成绩:%d\n", pdata->score);

	return 0;
}

int comparefun(void *pnode)
{
	stu_t *pdata = NULL;
	
	pdata = pnode;
	if (pdata->sex == 'm')
	{
		return 1;
	}

	return 0;
}

int changesex(void *pnode)
{
	stu_t *pdata = NULL;
	
	pdata = pnode;
	pdata->sex = 'f';

	return 0;
}

int findlaststudent(void *pnode)
{
	stu_t *pdata = NULL;
	
	pdata = pnode;
	if (pdata->score < 80)
	{
		return 1;
	}

	return 0;
}

int printlaststudent(void *pnode)
{
	stu_t *pdata = NULL;
	
	pdata = pnode;
	printf("%s\n", pdata->name);

	return 0;
}

int main(void)
{
	int i = 0;
	linknode *phead = NULL;
	stu_t s[5] = {
		{{NULL}, "zhangsan", 'm', 19, 100},
		{{NULL}, "lisi", 'f', 18, 90},
		{{NULL}, "wanger", 'm', 17, 60},
		{{NULL}, "zhaowu", 'f', 16, 90},
		{{NULL}, "maliu", 'm', 17, 85},
	};
	
	phead = createkerlist();
	for (i = 0; i < 5; i++)
	{
		insertheadkerlist(phead, &s[i]);
	}	

	printf("==============================\n");
	foreachkerlist(phead, shownode);
//	deletekerlist(phead, comparefun);
	printf("==============================\n");
	foreachkerlist(phead, shownode);

	execcomkerlist(phead, comparefun, changesex);
	printf("==============================\n");
	foreachkerlist(phead, shownode);

	printf("==============================\n");
	execcomkerlist(phead, findlaststudent, printlaststudent);

	destroykerlist(&phead);
	printf("phead = %p\n", phead);

	return 0;
}
