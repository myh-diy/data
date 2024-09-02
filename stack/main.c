#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

int main(int argc, const char *argv[])
{
	DataType data;
	StackList *pstack = create_stack();
	if (NULL == pstack)
	{
		return -1;
	}
	
	push_stack(pstack, 1);
	push_stack(pstack, 2);
	push_stack(pstack, 3);
	push_stack(pstack, 4);
	
	pop_stack(pstack, &data);
	printf("pop %d\n", data);

	int ret = get_stack_top(pstack, &data);
	if (0 == ret)
	{
		printf("top = %d\n", data);
	}

	destaroy_stack(pstack);
	return 0;
}
