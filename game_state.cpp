#include "game_state.h"

void GameState::move(int old_x, int old_y, int new_x, int new_y) 
{
    int oldValue = board[old_x][old_y];
    int newValue = board[new_x][new_y];
    if (oldValue != 0 && oldValue * newValue <= 0) {
        // TODO: Code evaluate function() in here
        int pieceValues[] = {-10, -1000, -90, -30, -30, -50, 0, 50, 30, 30, 90, 1000, 10};
        value -= pieceValues[newValue + 6];
        // add move to stack
        std::string move = std::to_string(old_x) + std::to_string(old_y) +
                           std::to_string(new_x) + std::to_string(new_y) +
                           char(oldValue + 65) + char(newValue + 65);
        moves.push(move);
        // std::cout << "Push (" << old_x << ", " << old_y << ") and (" << new_x << ", " << new_y << ") into stack" << std::endl;

        board[new_x][new_y] = oldValue;
        board[old_x][old_y] = 0;
        
        setXY(new_x, new_y);
    }
}

void GameState::undo() 
{
    if (!moves.empty()) {
        std::string move = moves.top();
        moves.pop();
        board[move[0] - '0'][move[1] - '0'] = move[4] - 'A';
        board[move[2] - '0'][move[3] - '0'] = move[5] - 'A';
        int pieceValues[] = {-10, -1000, -90, -30, -30, -50, 0, 50, 30, 30, 90, 1000, 10};
        value += pieceValues[move[5] - 'A' + 6];
        // Check error if exist
        if (!moves.empty()) {
            move = moves.top();
            setXY(move[2] - '0', move[3] - '0');
        } else {
            setXY(0, 0);
        }
    } else {
        std::cout << "Can not undo anymore" << std::endl;
    }
}

void GameState::play(int old_x, int old_y, int new_x, int new_y) 
{
    
    if (!gameStop) {
        move(old_x, old_y, new_x, new_y);
        togglePlayer();
        checkAndProcessFinalState();

        thinking = true;
        if (!gameStop && playMode == PlayMode::HumanVsMachine) {
            std::pair<int, std::string> p = minimax();
            std::string mov = p.second;
            move(mov[0] - '0', mov[1] - '0', mov[2] - '0', mov[3] - '0');
            togglePlayer();

            checkAndProcessFinalState();
            setXY(mov[2] - '0', mov[3] - '0');
        }
        thinking = false;
    }
}

std::string GameState::getFinalMove() const {
    if (moves.empty()) {
        std::cout << "Do not have any move in stack" << std::endl;
        return "";
    }
    return moves.top();
}

// bool GameState::isChecked() {
//     thinking = true;
//     std::pair<int, std::string> p = minimax(1, currentPlayer);
//     std::string mov = p.second;
//     move(mov[0] - '0', mov[1] - '0', mov[2] - '0', mov[3] - '0');
//     if (checkmate()) {
//         if (currentPlayer)
//             checkedWhiteKing = true;
//         else 
//             checkedBlackKing = true;
//         return true;
//     }
//     thinking = false;
//     return false;
// }

bool GameState::checkmate() {
    if (value > 500 || value < -500)
        return true;
    return false;
}

void GameState::checkAndProcessFinalState() {
    if (checkmate()) {
        gameStop = true;
    }
}

Matrix GameState::getPossibleMoves() {
    return calculatePossibleMoves(x, y);
}

int GameState::evaluateBoard() {
    // TODO
    return value;
}

void GameState::togglePlayer() {
    currentPlayer = !currentPlayer;
}

Matrix GameState::getPossibleBlackMoves() {
    Matrix possibleBlackMoves;
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (board[i][j] < 0) {
                Matrix tmp = calculatePossibleMoves(i, j);
                possibleBlackMoves.insert(possibleBlackMoves.end(), tmp.begin(), tmp.end());
            }
        }
    }
    return possibleBlackMoves;
}

Matrix GameState::getPossibleWhiteMoves() {
    Matrix possibleWhiteMoves;
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (board[i][j] > 0) {
                Matrix tmp = calculatePossibleMoves(i, j);
                possibleWhiteMoves.insert(possibleWhiteMoves.end(), tmp.begin(), tmp.end());
            }
        }
    }
    return possibleWhiteMoves;
}



