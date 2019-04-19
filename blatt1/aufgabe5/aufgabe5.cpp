//
// Created by hp on 19.04.19.
//

#include <iostream>

int static count()
{
    static int counter = 1;
    return counter++;
}


int main()
{
    std::cout << count() << std::endl;
    std::cout << count() << std::endl;
    std::cout << count() << std::endl;
    std::cout << count() << std::endl;
    std::cout << count() << std::endl;
    return EXIT_SUCCESS;
}
