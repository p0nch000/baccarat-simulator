#include "Deck.h"
#include <algorithm>
#include <random>
#include <chrono>

Deck::Deck(int numDecks) : numDecks_(numDecks) {
    initialize();
    shuffle();
}

void Deck::initialize() {
    cards_.clear();
    cards_.reserve(numDecks_ * 52);

    for (int d = 0; d < numDecks_; ++d)
        for (int s = 0; s < 4; ++s)
            for (int r = 1; r <= 13; ++r)
                cards_.emplace_back(static_cast<Card::Rank>(r), static_cast<Card::Suit>(s));
}

void Deck::shuffle() {
    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 rng(static_cast<unsigned>(seed));
    std::shuffle(cards_.begin(), cards_.end(), rng);
}

Card Deck::dealCard() {
    if (cards_.empty()) reset();
    Card card = cards_.back();
    cards_.pop_back();
    return card;
}

bool Deck::needsReshuffle() const {
    int total = numDecks_ * 52;
    double used = static_cast<double>(total - static_cast<int>(cards_.size())) / total;
    return used >= PENETRATION;
}

void Deck::reset() {
    initialize();
    shuffle();
}
