//
// Created by hp on 5/23/19.
//

#include <iostream>
#include <random>

class LU
{
    int N;
    float** L;
    float** U;
    float** A;

public:
    LU() = default;
    void LUdecomposition(float** a, float** l, float** u, int n)
    {
        // Algorithmus ohne Pivotierung
        A = a;
        L = l;
        U = u;
        mcpy(U, a, 3);
        eMatrix(L, 3);

        for (int i = 0; i < n-1; i++)
        {
            for (int k = i + 1; k < n; k++)
            {
                L[k][i] = U[k][i] / U[i][i];
                for (int j = i; j < n; j++)
                {
                    U[k][j] = U[k][j] - L[k][i] * U[i][j];
                }
            }
        }

        std::cout << "Matrix A: \n";
        printMatrix(A, 3);
        std::cout << "Matrix L: \n";
        printMatrix(L, 3);
        std::cout << "Matrix U: \n";
        printMatrix(U, 3);
    }

    static void printMatrix(float** M, int n)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                std::cout << M[i][j] << " ";
            }
            std::cout << '\n';
        }
    }
    template <typename T>
    static void mcpy(T** dest, T** src, size_t n)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                dest[i][j] = src[i][j];
            }
        }
    }

    static void eMatrix(float** m, int n)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                m[i][j] = i == j ? 1 : 0;
            }
        }
    }
    ~LU() = default;
};


int main()
{
    float a[3] = {1, 2, 3};
    float b[3] = {1, 1, 1};
    float c[3] = {3, 3, 1};
    float** A;
    A = new float*[3];
    A[0] = a;
    A[1] = b;
    A[2] = c;

    float** L = new float*[3];
    L[0] = new float[3];
    L[1] = new float[3];
    L[2] = new float[3];
    float** U = new float*[3];
    U[0] = new float[3];
    U[1] = new float[3];
    U[2] = new float[3];
    int n = 3;

    LU lu{};
    lu.LUdecomposition(A, L, U, n);

    void (LU::* ptr)(float**, float**, float**, int) = &LU::LUdecomposition;

    (lu.*ptr)(A, L, U, n);


    return EXIT_SUCCESS;
}