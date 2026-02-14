#include "Player.h"

Player::Player(double startingBalance) : balance_(startingBalance) {}

void Player::placeBet(BetType type, double amount) {
    currentBetType_ = type;
    currentBet_ = amount;
    balance_ -= amount;
}

double Player::settleBet(BaccaratGame::Winner outcome) {
    double payout = 0.0;

    if (outcome == BaccaratGame::Winner::TIE && currentBetType_ != BetType::TIE) {
        payout = currentBet_;
    } else if (outcome == currentBetType_) {
        switch (currentBetType_) {
            case BetType::PLAYER: payout = currentBet_ * (1.0 + PLAYER_PAYOUT); break;
            case BetType::BANKER: payout = currentBet_ * (1.0 + BANKER_PAYOUT); break;
            case BetType::TIE:   payout = currentBet_ * (1.0 + TIE_PAYOUT); break;
        }
    }

    balance_ += payout;
    double net = payout - currentBet_;
    resetBet();
    return net;
}

void Player::resetBet() {
    currentBet_ = 0.0;
}
