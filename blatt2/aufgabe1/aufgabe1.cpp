//
// Created by hp on 19.04.19.
//

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cfenv>


int factorial(int n)
{

    return n == 1 ? 1 : n * factorial(n - 1);
}

double factorial(double n)
{
    return n == 1 ? 1.0 : n * factorial(n - 1);
}

// Methode 1
double Euler(int n)
{
    int counter = 1;
    double result = 0;
    while (counter <= n)
    {
        result += 1.0 / factorial(counter);
        counter++;
    }
    return result;
}

// Methode 2
double Euler2(int n)
{
    return n == 1 ? 1 : (1.0/factorial(n)) + Euler2(n - 1);
}




int main()
{
    std::cout.precision(16);

    std::cout << Euler(13) << std::endl;
    std::cout << Euler2(13) << std::endl;

    // Vergleich
    std::cout << Euler(10) - Euler(9) << " " << 1.0 / factorial(10) << std::endl;

    // Bermerkung: e_n - e_n-1 hat eine bessere Genauigkeit

    std::cout << Euler(10) - Euler(9) << " " << 1.0 / factorial(10.0) << std::endl;

    // Bemerkung: Kein Unterschied

    return 0;
}