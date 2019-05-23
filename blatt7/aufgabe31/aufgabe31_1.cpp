//
// Created by hp on 5/23/19.
//

#include <iostream>               // Standard-Bibliothek fuer Input/Output
#include "header.h"

// Format: using namespace std vermeiden

double a = 4;

// Funktionname: CamelFormat!
void printStatement() {
    std::cout << "a is: "<< a <<"\n";
}

static float x;

extern void init_x() {
    x = 4.5;
    std::cout << "x is "<<x<<"\n";
}

// Format: Extern und static passen nicht zusammen
extern char myvariable;
