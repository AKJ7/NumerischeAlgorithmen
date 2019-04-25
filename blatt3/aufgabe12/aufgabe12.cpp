//
// Created by hp on 25.04.19.
//


#include <iostream>
#include <algorithm>
#include <cstring>
#include <type_traits>

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
    return std::find(p, p + strlen(p), c);
}

char* test = (char*)"Hallo";
void reverse(char* p)
{
    unsigned counter{};
    unsigned index{};
    size_t length = strlen(p);
    char temp;
    *(test + 2) = '\0';
    std::cout << test << std::endl;
}


int main()
{

    std::cout << find('s', const_cast<char*>("beispiel")) << '\n'; // Ausgabe spiel
    char* p = const_cast<char*>("hallo");
    reverse(p);
//    std::cout << p << std::endl;
    return 0;
}