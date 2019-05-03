//
// Created by hp on 03.05.19.
//

#include <iostream>
#include <cmath>


double distance(int n, double* a, double* b)
{
    double result = 0;
    while (n)
    {
        result += pow(a[--n] - b[n], 2);
    }
    return sqrt(result);
}

double* element(int i, int j, double* A, int m)
{
    return &A[ (i -1)  + m * (j - 1)];
}

void mult(int m, int n, double* M, double* v, double* w)
{
    for (int i = 1; i <= m; i++)
    {
        w[i - 1] = 0;
        for (int j = 1; j <= n; j++)
        {
            w[i - 1] += *element(i, j, M, m) * v[j - 1];
        }
    }
}


int main()
{

    // a
    double a[] = {1, 2};
    double b[] = {2, 3};
    std::cout << "Distance: " << distance(2, a, b) << '\n';

    // b

//    [1 4 7 10
//    2 5 8 11
//    3 6 9 12]
    double A[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}; // 3x4 Matrix
    std::cout << "Element: " << *element(3, 3, A, 3) << "\n\n";

//     c
    double* M = A;
    double v[] = {1, 2, 3, 4};
    double w[3];
    mult(3, 4, M, v, w);
    std::cout << "w: \n";
    for (double m : w)
        std::cout << "["<< m <<"]" << '\n';

    return EXIT_SUCCESS;
}
