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


#include "../grap.h"


namespace UI
{
    const int window_width = 800;
    const int window_height = 800;
    const char *windowName = "GraphenTheorie Projekt";
    const int fontSize = 40;

    double operator ""_deg(const char* v)
    {
        return std::stod(v) * 57.2958;
    }

    float rad2Deg(float v)
    {
        return v * 57.2958;
    }

    class GraphTheorieEngine
    {
    private:
        GraphenTheorie::Graph* graph;
        std::vector<std::pair<sf::CircleShape, sf::Text>> nodeContainer;
        std::pair<int, int> offset{window_width/2, window_height/2};
        std::vector<sf::RectangleShape> lines;
        std::vector<sf::Text> weights;
        float R = static_cast<float>(window_width) / 2 - 50.f;
        std::pair<int, int> stats = graph->getstats();
        std::vector<std::pair<char, char>> nodePairs;
        sf::Font font;
    protected:
        void generateNodes()
        {
            for (const auto& a : *graph)
            {
                std::string s(1, a.first);
                nodeContainer.emplace_back(sf::CircleShape(40.f), sf::Text(s, font, fontSize));
            }
            setup();
        }
        void generateVertices()
        {
            char nodeChar{};
            size_t counter{};
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
                    if (std::find_if(nodePairs.begin(), nodePairs.end(), [&](const std::pair<char, char>& val) { return (val.first == nodeChar && val.second == b.getData().first) || (val.first == b.getData().first && val.second == nodeChar);}) != nodePairs.end())
                    {
                        continue;
                    }
                    nodePairs.emplace_back(nodeChar, b.getData().first);
                    auto c = std::find_if(nodeContainer.begin(), nodeContainer.end(), [&](const std::pair<sf::CircleShape, sf::Text>& node) { return *node.second.getString().getData() == b.getData().first;});
                    lines.emplace_back(sf::RectangleShape(sf::Vector2f(euklidistance(a.first.getPosition(), c->second.getPosition()), 14)));
                    lines[counter].rotate(angle(a.first.getPosition(), c->second.getPosition()));
                    lines[counter].setOutlineColor(sf::Color::Blue);
                    lines[counter].setFillColor(sf::Color::Blue);
                    lines[counter].setPosition(a.first.getPosition().x, a.first.getPosition().y);
                    weights.emplace_back(sf::Text(std::to_string(b.getData().second), font, 30));
                    weights[counter].setPosition(0.5 * (a.first.getPosition().x + c->first.getPosition().x) + 10, 0.5 * (a.first.getPosition().y + c->first.getPosition().y));
                    weights[counter].setFillColor(sf::Color::Black);
                    weights[counter].setStyle(sf::Text::Bold);
                    counter++;
                }
            }
        }
        inline void setup()
        {
            int counter{};
            for (auto& a : nodeContainer)
            {
                a.first.setOutlineColor(sf::Color::Black);
                a.first.setOutlineThickness(2);
                a.first.setFillColor(sf::Color::Blue);
                a.first.setOrigin(a.first.getRadius(), a.first.getRadius());
                a.first.setPosition(R * cos(2*  M_PI * float(counter) / stats.first) + offset.first , R * sin(2 * M_PI * float(counter) / stats.first) + offset.second);
                a.second.setPosition(R * cos(2*  M_PI * float(counter) / stats.first) + offset.first - 13, R * sin(2 * M_PI * float(counter) / stats.first) + offset.second - 25);
                a.second.setFillColor(sf::Color::Black);
                a.second.setStyle(sf::Text::Bold);
                counter++;
            }
        }
    public:
        explicit GraphTheorieEngine(GraphenTheorie::Graph* graph1) : graph{graph1}
        {
            if (!font.loadFromFile("../../projekt/src/ui/arial.ttf"))
            {
                throw std::runtime_error("Could not load Font's file");
            }
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
        std::tuple<float> getStats()
        {
            return {R};
        }
        ~GraphTheorieEngine() = default;
    };
}


#endif //NUMERISCHE_ALGORITHMEN_UI_H