// -----------------------------------------------------
// Calculate possible moves from pos (i, j)
Matrix GameState::calculatePossibleMoves(int i, int j) {
    Matrix possibleMoves;
    int type = abs(board[i][j]);
    switch (type) {
        case 6:
            possibleMoves = calculatePossiblePawnMoves(i, j);
            break;
        case 2:
            possibleMoves = calculatePossibleKnightMoves(i, j);
            break;
        case 3:
            possibleMoves = calculatePossibleBishopMoves(i, j);
            break;
        case 4:
            possibleMoves = calculatePossibleQueenMoves(i, j);
            break;
        case 1:
            possibleMoves = calculatePossibleRookMoves(i, j);
            break;
        case 5:
            possibleMoves = calculatePossibleKingMoves(i, j);
            break;
        default: break;
    }
    return possibleMoves;
}

Matrix GameState::calculatePossiblePawnMoves(int i, int j) {
    Matrix possibleMoves;
    int k = board[i][j] / abs(board[i][j]);
    if ((i == 1 || i == 6) && board[i - k][j] == 0 && board[i - 2 * k][j] == 0 && i - 2 * k >= 0 && i - 2 * k < 8)
        possibleMoves.push_back({i - 2 * k, j, i, j});
    if (board[i - k][j] == 0 && i - k < 8 && i - k >= 0)
        possibleMoves.push_back({i - k, j, i, j});
    if (board[i - k][j + 1] * board[i][j] < 0 && i - k >= 0 && i - k < 8 && j + 1 < 8)
        possibleMoves.push_back({i - k, j + 1, i, j});
    if (board[i - k][j - 1] * board[i][j] < 0 && i - k >= 0 && i - k < 8 && j - 1 >= 0)
        possibleMoves.push_back({i - k, j - 1, i, j});
    return possibleMoves;
}

Matrix GameState::calculatePossibleKnightMoves(int i, int j) {
    Matrix possibleMoves;
    int z = board[i][j];
    if (z * board[i + 2][j + 1] <= 0 && i + 2 < 8 && j + 1 < 8) 
        possibleMoves.push_back({i + 2, j + 1, i, j});
    if (z * board[i + 2][j - 1] <= 0 && i + 2 < 8 && j - 1 >= 0) 
        possibleMoves.push_back({i + 2, j - 1, i, j});
    if (z * board[i - 2][j + 1] <= 0 && i - 2 >= 0 && j + 1 < 8) 
        possibleMoves.push_back({i - 2, j + 1, i, j});
    if (z * board[i - 2][j - 1] <= 0 && i - 2 >= 0 && j - 1 >= 0) 
        possibleMoves.push_back({i - 2, j - 1, i, j});
    if (z * board[i + 1][j + 2] <= 0 && i + 1 < 8 && j + 2 < 8) 
        possibleMoves.push_back({i + 1, j + 2, i, j});
    if (z * board[i + 1][j - 2] <= 0 && i + 1 < 8 && j - 2 >= 0) 
        possibleMoves.push_back({i + 1, j - 2, i, j});
    if (z * board[i - 1][j + 2] <= 0 && i - 1 >= 0 && j + 2 < 8) 
        possibleMoves.push_back({i - 1, j + 2, i, j});
    if (z * board[i - 1][j - 2] <= 0 && i - 1 >= 0 && j - 2 >= 0) 
        possibleMoves.push_back({i - 1, j - 2, i, j});
    return possibleMoves;
}

