#include "Statistics.h"

using Winner = BaccaratGame::Winner;

void Statistics::recordHand(Winner winner, bool natural, bool playerPair, bool bankerPair, double netProfit) {
    ++handsPlayed_;
    totalProfit_ += netProfit;

    if (natural) ++naturals_;
    if (playerPair) ++playerPairs_;
    if (bankerPair) ++bankerPairs_;

    switch (winner) {
        case Winner::PLAYER: ++playerWins_; break;
        case Winner::BANKER: ++bankerWins_; break;
        case Winner::TIE:    ++tieWins_; break;
    }

    if (winner == lastWinner_) {
        ++currentStreak_;
    } else {
        currentStreak_ = 1;
        streakType_ = winner;
        lastWinner_ = winner;
    }

    if (currentStreak_ > longestStreak_)
        longestStreak_ = currentStreak_;
}

void Statistics::reset() {
    handsPlayed_ = playerWins_ = bankerWins_ = tieWins_ = 0;
    naturals_ = playerPairs_ = bankerPairs_ = 0;
    currentStreak_ = longestStreak_ = 0;
    totalProfit_ = 0.0;
    streakType_ = lastWinner_ = Winner::TIE;
}

double Statistics::playerWinPct() const {
    return handsPlayed_ > 0 ? 100.0 * playerWins_ / handsPlayed_ : 0.0;
}

double Statistics::bankerWinPct() const {
    return handsPlayed_ > 0 ? 100.0 * bankerWins_ / handsPlayed_ : 0.0;
}

double Statistics::tieWinPct() const {
    return handsPlayed_ > 0 ? 100.0 * tieWins_ / handsPlayed_ : 0.0;
}
