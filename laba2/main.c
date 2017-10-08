#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h> //strerror() преобразовать код ошибки в строку
#include "matrix.h"

int main (int argc, char *argv[]){
	int count = argc-1; // количество файлов введенных в командную строку
	FILE * fp;
	Matrix **A = (Matrix**) calloc(count, sizeof(Matrix*)); //выделяем память под массив указателей на структуру-Matrix
	
	for (int i = 0; i < count; ++i) { //заполняем матрицы из файлов
		const char* file_name = *++argv;  //имя файла
	
		fp = fopen(file_name, "r");   //попытка открыть файл
		if (errno != 0){							//если возникал ошибка 
			printf("%s:%s\n",file_name, strerror(errno));  //печатаем с к каким файлом и что не так
			return errno;  //завершаем работу программы возрващая код ошибки
		}
			A[i] = create_matrix_from_file(fp); 
			fclose(fp);
		
	}
	for (int i = 0; i < count; ++i) {  //печатаем считанные матрицы
		printf("Matrix %d\n",i);
		printMatrix(A[i]);
		printf("\n");
	}
	for (int i = 0; i < count;i++){
		printf("Norma %d matrix = %Lf\n",i,norm(A[i])); //печатаем нормы матрицы
	}

	for (int i = 0; i < count; ++i) //удаляем каждую матрицу
		free(A[i]);
	free(A); // удаляем массив указателей на матрицы 
	return 0;
}
