#include "Field.hpp"

#include <SFML/Graphics.hpp>

#include "Game.hpp"

Field::Field(const int width, const int height) : 
    width(width),
    height(height),
    field(height, std::vector<int>(width)),
    box(sf::Vector2f(float(Game::Get()->GetCellSize()), float(Game::Get()->GetCellSize())))
{
    box.setOutlineColor(sf::Color::Black);
    box.setOutlineThickness(1);

    colors.push_back(sf::Color::Green);
    colors.push_back(sf::Color::Red);
}

void Field::Draw(sf::RenderWindow *window) {
    for (int x = 0; x < width; x++)
        for (int y = 0; y < height; y++) {
            if (field[y][x]) box.setFillColor(colors[field[y][x] - 1]);
            else box.setFillColor(sf::Color::White);
            box.setPosition(sf::Vector2f(float(Game::Get()->GetCellSize() * x), float(Game::Get()->GetCellSize() * y)));
            window->draw(box);
        }
}

void Field::Update() {
    auto rules = Game::Get()->GetRules();
    for (int x = 0; x < width; x++)
        for (int y = 0; y < height; y++) {
            int neightbours = 0;
            for (int dx = -1; dx <= 1; dx++)
                for (int dy = -1; dy <= 1; dy++)
                    if (dx != 0 || dy != 0)
                        neightbours++;
            field[y][x] = rules[field[y][x]][neightbours];
        }
}