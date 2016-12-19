#include "Field.hpp"

#include <SFML/Graphics.hpp>

#include "Game.hpp"

Field::Field(const int width, const int height) : 
    width(width),
    height(height),
    field(height, std::vector<int>(width)),
    backField(height, std::vector<int>(width)),
    box(sf::Vector2f(float(Game::Get()->GetCellSize()), float(Game::Get()->GetCellSize())))
{
    box.setOutlineColor(sf::Color(200, 200, 200));
    box.setOutlineThickness(1);

    colors.push_back(sf::Color(170, 170, 170)); // Dark Gray
    colors.push_back(sf::Color(100, 100, 100)); // Light Gray
    colors.push_back(sf::Color(143, 188, 143)); // Light Green
    colors.push_back(sf::Color(210, 105, 30));  // Orange
    
    colors.push_back(sf::Color(148, 0, 211));
    colors.push_back(sf::Color(54, 54, 54));
    colors.push_back(sf::Color(0, 139, 0));
    colors.push_back(sf::Color(139, 0, 0));
    colors.push_back(sf::Color(148, 0, 211));
    colors.push_back(sf::Color(165, 42, 42));
    colors.push_back(sf::Color(70, 130, 180));
    colors.push_back(sf::Color(210, 105, 30));
    colors.push_back(sf::Color(54, 54, 54));
    colors.push_back(sf::Color(0, 0, 139));
    colors.push_back(sf::Color(0, 139, 0));
    colors.push_back(sf::Color(139, 0, 0));
    colors.push_back(sf::Color(148, 0, 211));
    colors.push_back(sf::Color(165, 42, 42));
    colors.push_back(sf::Color(70, 130, 180));
}

void Field::Draw(sf::RenderWindow *window) {
    for (int x = 0; x < width; x++)
        for (int y = 0; y < height; y++) {
            if (field[y][x]) box.setFillColor(colors[field[y][x] - 1]);
            else box.setFillColor(sf::Color(245, 245, 245));
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
                    if (dx != 0 || dy != 0) {
                        int neightbourX = x + dx;
                        int neightbourY = y + dy;
                        if (neightbourX < 0) neightbourX = width + neightbourX;
                        if (neightbourY < 0) neightbourY = width + neightbourY;
                        if (neightbourX >= width)  neightbourX = neightbourX - width;
                        if (neightbourY >= height) neightbourY = neightbourY - height;

                        if (field[neightbourY][neightbourX] && field[neightbourY][neightbourX] != 3) neightbours++;
                    }
            backField[y][x] = rules[field[y][x]][neightbours];
        }
    std::swap(field, backField);
}