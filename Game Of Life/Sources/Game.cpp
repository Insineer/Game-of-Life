#include "Game.hpp"

#include <SFML/Graphics.hpp>

void Game::update() {
    field->Update();
}

void Game::draw() {
    sf::Event event;
    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window->close();
            active = false;
        }
    }

    window->clear(sf::Color::Blue);
    field->Draw(window.get());
    window->display();
}

Game::Game() {
    inst = this;
    window.reset(new sf::RenderWindow(sf::VideoMode(kFieldWidth * kCellSize, kFieldHeight * kCellSize), "Game of Life"));
    field.reset(new Field(kFieldWidth, kFieldHeight));

    active = true;

    while (active) {
        update();
        draw();
    }
}

const int Game::GetCellSize() const { return kCellSize; }

Game *Game::inst;