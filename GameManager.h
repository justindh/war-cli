#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "Player.h"
#include <vector>

class GameManager {
public:
    GameManager(int numPlayers);
    void playGame();

private:
    std::vector<Player> players;
    void initializeGame();
    std::vector<Card> buildDeck();
    void playRound();
    int determineRoundWinner(const std::vector<Card> cards);
    void collectCards(int winnerIndex, const std::vector<Card>& cards);
    void handleWar(const std::vector<int>& tiedPlayers);
    bool checkEndGame() const;
    void displayResults() const;
    void PayWinner(int winnerId);
    void promptEnterKey();
};

#endif // GAMEMANAGER_H