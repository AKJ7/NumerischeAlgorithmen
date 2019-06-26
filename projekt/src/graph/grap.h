//
// Created by hp on 6/9/19.
//

#ifndef NUMERISCHE_ALGORITHMEN_GRAP_H
#define NUMERISCHE_ALGORITHMEN_GRAP_H

#include <unordered_map>        // std::unordered_map
#include <string>               // std::string
#include <vector>               // std::vector
#include <iterator>
#include <tuple>                // std::tuple
#include <cassert>              // assert
#include <random>               // std::random_device, std::mt19937, std::uniform_real_distribution, std::uniform_int_distribution
#include <algorithm>            // std::find, std::find_if, std::for_each, std::sort
#include <utility>              // std::pair
#include <type_traits>          // std::is_pod
#include <iostream>             // std::cout


namespace GraphenTheorie
{
    template <typename T = double>
    class Graph
    {
    public:
        template <typename K = double>
        class Kante
        {
        private:
            friend Graph;
            char nachbar;
            K gewicht;
        public:
            Kante(char nachbar, T gewicht) : nachbar{nachbar}, gewicht{gewicht} {}
            std::pair<char, T> get() const noexcept { return {nachbar, gewicht}; };
            ~Kante() = default;
        };

    private:
        typedef std::unordered_map<char, std::vector<Kante<T>>> graphType;
        graphType graphMap;
        static constexpr const char* alphabet = "abcdefghijklmnopqrstuvwxyz";
    public:
        Graph()
        {
            static_assert(std::is_pod<T>::value, "Graph only supports POD Type data");
        };
        void randomize(unsigned n, unsigned k)
        {
            if (!((n - 1 <= k) && (k <= n * (n - 1) * 0.5)))
                throw std::invalid_argument("Voraussetzung 'N - 1 <= K <= N * (N - 1) * 0.5' verletzt!");
            auto generateRandomWeight = []() -> double
            {
                static std::random_device rd;
                static std::mt19937 gen(rd());
                static std::uniform_real_distribution<double> dis(0.0001, 0.9999);
                return dis(gen);
            };
            auto generatedRandomIndex = [&]() -> int
            {
                static std::random_device rd;
                static std::mt19937 gen(rd());
                static std::uniform_int_distribution<> distribution(0, n-1);
                return distribution(gen);
            };
            auto exists = [&](char in, char a)
            {
               return std::find_if(graphMap[in].begin(), graphMap[in].end(), [&](const Kante<T>& k) { return k.get().first == a; }) != graphMap[in].end();
            };
            for (int i = 0; i < n; i++)
                addNode(alphabet[i]);
            for (int i = 0; i < k; i++)
            {
                static char node;
                char current = alphabet[generatedRandomIndex()];
                while ((node = alphabet[generatedRandomIndex()]) == current || exists(current, node)) { current = alphabet[generatedRandomIndex()]; }
                addNode(current, node, generateRandomWeight());
            }
            if (!isZusammenhaengend())
            {
                //TODO: Moegliche Implementierung: Verbindung der nicht zusammenhaengenden Ecken, falls der Graph nicht zusammenhaengend ist!
                std::cout << *this << '\n';
                throw std::logic_error("Graph nicht zusammenhaengend. Abbruch!");
            }
        }
        void addNode(char c)
        {
            graphMap.insert({c, {}});
        }
        void addNode(char node, char nachbar, T weight)
        {
            graphMap[node].emplace_back(nachbar, weight);
            graphMap[nachbar].emplace_back(node, weight);
        }
        void addNode(char node, std::vector<std::pair<char, T>> nachbars)
        {
            for (auto& a : nachbars)
                addNode(node, a.first, a.second);
        }
        void removeVertice(char node, char nachbar)
        {
            auto eraseVertice = [&](char node1, char node2)
            {
                auto a = std::find_if(graphMap[node1].begin(), graphMap[node1].end(), [&](const Kante<T>& kante) { return kante.nachbar == node2; });
                if (a != graphMap[node1].end())
                    graphMap[node1].erase(a);
            };
            eraseVertice(node, nachbar);
            eraseVertice(nachbar, node);
        }
        std::pair<std::vector<char>&, std::vector<std::string>&> normalise()
        {
            static std::vector<char> V;
            static std::vector<std::string> E;
            V.clear();
            E.clear();
            const std::string w = "v_";
            auto exists = [&](char a, char b) {
                return std::find_if(E.begin(), E.end(), [&](const std::string& ver) { return (ver[2] == a && ver[3] == b) || (ver[2] == b && ver[3] == a);}) != E.end();
            };
            for (auto& a : *this)
            {
                V.emplace_back(a.first);
                for (auto& b : a.second)
                    if (!exists(a.first,b.get().first))
                        E.emplace_back(w + a.first + b.get().first);
            }
            return {V, E};
        }
        /// @param b Ende
        /// @param a Start
        bool find(char a, char b, std::vector<std::pair<char, char>>& container)
        {
            if (std::find_if(graphMap[a].begin(), graphMap[a].end(), [&](Kante<double>& k) { return k.get().first == b; }) != graphMap[a].end())
            {
                container.emplace_back(a, b);
                return true;
            } else {
                for (auto& c : graphMap[a])
                {
                    if (std::find_if(container.begin(), container.end(), [&](std::pair<char, char>& s) { return (s.first == c.get().first && s.second == a) || (s.first == a && s.second == c.get().first);}) == container.end())
                    {
                        container.emplace_back(c.get().first, a);
                        if (c.get().first != b && find(c.get().first, b, container))
                        {
                            return true;
                        }
                    }
                }
            }
            return false;
        }
        void generatePermutation(std::vector<std::pair<char, char>>& per)
        {
            auto normalisiert = normalise();
            for (char a : normalisiert.first)
                for (char b : normalisiert.first)
                    if (a != b && std::find_if(per.begin(), per.end(), [&](const std::pair<char, char>& v) { return (v.first == a && v.second == b) || (v.first == b && v.second == a);}) == per.end())
                        per.emplace_back(a, b);
        }
        bool isZusammenhaengend()
        {
            std::vector<std::pair<char, char>> Nodes;
            auto normalisiert = normalise();
            std::vector<std::pair<char, char>> permutations;
            [&]()
            {
                for (char a : normalisiert.first)
                    for (char b : normalisiert.first)
                        if (a != b && std::find_if(permutations.begin(), permutations.end(), [&](const std::pair<char, char>& v) { return (v.first == a && v.second == b) || (v.first == b && v.second == a);}) == permutations.end())
                            permutations.emplace_back(a, b);
            }();
            auto exists = [&](char a, char b) -> bool
            {
                return std::find_if(Nodes.begin(), Nodes.end(), [&](const std::pair<char, char>& node) { return (node.first == a && node.second == b) || (node.first == b &&node.second == a);}) != Nodes.end();
            };
            std::vector<std::pair<char, char>> container;
            for (const auto& a : permutations)
            {
                container.clear();
                if (!find(a.first, a.second, container))
                    return false;
            }
            return true;
        }
        bool findKreis(char current, char end, std::vector<std::pair<char, char>>& container)
        {
            for (auto& v : graphMap[current])
            {
                if (std::find_if(container.begin(), container.end(), [&](std::pair<char, char>& p) { return (p.first == current && p.second == v.get().first) || (p.first == v.get().first && p.second == current);}) == container.end())
                {
                    container.emplace_back(v.get().first, current);
                    if (v.get().first == end)
                        return true;
                    if (findKreis(v.get().first, end, container ))
                        return true;
                }
            }
            return false;
        }
        bool hatKreis()
        {
            std::vector<std::pair<char, char>> container;
            for (const auto& a : *this)
            {
                container.clear();
                if (findKreis(a.first, a.first, container))
                    return true;
            }
            return false;
        }
        std::vector<Kante<T>>& operator[](char c) { return graphMap[c]; }
        inline typename std::unordered_map<char, std::vector<Kante<T>>>::iterator  begin() { return graphMap.begin(); }
        inline typename std::unordered_map<char, std::vector<Kante<T>>>::iterator end() { return graphMap.end(); }
    };
}

