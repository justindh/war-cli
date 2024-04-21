#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include <algorithm>
#include "Card.h"
#include <stdexcept>

class Player {
    private:
        std::vector<Card> deck; // cards to be drawn from
        std::vector<Card> discardPile; // cards won in battle
        std::vector<Card> cardsInPlay; // cards wagered
        std::string name;
        Card currentCard;
        void shuffleDiscardIntoDeck();
        struct Metrics{
            // Metrics for end of game report
            int battlesWon = 0;
            int warsWon = 0;
            int warsParticipated = 0;
        } metrics;

    public:
        // constructor
        Player(const std::string& playerName, std::vector<Card> initialDeck);
        Player();
        bool isUser = false;

        // returns player name
        std::string toString() const {
            return name;
        };

        // draws new card to the current card and adds it to the cardsInPlay
        Card drawCard();

        // returns current card ready for play
        const Card& getCurrentCard() const { return currentCard; }

        // Detirmines if player is alive
        bool hasCards() const {
            return !deck.empty() || !discardPile.empty();
        }

        int deckSize() const {
            return deck.size();
        }

        int discardSize() const {
            return discardPile.size();
        }

        // return all the cards player lost
        std::vector<Card> collectWinnings();

        // recieves cards that player won
        void giveCards(std::vector<Card>);

        //
        void win(){metrics.battlesWon++;}
        void winWar(){metrics.warsWon++;}
        void enterWar(){metrics.warsParticipated++;}
        Player::Metrics stats() const {
            return metrics;
        };
};

#endif