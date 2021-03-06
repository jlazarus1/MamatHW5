//
// Created by Or David on 19/01/2019.
//

#include "complex.h"
#include <cmath>


Complex::Complex(double r, double i) :im_(i),re_(r) {}

double Complex::get_i() const {
    return im_;
}


double Complex::get_r() const {
    return re_;
}

Complex::Complex(const Complex& rhs) {

    im_= rhs.get_i();
    re_ = rhs.get_r();
}

Complex Complex::operator+(const Complex &c) const {

    double r(re_ + c.get_r());
    double i(im_ + c.get_i());
    Complex sol(r,i);
    return sol;
}


Complex Complex::operator*(const Complex &c) const {
    double r = re_*c.get_r() - im_*c.get_i();
    double i = re_*c.get_i() + im_*c.get_r();

    Complex sol(r,i);

    return sol;
}


Complex Complex::operator-(const Complex &c) const {
    double r(re_ - c.get_r());
    double i(im_ - c.get_i());
    Complex sol(r,i);
    return sol;
}

    double abs(const Complex &c) {
        double r = c.get_r();
        double i = c.get_i();
        return sqrt(r * r + i * i);
    }


ostream& operator<<(ostream& ro , const Complex& c) {
    ro << c.get_r() << " + " << c.get_i() << "i";
    return ro;
}
