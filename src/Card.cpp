#include "Card.h"

Card::Card(Rank rank, Suit suit) : rank_(rank), suit_(suit) {}

int Card::baccaratValue() const {
    int value = static_cast<int>(rank_);
    return value >= 10 ? 0 : value;
}

std::string Card::rankSymbol() const {
    switch (rank_) {
        case Rank::ACE:   return "A";
        case Rank::TWO:   return "2";
        case Rank::THREE: return "3";
        case Rank::FOUR:  return "4";
        case Rank::FIVE:  return "5";
        case Rank::SIX:   return "6";
        case Rank::SEVEN: return "7";
        case Rank::EIGHT: return "8";
        case Rank::NINE:  return "9";
        case Rank::TEN:   return "10";
        case Rank::JACK:  return "J";
        case Rank::QUEEN: return "Q";
        case Rank::KING:  return "K";
        default:          return "?";
    }
}

std::string Card::suitSymbol() const {
    switch (suit_) {
        case Suit::HEARTS:   return "\u2665";
        case Suit::DIAMONDS: return "\u2666";
        case Suit::CLUBS:    return "\u2663";
        case Suit::SPADES:   return "\u2660";
        default:             return "?";
    }
}
