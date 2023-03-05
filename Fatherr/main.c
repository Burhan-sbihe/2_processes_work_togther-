#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include"function.h"

int matrix_dimension_in_integer;
int number_of_generation;
char updated_forest[1];
FILE* output;

int main(int argc, char* argv[])
{
	FILE* input = NULL;
	char** matrix;

	fopen_s(&input, argv[1], "r");
	fopen_s(&output, argv[2], "w"); // OPEN THE OUTPUT FILE
	matrix = file_read(input);
	
	Run_Generation(matrix);

	fclose(output); // CLOSE THE OUTPUT FILE
}

