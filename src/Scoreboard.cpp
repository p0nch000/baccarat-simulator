#include "Scoreboard.h"

using Winner = BaccaratGame::Winner;

void Scoreboard::recordResult(Winner result) {
    history_.push_back(result);
}

void Scoreboard::clear() {
    history_.clear();
}

std::vector<std::vector<Scoreboard::BigRoadEntry>> Scoreboard::buildBigRoadColumns() const {
    std::vector<std::vector<BigRoadEntry>> columns;

    Winner lastNonTie = Winner::TIE;

    for (auto result : history_) {
        if (result == Winner::TIE) {
            if (!columns.empty() && !columns.back().empty())
                columns.back().back().hasTie = true;
            continue;
        }

        if (columns.empty() || result != lastNonTie) {
            columns.push_back({{result, false}});
        } else {
            columns.back().push_back({result, false});
        }
        lastNonTie = result;
    }

    return columns;
}

std::vector<std::string> Scoreboard::renderBigRoad() const {
    auto columns = buildBigRoadColumns();

    char grid[ROAD_ROWS][ROAD_COLS];
    bool tieGrid[ROAD_ROWS][ROAD_COLS];
    for (int r = 0; r < ROAD_ROWS; ++r)
        for (int c = 0; c < ROAD_COLS; ++c) {
            grid[r][c] = ' ';
            tieGrid[r][c] = false;
        }

    int startCol = 0;
    if (static_cast<int>(columns.size()) > ROAD_COLS) {
        startCol = static_cast<int>(columns.size()) - ROAD_COLS;
    }

    for (int ci = startCol; ci < static_cast<int>(columns.size()); ++ci) {
        int col = ci - startCol;
        if (col >= ROAD_COLS) break;

        auto& entries = columns[ci];
        for (int ri = 0; ri < static_cast<int>(entries.size()) && ri < ROAD_ROWS; ++ri) {
            grid[ri][col] = entries[ri].winner == Winner::PLAYER ? 'P' : 'B';
            tieGrid[ri][col] = entries[ri].hasTie;
        }
    }

    std::string blue = "\033[94m";
    std::string red = "\033[91m";
    std::string green = "\033[92m";
    std::string reset = "\033[0m";
    std::string dim = "\033[2m";

    std::vector<std::string> lines;
    std::string top = dim + "\u250c\u2500 BIG ROAD ";
    for (int i = 0; i < ROAD_COLS * 3 - 9; ++i) top += "\u2500";
    top += "\u2510" + reset;
    lines.push_back(top);

    for (int r = 0; r < ROAD_ROWS; ++r) {
        std::string row = dim + "\u2502" + reset;
        for (int c = 0; c < ROAD_COLS; ++c) {
            if (grid[r][c] == 'P') {
                row += blue + " \u25cf" + reset;
                row += tieGrid[r][c] ? green + "/" + reset : " ";
            } else if (grid[r][c] == 'B') {
                row += red + " \u25cf" + reset;
                row += tieGrid[r][c] ? green + "/" + reset : " ";
            } else {
                row += "   ";
            }
        }
        row += dim + "\u2502" + reset;
        lines.push_back(row);
    }

    std::string bottom = dim + "\u2514";
    for (int i = 0; i < ROAD_COLS * 3 + 1; ++i) bottom += "\u2500";
    bottom += "\u2518" + reset;
    lines.push_back(bottom);

    return lines;
}

std::vector<std::string> Scoreboard::renderBeadPlate() const {
    char grid[BEAD_ROWS][BEAD_COLS];
    for (int r = 0; r < BEAD_ROWS; ++r)
        for (int c = 0; c < BEAD_COLS; ++c)
            grid[r][c] = ' ';

    int startIdx = 0;
    int maxBeads = BEAD_ROWS * BEAD_COLS;
    if (static_cast<int>(history_.size()) > maxBeads)
        startIdx = static_cast<int>(history_.size()) - maxBeads;

    int idx = 0;
    for (int i = startIdx; i < static_cast<int>(history_.size()); ++i) {
        int col = idx / BEAD_ROWS;
        int row = idx % BEAD_ROWS;
        if (col >= BEAD_COLS) break;

        switch (history_[i]) {
            case Winner::PLAYER: grid[row][col] = 'P'; break;
            case Winner::BANKER: grid[row][col] = 'B'; break;
            case Winner::TIE:    grid[row][col] = 'T'; break;
        }
        ++idx;
    }

    std::string blue = "\033[94m";
    std::string red = "\033[91m";
    std::string green = "\033[92m";
    std::string reset = "\033[0m";
    std::string dim = "\033[2m";

    std::vector<std::string> lines;
    std::string top = dim + "\u250c\u2500 BEAD PLATE ";
    for (int i = 0; i < BEAD_COLS * 3 - 11; ++i) top += "\u2500";
    top += "\u2510" + reset;
    lines.push_back(top);

    for (int r = 0; r < BEAD_ROWS; ++r) {
        std::string row = dim + "\u2502" + reset;
        for (int c = 0; c < BEAD_COLS; ++c) {
            if (grid[r][c] == 'P')      row += blue + " P" + reset + " ";
            else if (grid[r][c] == 'B') row += red + " B" + reset + " ";
            else if (grid[r][c] == 'T') row += green + " T" + reset + " ";
            else                         row += " \u00b7 ";
        }
        row += dim + "\u2502" + reset;
        lines.push_back(row);
    }

    std::string bottom = dim + "\u2514";
    for (int i = 0; i < BEAD_COLS * 3 + 1; ++i) bottom += "\u2500";
    bottom += "\u2518" + reset;
    lines.push_back(bottom);

    return lines;
}
