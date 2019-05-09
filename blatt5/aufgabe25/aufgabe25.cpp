//
// Created by hp on 09.05.19.
//

#include <iostream>
#include <tuple>
#include <cmath>
#include <string>
#include <algorithm>


class Punkt
{
private:
    double x, y;

public:
    Punkt() = default;
    Punkt(double _x, double _y) : x{_x}, y{_y} {}
    explicit Punkt(std::pair<double, double>&& a ){ x = a.first; y = a.second; }
    ~Punkt() = default;
    Punkt( const Punkt& punkt) noexcept : x{punkt.x}, y{punkt.y}{}
    double* get() const { static double punkt[2]; punkt[0] = x; punkt[1] = y; return punkt;}
    void set(double a, double b) noexcept {x = a; y = b;}
    double operator[](std::string&& name){ if (name == "x") {return x;} else if (name == "y"){return y;} else {throw std::invalid_argument(name);}}
};

double Abstand(Punkt& punkt1, Punkt& punkt2);

class Dreieck
{
private:
    Punkt a, b, c;
    friend double Abstand(Punkt& punkt1, Punkt& punkt2);
    friend void getDistance1(double a[3], Dreieck&D);
public:
    Dreieck() = default;
    Dreieck(const Punkt& A, const Punkt& B, const Punkt& C) noexcept : a{A}, b{B}, c{C} { }
    Dreieck(Dreieck& dreieck) = default;
    std::tuple<Punkt, Punkt, Punkt> get() const { return std::make_tuple(a, b, c); }
    void set( const Punkt& A, const Punkt& B, const Punkt& C) { a = A; b = B; c = C; }
    Punkt& operator[] (char charac) {
        switch (charac)
        {
            case 'a':
                return a;
            case 'b':
                return b;
            case 'c':
                return c;
            default:
                throw std::invalid_argument("Character not supported");
        }
    }
    ~Dreieck() = default;
};

double Abstand(Punkt& punkt1, Punkt& punkt2)
{
    return sqrt(pow(punkt1.get()[0] - punkt2.get()[0], 2) + pow(punkt1.get()[1] - punkt2.get()[1], 2));
}

void getDistance(double a[3], Dreieck& D)
{
    a[0] = Abstand(D['a'], D['b']);
    a[1] = Abstand(D['a'], D['c']);
    a[2] = Abstand(D['b'], D['c']);
}

void getDistance1(double a[3], Dreieck&D)
{
    a[0] = Abstand(D.a, D.b);
    a[1] = Abstand(D.a, D.c);
    a[2] = Abstand(D.b, D.c);
}

bool compareArray(double a[3], double b[3])
{
    std::sort(a, a+3);
    std::sort(b, b+3);
    int counter{};
    while (counter < 3)
    {
        if (b[counter] != a[counter])
            return false;
        counter++;
    }
    return true;
}

bool kongruent1(Dreieck& D1, Dreieck& D2)
{
    double a[3];
    double b[3];
    getDistance(a, D1);
    getDistance(b, D2);
    return compareArray(a, b);
}

bool kongruenz2(Dreieck& D1, Dreieck& D2) {
    double a[3];
    double b[3];
    getDistance1(a, D1);
    getDistance1(b, D2);
    return compareArray(a, b);
}

int main()
{

    Punkt a(1, 0);
    Punkt b(1, 1);
    Punkt c(0, 1);
    Dreieck dreieck(a, b, c);
    Dreieck dreieck1 = dreieck;
//    dreieck.set(a, b, Punkt(2, 4));
    Dreieck dreieck2(Punkt(0,0), Punkt(0, 1), Punkt(1, 1));
    std::cout << std::boolalpha << kongruent1(dreieck1, dreieck2) << '\n';
    return EXIT_SUCCESS;
}