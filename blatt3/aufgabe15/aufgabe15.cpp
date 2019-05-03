//
// Created by hp on 25.04.19.
//

#include <iostream>
#include <cassert>
#include <cmath>
#include <cstdarg>

//double pol(int n, double a[], double x)
//{
//    return n == 0 ? *a : (*a) * std::pow(x, n) + pol(n - 1, ++a, x) ;
//}

double horner1(int n, double a[], double x)
{
    return n == 0 ? *a : a[n--]  + x* horner1(n, a, x);
}


void horner2(int n, double a[], double x, double* res)
{
    *res = horner1(n, a, x);
}

void horner3(int n, double a[], double x, double& res)
{
    res = horner1(n, a, x);
}

void* operator new[](size_t size, ...)
{
    auto ptr = (double*)malloc(size);
    double* ptr2 = ptr;
    va_list args;
    va_start(args, size);

    for (int i = 0; i < size/8; ++i)
    {
        *(ptr2 + i) = va_arg(args, int);
    }
    va_end(args);

    return ptr;
}


int main()
{
    // Statischer Speicherallokation
    double koef[] = {2, 2, 1};
    double res2, res3;
    std::cout << "Res1: " << horner1(2, koef, 2) << std::endl;
    horner2(2, koef, 2, &res2);
    horner3(2, koef, 2, res3);
    std::cout << "Res2: " << res2 << '\n';
    std::cout << "Res3: " << res3 << '\n';


    // Dynamischer Speicherallokation
    uint32_t n = 2;
    auto koef2 = new(1, 2, 1) double[3];

    std::cout << "Res11: " << horner1(2, koef2, 2) << std::endl;

    return 0;
}