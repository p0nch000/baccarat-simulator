#ifndef BACCARAT_SIMULATOR_PLAYER_H
#define BACCARAT_SIMULATOR_PLAYER_H

#include "BaccaratGame.h"

class Player {
public:
    using BetType = BaccaratGame::Winner;

    explicit Player(double startingBalance = 1000.0);

    void placeBet(BetType type, double amount);
    double settleBet(BaccaratGame::Winner outcome);
    void resetBet();

    [[nodiscard]] double balance() const { return balance_; }
    [[nodiscard]] double currentBet() const { return currentBet_; }
    [[nodiscard]] BetType currentBetType() const { return currentBetType_; }
    [[nodiscard]] bool hasBet() const { return currentBet_ > 0; }
    [[nodiscard]] bool isBroke() const { return balance_ < minimumBet(); }

    static constexpr double minimumBet() { return 10.0; }
    static constexpr double maximumBet() { return 10000.0; }

    static constexpr double PLAYER_PAYOUT = 1.0;
    static constexpr double BANKER_PAYOUT = 0.95;
    static constexpr double TIE_PAYOUT = 8.0;

private:
    double balance_;
    double currentBet_ = 0.0;
    BetType currentBetType_ = BetType::PLAYER;
};

#endif
