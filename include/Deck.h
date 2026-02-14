#ifndef BACCARAT_SIMULATOR_DECK_H
#define BACCARAT_SIMULATOR_DECK_H

#include "Card.h"
#include <vector>

class Deck {
public:
    explicit Deck(int numDecks = 8);

    void shuffle();
    void reset();
    Card dealCard();

    [[nodiscard]] bool needsReshuffle() const;
    [[nodiscard]] size_t remainingCards() const { return cards_.size(); }

private:
    std::vector<Card> cards_;
    int numDecks_;
    static constexpr double PENETRATION = 0.75;

    void initialize();
};

#endif
