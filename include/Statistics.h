#ifndef BACCARAT_SIMULATOR_STATISTICS_H
#define BACCARAT_SIMULATOR_STATISTICS_H

#include "BaccaratGame.h"

class Statistics {
public:
    void recordHand(BaccaratGame::Winner winner, bool natural, bool playerPair, bool bankerPair, double netProfit);
    void reset();

    [[nodiscard]] int handsPlayed() const { return handsPlayed_; }
    [[nodiscard]] int playerWins() const { return playerWins_; }
    [[nodiscard]] int bankerWins() const { return bankerWins_; }
    [[nodiscard]] int tieWins() const { return tieWins_; }
    [[nodiscard]] int naturalCount() const { return naturals_; }
    [[nodiscard]] int playerPairCount() const { return playerPairs_; }
    [[nodiscard]] int bankerPairCount() const { return bankerPairs_; }
    [[nodiscard]] int currentStreak() const { return currentStreak_; }
    [[nodiscard]] int longestStreak() const { return longestStreak_; }
    [[nodiscard]] BaccaratGame::Winner streakType() const { return streakType_; }
    [[nodiscard]] double totalProfit() const { return totalProfit_; }

    [[nodiscard]] double playerWinPct() const;
    [[nodiscard]] double bankerWinPct() const;
    [[nodiscard]] double tieWinPct() const;

private:
    int handsPlayed_ = 0;
    int playerWins_ = 0;
    int bankerWins_ = 0;
    int tieWins_ = 0;
    int naturals_ = 0;
    int playerPairs_ = 0;
    int bankerPairs_ = 0;
    int currentStreak_ = 0;
    int longestStreak_ = 0;
    BaccaratGame::Winner streakType_ = BaccaratGame::Winner::TIE;
    BaccaratGame::Winner lastWinner_ = BaccaratGame::Winner::TIE;
    double totalProfit_ = 0.0;
};

#endif
