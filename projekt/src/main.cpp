//
// Created by hp on 6/9/19.
//

#include <iostream>
#include <SFML/Graphics.hpp>

#include "graph/grap.h"
#include "ui/ui.h"


int main()
{
    using namespace GraphenTheorie;
    using namespace UI;

    Graph<> graph;
    graph.randomize(5, 7);
    std::cout << graph <<'\n';
    auto maxGraph = maximalerSpannbaum(graph);
    std::cout << '\n' << maxGraph << '\n';
    GraphEngine graphEngine(&graph);
    GraphEngine maxGraphEngine(&maxGraph);
    sf::RenderWindow window(sf::VideoMode(window_width, window_height), graphWindowName);
    sf::RenderWindow loesung(sf::VideoMode(window_width, window_height), maxGraphWindowName);
    window.setFramerateLimit(30);
    loesung.setFramerateLimit(30);

    while (window.isOpen() && loesung.isOpen())
    {
        sf::Event event{};
        while (window.pollEvent(event) || loesung.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
                loesung.close();
            }
        }
        window.clear(sf::Color::White);
        loesung.clear(sf::Color::White);
        for (const auto& b : graphEngine.fetchVertices())
            window.draw(b);
        for (const auto& b : maxGraphEngine.fetchVertices())
            loesung.draw(b);
        for (const auto& b: graphEngine.fetchNodes())
        {
            window.draw(b.first);
            window.draw(b.second);
        }
        for (const auto& b: maxGraphEngine.fetchNodes())
        {
            loesung.draw(b.first);
            loesung.draw(b.second);
        }
        for (const auto& a : graphEngine.fetchWeights())
            window.draw(a);
        for (const auto& b: maxGraphEngine.fetchWeights())
            loesung.draw(b);
        window.display();
        loesung.display();
    }
    return EXIT_SUCCESS;
}