#include "Game.hpp"

#include <SFML/Graphics.hpp>

void Game::update(sf::Time timeElapsed) {
    fieldTimeout += timeElapsed;
    if (fieldTimeout.asSeconds() >= 1) {
        field->Update();
        fieldTimeout = sf::Time::Zero;
    }
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

    // Rules              neighbours:  0   1   2   3   4   5   6   7   8
    rules.push_back({ 1,  1,  1,  1,  1,  1,  1,  1,  1 });
    rules.push_back({ 0,  0,  0,  0,  0,  0,  0,  0,  0 });

    active = true;

    sf::Clock clock;

    while (active) {
        update(clock.restart());
        draw();
    }
}

const int Game::GetCellSize() const { return kCellSize; }

Game *Game::inst;