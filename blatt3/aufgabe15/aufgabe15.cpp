//
// Created by hp on 25.04.19.
//

#include <iostream>
#include <cassert>
#include <cmath>



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


int main()
{
    double koef[] = {1, 2, 1};
    double res1, res2;
    std::cout << horner1(2, koef, 2) << std::endl;
    horner2(2, koef, 2, &res1);
    horner3(2, koef, 2, res2);
    std::cout << "Res1: " << res1 << '\n';
    std::cout << "Res2: " << res2 << '\n';
    return 0;
}