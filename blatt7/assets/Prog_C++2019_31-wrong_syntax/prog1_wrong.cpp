//
//  prog1_wrong.cpp
//
//
//  Created by Johannes Kraus and Maria Lymbery on 11/05/2019.
//
//

#include <iostream>               // Standard-Bibliothek fuer Input/Output
#include "header.h"
using namespace std;

double a = 4;
void printstatement() {
    cout << "a is "<<a<<"\n";
}

static float x;

static void init_x() {
    x = 4.5;
    cout << "x is "<<x<<"\n";
}

extern static char myvariable;

