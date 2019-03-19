
#ifndef TEMA1_MATRICE_H
#define TEMA1_MATRICE_H


#include <ostream>
#include "Complex.h"

class Matrice {
private:
    unsigned int linii, coloane;

    struct pozitie
    {
        unsigned int linie;
        unsigned int coloana;
    };

    struct nod
    {
        Complex val;
        struct pozitie poz;
        struct nod *next;
    };
    struct nod *head;

    friend int comparaPoz(struct pozitie p1, struct pozitie p2);
    Matrice transpusa();
    void cofactor(Complex **mat, Complex **cof, int i, int j, int n);
    Complex det(Complex **mat, int n);
    void adjuncta(Complex **mat, Complex **adj, int n);

public:
    Matrice(unsigned int linii, unsigned int coloane);
    void adauga(Complex z, unsigned int linie, unsigned int coloana);

    Matrice operator+(const Matrice &z);
    Matrice operator*(Matrice &z);

    friend std::ostream &operator<<(std::ostream &os, const Matrice &matrice);
    friend std::istream &operator>>(std::istream &is, Matrice &matrice);

    Complex determinant();
    void inversa();


};


#endif
