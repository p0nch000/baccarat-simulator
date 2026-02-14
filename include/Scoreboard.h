#ifndef BACCARAT_SIMULATOR_SCOREBOARD_H
#define BACCARAT_SIMULATOR_SCOREBOARD_H

#include "BaccaratGame.h"
#include <vector>
#include <string>

class Scoreboard {
public:
    static constexpr int ROAD_ROWS = 6;
    static constexpr int ROAD_COLS = 20;
    static constexpr int BEAD_ROWS = 6;
    static constexpr int BEAD_COLS = 12;

    void recordResult(BaccaratGame::Winner result);
    void clear();

    [[nodiscard]] const std::vector<BaccaratGame::Winner>& history() const { return history_; }
    [[nodiscard]] std::vector<std::string> renderBigRoad() const;
    [[nodiscard]] std::vector<std::string> renderBeadPlate() const;
    [[nodiscard]] size_t totalHands() const { return history_.size(); }

private:
    std::vector<BaccaratGame::Winner> history_;

    struct BigRoadEntry {
        BaccaratGame::Winner winner;
        bool hasTie = false;
    };

    [[nodiscard]] std::vector<std::vector<BigRoadEntry>> buildBigRoadColumns() const;
};

#endif
