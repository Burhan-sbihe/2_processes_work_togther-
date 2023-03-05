#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

extern int matrix_dimension_in_integer;
extern int number_of_generation;
extern char updated_forest[1]="";
extern FILE* output;

void cleaning_forest(char* forest, char* cleand_forest)
{
	int counter = 0, i = 0;
	while (i < strlen(forest) == 1)
	{
		if ((forest[i] == 'T') || (forest[i] == 'F') || (forest[i] == 'G'))
		{
			cleand_forest[counter] = forest[i];
			counter++;
		}
		i++;
	}
	cleand_forest[counter] = '\0';
}

void put_string_in_2dmatrix(char** matrix, char* string, int dimention)
{
	int counter = 0, row, colum;
	while (string[counter] != '\0')
	{
		row = counter / dimention;
		colum = counter % dimention;
		matrix[row][colum] = string[counter];
		counter++;
	}
}

char** file_read(FILE* input_forest)
{
	char the_forest[100] = "", line[100] = "", * clean_forest;
	char** two_d_matrix;
	int  counter;
	
	matrix_dimension_in_integer = atoi(fgets(line, 50, input_forest));
	
	clean_forest = malloc(((matrix_dimension_in_integer * matrix_dimension_in_integer) + 1) * sizeof(char));
	
	two_d_matrix = malloc(matrix_dimension_in_integer * sizeof(char*));
	
	for (counter = 0; counter < matrix_dimension_in_integer; counter++)
	{
		two_d_matrix[counter] = malloc(matrix_dimension_in_integer * sizeof(char));
	}
	number_of_generation = atoi(fgets(line, 50, input_forest));

	fgets(line, 50, input_forest);

	strcpy(the_forest, line);
	while (!feof(input_forest))
	{
		fgets(line, 50, input_forest);
		strcat(the_forest, line);
	}
	cleaning_forest(the_forest, clean_forest);
	//fprintf(output, "%s\n", cleaning_forest);
	printf("%s\n", clean_forest); /////////////////////////// WRITE THIS TO OUTPUT FILE!!!
	put_string_in_2dmatrix(two_d_matrix, clean_forest, matrix_dimension_in_integer);
	return two_d_matrix;
}


/* THE AVAILABLE FUNCTION RETURNS 1 WHEN ITS AVAILABLE
TO CHEK THE NEIGHBORS AND NOT EXCEED DIMENTION SIZE, ELSE RETURNS 0*/
int Available(int i, int j) 
{
	if (((i >= 0) && (i < matrix_dimension_in_integer)) && ((j >= 0) && (j < matrix_dimension_in_integer)))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


/*THE Tree_to_Fire FUNCTION TURNS EVERY Tree TO Fire */
void Tree_to_Fire(char** forest, int row, int colum)
{
	if (Available(row - 1, colum) && (forest[row - 1][colum] == 'F'))
		strcat(updated_forest, "F");
	
	else if (Available(row + 1, colum) && (forest[row + 1][colum] == 'F'))
		strcat(updated_forest, "F");

	else if (Available(row, colum - 1) && (forest[row][colum - 1] == 'F'))
		strcat(updated_forest, "F");

	else if (Available(row, colum + 1) && (forest[row][colum + 1] == 'F'))
		strcat(updated_forest, "F");

	else
		strcat(updated_forest, "T");
}

/*THE Ground_to_Tree FUNCTION TURNS EVERY GROUND TO TREE IF THERE IS TWO TREE NEIGHBORS*/
void Ground_to_Tree(char** forest, int row, int colum)
{
	int Counter = 0;

	if (Available(row - 1, colum) && (forest[row - 1][colum] == 'T'))
		Counter++;
	if (Available(row + 1, colum) && (forest[row + 1][colum] == 'T'))
		Counter++;
	if (Available(row, colum - 1) && (forest[row][colum - 1] == 'T'))
		Counter++;
	if (Available(row, colum + 1) && (forest[row][colum + 1] == 'T'))
		Counter++;
	if (Available(row-1, colum - 1) && (forest[row-1][colum - 1] == 'T'))
		Counter++;
	if (Available(row-1, colum + 1) && (forest[row-1][colum + 1] == 'T'))
		Counter++;
	if (Available(row+1, colum + 1) && (forest[row+1][colum + 1] == 'T'))
		Counter++;
	if (Available(row+1, colum - 1) && (forest[row+1][colum - 1] == 'T'))
		Counter++;

	if (Counter >=2)
		strcat(updated_forest, "T");
	else
		strcat(updated_forest, "G");
}

void Run_Generation(char** forest)
{
	int row, colum, generation_num= number_of_generation-1;
	
	while (generation_num != 0)
	{
		for (row = 0; row < matrix_dimension_in_integer; row++)
		{
			for (colum = 0; colum < matrix_dimension_in_integer; colum++)
			{

				if (forest[row][colum] == 'T')
					Tree_to_Fire(forest, row, colum);

				else if (forest[row][colum] == 'F') // Fire TURNS TO Ground 
					strcat(updated_forest, "G");

				else if (forest[row][colum] == 'G')
					Ground_to_Tree(forest, row, colum);
			}
		}
		printf("%s\n", updated_forest);
		fprintf(output, "%s\n", updated_forest);
		//fputs("HAHA", output);
		put_string_in_2dmatrix(forest, updated_forest, matrix_dimension_in_integer); //	SET THE NEW FOREST AFTER EVERY GENERATION
		strcpy(updated_forest, ""); // RESET THE UPTADET_FOREST STRING FOR THE NEW GENERATION
		generation_num--;

	}
}


