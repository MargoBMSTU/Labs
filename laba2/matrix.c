#include "matrix.h"

double getnum(FILE * fp){  //получает число из файла
	double num = 0;
	if( fscanf(fp, "%lf", &num) == 1){//возвращает число успешно считанных позиций (в данном случае мы считываем 1 число)
		return num;											//если мы успешно считали это 1 число то мы просто его возвращаем
	}else {														//иначе (если мы не считали 1 число типа дабл)
		printf("Error. Not a double number in file\n");   // отправляем что пошло не так
		exit(1);				  
	}								
}


double get_elem(Matrix* p, int row, int col){  //получить элемент под номером row,col(строка,столбец)
	return p->m[row][col];
}
void set_elem(Matrix* p, int row, int col, double val){  //положить в элемент матрицы под номером row,col число val
	p->m[row][col] = val;
	return;
}
int get_rows(Matrix* p){   //получить количество строк в матрице
	return p->rows;
}
int get_cols(Matrix* p){  //получить количество столбцов в матрице
	return p->cols;
}

Matrix* Matr_alloc(int rows, int cols){ /*выделение памяти под структуру и инициализация полей rows и cols*/
	Matrix *p = (Matrix*) malloc( sizeof(Matrix) ); //выделяем память под хранение матрицы(2 инта и указатель,4+4+8=16 байт)
	p->rows = rows; //р - указатель на структуру, p->row - поле row этой структуры
	p->cols = cols;
	return p;
}

Matrix* create_matrix_from_file(FILE *f){  //создать матрицу 
	int rows = getnum(f); //читаем из файла первое число (получаем количество строк)
	int cols = getnum(f); //читаем из файла второе число (получаем количество столбцов)
	Matrix* p = Matr_alloc(rows, cols); // выделяем память под Структуру-матрицу и кладем в неё количество строк и столбцов 

	p->m = (double**) calloc(get_rows(p), sizeof(double*));//выделяем память под указатели на строки   (массив указателей)
	for (int i = 0; i < get_rows(p); ++i) 
		p->m[i] = (double*) calloc(get_cols(p), sizeof(double));//выделяем память для каждой строки

	for (int i = 0; i < get_rows(p); ++i) 
		for (int j = 0; j < get_cols(p); ++j){
			set_elem(p,i,j,getnum(f));      //заполняем двумерный массив(матрицу)
		} 
	return p;
}



void printMatrix(Matrix *p){  //печать матрицы
	for (int i = 0; i < get_rows(p); ++i) {
		for (int j = 0; j < get_cols(p); ++j){
			printf("%f ", get_elem(p, i, j));  
		} 
		printf("\n"); 
	}
	return;
}
long double norm(Matrix *p){//поиск нормы матрицы	
	long double norma = 0;
	for (int i = 0; i < get_rows(p); ++i)
		norma = norma + get_elem(p,i,0);
	for (int j = 1; j < get_cols(p); ++j){		
		long double sum = 0;
		for (int i = 0; i < get_rows(p); ++i)
		  sum = sum + get_elem(p,i,j);	
		if (sum>norma) {norma = sum;}
	}
	return norma;
}

void free_matrix(Matrix *p){
	for (int i = 0; i < get_rows(p); ++i) //удаляем память выделенную под строки(массивы)
		free(p->m[i]);     
	free(p->m);					 //удалем сам массив указалетей на эти строки
	free(p);						 //удаляем память выделенную под структуру Matrix
}
