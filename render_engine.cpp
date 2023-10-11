#include "render_engine.h"

void GameWindow::render() {
    clear();
    renderPlayingScreen();
    // switch (state.getPlayScreen())
    // {
    // case GameState::PlayScreen::PlayModeScreen:
    //     renderPlayModeScreen();
    //     break;
    // case GameState::PlayScreen::PlayingScreen:
    //     renderPlayingScreen();
    //     break;
    // }

    display();
}

// void GameWindow::renderPlayModeScreen(); 

void GameWindow::renderPlayingScreen() 
{
    draw(backgroundSprite);

    if (!state.isEmptyMove()) 
    {
        std::string move = state.getFinalMove();
        draw(createFillColorCell(move[0] - '0', move[1] - '0'));
        draw(createFillColorCell(move[2] - '0', move[3] - '0'));

        if (state.getFirstClick()) 
        {
            draw(createFillColorCell(state.getX(), state.getY()));
            Matrix possMove = state.getPossibleMoves();
            if (!possMove.empty() && state.getCurrentPlayer()) {
                for (auto row : possMove) {
                    draw(createFillColorCircle(row[0], row[1]));
                }
            }
        }
    } 
    else if (state.getFirstClick()) 
    {
        draw(createFillColorCell(state.getX(), state.getY()));
        Matrix possMove = state.getPossibleMoves();
        if (!possMove.empty() && state.getCurrentPlayer()) {
            for (auto row : possMove) {
                draw(createFillColorCircle(row[0], row[1]));
            }
        }
    }

    if (hoverI != -1 && hoverJ != -1) {
        sf::RectangleShape shape(sf::Vector2f(CELL_WIDTH, CELL_WIDTH));
        shape.setFillColor(sf::Color::Transparent);
        shape.setOutlineColor(sf::Color::Black);
        shape.setOutlineThickness(-2.f);
        shape.setPosition(hoverI * CELL_WIDTH + BORDER_WIDTH, hoverJ * CELL_WIDTH + BORDER_WIDTH);
        
        draw(shape);
    }

    // Draw chess pieces
    sf::Texture& chessPieces = manager.getChessTexture();
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            int type = state.getChessPieceType(i, j);
            if (type != 0)
                draw(createPiece(chessPieces, i, j, type));
        }
    }

    // Draw the final message
}

void GameWindow::setHoveredCell(int i, int j) {
    hoverI = i;
    hoverJ = j;
}

// void GameWindow::setHoveredButtons(sf::Vector2i localPosition)
// {
//     isHoverOnButtonHvsH = GameWindow::getButtonHvsHRect().contains(localPosition);
//     isHoverOnButtonHvsM = GameWindow::getButtonHvsMRect().contains(localPosition);
//     isHoverOnButtonMvsH = GameWindow::getButtonMvsHRect().contains(localPosition);
// }


sf::RectangleShape GameWindow::createPiece(sf::Texture& texture, int i, int j, int type) {
    sf::RectangleShape shape(sf::Vector2f(CELL_WIDTH, CELL_WIDTH));
    shape.setTexture(&texture);
    int x = (abs(type) - 1) * CELL_WIDTH;
    int y = (type > 0 ? CELL_WIDTH : 0); 
    shape.setTextureRect(sf::IntRect(x, y, CELL_WIDTH, CELL_WIDTH));
    shape.setPosition(sf::Vector2f(j * CELL_WIDTH + BORDER_WIDTH, i * CELL_WIDTH + BORDER_WIDTH));
    return shape;
}

sf::RectangleShape GameWindow::createFillColorCell(int i, int j) {
    sf::RectangleShape shape(sf::Vector2f(CELL_WIDTH, CELL_WIDTH));
    if ((i + j) % 2 == 1)
        shape.setFillColor(sf::Color(191, 203, 95));	
    else    
        shape.setFillColor(sf::Color(245, 246, 152));
    shape.setPosition(j * CELL_WIDTH + BORDER_WIDTH, i * CELL_WIDTH + BORDER_WIDTH);
    return shape;
}

sf::CircleShape GameWindow::createFillColorCircle(int i, int j) {
    sf::CircleShape shape;
    shape.setRadius(CELL_WIDTH / 6);
    if ((i + j) % 2 == 1)
        shape.setFillColor(sf::Color(113, 136, 83)); 
    else    
        shape.setFillColor(sf::Color(210, 213, 186));
    shape.setPosition((j + 1.f / 3) * CELL_WIDTH + BORDER_WIDTH, (i + 1.f / 3) * CELL_WIDTH + BORDER_WIDTH);
    return shape;
}