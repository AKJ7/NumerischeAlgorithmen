#include <iostream>               // Standard-Bibliothek fuer Input/Output
using namespace std;


class complexNumber {
private:
    double re;
    double im;
public:
    complexNumber() : re{}, im{} { cout << "constructor of complexNumber\n";}
};

class Test {
public:
    static int Note;
    int x{};
    Test* myNote()
    {
        return this;
    }
};

int Test::Note = 0;

int main()
{
    complexNumber* obj = new complexNumber();
    complexNumber *arr = new complexNumber[10];
    cout << "Note = " << Test::Note << "\n\n";
    Test t;
    cout << t.x << '\n';
    cout << Test::Note << '\n';
    return 0;
}

