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

    // Rules
    //   neighbours:   0   1   2   3   4   5   6   7   8

    rules.push_back({  0,  0,  1,  0,  0,  0,  0,  0,  0 }); // Dead sea
    rules.push_back({  2,  2,  2,  2,  2,  2,  2,  2,  2 }); // brain in sea
    rules.push_back({  0,  0,  0,  0,  0,  0,  0,  0,  0 }); // refractory brain in sea
    rules.push_back({  3,  3,  3,  4,  3,  3,  3,  3,  3 }); // dead land
    rules.push_back({  3,  3,  4,  4,  3,  3,  3,  3,  3 }); // firing life on land

    //rules.push_back({  0,  0,  1,  0,  0,  0,  3,  3,  0 }); // Dead sea
    //rules.push_back({  2,  2,  2,  2,  2,  2,  2,  2,  2 }); // brain in sea
    //rules.push_back({  0,  0,  0,  0,  0,  0,  0,  0,  0 }); // refractory brain in sea
    //rules.push_back({  3,  0,  3,  3,  3,  4,  3,  3,  3 }); // dead land
    //rules.push_back({  3,  3,  3,  3,  3,  4,  4,  3,  3 }); // firing life on land

    srand(100);
    for (int x = 0; x < 100; x++)
        for (int y = 50; y < 100; y++)
            field->SetCell(x, y, 0);
    for (int x = 0; x < 100; x++)
        for (int y = 0; y < 50; y++)
            //field->SetCell(x, y, rand() % 2 + 3);
            field->SetCell(x, y, 3);

    for (int x = 75; x < 85; x++)
        for (int y = 75; y < 85; y++)
            field->SetCell(x, y, rand() % 2);

    for (int x = 10; x < 90; x++)
        for (int y = 10; y < 40; y++)
            field->SetCell(x, y, rand() % 2 + 3);

    //field->SetCell(25, 25, 1);
    //field->SetCell(75, 75, 4);

    active = true;

    sf::Clock clock;

    while (active) {
        update(clock.restart());
        draw();
    }
}

const int Game::GetCellSize() const { return kCellSize; }

Game *Game::inst;