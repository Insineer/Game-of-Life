#include "Field.hpp"

#include <SFML/Graphics.hpp>

#include "Game.hpp"

Field::Field(const int width, const int height) : 
    width(width),
    height(height),
    field(height, std::vector<int>(width)),
    box(sf::Vector2f(Game::Get()->GetCellSize(), Game::Get()->GetCellSize()))
{
    box.setOutlineColor(sf::Color::Black);
    box.setOutlineThickness(1);
}

void Field::Draw(sf::RenderWindow *window) {
    for (int x = 0; x < width; x++)
        for (int y = 0; y < height; y++) {
            box.setPosition(sf::Vector2f(Game::Get()->GetCellSize() * x, Game::Get()->GetCellSize() * y));
            window->draw(box);
        }
}

void Field::Update() {

}