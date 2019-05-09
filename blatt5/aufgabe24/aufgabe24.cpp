//
// Created by hp on 09.05.19.
//

#include <iostream>               // Standard-Bibliothek fuer Input/Output

using namespace std;

class Square {

public:
    Square() : x(0) {};
    double getX() const { return x; }
    void setX(double X) { this->x =X; }
    static double count;
private:
    double x;
};

class SquareMesh {
private:
    friend class Square;
    double side;
public:
    SquareMesh() { side = -1.5; };
    void showSideSquare(Square& x) {
        std::cout << "Side of the square " << x.getX() <<endl;
    }
    ~SquareMesh() = default;

};

double Square::count= 4;

int main()
{
    Square MySquare;
    cout<<"Side of MySquare = "<<MySquare.getX()<<endl;
    MySquare.setX(2.3);
    cout<<"Side of MySquare = "<<MySquare.getX()<<endl;
    double side = 4;
    SquareMesh MySquareMesh;
    cout<<"Side of MySquare = ";
    MySquareMesh.showSideSquare(MySquare);
    return 0;
}

