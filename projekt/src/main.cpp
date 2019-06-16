//
// Created by hp on 6/9/19.
//

#include <iostream>
#include <SFML/Graphics.hpp>

#include "grap.h"
#include "ui/ui.h"


//int main()
//{
//    GraphenTheorie::Graph graph(4, 4);
//
//    GraphenTheorie::Graph maxGraph = GraphenTheorie::maximalerSpannbaum(graph);
//    std::cout << maxGraph << '\n';
//
//    std::vector<std::pair<sf::RenderWindow*, UI::GraphTheorieEngine>> windows;
//    windows.emplace_back(new sf::RenderWindow(sf::VideoMode(UI::window_height, UI::window_width), UI::windowName), UI::GraphTheorieEngine(&graph));
//    windows.emplace_back(new sf::RenderWindow(sf::VideoMode(UI::window_height, UI::window_width), "Maximaler Spannbaum"), UI::GraphTheorieEngine(&maxGraph));
//
//    for (auto& window : windows)
//        window.first->setFramerateLimit(60);
//
//    while (windows[0].first->isOpen() && windows[1].first->isOpen())
//    {
//        sf::Event event;
//        while (windows[0].first->pollEvent(event) || windows[1].first->pollEvent(event))
//        {
//            if (event.type == sf::Event::Closed)
//            {
//                std::for_each(windows.begin(), windows.end(), [](std::pair<sf::RenderWindow*, UI::GraphTheorieEngine>& window) { window.first->close(); });
//            }
//        }
//        std::for_each(windows.begin(), windows.end(), [](std::pair<sf::RenderWindow*, UI::GraphTheorieEngine>& window) { window.first->clear(sf::Color::White); });
//
//        for (std::pair<sf::RenderWindow*, UI::GraphTheorieEngine>& b: windows)
//        {
//            for (const auto& c : b.second.fetchVertices())
//                b.first->draw(c);
////            for (const auto& c : b.second.fetchNodes())
////            {
////                b.first->draw(c.first);
////                b.first->draw(c.second);
////            }
//            for (const auto& e : b.second.fetchWeights())
//            {
//                b.first->draw(e);
////                std::cout << e.getPosition().x << '\n';
//            }
//            b.first->display();
//        }
//    }
//
//    for (auto& a : windows)
//    {
//        delete(a.first);
//    }
//    return EXIT_SUCCESS;
//}


int main()
{
    GraphenTheorie::Graph graph(5, 7);

    GraphenTheorie::Graph maxGraph = GraphenTheorie::maximalerSpannbaum(graph);
    std::cout << maxGraph << '\n';

    UI::GraphTheorieEngine graphTheorieEngine(&graph);
    UI::GraphTheorieEngine maxGraphEngine(&maxGraph);

    sf::RenderWindow window(sf::VideoMode(UI::window_width, UI::window_height), UI::windowName);
    sf::RenderWindow loesung(sf::VideoMode(UI::window_width, UI::window_height), "Loesung");

    window.setFramerateLimit(60);
    loesung.setFramerateLimit(60);
    while (window.isOpen() && loesung.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event) || loesung.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
                loesung.close();
            }
        }
        window.clear(sf::Color::White);
        loesung.clear(sf::Color::White);
        for (const auto& b: graphTheorieEngine.fetchVertices())
        {
            window.draw(b);
        }
        for (const auto& b: maxGraphEngine.fetchVertices())
        {
            loesung.draw(b);
        }
        for (const auto& a : graphTheorieEngine.fetchNodes())
        {
            window.draw(a.first);
            window.draw(a.second);
        }
        for (const auto& a : maxGraphEngine.fetchNodes())
        {
            loesung.draw(a.first);
            loesung.draw(a.second);
        }

        for (auto const& a : graphTheorieEngine.fetchWeights())
        {
            window.draw(a);
        }
        for (auto const& a: maxGraphEngine.fetchWeights())
            loesung.draw(a);

        window.display();
        loesung.display();
    }
    return EXIT_SUCCESS;
}


//int main()
//{
//
////    GraphenTheorie::Graph graph;
////    graph.addNode('a', 'b', 10);
////    std::cout << graph << '\n';
//
//    GraphenTheorie::Graph graph(4, 3);
//    std::cout << graph << std::endl;
//
//    auto graph1 = GraphenTheorie::maximalerSpannbaum(graph);
//    std::cout << graph1 << std::endl;
//
//    return EXIT_SUCCESS;
//}