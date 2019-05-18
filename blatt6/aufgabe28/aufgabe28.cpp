#include <iostream>
#include <stdio.h>
#include <utility>

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

void swap3(int& a, int&& b)
{
    swap2(a, std::forward<int&>(b));
}

int main()
{
    int a = 5;
    int c = 0;
    // int *c;
    //c = nullptr;
    swap(&a, &c);
    int d = 0;
    int *dptr = &d;
    swap2(a,d);
    swap3(a,4);  // Alternative 4 as lvalue irgendwo speichern um die Addresse abfragen zu koennen
    swap2(a,*dptr);
    return 0;
}
