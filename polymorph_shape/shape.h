
#ifndef CLION_HW6_SHAPE_H
#define CLION_HW6_SHAPE_H

#include <cmath> //M_PI
#include <iostream>
#include <fstream>
#include <string> 

class shape { 
public:
    virtual double area() = 0; 
    virtual double volume() = 0; 
    virtual void show() = 0; 
};

class cylinder : public shape{ 
public:
    cylinder(double R, double H);

    double area() override ;
    double volume() override ;
    void show() override ;

private:
    double R;
    double H;
};

class parallelepiped : public shape {
public:
    parallelepiped(double a, double b, double c);
    double area() override ;
    double volume() override ;
    void show() override ;
private:
    double a;
    double b;
    double c;
};

int create_mas_from_file(std::ifstream& input,shape** &mas); 
void free_mas(shape** mas, int size);
#endif //CLION_HW6_SHAPE_H
