#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <stdio.h>
#include <stdlib.h>


typedef struct Matr {  
	int rows;
	int cols;							
	double **m;
} Matrix;       //теперь вместо того чтобы при объявлении "struct Matr A" можно обойтись прсто Matrix A

Matrix* create_matrix_from_file(FILE *f);
void free_matrix(Matrix *p);
double get_elem(Matrix* p, int row, int col);
void set_elem(Matrix* p, int row, int col, double val);
int get_rows(Matrix* p);
int get_cols(Matrix* p);
long double norm(Matrix *p);
void printMatrix(Matrix *p);

#endif 
