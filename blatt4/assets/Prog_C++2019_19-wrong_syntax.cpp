//
//  Prog_C++2019_19-correctsyntax.cpp
//
//
//  Created by Johannes Kraus and Maria Lymbery on 30/04/2019.
//
//

#include <iostream>               // Standard-Bibliothek fuer Input/Output
using namespace std;


class complexNumber {
public:
    double re;
    double im;
private:
    complexNumber()
    {
        cout << "constructor of complexNumber\n";
    }
};

class Test {
    static int Note=4;
    int x;
public:
    static Test* myNote()
    {
        return this;
    }
};

int main()
{
    complexNumber *obj = new complexNumber;
    complexNumber *arr = new complexNumber[10];
    cout<<"Note = "<<Test::Note << endl<<endl;
    Test t;
    cout << t.x<<"\n";
    cout << t.Note<<"\n";
    return 0;
}

