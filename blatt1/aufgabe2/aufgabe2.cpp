//
// Created by hp on 19.04.19.
//

#include <iostream>
#include <cmath>
#include <algorithm>

template <int START, int END>
struct Range
{


};

// Methode 1
void poweroftwo(int n)
{
    if (n < 0) throw std::invalid_argument("No negativ values allowed");
    int counter{};
    while (counter <= n)
    {
        std::cout << std::pow(2, counter) << std::endl;
        counter++;
    }
}

// Methode 2
void poweroftwo2(int n)
{
//    std::for_each(0, n, [](int counter){std::cout << std::pow(2, counter) << std::endl;});
}

// Methode 1
void dreick(int n)
{
    for (int m = 0; m <= n; m++)
    {
        for (int l = 0; l <= m; l++)
        {
            std::cout << "*";
        }
        std::cout << '\n';
    }
}

// Methode 2
void dreick2(int n)
{
    int counter = 1, counter2 = 1;
    while (counter <= n)
    {
        std::cout << "**********";
        counter2 = 1;
        while ((counter2 + counter) <= 10)
        {
            std::cout << '\b';
            counter2++;
        }
        std::cout << '\n';
        counter++;
    }
}

void pruefer(int x, int y) {
    auto interval = [&](int val, int min, int max) {
        std::cout << val << " liegt " << ((val >= min && val <= max) ? "" : "nicht ") << "zwischen " << min << " und "
        << max << '\n';
    };
    interval(x, 10, 20);
    interval(y, 100, 120);
}

// d

void ddreick(int n)
{
    for (int m = 0; m <= n; m++)
    {
        for (int l = 0; l <= m; l++)
        {
            (m % 2 == 0) ?  std::cout << "+" : std::cout << "*";
        }
        std::cout << '\n';
    }
}


int main()
{

    ddreick(10);

    return EXIT_SUCCESS;
}