template <typename T>
std::ostream& operator<<(std::ostream& o, GraphenTheorie::Graph<T>& graph)
{
    o << "V = {";
    auto G = graph.normalise();
    std::for_each(G.first.begin(), G.first.end(), [&](char v){ o << v << ", ";});
    o << (G.first.size() < 1 ? "}" : "\b\b}") << '\n';
    o << "E = {";
    std::for_each(G.second.begin(), G.second.end(), [&](const std::string& v) { o << v << ", "; });
    o << (G.second.size() < 1 ? "}" : "\b\b}") << '\n';
    for (auto& a : graph)
    {
        o << a.first << ": ";
        for (auto& b: a.second)
            o << "(" << b.get().first << ", " << b.get().second << ") ";
        o << '\n';
    }
    return o;
}

template <typename T>
auto maximalerSpannbaum(GraphenTheorie::Graph<T>& graph) -> GraphenTheorie::Graph<T>
{
    using namespace GraphenTheorie;
    Graph<T> graph1;
    std::vector<std::tuple<char, char, T>> kanten;
    typedef GraphenTheorie::Graph<double>::Kante<double> kantenTyp;

    auto exists = [&](char a, char b) -> bool
    {
        return std::find_if(kanten.begin(), kanten.end(), [&](const std::tuple<char, char, T>& kante){
            return (std::get<0>(kante) == a && std::get<1>(kante) == b) || (std::get<0>(kante) == b && std::get<1>(kante) == a);
        }) != kanten.end();
    };

    for (auto& a : graph)   // Python hehe
        for (auto& b : a.second)
            if (!exists(a.first, b.get().first))
                kanten.emplace_back(a.first, b.get().first, b.get().second);

    std::sort(kanten.begin(), kanten.end(), [](const std::tuple<char, char, T>& a, const std::tuple<char, char, T>& b) { return std::get<2>(a) > std::get<2>(b);});
    size_t counter{};

    for (const auto& a : graph)
    {
        graph1.addNode(a.first);
    }

    for (auto& kante : kanten)
    {
        graph1.addNode(std::get<0>(kante), std::get<1>(kante), std::get<2>(kante));
        if (graph1.hatKreis())
        {
            graph1.removeVertice(std::get<0>(kante), std::get<1>(kante));
        }
        if (graph1.isZusammenhaengend())
        {
            break;
        }
    }
    return graph1;
}

#endif //NUMERISCHE_ALGORITHMEN_GRAP_H
