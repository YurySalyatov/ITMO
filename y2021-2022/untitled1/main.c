#include "return_codes.h"

#include <malloc.h>
#include <math.h>
#include <stdio.h>

// read n from input file
size_t read_n(FILE *filein)
{
	size_t n = 0;
	fscanf(filein, "%Iu\n", &n);
	return n;
}

//void print_f(float matrix[], size_t n) {
//	for (size_t i = 0; i < n; i++) {
//		for (size_t j = 0; j < n + 1; j++) {
//			printf("%f ", matrix[i * (n + 1) + j]);
//		}
//		printf("\n");
//	}
//	printf("\n");
//}

// read matrix from input file
void read_to_array(FILE *filein, float matrix[], size_t n)
{
	for (size_t i = 0; i < n; i++)
	{
		for (size_t j = 1; j <= n; j++)
		{
			fscanf(filein, "%f ", &matrix[i * (n + 1) + j - 1]);
		}
		fscanf(filein, "%f\n", &matrix[i * (n + 1) + n]);
	}
}

// write to file
void write_answer_to_file(FILE *fileout, float q[], size_t n)
{
	// printf("printing the answer\n");
	for (size_t i = 0; i < n; i++)
	{
		fprintf(fileout, "%f\n", q[i * (n + 1) + n]);
	}
}

// find next row to swap it with now row
size_t find_next_i(float const matrix[], size_t start, size_t shift, size_t n)
{
	size_t l = start - shift + 1;
	while (matrix[l * (n + 1) + start] == 0 && l < n)
	{
		l++;
	}
	return l;
}

// swap now row and found fow
void swap(float matrix[], size_t l, size_t k, size_t n)
{
	for (size_t i = 0; i < n + 1; i++)
	{
		float t = matrix[l * (n + 1) + i];
		matrix[l * (n + 1) + i] = matrix[k * (n + 1) + i];
		matrix[k * (n + 1) + i] = t;
	}
}

// want to know how many solutions we have
int check_solutions(float const matrix[], size_t shift, size_t n)
{
	int flag = 1;
	// expected one solution
	if (shift != 0)
	{
		flag = -1;
		// expected many solutions
	}
	for (size_t i = n - shift; i < n; i++)
	{
		if (matrix[(n - 1) * (n + 1) + i + 1] != 0)
		{
			flag = 0;
			break;
			// we have no solution
		}
	}
	return flag;
}

// subtraction row for right_step_Gays()
void down_subtraction(float matrix[], size_t n, size_t start, size_t shift)
{
	for (size_t j = start - shift + 1; j < n; j++)
	{
		float mult = matrix[j * (n + 1) + start] / matrix[(start - shift) * (n + 1) + start];
		for (size_t k = start; k < n + 1; k++)
		{
			matrix[j * (n + 1) + k] -= mult * matrix[(start - shift) * (n + 1) + k];
			if (fabsf(matrix[j * (n + 1) + k]) < 0.00001)
			{
				matrix[j * (n + 1) + k] = 0;
			}
		}
	}
}

// it will be done if have one solution
void back_step_Gaus(float matrix[], size_t n)
{
	for (size_t i = n; i > 0; i--)
	{
		for (size_t j = i - 1; j > 0; j--)
		{
			matrix[(j - 1) * (n + 1) + n] -= matrix[(j - 1) * (n + 1) + (i - 1)] / matrix[(i - 1) * (n + 1) + (i - 1)] * matrix[(i - 1) * (n + 1) + n];
			matrix[(j - 1) * (n + 1) + (i - 1)] = 0;
		}
		matrix[(i - 1) * (n + 1) + n] /= matrix[(i - 1) * (n + 1) + (i - 1)];
		if (fabsf(matrix[(i - 1) * (n + 1) + n]) < 0.00001)
		{
			matrix[(i - 1) * (n + 1) + n] = 0;
			// number is too small, maybe it is 0
		}
		matrix[(i - 1) * (n + 1) + (i - 1)] = 1;
		// make beautiful matrix
	}
}
// want to know number of solutions
int right_step_Gaus(float matrix[], size_t n)
{
	size_t shift = 0;
	for (size_t i = 0; i < n; i++)
	{
		if (matrix[(i - shift) * (n + 1) + i] == 0)
		// check element not 0
		{
			size_t k = find_next_i(&matrix[0], i, shift, n);
			// expected row with not 0 element under now
			if (k < n)
			{
				swap(&matrix[0], i - shift, k, n);
				// find row with not 0 element under now
				down_subtraction(&matrix[0], n, i, shift);
				// subtract row
			}
			else
			{
				shift++;
				// can't find not 0 element under now, move to right col;
			}
		}
		else
		{
			down_subtraction(&matrix[0], n, i, shift);
			//          subtract row
		}
	}
	int solution = check_solutions(&matrix[0], shift, n);
	//  know how many solution we have
	return solution;
}

int main(int arg, char *args[])
{
	if (arg != 3)
	{
		printf("Incorrect number of arguments, expected 3, received %i", arg);
		return ERROR_INVALID_PARAMETER;
		// incorrect number of arguments
	}
	FILE *filein = fopen(args[1], "r");
	//  try to open input file
	if (filein == NULL)
	{
		printf("Can't open or find input file with name: %s", args[1]);
		return ERROR_NOT_FOUND;
		//      something error with input file
	}
	size_t n = read_n(filein);
	//  read size of matrix from input file
	float *matrix = malloc(n * (n + 1) * sizeof(float));
	printf("%i\n", sizeof (matrix));
	//  try to free some memory for matrix n(n + 1)
	if (matrix == NULL)
	{
		printf("There is no memory on your computer for array of float with size %i", n * (n + 1));
		fclose(filein);
		return ERROR_MEMORY;
		// not enough memory, close input file
	}

	read_to_array(filein, matrix, n);
	// read data from input file
	fclose(filein);
	// close file after read
	FILE *fileout = fopen(args[2], "w");
	// try to open output file
	if (fileout == NULL)
	{
		printf("Can't open or find input file with name: %s", args[2]);
		free(matrix);
		return ERROR_NOT_FOUND;
		// can't open output file, free taken memory
	}
	int solution = right_step_Gaus(matrix, n);
	//  know how many solution matrix has
	if (solution == 1)
	{
		back_step_Gaus(matrix, n);
		// find this one solution
		write_answer_to_file(fileout, matrix, n);
		// write solution to file
	}
	else
	{
		if (solution == -1)
		{
			fprintf(fileout, "many solutions\n");
			// write that we have many solutions
		}
		else
		{
			fprintf(fileout, "no solution\n");
			// write that we have no solution
		}
	}
	free(matrix);
	fclose(fileout);
	//  free taken memory, close output file after write
	return 0;
	//  program end correctly
}