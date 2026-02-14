#ifndef BACCARAT_SIMULATOR_DISPLAY_H
#define BACCARAT_SIMULATOR_DISPLAY_H

#include "Card.h"
#include "BaccaratGame.h"
#include "Player.h"
#include "Scoreboard.h"
#include "Statistics.h"
#include <vector>
#include <string>

namespace Display {

    struct Colors {
        static const std::string RESET;
        static const std::string BOLD;
        static const std::string DIM;
        static const std::string RED;
        static const std::string GREEN;
        static const std::string BLUE;
        static const std::string CYAN;
        static const std::string GOLD;
        static const std::string WHITE;
        static const std::string BG_GREEN;
        static const std::string UNDERLINE;
    };

    void setupConsole();
    void clearScreen();
    void delay(int ms);

    void printTitle();
    void printMainMenu();
    void printBetTypePrompt();
    void printBetAmountPrompt(double balance, double minBet, double maxBet);
    void printDealing();

    void printGameTable(const BaccaratGame& game, BaccaratGame::Winner winner,
                        const Player& player, double netProfit);
    void printCardArt(const std::vector<Card>& hand, const std::string& color);
    void printScoreboard(const Scoreboard& board);
    void printStatistics(const Statistics& stats, double balance);
    void printBalanceBar(double balance);
    void printBroke();
    void printGoodbye();
    void printNewShoe();
    void printInvalidInput();

}

#endif
