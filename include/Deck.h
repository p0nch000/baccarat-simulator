#ifndef BACCARAT_SIMULATOR_DECK_H
#define BACCARAT_SIMULATOR_DECK_H

#include "Card.h"
#include <vector>

class Deck {
public:
    Deck(int numDecks = 8);

    void shuffle();

    Card dealCard();

    bool needsReshuffle() const;

    void reset();

    size_t remainingCards() const { return cards_.size(); }

private:
    std::vector<Card> cards_;
    int numDecks_;
    static constexpr double PENETRATION = 0.75;

    void initializeDeck();
};
#endif //BACCARAT_SIMULATOR_DECK_H