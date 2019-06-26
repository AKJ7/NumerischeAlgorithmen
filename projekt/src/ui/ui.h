//
// Created by hp on 6/15/19.
//

#ifndef NUMERISCHE_ALGORITHMEN_UI_H
#define NUMERISCHE_ALGORITHMEN_UI_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iterator>
#include <algorithm>
#include <tuple>
#include <utility>
#include <cmath>

#include "../graph/grap.h"


constexpr const double M_RAD = 180 / M_PI;
double operator ""_deg(const char* v)
{
    return std::stod(v) * M_RAD;
}


namespace UI
{
    constexpr const int window_width = 800;
    constexpr const int window_height = 800;
    constexpr const char* graphWindowName = "Originaler Graph";
    constexpr const char* maxGraphWindowName = "Maximaler Aufspannender Baum";
    constexpr const int fontSize = 40;
    constexpr float R = static_cast<float>(window_width) * 0.5 - 50.0f;

    template <typename T>
    T rad2Deg(T v) noexcept
    {
        return v * M_RAD;
    }

    template <typename T>
    T deg2Rad(T v) noexcept
    {
        return v / M_RAD;
    }

    class GraphEngine final
    {
        GraphenTheorie::Graph<double>* graph;
        std::vector<std::pair<sf::CircleShape, sf::Text>> nodeContainer;
        std::pair<int, int> offset{ window_width * 0.5, window_height * 0.5};
        std::vector<sf::RectangleShape> lines;
        std::pair<int, int> stats;
        std::vector<sf::Text> weights;
        sf::Font font;

    protected:
        void generateNodes()
        {
            int counter{};
            for (const auto& a: *graph)
            {
                std::string s(1, a.first);
                nodeContainer.emplace_back(sf::CircleShape(40.f), sf::Text(s, font, fontSize));
                nodeContainer.at(counter).first.setOutlineColor(sf::Color::Black);
                nodeContainer.at(counter).first.setOutlineThickness(2);
                nodeContainer.at(counter).first.setFillColor(sf::Color::Blue);
                nodeContainer.at(counter).first.setOrigin(nodeContainer.at(counter).first.getRadius(), nodeContainer.at(counter).first.getRadius());
                nodeContainer.at(counter).first.setPosition(R * cos(2*  M_PI * float(counter) / stats.first) + offset.first , R * sin(2 * M_PI * float(counter) / stats.first) + offset.second);
                nodeContainer.at(counter).second.setPosition(R * cos(2*  M_PI * float(counter) / stats.first) + offset.first - 13, R * sin(2 * M_PI * float(counter) / stats.first) + offset.second - 25);
                nodeContainer.at(counter).second.setFillColor(sf::Color::Black);
                nodeContainer.at(counter).second.setStyle(sf::Text::Bold);
                counter++;
            }
        }
        void generateVertices()
        {
            char nodeChar{};
            size_t counter{};
            std::vector<std::pair<char, char>> nodePairs;
            auto euklidistance = [](const sf::Vector2f& v1, const sf::Vector2f& v2) -> double
            {
                return sqrt(pow(v2.x - v1.x, 2) + pow(v2.y - v1.y, 2));
            };
            auto angle = [](const sf::Vector2f& v1, const sf::Vector2f& v2) -> double
            {
                static double value;
                value = rad2Deg(atanf( (v1.y - v2.y) / (v2.x - v1.x)));
                if (v1.x > v2.x && v1.y < v2.y)
                    return 180 - value;
                if (v2.x > v1.x &&  v2.y > v1.y)
                    return -value;
                if (v2.x > v1.x && v2.y < v1.y)
                    return -value;
                if (v2.x < v1.x && v2.y < v1.y)
                    return -180 - value;
                return value;
            };
            for (const auto& a : nodeContainer)
            {
                nodeChar = *a.second.getString().getData();
                for (auto b : graph->operator[](nodeChar))
                {
                    if (std::find_if(nodePairs.begin(), nodePairs.end(), [&](const std::pair<char, char>& val) { return (val.first == nodeChar && val.second == b.get().first) || (val.first == b.get().first && val.second == nodeChar);}) != nodePairs.end())
                        continue;
                    nodePairs.emplace_back(nodeChar, b.get().first);
                    auto c = std::find_if(nodeContainer.begin(), nodeContainer.end(), [&](const std::pair<sf::CircleShape, sf::Text>& node) { return *node.second.getString().getData() == b.get().first;});
                    lines.emplace_back(sf::RectangleShape(sf::Vector2f(euklidistance(a.first.getPosition(), c->second.getPosition()), 14)));
                    lines[counter].rotate(angle(a.first.getPosition(), c->second.getPosition()));
                    lines[counter].setOutlineColor(sf::Color::Blue);
                    lines[counter].setFillColor(sf::Color::Blue);
                    lines[counter].setPosition(a.first.getPosition().x, a.first.getPosition().y);
                    weights.emplace_back(sf::Text(std::to_string(b.get().second), font, 30));
                    weights[counter].setPosition(0.5 * (a.first.getPosition().x + c->first.getPosition().x) + 10, 0.5 * (a.first.getPosition().y + c->first.getPosition().y));
                    weights[counter].setFillColor(sf::Color::Black);
                    weights[counter].setStyle(sf::Text::Bold);
                    counter++;
                }
            }
        }

    public:
        explicit GraphEngine(GraphenTheorie::Graph<double>* graph1) : graph{graph1}
        {
            if (!graph)
                throw std::invalid_argument("Invalid Graph Ptr");
            if (!font.loadFromFile("../../projekt/src/ui/arial.ttf"))
                throw std::runtime_error("Could not load Font's file");
            auto a = graph->normalise();
            stats = {a.first.size(), a.second.size()};
            generateNodes();
            generateVertices();
        }
        std::vector<std::pair<sf::CircleShape, sf::Text>>& fetchNodes() noexcept
        {
            return nodeContainer;
        }
        std::vector<sf::RectangleShape>& fetchVertices() noexcept
        {
            return lines;
        }
        std::vector<sf::Text>& fetchWeights() noexcept
        {
            return weights;
        }
        ~GraphEngine() = default;
    };
}


#endif //NUMERISCHE_ALGORITHMEN_UI_H
