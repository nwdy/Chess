#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <SFML/Graphics.hpp>

class ResourceManager
{
    sf::Texture backgroundTexture;
    sf::Texture chessTexture;
    sf::Font font;
    // sf::Texture buttonTexture;

public:
    ResourceManager();

    // Getters
    sf::Texture& getBackgroundTexture();
    sf::Texture& getChessTexture();
    sf::Font& getFont();
    // sf::Texture& getButtonTexture();
};

#endif