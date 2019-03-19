
#include <iostream>
#include "Complex.h"

Complex::Complex(double re, double im) : re(re), im(im) {   }

Complex Complex::operator+(const Complex &z) {
    Complex res(this->re + z.re, this->im + z.im);
    return res;
}

Complex Complex::operator*(const Complex &z) {
    double re = this->re * z.re - this->im * z.im;
    double im = this->re * z.im + this->im * z.re;
    Complex res(re, im);
    return res;
}

Complex Complex::operator/(Complex &z){
    Complex conj(z.re, -z.im);
    Complex numitor = *this * conj;
    Complex numarator = z * conj;
    Complex res(numitor.re / numarator.re, numitor.im / numarator.re);
    return res;

}

std::ostream &operator<<(std::ostream &os, const Complex &z) {
    os << z.re;
    if(z.im > 0) {
        os << "+";
        if(z.im != 1)
            os << z.im;
        os << "i";
    }
    return os;
}

std::istream &operator>>(std::istream &is, Complex &z) {
    std::cout << "Partea reala: ";
    is >>  z.re;
    std::cout << "Partea imaginara: ";
    is >> z.im;
    return is;
}

void Complex::setRe(double re) {
    Complex::re = re;
}

void Complex::setIm(double im) {
    Complex::im = im;
}
