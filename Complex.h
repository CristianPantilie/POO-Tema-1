
#ifndef TEMA1_COMPLEX_H
#define TEMA1_COMPLEX_H

#include <ostream>

class Complex {
private:
    double re, im;
public:
    Complex(double re = 0, double im = 0);

    friend class Matrice;

    void setRe(double re);
    void setIm(double im);

    Complex operator+(const Complex &z);
    Complex operator*(const Complex &z);
    Complex operator/(Complex &z);

    friend std::ostream &operator<<(std::ostream &os, const Complex &z);
    friend std::istream &operator>>(std::istream &is, Complex &z);
};


#endif