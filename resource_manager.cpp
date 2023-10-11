#include <iostream>
#include "resource_manager.h"

ResourceManager::ResourceManager() 
{
    // Load background
    if (!backgroundTexture.loadFromFile("resource/board64.png"))
    {
        std::cerr << "Error loading board.png" << std::endl;
        exit(1);
    }

    if (!chessTexture.loadFromFile("resource/figures64.png"))
    {
        std::cerr << "Error loading resource/figures.png" << std::endl;
        exit(1);
    }

    // Load font
    if (!font.loadFromFile("resource/arial.ttf"))
    {
        std::cerr << "Error loading resource/arial.ttf" << std::endl;
        exit(1);
    }
}

// Getters
sf::Texture& ResourceManager::getBackgroundTexture() {
    return backgroundTexture;
};

sf::Texture& ResourceManager::getChessTexture() {
    return chessTexture;
}

sf::Font& ResourceManager::getFont() {
    return font;
};