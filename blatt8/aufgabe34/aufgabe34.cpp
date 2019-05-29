//
// Created by hp on 5/29/19.
//

#include <iostream>
#include <cmath>


class Figure
{
protected:
    double area{};
    virtual void Flaeche() = 0;
public:
    double getArea() { return area; }
};


class Polygon : public Figure
{
protected:
    int Ecken;
public:
    explicit Polygon(int anzEcken) : Ecken{anzEcken} {};
    virtual int Anzahl_von_Ecken() { return Ecken; };
};


class Dreieck : public Polygon
{
private:
    double x_1, y_1, x_2, y_2, x_3, y_3;
public:
    Dreieck(double x_1, double y_1, double x_2, double y_2, double x_3, double y_3) : Polygon(3)
    {
        this->x_1 = x_1;
        this->x_2 = x_2;
        this->x_3 = x_3;
        this->y_1 = y_1;
        this->y_2 = y_2;
        this->y_3 = y_3;
        Flaeche();
    }
    void Flaeche() override
    {
        auto getLength = [](double a_1, double b_1, double a_2, double b_2) -> double
        {
            return sqrt(pow(a_2 - a_1, 2) + pow(b_2 - b_1, 2));
        };
        double a = getLength(x_1, y_1, x_2, y_2);
        double b = getLength(x_1, y_1, x_3, y_3);
        double c = getLength(x_2, y_2, x_3, y_3);
        double s = 0.5 * (a + b + c);
        area = std::sqrt(s* (s - a) * (s - b) * (s - c));
    }
};


class Rechteck : public Polygon
{
private:
    double coord[8];
public:
    Rechteck(double x_1, double y_1, double x_2, double y_2, double x_3, double y_3, double x_4, double y_4) : Polygon(4)
    {
        coord[0] = x_1;
        coord[1] = y_1;
        coord[2] = x_2;
        coord[3] = y_2;
        coord[4] = x_3;
        coord[5] = y_3;
        coord[6] = x_4;
        coord[7] = y_4;
        Flaeche();
    }
    Rechteck(double x_1, double y_1, double x_3, double y_3) : Rechteck(x_1, y_1, x_3, y_1, x_1, y_3, x_3, y_3) {  }
    void Flaeche() override
    {
        auto myAbs = [](double value)
        {
            return value < 0 ? -value : value;
        };
        auto getDiff = [this, myAbs](double start) -> double
        {
            for (double c : coord)
            {
                if (start != c)
                    return myAbs(start - c);
            }
            throw std::logic_error("Figure not a Rectangle");
        };
        area = getDiff(coord[0]) * getDiff(coord[1]);
    }
};


int main()
{
    Dreieck dreieck(0, 1, 1, 0, 0, 0);
    std::cout << dreieck.getArea() << '\n';

    Rechteck rechteck(0, 0, 2, 2);
    std::cout << rechteck.getArea() << '\n';

    return EXIT_SUCCESS;
}

