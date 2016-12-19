#pragma once

#include <vector>

#include <SFML/Graphics.hpp>

class Field {
private:
    const int width, height;

    std::vector< std::vector<int> > field;
    std::vector< std::vector<int> > backField;

    std::vector<sf::Color> colors;

    sf::RectangleShape box;

public:
    Field(const int width, const int height);

    void Draw(sf::RenderWindow *window);
    void Update();

    void SetCell(int x, int y, int content) { field[y][x] = content; }
};

