//
// Created by hp on 6/9/19.
//

#ifndef NUMERISCHE_ALGORITHMEN_GRAP_H
#define NUMERISCHE_ALGORITHMEN_GRAP_H

#include <unordered_map>
#include <string>
#include <vector>
#include <iterator>
#include <tuple>
#include <cassert>
#include <random>
#include <algorithm>
#include <utility>


namespace GraphenTheorie
{
    class Graph
    {
    public:
        class Kante
        {
        private:
            friend Graph;
            char nachbar;
            double gewicht;
        public:
            Kante(char nachbar, double gewicht) : nachbar{nachbar}, gewicht{gewicht} {}
            std::pair<char, double> getData() const noexcept { return {nachbar, gewicht}; }
            ~Kante() = default;
        };
    private:
        std::unordered_map<char, std::vector<Kante>> graphMap;
        typedef std::unordered_map<char, std::vector<Kante>> graphType;
        constexpr static const char *alphabet = "abcdefghijklmnopqrstuvwxyz";
        std::pair<int,int> g;
    public:
        Graph() = default;
        Graph(int n, int k)
        {
            if (!((n - 1 <= k) && (k <= n * (n - 1) * 0.5)))
                throw std::invalid_argument("Voraussetzung 'N - 1 <= K <= N * (N - 1) * 0.5' verletzt!");
            if (n > 26)
                throw std::invalid_argument("26 Buchstaben des Alphabets verfuegbar!");
            assert(n > 0);
            g = {n, k};
            auto generateRandomWeight = []() -> double
            {
                static std::random_device rd;
                static std::mt19937 gen(rd());
                static std::uniform_real_distribution<double> dis(0.0001, 0.9999);
                return dis(gen);
            };

            auto min = [](int a, int b) { return a > b ? b : a; };
            auto generatedRandomIndex = [&]() -> int
            {
                static std::random_device rd;
                static std::mt19937 gen(rd());
                static std::uniform_int_distribution<> distribution(0, n-1);
                return distribution(gen);
            };
            for (int i = 0; i < min(n, k); i++)
            {
                static char generatedNode;
                while((generatedNode = alphabet[generatedRandomIndex()]) == alphabet[i]) {}
                if (!nachbarExists(graphMap[alphabet[i]], generatedNode)){
                    addNode(alphabet[i], generatedNode, generateRandomWeight());
                } else {
                    i--;
                }
            }
            for (int i = n; i < k; i++)
            {
                static char generatedNode;
                static char nachbar;
                while (true)
                {
                    generatedNode = alphabet[generatedRandomIndex()];
                    while((nachbar = alphabet[generatedRandomIndex()]) == generatedNode) {}
                    if (std::find_if(graphMap[generatedNode].begin(), graphMap[generatedNode].end(), [](const Kante& kante)
                    {
                        return kante.nachbar == nachbar;
                    }) == graphMap[generatedNode].end())
                    {
                        if (!nachbarExists(graphMap[generatedNode], nachbar))
                        {
                            addNode(generatedNode, nachbar, generateRandomWeight());
                            break;
                        }
                    }
                }
            }
        }
        const std::pair<int, int>& getstats() { return g ; }
        bool nachbarExists(std::vector<Kante>& kanten, char node)
        {
            for (auto& kante : kanten)
            {
                if (node == kante.nachbar)
                    return true;
            }
            return false;
        }
        bool isIncluded(char current, char previous, char parent)
        {
            for (auto& a : graphMap[current])
            {
//                std::cout << "Current: " << current << " previous: " << previous << " parent: " << parent << '\n';
                if (a.nachbar == previous)
                {
                    continue;
                }
                if (a.nachbar == parent)
                {
                    return true;
                } else {
                    return isIncluded(a.nachbar, current, parent);
                }
            }
            return false;
        }
        inline bool hatKreis()
        {
            for (auto& a : graphMap)
            {
                if (isIncluded(a.first, a.first, a.first))
                    return true;
            }
            return false;
        }
        void addNode(char node, char nachbar, double gewicht)
        {
            graphMap[node].emplace_back(Kante(nachbar, gewicht));
            graphMap[nachbar].emplace_back(Kante(node, gewicht));
        }
        void addNode(char node, const std::vector<std::pair<char, double>>& nachbarn)
        {
            for (auto& nachbar : nachbarn)
                addNode(node, nachbar.first, nachbar.second);
        }
        void addNode(const std::tuple<char, char, double>& kante)
        {
            addNode(std::get<0>(kante), std::get<1>(kante), std::get<2>(kante));
        }
        void removeVertice(char node, char nachbar)
        {
            auto eraseVertice = [&](char node1, char node2)
            {
                auto a = std::find_if(graphMap[node1].begin(), graphMap[node1].end(), [&](const Kante& kante) { return kante.nachbar == node2; });
                if (a != graphMap[node1].end())
                    graphMap[node1].erase(a);
            };
            eraseVertice(node, nachbar);
            eraseVertice(nachbar, node);
        }
        graphType::iterator begin() { return graphMap.begin(); }
        graphType::iterator end() { return graphMap.end(); }
        ~Graph() = default;
    };

