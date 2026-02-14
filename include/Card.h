#ifndef BACCARAT_SIMULATOR_CARD_H
#define BACCARAT_SIMULATOR_CARD_H

#include <string>

class Card {
public:
    enum class Suit { HEARTS, DIAMONDS, CLUBS, SPADES };
    enum class Rank {
        ACE = 1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN,
        JACK, QUEEN, KING
    };

    Card(Rank rank, Suit suit);

    [[nodiscard]] int baccaratValue() const;
    [[nodiscard]] std::string rankSymbol() const;
    [[nodiscard]] std::string suitSymbol() const;
    [[nodiscard]] Rank rank() const { return rank_; }
    [[nodiscard]] Suit suit() const { return suit_; }

private:
    Rank rank_;
    Suit suit_;
};

#endif
