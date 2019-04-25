#include <iostream>               // Standard-Bibliothek fuer Input/Output
using namespace std;

// Fehlender Komma
struct complex
{
    double re;
    double im;
    bool operator== (const complex& rhs)
    {
        return this->re == rhs.re && this->im == rhs.im;
    }
};

class complexNumber {
public:
    double re;
    double im;

    void* operator new(size_t size) { return ::operator new(size);}
    //    void* operator new(size_t size) { void* ptr = std::malloc(size); return ptr? ptr : throw std::bad_alloc();}
    void* operator new[](size_t size) { return ::operator new(size);}
    //    void* operator new(size_t size) { void* ptr = std::malloc(size); return ptr? ptr : throw std::bad_alloc();}
    void operator delete(void* ptr){free(ptr);}
    void operator delete[](void* ptr){free(ptr);}
};

complex operator *(complex x, complex y)
{
    complex z;
    z.re=x.re*y.re-x.im*y.im;
    z.im=x.im*y.re+x.re*y.im;
    return z;
}

std::ostream& operator<<(std::ostream& out, complex z)
{
    return out << z.re << " + " << z.im << "i";
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
    complex x,z;
    x.re=1;
    x.im=2;
    complex y= {0,1};
    z=mymul(x,y);
    cout << z << '\n';
    z=x*y;
    cout << z << '\n';
    complex w;
    w = x;
    if (w == x)
        cout << "Same\n";
    complexNumber *obj = new complexNumber;
    complexNumber *arr = new complexNumber[10];
    delete(obj);
    delete[] (arr);
}

