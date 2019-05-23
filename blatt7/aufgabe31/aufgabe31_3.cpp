//
// Created by hp on 5/23/19.
//

#include <iostream>
#include <cmath>
#include "header.h"


// CamelFormat fuer den Namen
void printStatement();

// Externe Funktion
void init_x();

// Fehlendes Return und '\n' statt "\n"
double someSum() {
    double a = 3.5;
    double b = -14;
    double c;
    c = a + b;
    std::cout << "c is "<< c << '\n';
    return c;
}

// Statischer Wert Initialisierung
static float x = 4.5;

extern double y;

int main()
{
    printStatement();
    init_x();
    double c = someSum();
    std::cout << "c is "<< c <<"\n";
    return 0;
}
