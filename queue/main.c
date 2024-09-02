#include <stdio.h>
#include "queue.h"


int main(int argc, const char *argv[])
{
	DataType data;
	QueList *pque = create_queue();	
	if (NULL == pque)
	{
		return -1;
	}
	
	push_queue(pque, 1);
	push_queue(pque, 2);
	push_queue(pque, 3);
	push_queue(pque, 4);

	int ret = pop_queue(pque, &data);
	if (0 == ret)
	{
		printf("pop data = %d\n", data);

	}
	
	ret = get_queue_front(pque, &data);
	if (0 == ret)
	{
		printf("front data = %d\n", data);
	}

	destroy_queue(pque);
	return 0;
}
