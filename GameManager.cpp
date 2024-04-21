#include "GameManager.h"
#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>


GameManager::GameManager(int numPlayers) {

    std::vector<Card> initialDeck = buildDeck();
    // TODO: handle arbitrary number of players
    if (initialDeck.size() % numPlayers != 0) {
        throw std::runtime_error("required an even number of cards for all players");
    } 
    auto portionSize = initialDeck.size() / numPlayers;
    auto currentCard = initialDeck.begin();

    for (int i = 0; i < numPlayers; ++i) {
        std::vector<Card> playerDeck(currentCard, currentCard + portionSize);
        players.emplace_back("Player " + std::to_string(i + 1), playerDeck);
        currentCard += portionSize;
    }
    // Set the first player to the user
    players[0].isUser = true;
}

void GameManager::playGame() {
    while (!checkEndGame()) {
        playRound();
    }
    displayResults();
}

// buildDeck: Build a deck and then shuffle it
std::vector<Card> GameManager::buildDeck() {
    std::vector<Card> deck;
    for (int suit = static_cast<int>(Suit::Min); suit <= static_cast<int>(Suit::Max); ++suit) {
        for (int pip = static_cast<int>(Pip::Min); pip <= static_cast<int>(Pip::Max); ++pip) {
            deck.emplace_back(static_cast<Pip>(pip), static_cast<Suit>(suit));
        }
    }
    std::shuffle(deck.begin(), deck.end(), std::default_random_engine(std::chrono::system_clock::now().time_since_epoch().count()));
    return deck;
}

void GameManager::playRound() {
    std::cout << "\n\n================\n\n Starting new round \n\n================\n\n";
    std::vector<int> playersInRound;
    std::vector<Card> cardsInPlay;

    // Each player who has cards draws one
    for (int i = 0; i < players.size(); ++i) {
        if (players[i].hasCards()) {
            players[i].drawCard();
            playersInRound.push_back(i);
            std::cout << players[i].toString() << " plays: " << players[i].getCurrentCard().toString() << "\n";
            cardsInPlay.push_back(players[i].getCurrentCard());
        }
    }

    if (playersInRound.empty()) {
        std::cout << "No players have cards to play this round.\n";
        return;
    }

    // Determine the round winner or handle a tie
    int winnerIndex = determineRoundWinner(cardsInPlay);
    if (winnerIndex != -1) {
        winnerIndex = playersInRound[winnerIndex]; // Translate to global player index
        PayWinner(winnerIndex);
        players[winnerIndex].win();
        std::cout << players[winnerIndex].toString() << " wins the round.\n";
    } else {
        std::vector<int> tiedPlayers;
        Card highest = Card(); // Initialize to a default, possibly lowest possible card if needed
        // Find the highest card among those played this round
        for (int i = 0; i < cardsInPlay.size(); ++i) {
            if (cardsInPlay[i] > highest) {
                highest = cardsInPlay[i];
                tiedPlayers.clear(); // Clear previous tied players as a new highest card is found
                tiedPlayers.push_back(playersInRound[i]); // Start new list of tied players
            } else if (cardsInPlay[i] == highest) {
                tiedPlayers.push_back(playersInRound[i]); // Add to list of tied players
            }
        }
        if (!tiedPlayers.empty()) {
            handleWar(tiedPlayers);
        } else {
            std::cout << "Unexpected error: No tied players found when a tie was expected.\n";
        }
    }
    std::cout << "\n\nScores:\n";
    for (int i = 0; i < players.size(); ++i) {
        std::cout << players[i].toString() << "\t" 
            << players[i].deckSize() << "/" << players[i].discardSize() << " Deck/Discard \t"
            << players[i].stats().battlesWon << " battles won \t"
            << players[i].stats().warsWon << " wars won \n";
    }
}

int GameManager::determineRoundWinner(const std::vector<Card> cards) {
    Card highest = cards[0];
    int winnerIndex = 0;
    bool tie = false;

    for (int i = 1; i < cards.size(); ++i) {
        if (cards[i] > highest) {
            highest = cards[i];
            winnerIndex = i;
            tie = false;
        } else if (cards[i] == highest) {
            tie = true;
        }
    }

    return tie ? -1 : winnerIndex;
}


void GameManager::handleWar(const std::vector<int>& tiedPlayers) {
    std::cout << "\n\n----[ WAR ]----\n";
    std::vector<Card> warCards;

    for (int playerIndex : tiedPlayers) {
        players[playerIndex].enterWar();
        // We draw a card face down
        if (players[playerIndex].hasCards()) {
            players[playerIndex].drawCard(); // Draw face-down card
            std::cout << players[playerIndex].toString() << " places a card face down.\n";
        }
        // If we still have cards left, we draw a card face up
        if (players[playerIndex].hasCards()) {
            players[playerIndex].drawCard(); // Draw war card   
        }
        // We use the last drawn card, what ever the method as our next card
        warCards.push_back(players[playerIndex].getCurrentCard());
        std::cout << players[playerIndex].toString() << " plays " << players[playerIndex].getCurrentCard().toString() << " for war.\n";
    }

    int winnerIndex = determineRoundWinner(warCards);
    if (winnerIndex != -1) {
        players[winnerIndex].winWar();
        winnerIndex = tiedPlayers[winnerIndex];
        std::cout << players[winnerIndex].toString() << " wins the war!\n";
        PayWinner(winnerIndex);
    } else {
        std::cout << "War continues due to another tie.\n";
        handleWar(tiedPlayers);
    }
}

void GameManager::PayWinner(int winnerIndex) {
    for (int i = 0; i < players.size(); ++i) {
        if (i != winnerIndex) {
            std::vector<Card> winnings = players[i].collectWinnings();
            players[winnerIndex].giveCards(winnings);
        }
    }

    int totalCardsInPlay = 0;
    for (int i = 0; i < players.size(); ++i) {
        totalCardsInPlay += players[i].deckSize() + players[i].discardSize();
    }

    if (totalCardsInPlay != 52) {
        throw std::runtime_error("Too Many Cards in Play");
    }
}

bool GameManager::checkEndGame() const {
    int activePlayers = 0;
    for (const auto& player : players) {
        if (player.hasCards()) {
            activePlayers++;
        }
    }
    return activePlayers < 2; // End game if less than two players can play
}

void GameManager::displayResults() const {
    std::string winnerName;
    int maxCards = 0;  // Keep track of the maximum number of cards any player holds

    std::cout << "Game Over. Results:" << std::endl;

    // Iterate through all players to find the one with the most cards and to display their stats
    for (const auto& player : players) {
        int totalCards = player.deckSize() + player.discardSize();
        std::cout << player.toString() << " won " << player.stats().battlesWon << " battles, participated in "
                << player.stats().warsParticipated << " wars, and won " << player.stats().warsWon << " of them." << std::endl;

        if (totalCards > maxCards) {
            maxCards = totalCards;
            winnerName = player.toString();
        }
    }

    if (!winnerName.empty()) {
        std::cout << "\n\n==========================\n\n" << winnerName << " won the Game!!!!\n\n==========================\n\n";
    } else {
        std::cout << "\n\n=============\n\nNo clear winner could be determined.\n\n=============\n\n";
    }
}


void GameManager::promptEnterKey() {
    std::cout << "Press Enter to play a card...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}