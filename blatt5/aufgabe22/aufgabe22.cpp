//
// Created by hp on 09.05.19.
//

#include <iostream>
#include <utility>
#include <cassert>
#include <algorithm>
#include <iterator>

extern "C" {
    #include "mat.h"
}


class Polynom
{
private:
    unsigned int degree;
    double* m_coeff;

public:
    explicit Polynom(unsigned int n) : degree{n} { m_coeff = nullptr; }
    Polynom(unsigned int n, double* coeff) : Polynom(n) { m_coeff = coeff; }
    Polynom(const Polynom& p) = default;
    std::pair<unsigned int, double* > get() const { return {degree, m_coeff}; }
    void set_coef(double* coeff) { assert(coeff != nullptr); m_coeff = coeff; }
    void set_deg(unsigned int n)  { degree = n; }
    double eval(double x) const { return hoerner(degree, m_coeff, x); }
    Polynom derivative() const { return Polynom(degree - 1, polDerivative(degree, m_coeff));}
    Polynom integral(double c_0) const { return Polynom(degree + 1, polIntegral(degree, m_coeff, c_0)); }
    inline void pptrint() const noexcept
    {
        int counter = degree + 1;
        while (counter--)
        {
            std::cout << m_coeff[degree - counter] << "x^" << counter << " + ";
        }
        std::cout << "\b\b\b";
    }
    ~Polynom() = default;
};

int main()
{
    double koeff[] = {1,2,1};
    Polynom polynom(2, koeff);
    std::cout << "Original: ";
    polynom.pptrint();
    Polynom derivative = polynom.derivative();
    std::cout << "\nDerivative: ";
    derivative.pptrint();
    std::cout << "\nIntegral: ";
    auto integral = polynom.integral(323);
    integral.pptrint();

    return EXIT_SUCCESS;
}