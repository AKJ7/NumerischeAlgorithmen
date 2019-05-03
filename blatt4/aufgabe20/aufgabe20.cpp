//
// Created by hp on 03.05.19.
//

#include <iostream>
#include <cmath>
#include <string>

class Punkt
{
private:
    double x, y;

public:
    Punkt() = default;
    Punkt(double _x, double _y) : x{_x}, y{_y} {}
    ~Punkt() = default;
    Punkt( const Punkt& punkt) noexcept : x{punkt.y}, y{punkt.y}{}
    double* get() const { static double punkt[2]; punkt[0] = x; punkt[1] = y; return punkt;}
    void set(double a, double b) noexcept {x = a; y = b;}
    double operator[](const std::string& name){ if (name == "x") {return x;} else if (name == "y"){return y;} else {throw std::invalid_argument(name);}}
};


//double Abstand(Punkt& punkt1, Punkt& punkt2)
//{
//    return sqrt(pow(punkt1["x"] - punkt2["x"], 2) + pow(punkt1["y"] - punkt2["y"], 2));
//}

double Abstand(Punkt& punkt1, Punkt& punkt2)
{
    return sqrt(pow(punkt1.get()[0] - punkt2.get()[0], 2) + pow(punkt1.get()[1] - punkt2.get()[1], 2));
}


int main()
{

    auto p1 = new Punkt(0, 1);
    auto p2 = new Punkt(0, 2);
    std::cout << Abstand(*p1, *p2) << std::endl;

    return EXIT_SUCCESS;
}

