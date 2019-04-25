//
// Created by hp on 25.04.19.
//

#include <iostream>

template <typename T>
struct Operation
{
    T a;
    Operation(T a)
    {
        this->a = a;
    }
    int operator+(int b)
    {
        return a * a - b*b;
    }
    double operator+(double b)
    {
        return a * a + b * b;
    }
};


int main()
{

    Operation<int> operation = 1;
    operation = operation + 2;
    std::cout << operation.a << std::endl;

    Operation<double> operation2 = 1;
    operation2 = operation2 + 2.0;
    std::cout << operation2.a << std::endl;

    return 0;
}