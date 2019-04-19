//
//  myfac_aufgabe1.cpp
//
//
//  Created by Johannes Kraus and Maria Lymbery on 10/04/2019.
//
//

#include <iostream>               // Standard-Bibliothek fuer Input/Output
#include "header.h"

int factorial(int n)
{
    if (n==1 || n==0)
        return 1;
    else
        return n*factorial(n-1);
}

//int main() {
//    using namespace std;
//
//    for (int n=0; n<=3; n++)
//        cout << '\n' << factorial(n) << '\n';
//
//    return 0;
//}
