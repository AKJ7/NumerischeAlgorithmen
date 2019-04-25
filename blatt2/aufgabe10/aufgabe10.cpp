//
// Created by hp on 20.04.19.
//


#include <iostream>
#include <cfenv>
#include <cmath>
#include <array>
#include <utility>

struct DreicksKoord
{
    double a[2];
    double b[2];
    double c[2];
    DreicksKoord(double a_x, double a_y, double b_x, double b_y, double c_x, double c_y){
        a[0] = a_x;
        a[1] = a_y;
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        b[0] = b_x;
        b[1] = b_y;
        c[0] = c_x;
        c[1] = c_y;
    }
    DreicksKoord() = default;
};


struct Dreieck{
    struct koord
    {
        double a, b;
        double operator-(koord rhs)
        {
            return sqrt(pow(this->a - rhs.a, 2) + pow(this->b - rhs.b, 2));
        }
    };

    Dreieck(koord a, koord b, koord c)
    {
        dreieckKoord[0] = a;
        dreieckKoord[1] = b;
        dreieckKoord[2] = c;
    }

    Dreieck(DreicksKoord* dreicksKoord)
    {
        dreieckKoord[0] = {dreicksKoord->a[0], dreicksKoord->a[1]};
        dreieckKoord[1] = {dreicksKoord->b[0], dreicksKoord->b[1]};
        dreieckKoord[2] = {dreicksKoord->c[0], dreicksKoord->c[1]};
    }

    double getFlaeche()
    {
        // Heron's Methode
        double a = dreieckKoord[0] - dreieckKoord[1];
        double b = dreieckKoord[0] - dreieckKoord[2];
        double c = dreieckKoord[1] - dreieckKoord[2];
        double s = 0.5 * (a + b + c);
        return sqrt(s * (s - a)* (s - b) * (s - c));
    }
private:
    koord dreieckKoord[3];
};

std::istream& operator>>(std::istream& o, DreicksKoord& dreicksKoord)
{
    return o >> dreicksKoord.a[0] >> dreicksKoord.a[1] >> dreicksKoord.b[0] >> dreicksKoord.b[1] >> dreicksKoord.c[0]>> dreicksKoord.c[1];
}

int main()
{

    std::cout << "DreiecsEcken eingeben: (Format: a_x a_y b_x, b_y c_x c_y)";

    DreicksKoord dreicksKoord;
    std::cin >> dreicksKoord;

//    Dreieck dreieck({0, 0}, {1, 1}, {0, 1});
    Dreieck dreieck(&dreicksKoord);
    std::cout << dreieck.getFlaeche() << std::endl;

    return EXIT_SUCCESS;
}
