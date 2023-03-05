#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#define max_trees_number 100

int main()
{
	int fired_counter = 0, flag_end_tree = 0;
	char input_tree;
	while (!flag_end_tree)
	{
		input_tree = getc(stdin);
		if (input_tree == 'F')
		{
			fired_counter++;
		}
		if (isalpha(input_tree) == 0)
		{
			flag_end_tree = 1;
		}
	}
	return fired_counter;
}