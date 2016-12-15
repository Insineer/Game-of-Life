#pragma once

#include <vector>

#include <SFML/Graphics.hpp>

class Field {
private:
    const int width, height;

    std::vector< std::vector<int> > field;

    sf::RectangleShape box;

public:
    Field(const int width, const int height);

    void Draw(sf::RenderWindow *window);
    void Update();
};

