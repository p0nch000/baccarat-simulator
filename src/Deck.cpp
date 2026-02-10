#include "Deck.h"
#include <algorithm>
#include <random>
#include <chrono>

Deck::Deck(int numDecks) : numDecks_(numDecks) {
    initializeDeck();
    shuffle();
}

void Deck::initializeDeck() {
    cards_.clear();

    for (int deck = 0; deck < numDecks_; ++deck) {
        for (int suit = 0; suit < 4; ++suit) {
            for (int rank = 1; rank <= 13; ++rank) {
                cards_.push_back(Card(
                    static_cast<Card::Rank>(rank),
                    static_cast<Card::Suit>(suit)
                ));
            }
        }
    }
}

void Deck::shuffle() {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine rng(seed);

    std::shuffle(cards_.begin(), cards_.end(), rng);
}

Card Deck::dealCard() {
    if (cards_.empty()) {
        reset();
    }
    Card card = cards_.back();
    cards_.pop_back();
    return card;
}

bool Deck::needsReshuffle() const {
    int totalCards = numDecks_ * 52;
    int cardsUsed = totalCards - cards_.size();
    double penetration = static_cast<double>(cardsUsed) / totalCards;

    return penetration >= PENETRATION;
}

void Deck::reset() {
    initializeDeck();
    shuffle();
}