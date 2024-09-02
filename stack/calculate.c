#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"

int is_char_num(char ch)
{
	if (ch >= '0' && ch <= '9')
	{
		return 1;
	}
	return 0;
}

int get_opt_level(char opt)
{
	switch(opt)
	{
		case '+':
		case '-':
			return 1;
		case '*':
		case '/':
			return 2;
	}
}

int get_result(int num1, int num2, char opt)
{
	switch(opt)
	{
		case '+':return num1 + num2;
		case '-':return num1 - num2;
		case '/':return num1 / num2;
		case '*':return num1 * num2;
	}
}


int main(int argc, const char *argv[])
{
	char press[128] = {0};
	int num = 0;
	DataType data;
	DataType opt;
	DataType num1;
	DataType num2;
	DataType res = 0;

	StackList *pNumStack = create_stack();
	StackList *pOptStack = create_stack();

	fgets(press, sizeof(press), stdin);
	press[strlen(press)-1] = '\0';
	
	char *p = press;
	
	while (1)
	{
		if ('\0' == *p && is_empty_stack(pOptStack))
		{
			break;
		}

		while (is_char_num(*p))
		{
			num = num * 10 + (*p - '0');
			p++;
			if (!is_char_num(*p))
			{
				push_stack(pNumStack, num);
				num = 0;
			}
		}
			
		if (is_empty_stack(pOptStack))
		{
			push_stack(pOptStack, *p);
			p++;
			continue;
		}
		if ('\0' == *p && !is_empty_stack(pOptStack))
		{
			pop_stack(pOptStack, &opt);
			pop_stack(pNumStack, &num2);
			pop_stack(pNumStack, &num1);
			res = get_result(num1, num2, opt);
			push_stack(pNumStack, res);	
			continue;
		}
		get_stack_top(pOptStack, &data);
		if (get_opt_level(data) < get_opt_level(*p))
		{
			push_stack(pOptStack, *p);
			p++;
		}
		else if (get_opt_level(data) >= get_opt_level(*p))
		{
			pop_stack(pOptStack, &opt);
			pop_stack(pNumStack, &num2);
			pop_stack(pNumStack, &num1);
			res = get_result(num1, num2, opt);
			push_stack(pNumStack, res);
		}
	}

	get_stack_top(pNumStack, &res);
	printf("res = %d\n", res);
	

	destaroy_stack(pNumStack);
	destaroy_stack(pOptStack);

	return 0;
}
