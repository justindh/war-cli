#include "Card.h"

// Default Constructor
Card::Card() : pip(Pip::Init), suit(Suit::Clubs) {}
// Constructor
Card::Card(Pip p, Suit s) : pip(p), suit(s) {}


std::string Card::toString() const {

    std::string sSuit;
    switch (suit) {
            case Suit::Clubs:    sSuit = "Club"; break;
            case Suit::Diamonds: sSuit = "Diamond"; break;
            case Suit::Hearts:   sSuit = "Heart"; break;
            case Suit::Spades:   sSuit = "Spade"; break;
            default:             sSuit = ""; break; // TODO: Handle Jacks? or other suits
    }

    std::string sPip;
    switch (pip) {
        case Pip::Two:   sPip =  "2"; break;
        case Pip::Three: sPip =  "3"; break;
        case Pip::Four:  sPip =  "4"; break;
        case Pip::Five:  sPip =  "5"; break;
        case Pip::Six:   sPip =  "6"; break;
        case Pip::Seven: sPip =  "7"; break;
        case Pip::Eight: sPip =  "8"; break;
        case Pip::Nine:  sPip =  "9"; break;
        case Pip::Ten:   sPip =  "10"; break;
        case Pip::Jack:  sPip =  "Jack"; break;
        case Pip::Queen: sPip =  "Queen"; break;
        case Pip::King:  sPip =  "King"; break;
        case Pip::Ace:   sPip =  "Ace"; break;
        default:         sPip = ""; break; // TODO: Handle Jacks? or other cards
    }
    return sPip + " " + sSuit;
}