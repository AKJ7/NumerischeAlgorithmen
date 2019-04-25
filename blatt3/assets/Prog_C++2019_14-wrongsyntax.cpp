//
//  Prog_C++2019_14-correctsyntax.cpp
//
//
//  Created by Johannes Kraus and Maria Lymbery on 19/04/2019.
//
//

#include <iostream>               // Standard-Bibliothek fuer Input/Output
using namespace std;

struct mycomplex
{
    double re;
    double im;
}

class complexNumber {
public:
    double re;
    double im;
    void* operator new(size_t size) {}
    void* operator size[](size_t size) {}
};

complex operator.*(complex x, complex y)
{
    complex z;
    z.re=x.re*y.re-x.im*y.im;
    z.im=x.im*y.re+x.re*y.im;
    return z;
}

std::ostream& operator<<(std::ostream& out, complex z)
{
    out << z.re << " + " << z.im << "i";
    out << "\n";
    return out;
}

complex mymul(complex x, complex y)
{
    struct complex z;
    z.re=x.re*y.re-x.im*y.im;
    z.im=x.im*y.re+x.re*y.im;
    return(z);
}

int main()
{
    mycomplex x,z;
    x.re=1;
    x.im=2;
    mycomplex y= {0,1};
    z=mymul(x,y);
    cout << z << endl;
    z=x.*y;
    cout << z << endl;
    complex w;
    w = x;
    if (w == x)
        cout << "Same\n";
    complexNumber *obj = new complexNumber;
    complexNumber *arr = new complexNumber[10];
}

