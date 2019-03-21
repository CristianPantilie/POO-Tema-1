#include <iostream>
#include <fstream>
#include "Complex.h"
#include "Matrice.h"
using namespace std;

int main() {

    ofstream f;
    ifstream g;
    f.open("writehere.txt");
    g.open("readhere.txt");

    unsigned int linii, coloane;
    g >> linii >> coloane;
    Matrice A(linii, coloane);
    int k = 0, nr;
    g >> nr;
    while(k < nr){
        double re, im;
        unsigned int linie, coloana;
        g >> re >> im;
        g >> linie >> coloana;
        Complex z(re, im);
        A.adauga(z, linie, coloana);
        k++;
    }

    Matrice B(4, 1);
    Complex z5(6, 2);
    B.adauga(z5, 1, 1);
    Complex z6(-2, 3);
    B.adauga(z6, 4, 1);

    f << A << "\n*\n" << B << "\n=\n" << A * B << "\n\n";

    Matrice C(4, 4);
    Complex x1(3, 3);
    C.adauga(x1, 1, 2);
    Complex x2(-2, -2);
    C.adauga(x2, 2, 3);
    Complex x3(-8, 0);
    C.adauga(x3, 2, 4);
    Complex x5(0, -4);
    C.adauga(5, 3, 1);
    Complex x4(5, 2);
    C.adauga(x4, 4, 4);

    f << A << "\n+\n" << C << "\n=\n" << A + C << "\n\n";

    f << C << "\n\n" << "Determinantul = " << C.determinant() << "\n\n";
    f << "Inversa = \n" << C.inversa();


    f.close();
    g.close();
//
//    cout << "\n\nIntroduceti o matrice.\n";
//    Matrice mat(0, 0);
//    std::cin >> mat;
//    std::cout << mat;
    return 0;
}