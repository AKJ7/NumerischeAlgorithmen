//
// Created by hp on 25.04.19.
//


#include <iostream>
#include <algorithm>

size_t groesse(char* p)
{
    size_t counter{};
    while (*p)
    {
        counter++;
        p++;
    }
    return counter;
}


// Methode 1

char* find(char c, char* p)
{
    while (p++)
    {
        if (*p == c)
            return p;
    }
    return nullptr;
}

// Methode 2

char* find2(char c, char* p)
{
    return std::find(p, p + groesse(p), c);
}


void swap(char* m, char* n)
{
    static char temp;
    temp = *m;
    *m = *n;
    *n = temp;
}

void swap(char& m, char& n)
{
    static char temp;
    temp = m;
    m = n;
    n = temp;
}

void reverse(char* p)
{
    size_t g = groesse(p) - 1;
    for (int counter = 0, index = 0; counter < g; counter += 2, index++)
    {
        swap(p + index, p + g - index);
    }
}

void reverse2(char* p)
{
    size_t g = groesse(p) - 1;
    for (int counter = 0, index = 0; counter < g; counter += 2, index++)
    {
        swap(p[index], p[g - index]);
    }
}

void insert(char* in, const char* ptr)
{
    while (*ptr)
    {
        *(in++) = *(ptr++);
    }
    *in = 0;
}


int main()
{

    std::cout << find('s', const_cast<char*>("beispiel")) << '\n'; // Ausgabe spiel
    char* p = new char[100];
    insert(p, "Hallo");
    std::cout << "Original: " << p << std::endl;

    reverse(p);
    std::cout << "Reverse: " << p << std::endl;

    reverse2(p);
    std::cout << "Reverse2: " << p << std::endl;
    return 0;
}