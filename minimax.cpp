#include "game_state.h"

std::pair<int, std::string> GameState::minimax(int depth, bool maximizingPlayer, int alpha, int beta) 
{
    if (depth == 0 || isGameStop()) {
        return std::make_pair(evaluateBoard(), getFinalMove());
    }

    if (maximizingPlayer) 
    {
        int bestScore = INT_MIN;
        std::string bestMove;
        Matrix legalMoves = getPossibleWhiteMoves();
        for (Row mov : legalMoves) {
            move(mov[2], mov[3], mov[0], mov[1]);
            std::pair<int, std::string> eval = minimax(depth - 1, false, alpha, beta);
            if (eval.first > bestScore || bestScore == INT_MIN) {
                bestScore = eval.first;
                bestMove = getFinalMove();
            }
            // Undo
            undo();

            // Alpha-beta pruning
            if (bestScore >= beta) return std::make_pair(bestScore, bestMove);
            alpha = std::max(alpha, bestScore);
        }
        return std::make_pair(bestScore, bestMove);
    } 
    else 
    { // MinimizingPlayer
        int bestScore = INT_MAX;
        std::string bestMove;
        Matrix legalMoves = getPossibleBlackMoves();
        for (auto mov : legalMoves) {
            move(mov[2], mov[3], mov[0], mov[1]);
            std::pair<int, std::string> eval = minimax(depth - 1, true, alpha, beta);
            if (eval.first < bestScore || bestScore == INT_MAX) {
                bestScore = eval.first;
                bestMove = getFinalMove();
            }
            // Undo
            undo();
            // Alpha-beta pruning
            if (bestScore <= alpha) return std::make_pair(bestScore, bestMove);
            beta = std::min(beta, bestScore);
        }
        return std::make_pair(bestScore, bestMove);
    }
}