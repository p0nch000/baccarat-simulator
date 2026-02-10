#ifndef BACCARAT_SIMULATOR_CARD_H
#define BACCARAT_SIMULATOR_CARD_H

#include <string>

class Card {
public:
    enum class Suit {
        HEARTS,
        DIAMONDS,
        CLUBS,
        SPADES
    };

    enum class Rank {
        ACE = 1,
        TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN,
        JACK, QUEEN, KING
    };

    Card(Rank rank, Suit suit);

    int getBaccaratValue() const;
    std::string toString() const;

    Rank getRank() const { return rank_; }
    Suit getSuit() const { return suit_; }

private:
    Rank rank_;
    Suit suit_;

    std::string rankToString() const;
    std::string suitToString() const;
};
#endif //BACCARAT_SIMULATOR_CARD_H