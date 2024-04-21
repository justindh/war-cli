#include "Player.h"
#include <algorithm>
#include <random> 
#include <stdexcept>
#include <chrono>

Player::Player(const std::string& playerName, std::vector<Card> initialDeck) 
    : name(playerName), deck(initialDeck) {}

Player::Player(){}


void Player::shuffleDiscardIntoDeck() {
        auto rng = std::default_random_engine(std::chrono::system_clock::now().time_since_epoch().count());
        std::shuffle(discardPile.begin(), discardPile.end(), rng);

        deck = std::move(discardPile);
        discardPile.clear();
}

Card Player::drawCard() {
    if (deck.empty() && !discardPile.empty()) {
        shuffleDiscardIntoDeck();
    }
    if (deck.empty()) {
        throw std::runtime_error("have no cards, should of asked if I had any first");
    }
    currentCard = deck.front();
    deck.erase(deck.begin());
    cardsInPlay.push_back(currentCard);
    return currentCard;
}


std::vector<Card> Player::collectWinnings(){
    std::vector<Card> winnings = std::move(cardsInPlay);
    cardsInPlay.clear();
    return winnings;
}


void Player::giveCards(std::vector<Card> newCards){
    // Add player cards to discard cause we won
    for (Card c : cardsInPlay){
        discardPile.push_back(c);
    }
    cardsInPlay.clear();

    // Add our winnings to our discard
    for (Card c : newCards){
        discardPile.push_back(c);
    }
};
