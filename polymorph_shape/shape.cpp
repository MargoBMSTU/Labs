

#include "shape.h"

#define STEP 10 



double cylinder::area() { 
    return (2*M_PI*R*R + 2*M_PI*R*H); 
}

double cylinder::volume() {
    return (M_PI*R*R*H);
}

cylinder::cylinder(double R, double H) : R(R), H(H) {} 

void cylinder::show() { 
    std::cout << "This is a cylinder" << std::endl;
    std::cout << "H = " << H << std::endl;
    std::cout << "R = " << R << std::endl;
}

parallelepiped::parallelepiped(double a, double b, double c) : a(a), b(b), c(c) {} 

double parallelepiped::area() {
    return (a*b*2+b*c*2+a*c*2);
}

double parallelepiped::volume() {
    return (a*b*c);
}

void parallelepiped::show() { 
    std::cout << "This is a parallelepiped" << std::endl;
    std::cout << "a = " << a << std::endl;
    std::cout << "b = " << b << std::endl;
    std::cout << "c = " << c << std::endl;
}


int create_mas_from_file(std::ifstream& input, shape **&mas) {
    delete [] mas; 
    int size = STEP;
    mas = new shape*[size];
    int i = 0;
    while (!input.eof()){
        std::string name;
        input >> name; 
        if (name == "cylinder"){
            double r;
            double h;
            input >> r >> h;
            mas[i] = new cylinder(r,h);
        } else if (name == "parallelepiped"){
            double a,b,c;
            input >> a >> b >> c;
            mas[i] = new parallelepiped(a,b,c);
        }                
        else {           
            std::cout << "wrong input" << std::endl;
            return -1;
        }
        ++i;
        if (i >= size){
            size += STEP;
            shape** tmp = new shape*[size]; 
            for (int j = 0; j < size - STEP; ++j)
                tmp[j] = mas[j];
            delete [] mas;
            mas = tmp;
        }
    }
    size = i;
    shape** tmp2 = new shape*[size];
    for (int k = 0; k < size; ++k)
        tmp2[k] = mas[k]; 
    delete [] mas;
    mas = tmp2;
    return size;
}

void free_mas(shape **mas,int size) {
    for (int i = 0; i < size; ++i) {
        delete mas[i];
    }
    delete [] mas;
}
