//
// Created by hp on 19.04.19.
//

//
//  Prog_C++2019_9_wrongsyntax.cpp
//
//
//  Created by Johannes Kraus and Maria Lymbery on 13/04/2019.
//
//

#include <cmath>
#include <iostream>

// Rueckgabe float Wert statt int
double fun1()
{
    return -7.1;
}

// Verbesserung: long int als Rueckgabetyp
//double fun2(int x, int y)
//{
//    return x+y;
//}

double fun2(double x, double y)
{
    return x+y;
}

// Rueckgabe 0 geendetes String statt char
char fun3()
{
    return 'b';
}

// Modifizierte func3
const char* fun3_mod()
{
    return "b";
}


int main() {
    fun1();
    std::cout << &fun1 << "\n";
    std::cout << reinterpret_cast<void *>(fun1) << "\n";
    std::cout << fun3 << "\n";
    std::cout << (bool) fun3() << "\n";

//    int (*Ptr1)() = fun1();
    double (*Ptr1)() = fun1;
//    double (*Ptr2)() = fun2;
    double (*Ptr2)(double, double) =(fun2);
//    double (*Ptr2)() = fun2(2, 3);

    double ptr4 = fun2(2, 3);



    char (*Ptr3)() = fun3;

    std::cout << Ptr2(1.0, 3.5) << "\n";
//    std::cout << &ptr4(1.0, 3.0) << "\n";

}