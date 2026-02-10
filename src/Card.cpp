#include "Card.h"

Card::Card(Rank rank, Suit suit) : rank_(rank), suit_(suit) {}

int Card::getBaccaratValue() const {
    int rankValue = static_cast<int>(rank_);

    if (rankValue >= 10) {
        return 0;
    }

    return rankValue;
}

std::string Card::rankToString() const {
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

std::string Card::suitToString() const {
    switch (suit_) {
        case Suit::HEARTS:   return "\033[91m\u2665\033[0m";
        case Suit::DIAMONDS: return "\033[91m\u2666\033[0m";
        case Suit::CLUBS:    return "\u2663";
        case Suit::SPADES:   return "\u2660";
        default:             return "?";
    }
}

std::string Card::toString() const {
    return "[" + rankToString() + suitToString() + "]";
}