#ifndef RENDER_ENGINE_H
#define RENDER_ENGINE_H

#include <SFML/Graphics.hpp>

#include "game_state.h"
#include "resource_manager.h"

class GameWindow: public sf::RenderWindow {
    ResourceManager& manager;
    GameState& state;

    sf::Sprite backgroundSprite;

    int hoverI = -1;
    int hoverJ = -1;

public:
    static const int WINDOW_WIDTH = 512; // = 8 * 56 + 2 * 28
    static const int WINDOW_HEIGHT = 512;

    static const int CELL_WIDTH = 64;
    static const int BORDER_WIDTH = 0;
    static constexpr int LIMIT_BORDER_WIDTH = BORDER_WIDTH + 8 * CELL_WIDTH;

    GameWindow(ResourceManager& manager_, GameState& state_) 
        : sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Chess"),
          manager(manager_), state(state_),
          backgroundSprite(manager.getBackgroundTexture()) {}

    void render();

    // set the hover cell
    void setHoveredCell(int i, int j);

    // set hovered buttons
    // void setHoveredButtons(sf::Vector2i localPosition);

private:
    sf::RectangleShape createPiece(sf::Texture& texture, int i, int j, int type);
    sf::RectangleShape createFillColorCell(int i, int j);
    sf::CircleShape createFillColorCircle(int i, int j);
    // Render functions for each screen
    // void renderPlayModeScreen();
    void renderPlayingScreen();
};

#endif