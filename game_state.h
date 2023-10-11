#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <iostream>
#include <vector>
#include <stack>

typedef std::vector<int> Row;
typedef std::vector<Row> Matrix;

class GameState {
public:
    enum class PlayScreen {
        PlayModeScreen,
        PlayingScreen,
    };

    enum class PlayMode {
        HumanVsHuman,
        HumanVsMachine,
    };

private:
    int board[8][8] = 
    {
        -1, -2, -3, -4, -5, -3, -2, -1,
        -6, -6, -6, -6, -6, -6, -6, -6,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        6, 6, 6, 6, 6, 6, 6, 6,
        1, 2, 3, 4, 5, 3, 2, 1,
    };

    // Stack for undo function
    std::stack<std::string> moves; 

    int x = 0, y = 0; // state.getChessPieceType(0, 0) = -1
    bool firstClick = false;

    int value = 0;

    bool gameStop = false;
    bool thinking = false;
    bool currentPlayer = true; //true -> white, false -> black;

    bool checkedWhiteKing = false;
    bool checkedBlackKing = false;

    PlayScreen playScreen = PlayScreen::PlayingScreen;
    PlayMode playMode = PlayMode::HumanVsMachine;

public:
    PlayScreen getPlayScreen() const { return playScreen; }
    void setPlayScreen(PlayScreen playScreen) { this->playScreen = playScreen; }

    PlayMode getPlayMode() const { return playMode; }
    void setPlayMode(PlayMode playMode) { this->playMode = playMode; }

    // Get type (value) from the given positions i and j
    int getChessPieceType(int i, int j) const { return board[i][j]; }
    void setChessPieceType(int i, int j, int k) { board[i][j] = k; }

    int getCurrentChessPiece() const { return board[x][y]; }

    bool isGameStop() const { return gameStop; }
    bool isThinking() const { return thinking; }

    bool getCurrentPlayer() const { return currentPlayer; }
    void togglePlayer();

    int getX() const { return x; }
    int getY() const { return y; }
    void setXY(int x, int y) { this->x = x; this->y = y; }

    bool getFirstClick() const { return firstClick; }
    void setFisrtClick(bool firstClick) { this->firstClick = firstClick; }

    void move(int old_x, int old_y, int new_x, int new_y);

    // TODO
    void play(int old_x, int old_y, int new_x, int new_y);

    // void resetGame();
    void undo();
    std::string getFinalMove() const;
    bool isEmptyMove() const { return moves.empty(); };
    
    // Checkmate
    bool checkmate();

    // Get expected value of board
    int evaluateBoard();
    
    // Get possible moves from current selected cell (X, Y) 
    Matrix getPossibleMoves();

    // Get all possible moves of white chess pieces at a state
    Matrix getPossibleWhiteMoves();

    // Get all possible moves of white chess pieces at a state
    Matrix getPossibleBlackMoves();

    // Check
    // bool isChecked();

private:
    void checkAndProcessFinalState();

    Matrix calculatePossibleMoves(int i, int j);

    Matrix calculatePossibleRookMoves(int i, int j);
    Matrix calculatePossibleKnightMoves(int i, int j);
    Matrix calculatePossibleBishopMoves(int i, int j);
    Matrix calculatePossibleQueenMoves(int i, int j);
    Matrix calculatePossibleKingMoves(int i, int j);
    Matrix calculatePossiblePawnMoves(int i, int j);

    // Minimax
    std::pair<int, std::string> minimax(int depth = 4, bool maximizingPlayer = false, int alpha = INT_MIN, int beta = INT_MAX);
};


#endif