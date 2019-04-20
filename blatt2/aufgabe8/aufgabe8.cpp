//
// Created by hp on 20.04.19.
//

#include <iostream>
#include <limits>
#include <cmath>
#include <array>
#include <cfenv>


double bisektionsVerfahren(unsigned max_iter, double tol_f, const std::array<double, 2>& interval, double(f)(double) )
{
    static double c;
    static unsigned cur_iter = 0;
    cur_iter++;
    if (cur_iter == max_iter) return c;
    auto mitterlWertSatz = [&](double a, double b) -> bool { return f(a) * f(b) < 0; };
    if (mitterlWertSatz(interval[0], interval[1]))
    {
        c = 0.5 * (interval[0] + interval[1]);
        if (mitterlWertSatz(interval[0], c))
        {
            bisektionsVerfahren(max_iter, tol_f, {interval[0], c}, f);
        } else if (f(c) == 0) {
            return c;
        } else {
            bisektionsVerfahren(max_iter, tol_f, {c, interval[1]}, f);
        }
    } else {
        return c;
    }
}


int main()
{
    auto f = [](double x) -> double {return std::pow(x, 3) - 2 * x + 5;};
    std::cout << bisektionsVerfahren(20, 30, {-10, 10}, f) << std::endl;
    return EXIT_SUCCESS;
}