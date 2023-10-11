#include "controller.h"

void Controller::onMouseButtonReleased(sf::Event &event)
{
    if (state.getPlayScreen() == GameState::PlayScreen::PlayingScreen)
    {
        if (!state.isGameStop())
        {
            sf::Vector2i firstPosition = { event.mouseButton.x, event.mouseButton.y };

            if (firstPosition.x >= GameWindow::BORDER_WIDTH && firstPosition.y >= GameWindow::BORDER_WIDTH
                && firstPosition.x < GameWindow::LIMIT_BORDER_WIDTH && firstPosition.y < GameWindow::LIMIT_BORDER_WIDTH) 
            {
                int i = (firstPosition.y - GameWindow::BORDER_WIDTH) / GameWindow::CELL_WIDTH, // col
                    j = (firstPosition.x - GameWindow::BORDER_WIDTH) / GameWindow::CELL_WIDTH; // row

                if (!state.getFirstClick() && state.getChessPieceType(i, j) * state.getCurrentChessPiece() < 0) {
                    state.setXY(i, j);
                    // std::cout << "first click was activated (" << i + 1 << ", " << j + 1 << ")." << std::endl;
                    state.setFisrtClick(true);
                } else if (state.getFirstClick()) {
                    int multi = state.getChessPieceType(i, j) * state.getCurrentChessPiece();
                    if (multi <= 0) {
                        Matrix possMoves = state.getPossibleMoves();
                        for (auto row : possMoves) {
                            if (row[0] == i && row[1] == j && row[2] == state.getX() && row[3] == state.getY()) {
                                // std::cout << "second click was activated (" << i + 1 << ", " << j + 1 << ")." << std::endl;
                                state.play(state.getX(), state.getY(), i, j);
                                state.setFisrtClick(false);
                                std::cout << state.evaluateBoard() << std::endl;
                                break;
                            }
                        }
                    } else {
                        // std::cout << "first click was activated (" << i + 1 << ", " << j + 1 << ")." << std::endl;
                        state.setXY(i, j);
                    }
                }
            } 
            else {
                state.setFisrtClick(false);
            }
        } 
        else { // game is over so reset the game
            // state.resetGame();
            // change the play screen to PlayModeScreen
            // state.setPlayScreen(GameState::PlayScreen::PlayModeScreen);
        }
    } 
    else { // GameState::PlayScreen::PlayModeScreen
        // sf::Vector2i localPosition = { event.mouseButton.x, event.mouseButton.y};
        // checkButtonClicked(localPosition);
    }
}

// check if a button is clicked
// void Controller::checkButtonClicked(sf::Vector2i localPosition)
// {   
//    if (GameWindow::getButtonHvsHRect().contains(localPosition)) {
//         state.setPlayScreen(GameState::PlayScreen::PlayingScreen);
//         state.setPlayMode(GameState::PlayMode::HumanVsHuman);
//         std::cout << "Human vs Human" << std::endl;
//     } else if (GameWindow::getButtonHvsMRect().contains(localPosition)) {
//         state.setPlayScreen(GameState::PlayScreen::PlayingScreen);
//         state.setPlayMode(GameState::PlayMode::HumanVsMachine);
//         std::cout << "Human vs Machine" << std::endl;
//     } else if (GameWindow::getButtonMvsHRect().contains(localPosition)) {
//         state.setPlayScreen(GameState::PlayScreen::PlayingScreen);
//         state.setPlayMode(GameState::PlayMode::HumanVsMachine);
//         state.computerPlayFirst();
//         std::cout << "Machine vs Human" << std::endl;
//     }
// }

void Controller::onMouseMoved(sf::Event &event)
{
    if (state.getPlayScreen() == GameState::PlayScreen::PlayModeScreen) {
        // sf::Vector2i localPosition = { event.mouseMove.x, event.mouseMove.y};
        // checkButtonHovered(localPosition);
    } else {
        sf::Vector2i localPosition = sf::Mouse::getPosition(window);
        if (localPosition.x >= GameWindow::BORDER_WIDTH && localPosition.y >= GameWindow::BORDER_WIDTH
            && localPosition.x < GameWindow::LIMIT_BORDER_WIDTH && localPosition.y < GameWindow::LIMIT_BORDER_WIDTH) 
        {
            int i = (localPosition.x - GameWindow::BORDER_WIDTH) / GameWindow::CELL_WIDTH,
                j = (localPosition.y - GameWindow::BORDER_WIDTH) / GameWindow::CELL_WIDTH;
            window.setHoveredCell(i, j);
        } else {
            window.setHoveredCell(-1, -1);
        }
    }
}

// check if a button is hovered
// void Controller::checkButtonHovered(sf::Vector2i localPosition)
// {
//     window.setHoveredButtons(localPosition);
// }

void Controller::processEvent(sf::Event& event) 
{
    switch (event.type) {
        case sf::Event::MouseButtonReleased:
            addEvent(event); // to event thread queue
            break;
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::MouseMoved:
            onMouseMoved(event);
            break;
        case sf::Event::KeyPressed:
            addEvent(event);
            break;
            
        default: break;
    }
}

void Controller::addEvent(sf::Event event)
{
    mutex.lock();
    queue.push(event);
    mutex.unlock();
}

void Controller::launch() {
    thread.launch();
}

void Controller::wait() {
    thread.wait();
}

sf::Event Controller::getEvent()
{
    sf::Event event;
    event.type = sf::Event::Count;
    mutex.lock();
    if (!queue.empty()) {
        event = queue.front();
        queue.pop();
    }
    mutex.unlock();

    return event;
}

void Controller::run() {
    while(window.isOpen()) {
        sf::Event event = getEvent();
        switch (event.type) {
            case sf::Event::MouseButtonReleased:
                onMouseButtonReleased(event);
                break;
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Space) {
                    mutex.lock();
                    state.undo();
                    state.undo();
                    mutex.unlock();
                }
                break;
            default: break;
        }
    }
}