// Get the score of the state and the best next state
// s - the state
// isMax true if the current player is the maximizing player
// alpha MAX - best score
// beta MIN - best score
// std::pair<int, State> - the score and the best next state
std::pair<int, GameState::State> GameState::getScore(State s, bool isMax, int alpha, int beta)
{
    // base case
    if (isFinalState(s)) return make_pair(getScoreFinalState(s), s);

    // get all possible next states
    std::vector<State> states = getNextStates(s);
    
    // store the best score and the best next state
    const int INVALID = -10;
    int bestScore = INVALID;
    State bestState;

    // recursively get the score of the next states
    for (State ns: states) {
        std::pair<int, State> p = getScore(ns, !isMax, alpha, beta);
        int score = p.first;
        // update best score for MAX
        if (isMax) {
            if (bestScore < score || bestScore == INVALID) {
                bestScore = score;
                bestState = ns;
            }
            // prune if bestScore >= best option for MIN
            if (bestScore >= beta) return make_pair(bestScore, bestState);
            alpha = std::max(alpha, bestScore);
        } else { // update best score for MIN
            if (bestScore > score || bestScore == INVALID) {
                bestScore = score;
                bestState = ns;
            }
            // prune if bestScore <= best option for MAX
            if (bestScore <= alpha) return make_pair(bestScore, bestState);
            beta = std::min(beta, bestScore);
        }
    }
    return make_pair(bestScore, bestState);
}
