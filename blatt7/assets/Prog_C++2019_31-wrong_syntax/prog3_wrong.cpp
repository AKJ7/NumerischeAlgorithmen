//
//  prog3_wrong.cpp
//  
//
//  Created by Johannes Kraus and Maria Lymbery on 11/05/2019.
//
//
#include <iostream>
#include <cmath>
#include "header.h"

using namespace std;

void printstatement();

static void init_x();

double somesum() {
    double a = 3.5;
    double b = -14;
    double c;
    c = a+b;
    cout << "c is "<<c<<"\n";
}

static float x;
x = 4.5;

extern double y;

int main()
{
    printstatement();
    init_x();
    somesum();
    cout << "c is "<<c<<"\n";
    return 0;
}
