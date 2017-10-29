#include <iostream>
#include "mystring.hpp"
using namespace std;


void bubblesort(String* m, int size){  //сортировка пузырьком 
	for (int i = 0; i < size; ++i) 
		for (int j = i; j < size; ++j) 
			if (m[j] < m[i])
				m[j].swap_s(m[i]);
}

void printMas(String* m, int size){ //печать массива
	for (int i = 0; i < size; ++i) {
		cout << m[i] << " ";
	}
	cout << endl;
}

int main (int argc, char *argv[]){
	cout << "Enter mas size:";
	int size = 0;
	cin >> size; 
	cout << "Enter " << size << " words" << endl;
	String* mas = new String[size];
	for (int i = 0; i < size; ++i) {
		cin >> mas[i];
	}
	cout << "Your input:" <<endl;
	printMas(mas,size);
	bubblesort(mas,size);
	cout << "After sort:" <<endl;
	printMas(mas,size);
	delete	[] mas;
	return 0;
}
