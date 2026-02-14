#include <iostream>
#include <string>
#include <limits>
#include "BaccaratGame.h"
#include "Player.h"
#include "Scoreboard.h"
#include "Statistics.h"
#include "Display.h"

static int readInt() {
    int value;
    if (std::cin >> value) return value;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return -1;
}

static double readDouble() {
    double value;
    if (std::cin >> value) return value;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return -1.0;
}

static BaccaratGame::Winner readBetType() {
    while (true) {
        Display::printBetTypePrompt();
        int choice = readInt();
        switch (choice) {
            case 1: return BaccaratGame::Winner::PLAYER;
            case 2: return BaccaratGame::Winner::BANKER;
            case 3: return BaccaratGame::Winner::TIE;
            default: Display::printInvalidInput();
        }
    }
}

static double readBetAmount(double balance) {
    double maxBet = std::min(balance, Player::maximumBet());
    while (true) {
        Display::printBetAmountPrompt(balance, Player::minimumBet(), maxBet);
        double amount = readDouble();
        if (amount >= Player::minimumBet() && amount <= maxBet) return amount;
        Display::printInvalidInput();
    }
}

static void playHand(BaccaratGame& game, Player& player, Scoreboard& board, Statistics& stats) {
    auto betType = readBetType();
    double betAmount = readBetAmount(player.balance());

    player.placeBet(betType, betAmount);
    Display::printDealing();

    auto winner = game.playHand();
    double net = player.settleBet(winner);

    Display::printGameTable(game, winner, player, net);

    board.recordResult(winner);
    stats.recordHand(winner, game.isNatural(), game.isPlayerPair(), game.isBankerPair(), net);

    if (game.needsNewShoe()) {
        Display::printNewShoe();
        game.resetShoe();
    }
}

int main() {
    Display::setupConsole();

    BaccaratGame game;
    Player player;
    Scoreboard board;
    Statistics stats;

    bool running = true;

    while (running) {
        Display::clearScreen();
        Display::printTitle();
        Display::printBalanceBar(player.balance());
        Display::printMainMenu();

        int choice = readInt();

        switch (choice) {
            case 1:
                if (player.isBroke()) {
                    Display::printBroke();
                    Display::delay(1500);
                } else {
                    playHand(game, player, board, stats);
                    std::cout << "\n    Press Enter to continue...";
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cin.get();
                }
                break;

            case 2:
                Display::clearScreen();
                Display::printScoreboard(board);
                std::cout << "\n    Press Enter to continue...";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin.get();
                break;

            case 3:
                Display::clearScreen();
                Display::printStatistics(stats, player.balance());
                std::cout << "\n    Press Enter to continue...";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin.get();
                break;

            case 4:
                game.resetShoe();
                Display::printNewShoe();
                Display::delay(1000);
                break;

            case 5:
                running = false;
                break;

            default:
                Display::printInvalidInput();
                Display::delay(500);
                break;
        }
    }

    Display::printGoodbye();
    return 0;
}
