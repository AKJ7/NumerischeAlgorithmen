//
//  Prog_C++2019_9_wrongsyntax.cpp
//
//
//  Created by Johannes Kraus and Maria Lymbery on 13/04/2019.
//
//

#include <cmath>
#include <iostream>

int fun1()
{
    return -7.1;
}

double fun2(int x, int y)
{
    return x+y;
}

char fun3()
{
    return "b";
}

int main()
{
    fun1();
    std::cout << &fun1 << "\n";
    std::cout << reinterpret_cast<void*>(fun1)<<"\n";
    std::cout << fun3 << "\n";
    std::cout << (bool)fun3() << "\n";

    int (*Ptr1)() = fun1();
    double (*Ptr2)() = fun2;
    double (*Ptr2)() = fun2(2,3);
    int (*Ptr3)() = fun3;

    std::cout << Ptr2(1.0,3.5) << "\n";
    std::cout << &Ptr2(1.0,3.0) << "\n";
    
    return 0;
}
