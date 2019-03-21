

#include <iostream>
#include <fstream>
#include "Matrice.h"
using namespace std;

Matrice::Matrice(unsigned int linii, unsigned int coloane) : linii(linii), coloane(coloane) {
    this->head = nullptr;
}

//adauga in lista si o mentine sortata dupa pozitia numarului in matrice
void Matrice::adauga(Complex z, unsigned int linie, unsigned int coloana) {
    auto *nou = new struct nod;
    nou->val =  z;
    nou->poz.linie = linie;
    nou->poz.coloana = coloana;
    nou->next = nullptr;

    if(!this->head || comparaPoz(this->head->poz, nou->poz) >= 0)
    {
        nou->next = this->head;
        this->head = nou;
    }
    else
    {
        auto *iter = this->head;
        while(iter->next && comparaPoz(iter->next->poz, nou->poz) < 0)
            iter = iter->next;

        nou->next = iter->next;
        iter->next = nou;
    }
}


//verifica daca pozitia p1 este mai mica decat pozitia p2
int comparaPoz(Matrice::pozitie p1, Matrice::pozitie p2)
{
    if( (p1.linie < p2.linie) || (p1.linie == p2.linie && p1.coloana < p2.coloana) )
        return -1;    //mai mica
    else if(p1.linie == p2.linie && p1.coloana == p2.coloana)
        return 0;     //egale
    else
        return 1;     //mai mare

}

Matrice Matrice::operator+(const Matrice &z) {
    if(this->linii == z.linii && this->coloane == z.coloane)
    {
        Matrice rez(z.linii, z.coloane);

        auto *iter1 = this->head;
        auto *iter2 = z.head;

        while(iter1 || iter2)
        {
            int c;
            if(iter1 && iter2)
                c = comparaPoz(iter1->poz, iter2->poz);
            else if(!iter1)
                c = 1;
            else
                c = -1;

            if(c == 0)
            {
                rez.adauga(iter1->val + iter2->val, iter1->poz.linie, iter1->poz.coloana);
                iter1 = iter1->next;
                iter2 = iter2->next;
            }
            else if(c > 0)
            {
                rez.adauga(iter2->val, iter2->poz.linie, iter2->poz.coloana);
                iter2 = iter2->next;
            }
            else if(c < 0)
            {
                rez.adauga(iter1->val, iter1->poz.linie, iter1->poz.coloana);
                iter1 = iter1->next;

            }
        }
        return rez;
    }
    else
    {
        std::cout << "Matricile nu pot fi adunate";
        return Matrice(0, 0);
    }
}

Matrice Matrice::operator*(Matrice &z) {
    if(this->coloane == z.linii)
    {
        Matrice rez(this->linii, z.coloane);
        Matrice zt = z.transpusa();
        auto *iter1 = this->head;
        auto *iter2 = zt.head;

        for (int i = 1; i <= this->linii; ++i)
        {
            bool found = false;
            Complex r(0, 0);
            while(iter1 && iter1->poz.linie < i)
                iter1 = iter1->next;

            while(iter1 && iter1->poz.linie == i)
            {
                iter2 = zt.head;
                int col;
                for (int j = 1; j <= zt.linii; ++j) {

                    while (iter2 && iter2->poz.linie < j)
                        iter2 = iter2->next;

                    while (iter2 && iter2->poz.linie == j)
                    {
                        for (int k = 1; k <= zt.linii; ++k)
                        {
                            if (iter1->poz.coloana == k && iter2->poz.coloana == k) {
                                if (found)
                                    r = r + iter1->val * iter2->val;
                                else {
                                    r = iter1->val * iter2->val;
                                    found = true;
                                    col = j;
                                }
                            }
                        }
                        iter2 = iter2->next;
                    }
                }
                if (found)
                    rez.adauga(r, i, col);

                iter1 = iter1->next;
            }
        }
        return rez;
    }
    else
    {
        cout << "Matricile nu pot fi inmultite";
        return Matrice(0, 0);
    }
}

Matrice Matrice::transpusa() {

    Matrice rez(this->coloane, this->linii);
    auto *iter = this->head;

    while(iter)
    {
        rez.adauga(iter->val, iter->poz.coloana, iter->poz.linie);
        iter = iter->next;
    }

    return rez;
}

Complex Matrice::determinant()
{
    if(this->linii == this->coloane)
    {
        Complex mat[this->linii][this->coloane];
        auto *iter = this->head;
        for (int i = 0; i < this->linii ; ++i) {
            for (int j = 0; j < this->coloane; ++j) {
                if(iter && iter->poz.linie == i + 1 && iter->poz.coloana == j + 1)
                {
                    mat[i][j] = iter->val;
                    iter = iter->next;
                }
                else
                    mat[i][j] = 0;
            }
        }

        Complex *b[this->linii];
        for (int i = 0; i < this->linii ; ++i) {
            b[i] = mat[i];
        }

        return det(b, this->linii);

    }
    else
    {
        cout << "Matricea nu este patratica";
        return Complex();
    }
}

