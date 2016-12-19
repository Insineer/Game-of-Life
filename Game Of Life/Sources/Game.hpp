#pragma once

#include <SFML/Graphics.hpp>

#include "GameElements/Field.hpp"
#include "Useful.hpp"

class Game {
private:
    static Game *inst;

    const int kFieldWidth = 100;
    const int kFieldHeight = 100;
    const int kCellSize = 8;

    bool active;
    sf::Time fieldTimeout;

    uptr<sf::RenderWindow> window;
    uptr<Field> field;

    std::vector<std::vector<int>> rules;

    void update(sf::Time);
    void draw();

public:
    Game();

    static Game *Get() { return inst; }
    const int GetCellSize() const;
    const std::vector< std::vector<int>> &GetRules() const { return rules; }
};