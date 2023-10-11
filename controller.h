#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <SFML/Graphics.hpp>
#include <queue>
#include "game_state.h"
#include "render_engine.h"


class Controller {
    GameState& state;
    GameWindow& window;
    sf::Mutex mutex;

    std::queue<sf::Event> queue;
    sf::Thread thread;

public:
    Controller(GameState& state_, GameWindow& engine_) 
        : state(state_), window(engine_),
          thread(&Controller::run, this) {}

    void processEvent(sf::Event& event);
    void launch();
    void wait();

private:
    void onMouseMoved(sf::Event& event);
    void onMouseButtonReleased(sf::Event& event);

    // void checkButtonClicked(sf::Vector2i localPosition);
    // void checkButtonHovered(sf::Vector2i localPosition);
    
    void addEvent(sf::Event event);
    sf::Event getEvent();
    void run();
};

#endif