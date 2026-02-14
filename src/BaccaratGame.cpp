#include "BaccaratGame.h"
#include <numeric>

BaccaratGame::BaccaratGame() : deck_(8) {}

void BaccaratGame::clearHands() {
    playerHand_.clear();
    bankerHand_.clear();
}

void BaccaratGame::dealInitialCards() {
    playerHand_.push_back(deck_.dealCard());
    bankerHand_.push_back(deck_.dealCard());
    playerHand_.push_back(deck_.dealCard());
    bankerHand_.push_back(deck_.dealCard());
}

int BaccaratGame::handValue(const std::vector<Card>& hand) const {
    int total = std::accumulate(hand.begin(), hand.end(), 0,
        [](int sum, const Card& c) { return sum + c.baccaratValue(); });
    return total % 10;
}

int BaccaratGame::playerHandValue() const { return handValue(playerHand_); }
int BaccaratGame::bankerHandValue() const { return handValue(bankerHand_); }

bool BaccaratGame::isNatural() const {
    int pv = handValue(playerHand_);
    int bv = handValue(bankerHand_);
    return (playerHand_.size() == 2 && pv >= 8) || (bankerHand_.size() == 2 && bv >= 8);
}

bool BaccaratGame::isPlayerPair() const {
    return playerHand_.size() >= 2 && playerHand_[0].rank() == playerHand_[1].rank();
}

bool BaccaratGame::isBankerPair() const {
    return bankerHand_.size() >= 2 && bankerHand_[0].rank() == bankerHand_[1].rank();
}

bool BaccaratGame::playerDrawsThird() const {
    return playerHandValue() <= 5;
}

bool BaccaratGame::bankerDrawsThird(int playerThirdValue) const {
    int bt = bankerHandValue();

    if (playerThirdValue == -1) return bt <= 5;

    switch (bt) {
        case 0: case 1: case 2: return true;
        case 3: return playerThirdValue != 8;
        case 4: return playerThirdValue >= 2 && playerThirdValue <= 7;
        case 5: return playerThirdValue >= 4 && playerThirdValue <= 7;
        case 6: return playerThirdValue == 6 || playerThirdValue == 7;
        default: return false;
    }
}

void BaccaratGame::applyThirdCardRules() {
    if (playerHandValue() >= 8 || bankerHandValue() >= 8) return;

    int playerThirdValue = -1;
    if (playerDrawsThird()) {
        Card third = deck_.dealCard();
        playerThirdValue = third.baccaratValue();
        playerHand_.push_back(third);
    }

    if (bankerDrawsThird(playerThirdValue))
        bankerHand_.push_back(deck_.dealCard());
}

BaccaratGame::Winner BaccaratGame::playHand() {
    clearHands();
    dealInitialCards();
    applyThirdCardRules();

    int pv = playerHandValue();
    int bv = bankerHandValue();

    if (pv > bv) return Winner::PLAYER;
    if (bv > pv) return Winner::BANKER;
    return Winner::TIE;
}

void BaccaratGame::resetShoe() {
    deck_.reset();
}
