//
//  quadratic-eqn_aufgabe1.cpp
//  
//
//  Created by Johannes Kraus and Maria Lymbery on 10/04/2019.
//
//
// Loesen der quadratischen Gleichung a * x * x + b * x + c = 0
#include <iostream> // Ein- und Ausgabefunktionen
#include <cmath> // fuer Funktion sqrt()
#include "header.h"

using namespace std; // Namen der Standardbibliothek

//int factorial(int n);

int main()
{
    cout << "Eingabe der Koeffizienten a, b, c: ";
    double a, b, c;
    cin >> a >> b >> c;
    double root = sqrt(b * b - 4 * a * c);
    double root1 = -0.5 * (root + b) / a;
    double root2 = +0.5 * (root - b) / a;
    cout << "Loesungen: " << root1 << ", " << root2 << "\n";
    
//    for (int n=0; n<=4; n++)
//        cout << '\n' << factorial(n) << '\n';
    
    return 0; // Rueckgabewert fuer shell (0 <= Wert < 256!)
}
