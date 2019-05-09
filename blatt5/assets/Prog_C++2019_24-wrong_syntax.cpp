/home/hp/Downloads/Prog_C++2019_24-wrong_syntax.cpp/Prog_C++2019_24-wrong_syntax.cpp//
//  Prog_C++2019_24-wrong_syntax.cpp
//
//
//  Created by Johannes Kraus and Maria Lymbery on 2/05/2019.
//
//

using namespace std;
#include <iostream>               // Standard-Bibliothek fuer Input/Output


class Square {
public:
    Square : x(0){
    };
    static double count;

    double getX() {
        return x;
    }
    void setX(double X) {
        *this.x=X;
    }
private:
    double x;
};

class SquareMesh {
public:
    SquareMesh()
    {
        this->side = -1.5;
    };
    ~virtual SquareMesh() {};
    friend class Square;
    void showSideSquare(Square& x) {
        std::cout << "Side of the square " << Square.x<<endl;
    }
private:
    double side;
};

int Square::count= 4;

int main()
{
    Square MySquare;
    cout<<"Side of MySquare = "<<MySquare.getX()<<endl;
    MySquare.setX(2.3);
    cout<<"Side of MySquare = "<<MySquare.getX()<<endl;
    double side =4;
    SquareMesh MySquareMesh;
    cout<<"Side of MySquare = "<<My.showSideSquare(MySquare)<<endl;
    return 0;
}

