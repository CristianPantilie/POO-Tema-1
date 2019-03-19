#include <iostream>
#include "Complex.h"
#include "Matrice.h"
using namespace std;

int main() {



    Matrice A(4, 4);
    Complex z1(1, 2);
    A.adauga(z1, 1, 1);
    Complex z2(0, -4);
    A.adauga(z2, 2, 3);
    Complex z3(3, 3);
    A.adauga(z3, 3, 3);
    Complex z4(-7, 2);
    A.adauga(z4, 4, 4);

    Matrice B(4, 1);
    Complex z5(6, 2);
    B.adauga(z5, 1, 1);
    Complex z6(-2, 3);
    B.adauga(z6, 4, 1);

    cout << A << "\n*\n" << B << "\n=\n" << A * B << "\n\n";

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

    cout << A << "\n+\n" << C << "\n=\n" << A + C << "\n\n";

    cout << C << "\n\n" << "Determinantul = " << C.determinant() << "\n\n";
    cout << "Inversa = \n";
    C.inversa();

    cout << "\n\nIntroduceti o matrice.\n";
    Matrice mat(0, 0);
    std::cin >> mat;
    std::cout << mat;
    return 0;
}