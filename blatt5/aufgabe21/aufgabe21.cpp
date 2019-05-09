//
// Created by hp on 09.05.19.
//

#include <iostream>
#include <utility>
#include <cassert>

class Polynom
{
private:
    unsigned int degree;
    double* m_coeff;

public:
    explicit Polynom(unsigned int n) : degree{n} { m_coeff = nullptr; }
    Polynom(unsigned int n, double* coeff) : Polynom(n) { m_coeff = coeff; }
    Polynom(const Polynom& p) = default;
    std::pair<unsigned int, double* > get() { return {degree, m_coeff}; }
    void set_coef(double* coeff) { assert(coeff != nullptr); m_coeff = coeff; }
    void set_deg(unsigned int n) { degree = n; }
    ~Polynom() = default;
};

int main()
{
    double coef[] = {1, 2, 1};

    Polynom polynom1(2, coef);
    Polynom polynom2(3);
    polynom2 = polynom1;
    std::clog << polynom2.get().first << '\n';
    std::clog << "Koef: ";
    for (int i = 0; i <= polynom1.get().first; i++)
    {
        std::clog << *(polynom2.get().second + i) << ' ';
    }
    std::clog << '\n';

    return EXIT_SUCCESS;
}