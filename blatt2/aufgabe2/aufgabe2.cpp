//
// Created by hp on 19.04.19.
//

#include <iostream>
#include <algorithm>
#include <cmath>
#include <limits>
// s_r
template <bool VORWAERTS>
float partialSummen(unsigned n)
{
    return n == 1 ? 1 : 1.0/n + partialSummen<VORWAERTS>(n - 1);
}

// s_v
template <>
float partialSummen<false>(unsigned n)
{
    double resultat{};
    unsigned counter{1};
    while (counter <= n){
        resultat += 1.0f/counter;
        counter++;
    }
    return resultat;
}


int main()
{
    std::cout.precision(15);

//    std::cout << partialSummen<true>(5) << std::endl;

    // Ausgabe
    float s_r, s_v;
    for (int k = 1; k <= 6; k++)
    {
        auto wert = static_cast<unsigned >(std::pow(10, k));
        std::cout << "Wert: " << wert << std::endl;
        s_r = partialSummen<false>(wert);
        s_v = partialSummen<true>(wert);
//        std::cout << "k = " << k << ", s_r: " << s_r << ", s_v: " << s_v << " s_v - s_r: " <<'\n';
    }

    // Interpretation: s_v hat better precision als s_r. Dies koennte daran liegen, dass der Verlust der Precision bei

    return 0;
}