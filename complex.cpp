//
// Created by Or David on 19/01/2019.
//

#include "complex.h"
#include <cmath>


Complex::Complex(double r, double i) : re_(r) , im_(i){}

double Complex::get_i() const {
    return im_;
}


double Complex::get_r() const {
    return re_;
}

Complex& Complex::operator+(Complex &c) {

    double r(re_ + c.get_r());
    double i(im_ + c.get_i());
    Complex* sol;
    sol =new Complex(r,i);
    return *sol;
}


Complex& Complex::operator*(Complex &c) {
    double r = re_*c.get_r() - im_*c.get_i();
    double i = re_*c.get_i() + im_*c.get_r();
    Complex sol (r,i);
    return sol;
}


Complex& Complex::operator-(Complex &c) {
    double r(re_ - c.get_r());
    double i(im_ - c.get_i());
    Complex sol (r,i);
    return sol;
}

Complex& Complex::operator=(Complex &c) {
    re_ = c.get_r();
    im_ = c.get_i();
    return *this;
}


double abs(const Complex& c) {
    double r = c.get_r();
    double i = c.get_i();
    return sqrt(r*r + i*i);
}


ostream& operator<<(ostream& ro , const Complex& c) {
    ro << c.get_r() << " + " << c.get_i() << "i";
    return ro;
}