    inline auto maximalerSpannbaum(Graph& graph) -> Graph
    {
        Graph ergebnis{};
        std::tuple<char, char, double> maxKante{};
        std::vector<std::pair<char, char>> eckePair;
        std::vector<std::tuple<char, char, double>> sortierteKante;
        std::vector<std::tuple<char, char, double>> result;
        auto sortKante = [&graph, &sortierteKante, &result]()
        {
            for (auto& a: graph)
            {
                std::for_each(a.second.begin(), a.second.end(), [&](GraphenTheorie::Graph::Kante& kante){
                    sortierteKante.emplace_back(std::make_tuple(a.first, kante.getData().first, kante.getData().second));
                });
            }
            std::sort(sortierteKante.begin(), sortierteKante.end(), [](const std::tuple<char, char, double>& a, const std::tuple<char, char, double>& b) { return std::get<2>(a) > std::get<2>(b); });
            for (auto& q : sortierteKante)
            {
                auto r = std::find_if(result.begin(), result.end(), [&](const std::tuple<char, char, double>& kante) { return std::get<0>(kante) == std::get<1>(q) && std::get<1>(kante) == std::get<0>(q);});
                if (r == result.end())
                    result.emplace_back(q);
            }

        };
        sortKante();

        static std::size_t counter = 0;

        for (const auto& kante : result)
        {
            ergebnis.addNode(kante);
            if (ergebnis.hatKreis())
                ergebnis.removeVertice(std::get<0>(kante), std::get<1>(kante));
        }



//        while (true)
//        {
//            ergebnis.addNode(result[counter]);
//            if (ergebnis.hatKreis()) {
//                ergebnis.removeVertice(std::get<0>(result[counter]), std::get<1>(result[counter]));
//            }
//            counter++;
//            if (counter > result.size())
//                break;
//        }
        return ergebnis;
    }


//    inline auto maximalerSpannbaum(Graph& graph) -> Graph
//    {
//        Graph ergebnis{};
//        std::tuple<char, char, double> maxKante{};
//        std::vector<std::pair<char, char>> maxContainer;
//        double max{};
//        auto exists = [&](char ecke, char nachbar) -> bool
//        {
//            return std::find_if(maxContainer.begin(), maxContainer.end(), [&](const std::pair<char, char>& pair) {
//                return (pair.first == ecke && pair.second == nachbar) || (pair.first == nachbar && pair.second == ecke);
//            }) != maxContainer.end();
//        };
//        auto findNextExpensive = [&]()
//        {
//            double tempMax;
//            for (auto& a : graph)
//            {
//                std::for_each(a.second.begin(), a.second.end(), [&](Graph::Kante& kante) {
//                    if((tempMax  = kante.getData().second) >= max && !exists(a.first, kante.getData().first))
//                    {
//                        maxKante = {a.first, kante.getData().first, tempMax};
//                        maxContainer.emplace_back(std::make_pair(a.first, kante.getData().first));
//                        std::cout << "Max: " << a.first << " " << kante.getData().first <<" "<< tempMax << '\n';
//                    }
//                });
//            }
//        };
//
//        while(!ergebnis.hatKreis()){
//            findNextExpensive();
//            ergebnis.addNode(maxKante);
//            std::cout << std::get<0>(maxKante) << " " << std::get<1>(maxKante) << " " << std::get<2>(maxKante) << '\n';
//            if (maxContainer.size() >= graph.getstats().second)
//            {
//                break;
//            }
//        }
//        return ergebnis;
//    }
}

inline std::ostream& operator<<(std::ostream& o, GraphenTheorie::Graph& graph)
{
    std::vector<char> V;
    std::vector<std::string> G;
    const std::string w = "w_";
    auto exits = [&](char ecke, char nachbar) -> bool
    {
        return std::find_if(G.begin(), G.end(), [&](const std::string& kante)
        {
            return kante == w + ecke + nachbar || kante == w + nachbar + ecke;
        }) !=  G.end();
    };
    std::for_each(graph.begin(), graph.end(), [&](const std::pair<char, std::vector<GraphenTheorie::Graph::Kante>>& in)
    {
       V.emplace_back(in.first);
       for (auto& kante : in.second)
       {
           if (!exits(in.first, kante.getData().first))
           {
               G.emplace_back(w + in.first + kante.getData().first);
           }
       }
    });
    o << "V = {";
    std::for_each(V.begin(), V.end(), [&](char v) { o << v << ", ";});
    o << (V.size() > 2 ? "\b\b}\n" : "}\n");
    o << "G = {";
    std::for_each(G.begin(), G.end(), [&](const std::string& k) { o << k << ", ";});
    o << (V.size() > 2 ? "\b\b}\n" : "}\n");


    for (auto& node : graph)
    {
        o << "Node: " << node.first << " Nachbar: ";
        for (const auto& kante : node.second)
            o << '{' << kante.getData().first << ", " << kante.getData().second << "} ";
        o << '\n';
    }
    return o;
}

#endif //NUMERISCHE_ALGORITHMEN_GRAP_H
