#ifndef CARD_H
#define CARD_H

#include <string>

// Suit Hearts and clubs and what not
enum class Suit { 
    Clubs, Diamonds, Hearts, Spades, 
    Min = Clubs, Max = Spades
};
// Pip aka numbers and faces
enum class Pip {
    Init = 0,
    Two = 2, Three, Four, Five, Six, Seven, Eight, Nine, Ten, 
    Jack = 11, Queen, King, Ace, 
    Min = Two, Max = Ace
};

struct Card {
    Pip pip;
    Suit suit;
    
    Card();
    Card(Pip p, Suit s);

    // Customizing comparison operators between cards cause we only care about the pip values
    bool operator<(const Card& other) const { 
        return static_cast<int>(pip) < static_cast<int>(other.pip);
    }
    bool operator>(const Card& other) const {
        return static_cast<int>(pip) > static_cast<int>(other.pip);
    }
    bool operator==(const Card& other) const { 
        return pip == other.pip; 
    }

    std::string toString() const;

};


#endif