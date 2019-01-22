//
// Created by Or David on 19/01/2019.
//

#ifndef MAMATHW5_COMPLEX_H
#define MAMATHW5_COMPLEX_H

#include <iostream>

using namespace std;

class Complex{
private:
    double im_;
    double re_;

public:
    Complex(double r=0, double i=0);
    double get_r() const;
    double get_i() const;
    Complex& operator+(Complex& c);
    Complex& operator*(const Complex &c) const;
    Complex& operator-(Complex& c);
    Complex& operator=(Complex& c);
    friend ostream& operator<<(ostream& ro , const Complex& c);
    friend double abs(const Complex& c);
};

#endif //MAMATHW5_COMPLEX_H
