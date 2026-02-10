#include "BaccaratGame.h"
#include <sstream>
#include <iomanip>

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

int BaccaratGame::calculateHandValue(const std::vector<Card>& hand) const {
    int total = 0;
    for (const auto& card : hand) {
        total += card.getBaccaratValue();
    }
    return total % 10;
}

int BaccaratGame::getPlayerHandValue() const {
    return calculateHandValue(playerHand_);
}

int BaccaratGame::getBankerHandValue() const {
    return calculateHandValue(bankerHand_);
}

bool BaccaratGame::playerDrawsThirdCard() const {
    int playerTotal = getPlayerHandValue();
    return playerTotal <= 5;
}

bool BaccaratGame::bankerDrawsThirdCard(int playerThirdCardValue) const {
    int bankerTotal = getBankerHandValue();

    if (playerThirdCardValue == -1) {
        return bankerTotal <= 5;
    }

    switch (bankerTotal) {
        case 0:
        case 1:
        case 2:
            return true;
        case 3:
            return playerThirdCardValue != 8;
        case 4:
            return playerThirdCardValue >= 2 && playerThirdCardValue <= 7;
        case 5:
            return playerThirdCardValue >= 4 && playerThirdCardValue <= 7;
        case 6:
            return playerThirdCardValue == 6 || playerThirdCardValue == 7;
        case 7:
            return false;
        default:
            return false;
    }
}

void BaccaratGame::applyThirdCardRules() {
    int playerTotal = getPlayerHandValue();
    int bankerTotal = getBankerHandValue();

    if (playerTotal >= 8 || bankerTotal >= 8) {
        return;
    }

    // Player's turn
    int playerThirdCardValue = -1;
    if (playerDrawsThirdCard()) {
        Card playerThirdCard = deck_.dealCard();
        playerThirdCardValue = playerThirdCard.getBaccaratValue();
        playerHand_.push_back(playerThirdCard);
    }

    // Banker's turn
    if (bankerDrawsThirdCard(playerThirdCardValue)) {
        bankerHand_.push_back(deck_.dealCard());
    }
}

BaccaratGame:: Winner BaccaratGame::playHand() {
    clearHands();
    dealInitialCards();
    applyThirdCardRules();

    int playerTotal = getPlayerHandValue();
    int bankerTotal = getBankerHandValue();

    if (playerTotal > bankerTotal) {
        return Winner::PLAYER;
    } else if (bankerTotal > playerTotal) {
        return Winner::BANKER;
    } else {
        return Winner::TIE;
    }
}

std::string BaccaratGame::getHandSummary() const {
    std::ostringstream oss;

    oss << "PLAYER:  ";
    for (const auto& card : playerHand_) {
        oss << card.toString() << " ";
    }
    oss << std::setw(12 - playerHand_.size() * 4) << "" << "= " << getPlayerHandValue() << "\n";

    oss << "  BANKER:  ";
    for (const auto& card : bankerHand_) {
        oss << card.toString() << " ";
    }
    oss << std::setw(12 - bankerHand_.size() * 4) << "" << "= " << getBankerHandValue();

    return oss.str();
}
