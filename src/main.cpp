#include <iostream>
#include <thread>
#include <chrono>
#include "BaccaratGame.h"

#ifdef _WIN32
#include <windows.h>
#endif

const std::string RESET = "\033[0m";
const std::string BOLD = "\033[1m";
const std::string GREEN = "\033[92m";
const std::string CYAN = "\033[96m";
const std::string RED = "\033[91m";
const std::string BLUE = "\033[94m";
const std::string GOLD = "\033[33m";

void setupConsole() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    SetConsoleMode(hOut, dwMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
#endif
}

void delay(int ms) {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

void printTitle() {
    std::cout << GOLD << R"(
    ╔═══════════════════════════════════════╗
    ║     🎰  B A C C A R A T  🎰          ║
    ║         ♠ ♥ ♦ ♣                       ║
    ╚═══════════════════════════════════════╝
    )" << RESET << std::endl;
}

void printDealing() {
    std::cout << CYAN << "  Dealing";
    for (int i = 0; i < 3; ++i) {
        std::cout << "." << std::flush;
        delay(300);
    }
    std::cout << RESET << "\n" << std::endl;
}

int main() {
    setupConsole();
    printTitle();

    BaccaratGame game;

    for (int i = 1; i <= 5; ++i) {
        std::cout << BOLD << "  ┌─────────────────────────────────┐" << RESET << std::endl;
        std::cout << BOLD << "  │  Hand #" << i << "                         │" << RESET << std::endl;
        std::cout << BOLD << "  └─────────────────────────────────┘" << RESET << std::endl;

        printDealing();

        BaccaratGame::Winner winner = game.playHand();

        std::cout << "  " << game.getHandSummary();

        std::cout << "\n  " << BOLD << ">>> ";
        switch (winner) {
            case BaccaratGame::Winner::PLAYER:
                std::cout << BLUE << "PLAYER WINS!" << RESET;
                break;
            case BaccaratGame::Winner::BANKER:
                std::cout << RED << "BANKER WINS!" << RESET;
                break;
            case BaccaratGame::Winner::TIE:
                std::cout << GREEN << "TIE GAME!" << RESET;
                break;
        }
        std::cout << BOLD << " <<<" << RESET << "\n" << std::endl;

        delay(500);
    }

    std::cout << GOLD << "  Thanks for playing!\n" << RESET << std::endl;

    return 0;
}
