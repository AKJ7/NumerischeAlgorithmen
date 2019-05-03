//
// Created by hp on 03.05.19.
//

#include <iostream>
#include <cmath>

template <typename T>
void swap(T* a, T* b)
{
    T temp;
    temp = *a;
    *a = *b;
    *b = temp;
}
//template <typename T>
//void bubblesort(T* feld, int n)
//{
//    static int max = n;
//    while (--n)
//    {
//        if (n >= max) continue;
//        std::cout << "Vergleich: " << feld[n] << " vs " << feld[n - 1] << '\n';
//
//        if (feld[n] < feld[n - 1]){
//            swap(&feld[n], &feld[n -1]);
//            std::cout << "n: " << n++ << '\n';
//            bubblesort(feld, n + 1);
//        }
//    }
//}

template<typename T>
bool isSorted(T* a, int n)
{
    while (n)
    {
        if (a[n] < a[n - 1]){
            return false;
        }
        n--;
    }
    return true;
}


//template <typename T>
//void bubblesort(T* feld, int n)
//{
//    while (!isSorted(feld, --n))
//    {
//        std::cout << "n: " << n << '\n';
//        swap(&feld[n], &feld[n - 1]);
//        bubblesort(feld, n);
//    }
//}


//template <typename T>
//void bubblesort(T* feld, int n)
//{
//    while (!isSorted(feld, --n))
//    {
//        std::cout << "n: " << n << " swap: " << feld[n] << " " << feld[n- 1] << '\n';
//        swap(&feld[n], &feld[n - 1]);
//        bubblesort(feld, n);
//    }
//}

template<typename T>
void bubblesort(T* feld, int n)
{
    for (int i = n; i != 0; i--)
    {
        for (int j = 0; j < i - 1; j++)
        {
            if (feld[j] > feld[j + 1])
                swap(&feld[j], &feld[j + 1]);
        }
    }



}

int main() {

    int a = 2;
    int b = 3;
    swap(&a, &b);

    int feld[] = {1, 10, 3, 4, 3};
    bubblesort(feld, 5);
    for (int c : feld)
        std::cout << c << '\n';
    return EXIT_SUCCESS;
}