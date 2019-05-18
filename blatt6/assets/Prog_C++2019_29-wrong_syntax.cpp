//
//  Prog_C++2019_29-wrong_syntax.cpp
//
//
//  Created by Johannes Kraus and Maria Lymbery on 13/05/2019.
//
//

#include <iostream>
#include <stdio.h>


void swap(int* a, int* b)
{
    int c = *a;
    *a = *b;
    *b = c;
}

void swap2(int& a, int& b)
{
    int c = a;
    a = b;
    b = c;
}

int main()
{
    int a = 5;
    
    int *c;
    c = 0;
    swap(&a,c);
    const int d = 0;
    int *dptr = &d;
    swap2(a,d);
    swap2(a,4);
    swap2(a,*dptr);
    return 0;
}