Matrix GameState::calculatePossibleBishopMoves(int i, int j) {
    Matrix possibleMoves;
    int z = board[i][j];

    // Top-left diagonal
    for (int y = i - 1, x = j - 1; y >= 0 && x >= 0; y--, x--) {
        if (board[y][x] == 0) {
            possibleMoves.push_back({y, x, i, j});
        } else if (board[y][x] * z < 0) {
            possibleMoves.push_back({y, x, i, j});
            break;
        } else {
            break;
        }
    }

    // Top-right diagonal
    for (int y = i - 1, x = j + 1; y >= 0 && x < 8; y--, x++) {
        if (board[y][x] == 0) {
            possibleMoves.push_back({y, x, i, j});
        } else if (board[y][x] * z < 0) {
            possibleMoves.push_back({y, x, i, j});
            break;
        } else {
            break;
        }
    }

    // Bottom-left diagonal
    for (int y = i + 1, x = j - 1; y < 8 && x >= 0; y++, x--) {
        if (board[y][x] == 0) {
            possibleMoves.push_back({y, x, i, j});
        } else if (board[y][x] * z < 0) {
            possibleMoves.push_back({y, x, i, j});
            break;
        } else {
            break;
        }
    }

    // Bottom-right diagonal
    for (int y = i + 1, x = j + 1; y < 8 && x < 8; y++, x++) {
        if (board[y][x] == 0) {
            possibleMoves.push_back({y, x, i, j});
        } else if (board[y][x] * z < 0) {
            possibleMoves.push_back({y, x, i, j});
            break;
        } else {
            break;
        }
    }
    return possibleMoves;
}

Matrix GameState::calculatePossibleQueenMoves(int i, int j) {
    Matrix possibleMoves = calculatePossibleRookMoves(i, j);
    Matrix tmp = calculatePossibleBishopMoves(i, j);
    possibleMoves.insert(possibleMoves.end(), tmp.begin(), tmp.end());
    return possibleMoves;
}

Matrix GameState::calculatePossibleRookMoves(int i, int j) {
    Matrix possibleMoves;
    int z = board[i][j];

    // Move up
    for (int y = i - 1; y >= 0; y--) {
        if (board[y][j] == 0) {
            possibleMoves.push_back({y, j, i, j});
        } else if (z * board[y][j] < 0) {
            possibleMoves.push_back({y, j, i, j});
            break;
        } else {
            break;
        }
    }

    // Move down
    for (int y = i + 1; y < 8; y++) {
        if (board[y][j] == 0) {
            possibleMoves.push_back({y, j, i, j});
        } else if (board[y][j] * z < 0) {
            possibleMoves.push_back({y, j, i, j});
            break;
        } else {
            break;
        }
    }

    // Move left
    for (int x = j - 1; x >= 0; x--) {
        if (board[i][x] == 0) {
            possibleMoves.push_back({i, x, i, j});
        } else if (board[i][x] * z < 0) {
            possibleMoves.push_back({i, x, i, j});
            break;
        } else {
            break;
        }
    }

    // Move right
    for (int x = j + 1; x < 8; x++) {
        if (board[i][x] == 0) {
            possibleMoves.push_back({i, x, i, j});
        } else if (board[i][x] * z < 0) {
            possibleMoves.push_back({i, x, i, j});
            break;
        } else {
            break;
        }
    }

    return possibleMoves;
}

Matrix GameState::calculatePossibleKingMoves(int i, int j) {
    Matrix possibleMoves;
    int z = board[i][j];
    if (z * board[i + 1][j + 1] <= 0 && i + 1 < 8 && j + 2 < 8)
        possibleMoves.push_back({i + 1, j + 1, i, j});
    if (z * board[i + 1][j] <= 0 && i + 1 < 8)
        possibleMoves.push_back({i + 1, j, i, j});
    if (z * board[i + 1][j - 1] <= 0 && i + 1 < 8 && j - 1 >= 0)
        possibleMoves.push_back({i + 1, j - 1, i, j});
    if (z * board[i][j + 1] <= 0 && j + 1 < 8)
        possibleMoves.push_back({i, j + 1, i, j, i, j});
    if (z * board[i][j - 1] <= 0 && j - 1 >= 0)
        possibleMoves.push_back({i, j - 1, i, j});
    if (z * board[i - 1][j + 1] <= 0 && i - 1 >= 0 && j + 1 < 8)
        possibleMoves.push_back({i - 1, j + 1, i, j});
    if (z * board[i - 1][j] <= 0 && i - 1 >= 0)
        possibleMoves.push_back({i - 1, j, i, j});
    if (z * board[i - 1][j - 1] <= 0 && i - 1 >= 0 && j - 1 >= 0)
        possibleMoves.push_back({i - 1, j - 1, i, j});

    return possibleMoves;
}