#include <iostream>
#include <cmath>


struct elem
{
    int num;
    elem* next;
    explicit elem(int n) : num {n}, next{} {}
};


class Liste
{
public:
    elem* pEnd;
    elem* pCurrent;
    elem* pStart;

    Liste() : pEnd{}, pStart{}, pCurrent{} {}
    void append(int n)
    {
        pCurrent = new elem(n);
        pCurrent->next = pEnd;
        pEnd = pCurrent;
        static bool start = [&](){ pStart = pCurrent; return true;}();
    }
    ~Liste()
    {
        elem* ptr = pEnd;
        while (ptr != pStart)
        {
            static int counter{};
            counter++;
            pCurrent = ptr;
            ptr = ptr->next;
            delete(pCurrent);
        }
    }
};


class Liste2
{
public:
    elem* pStart;
    elem* pEnd;
    elem* pCurrent;

    Liste2() { pStart = pEnd = new elem(0);}
    void append(int n)
    {
        pEnd->num = n;
        pEnd->next = new elem(0);
        pEnd = pEnd->next;
    }

    ~Liste2() {
        elem* ptr = pStart;
        while (ptr->next)
        {
            elem* ptrlast = ptr;
            ptr = ptr->next;
            delete ptrlast;
        }
    }
};




int main(){

    Liste meineListe;

    meineListe.append(10);
    meineListe.append(11);
    meineListe.append(21);
    meineListe.append(31);
    meineListe.append(12321);


    elem* ptr = meineListe.pEnd;
    while (ptr != meineListe.pStart)
    {
        std::cout << ptr->num << '\n';
        ptr = ptr->next;
    }

//    std::cout << meineListe.pCurrent->next->num << std::endl;
//    std::cout << meineListe.pStart->num << std::endl;
//    std::cout << meineListe.pEnd->num << std::endl;


//    Liste2 liste2;
//    liste2.append(10);
//    liste2.append(20);
//    liste2.append(32);
//    liste2.append(2454);
//    liste2.append(54645);
//
//
//    for (elem* ptr = liste2.pStart; ptr->next; ptr = ptr->next)
//    {
//        std::cout << ptr->num << std::endl;
//    }


    return 0;
}





































////
////
//// Created by hp on 03.05.19.
//
//
//#include <iostream>
//
//
//struct elem
//{
//    int num;
//    elem* next;
//    elem(int i) : num{i} {}
//};
//
//
//class Liste
//{
//public:
//    elem* pStart = nullptr;
//    elem* pEnd = nullptr;
//    elem* pCurrent = nullptr;
//
//public:
//    Liste() {};
//    void append(int i) {
//        pCurrent = new elem(i);
//        pEnd = pCurrent;
////        static bool a = [&]() -> bool{ pStart = pCurrent; return true; }();
//        pCurrent = pCurrent->next;
//    }
//    bool iter() const {}
//    ~Liste() {};
//};
//
//
//int main()
//{
//    Liste meineListe;
//    meineListe.append(2);
//    meineListe.append(3);
//    meineListe.append(4);
//    meineListe.append(5);
//    meineListe.append(6);
//    meineListe.append(7);
//
//    std::cout << *meineListe.pStart->next->num << std::endl;
//
//
////    for ( elem* ptr = meineListe.pStart; ptr != nullptr; ptr = ptr->next)
////    {
////        std::cout << ptr->num << std::endl;
////    }
//
//    return 0;
//}