void Matrice::cofactor(Complex **mat, Complex **cof, int i, int j, int n) {
    int l = 0, k = 0;
    for (int lin = 0; lin < n; ++lin) {
        for (int col = 0; col < n; ++col) {
            if(lin != i && col != j)
            {
                cof[l][k++] = mat[lin][col];
                if(k == n - 1)
                {
                    k = 0;
                    l++;
                }
            }
        }
    }
}

Complex Matrice::det(Complex **mat, int n) {

    Complex D;

     if(n == 2) {
         Complex c1 = mat[0][0] * mat[1][1];
         Complex c2 = mat[0][1] * mat[1][0];
         return c1 + Complex(-1) * c2;
     }

    Complex **cof = new Complex *[n];
    for (int i = 0; i < n; ++i) {
        cof[i] = new Complex[n];
    }
    Complex semn(1);

    for (int i = 0; i < n; ++i) {
        cofactor(mat, cof, 0, i, n);
        D =  D + semn * mat[0][i] * det(cof, n - 1);
        semn.setRe(-1);
    }

    return D;
}

void Matrice::adjuncta(Complex **mat, Complex **adj, int n) {

    if(n == 1){
        adj[0][0] = 1;
        return;
    }

    Complex semn(1);
    Complex **temp = new Complex*[n];
    for (int i = 0; i < n; ++i) {
        temp[i] = new Complex[n];
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cofactor(mat, temp, i, j, n);

            if((i + j) % 2 == 0) {
                semn = 1;
            }
            else {
                semn = -1;
            }

            adj[j][i] = semn * det(temp, n - 1);
        }
    }
}

Matrice Matrice::inversa() {

    Complex det = this->determinant();
    if(det.im == 0 && det.re == 0)
    {
        cout << "Nu se poate calcula inversa";
        return Matrice(0, 0);
    }

    Complex **mat = new Complex *[this->linii];
    for (int i = 0; i < this->linii; ++i) {
        mat[i] = new Complex[this->linii];
    }
    auto *iter = this->head;
    for (int i = 0; i < this->linii ; ++i) {
        for (int j = 0; j < this->coloane; ++j) {
            if(iter && iter->poz.linie == i + 1 && iter->poz.coloana == j + 1)
            {
                mat[i][j] = iter->val;
                iter = iter->next;
            }
            else
                mat[i][j] = 0;
        }
    }

    Complex inversa[this->linii][this->linii];
    Complex **adj = new Complex *[this->linii];
    for (int i = 0; i < this->linii; ++i) {
        adj[i] = new Complex[this->linii];
    }

    adjuncta(mat, adj, this->linii);

    for (int i = 0; i < this->linii; ++i) {
        for (int j = 0; j < this->linii; ++j) {
            inversa[i][j] = adj[i][j] / det;
        }
    }

    Matrice inv(this->linii, this->linii);

    for (int i = 0; i < this->linii; ++i) {
        for (int j = 0; j < this->linii; ++j) {
                inv.adauga(inversa[i][j], i + 1, j + 1);
        }
    }

    return inv;
//
//    for (int i = 0; i < this->linii; ++i) {
//        for (int j = 0; j < this->linii; ++j) {
//            f << inversa[i][j] << " ";
//        }
//        f << "\n";
//    }
}

ostream &operator<<(ostream &os, const Matrice &matrice) {
    if(!matrice.head)
        os << "Matricea este goala";
    else
    {
        auto *iter = matrice.head;

        for (int i = 1; i <= matrice.linii; ++i) {
            for (int j = 1; j <= matrice.coloane; ++j) {
                if(iter->poz.linie == i && iter->poz.coloana == j)
                {
                    os << iter->val << "       ";
                    if(iter->next)
                        iter = iter->next;
                }
                else
                    os << "   " << 0 << "       ";
            }
            os << endl;
        }
    }
    return os;
}

std::istream &operator>>(std::istream &is, Matrice &matrice) {
    cout << "\nNr. de linii: ";
    is >> matrice.linii;
    cout << "\nNr. de coloane: ";
    is >> matrice.coloane;
    while(true) {
        cout << "\nApasati 1 pentru a introduce un numar complex si 0 pentru a va opri";
        int i;
        is >> i;
        if (i == 1) {
            Complex z;
            unsigned int lin, col;
            is >> z;
            cout << "\nLinia: ";
            is >> lin;
            cout << "\nColoana: ";
            is >> col;
            matrice.adauga(z, lin, col);
        } else
            break;
    }

    return is;
}

