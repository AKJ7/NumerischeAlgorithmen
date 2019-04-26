//
// Created by hp on 26.04.19.
//

#include <iostream>
#include <cstring>


int factoriel(int n)
{
    return n == 0? 1 : n * factoriel(n - 1);
}

int binom(int n, int k)
{
    return factoriel(n) / (factoriel(k) * factoriel(n - k));
}

void pascal(int* p, int n)
{
    int k = 0;
    while (*(p + k) != 0)
    {
        k++;
    }
    for (int i = 0; i <= n ; i++)
    {
        *(p + i + k) = binom(n, i);
    }
}

void fibo(int* P, int* F, int n)
{
//    int result{};
//    for (int a = 0; a < n; a++)
//    {
//        result = 0;
//        for (int b = 0; b < a; b++)
//        {
//            result += *(P + b + a);
//        }
//        *(F + a) = result;
//    }
}

/// @brief Werte bis n in diagonalform
/// @param n max index
/// @returns ptr to the diagonal index
int* diagonalIndex(const size_t n)
{
    auto p = new int[n];
    int i = 1;
    int pos = 0;
    int scale = 0;
    for (int j = 0; j < 10; j++)
    {
        i += j;
        scale = j % 2 == 0  && j != 0 ? j - 1 : j;
        *(p + pos) = i;



        std::cout << i << '\n';
    }



    return p;
}


void pascalN(int* p, int n)
{
    for (int i = 0; i < n; i++)
    {
        pascal(p, i);
    }
}

int main()
{
    const int n = 100;
    int ptr[n];
    memset(ptr, 0, sizeof(ptr));

    pascalN(ptr, 5);
    for (auto a : ptr)
    {
//        std::cout << a << ' ';
    }
    std::cout << '\n';
    int fiboPtr[100];
    memset(fiboPtr, 0, sizeof(fiboPtr));
    fibo(ptr, fiboPtr, 5);
    diagonalIndex(100);
    return 0;
}