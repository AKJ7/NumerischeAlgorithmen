//
// Created by hp on 19.04.19.
//
#include <iostream>
#include <array>
#include <algorithm>


void maximin(int a, int b)
{
    (a > b) ? std::cout << "Max: " << a : (a == b) ? std::cout << "Gleicheit" : std::cout << "Max: " << b;
    std::cout << std::endl;
}

void maximin(unsigned a, unsigned b)
{
    (a > b) ? std::cout << "Max: " << a : (a == b) ? std::cout << "Gleicheit" : std::cout << "Max: " << b;
    std::cout << std::endl;
}

void maximini(unsigned a, unsigned b, unsigned c)
{
    unsigned arr[3] = {a, b, c};
    int counter{};
    for (unsigned v : arr)
    {
        counter = 0;
        for (unsigned w : arr)
        {
            if (v >= w)
                counter++;
            else  break;
        }
        if (counter == 3)
        {
            std::cout << "Max: " << v << std::endl;
            return;
        }
    }
}

// Methode 2

void maximini(const std::array<int, 3>& v)
{
    std::cout << "Max: " << *std::max_element(v.begin(), v.end()) << std::endl;
}


//int main(int argc, char** argv)
//{
//    int a; int b;
//    auto checkNichtNeg = [](int a, int b) { if (a < 0 || b < 0) throw std::invalid_argument("Keine Negative Zahl erlaubt!");};
//    if (argc == 1)
//    {
//        std::cout << "Eingabeformat: x y\n";
//        std::cin >> a >> b;
//        checkNichtNeg(a, b);
//        maximin(a, b);
//        return EXIT_SUCCESS;
//    }
//    if (argc != 3)
//    {
//        throw std::invalid_argument("Siehe Format");
//    }
//    a = std::stoi(argv[1]);
//    b = std::stoi(argv[2]);
//    checkNichtNeg(a, b);
//    maximin(a, b);
//    return 0;
//}

int main(int argc, char** argv)
{
    int a, b, c;

    auto nichtNeg = [](int a, int b, int c){if (a < 0 || b < 0 || c < 0) {throw std::invalid_argument("Negativitaet unerlaubt!");}};

    if (argc == 1)
    {
        std::cout << "Eingabe: a b c\n";
        std::cin >> a >> b >> c;
        nichtNeg(a, b, c);
//        maximini(a, b, c);
        maximini({a, b, c});
        return EXIT_SUCCESS;
    }

    if (argc != 4)
    {
        throw std::invalid_argument("Nur 3 Zahlen erlaubt!");
    }
    a = std::stoi(*++argv);
    b = std::stoi(*++argv);
    c = std::stoi(*++argv);
//    maximini(a, b, c);
    maximini({a, b, c});
    return  0;
}

