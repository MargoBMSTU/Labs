#include <iostream>
#include <fstream>
#include "shape.h"

using namespace std;



int main(int argc,char **argv) {
    ifstream input(*++argv); 
    shape **mas = NULL;  
    int size = 0;
    if (input.is_open()) { 
        size = create_mas_from_file(input, mas); 
        for (int i = 0; i < size; ++i) { 
            mas[i]->show();
            cout << "area = " << mas[i]->area() << endl;
            cout << "volume = " << mas[i]->volume() << endl << endl;
        }
    } else {
        cout << "Can't open file" << endl;
    }
    free_mas(mas, size); 
    input.close();
    return 0;
}
