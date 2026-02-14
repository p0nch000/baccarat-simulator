#include "Display.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <thread>
#include <chrono>

#ifdef _WIN32
#include <windows.h>
#endif

namespace Display {

const std::string Colors::RESET     = "\033[0m";
const std::string Colors::BOLD      = "\033[1m";
const std::string Colors::DIM       = "\033[2m";
const std::string Colors::RED       = "\033[91m";
const std::string Colors::GREEN     = "\033[92m";
const std::string Colors::BLUE      = "\033[94m";
const std::string Colors::CYAN      = "\033[96m";
const std::string Colors::GOLD      = "\033[33m";
const std::string Colors::WHITE     = "\033[97m";
const std::string Colors::BG_GREEN  = "\033[42m";
const std::string Colors::UNDERLINE = "\033[4m";

void setupConsole() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    SetConsoleMode(hOut, dwMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
#endif
}

void clearScreen() {
    std::cout << "\033[2J\033[H" << std::flush;
}

void delay(int ms) {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

void printTitle() {
    std::cout << Colors::GOLD << R"(
    ╔══════════════════════════════════════════════════════╗
    ║                                                      ║
    ║            ♠  B A C C A R A T  ♠                     ║
    ║                   ♥ ♦ ♣ ♠                            ║
    ║                                                      ║
    ╚══════════════════════════════════════════════════════╝
    )" << Colors::RESET << "\n";
}

void printMainMenu() {
    std::cout << Colors::BOLD << Colors::WHITE;
    std::cout << "    \u250c\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2510\n";
    std::cout << "    \u2502  [1]  Play Hand              \u2502\n";
    std::cout << "    \u2502  [2]  View Scoreboard        \u2502\n";
    std::cout << "    \u2502  [3]  View Statistics        \u2502\n";
    std::cout << "    \u2502  [4]  New Shoe               \u2502\n";
    std::cout << "    \u2502  [5]  Quit                   \u2502\n";
    std::cout << "    \u2514\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2518\n";
    std::cout << Colors::RESET;
    std::cout << "\n    " << Colors::DIM << "Select: " << Colors::RESET;
}

void printBetTypePrompt() {
    std::cout << "\n";
    std::cout << "    " << Colors::BOLD << "Place your bet:" << Colors::RESET << "\n";
    std::cout << "    " << Colors::BLUE << "[1] PLAYER" << Colors::RESET
              << "  " << Colors::RED << "[2] BANKER" << Colors::RESET
              << "  " << Colors::GREEN << "[3] TIE" << Colors::RESET << "\n";
    std::cout << "    " << Colors::DIM << "Select: " << Colors::RESET;
}

void printBetAmountPrompt(double balance, double minBet, double maxBet) {
    std::cout << "\n    " << Colors::DIM << "Balance: " << Colors::RESET
              << Colors::GOLD << "$" << std::fixed << std::setprecision(0) << balance << Colors::RESET << "\n";
    std::cout << "    " << Colors::DIM << "Min: $" << std::setprecision(0) << minBet
              << "  Max: $" << std::setprecision(0) << maxBet << Colors::RESET << "\n";
    std::cout << "    " << Colors::DIM << "Amount: $" << Colors::RESET;
}

void printDealing() {
    std::cout << "\n    " << Colors::CYAN << "Dealing";
    for (int i = 0; i < 3; ++i) {
        std::cout << "." << std::flush;
        delay(250);
    }
    std::cout << Colors::RESET << "\n";
}

static std::string suitColor(Card::Suit suit) {
    if (suit == Card::Suit::HEARTS || suit == Card::Suit::DIAMONDS)
        return Colors::RED;
    return Colors::WHITE;
}

void printCardArt(const std::vector<Card>& hand, const std::string& labelColor) {
    std::string tops, midRank, midSuit, bottoms;

    for (const auto& card : hand) {
        std::string sc = suitColor(card.suit());
        std::string r = card.rankSymbol();
        std::string s = card.suitSymbol();

        tops += sc + "\u250c\u2500\u2500\u2500\u2510" + Colors::RESET + " ";

        std::string rankPad = r.size() > 1 ? "" : " ";
        midRank += sc + "\u2502" + Colors::RESET + Colors::BOLD + r + rankPad + sc + " \u2502" + Colors::RESET + " ";
        midSuit += sc + "\u2502 " + Colors::RESET + sc + s + sc + " \u2502" + Colors::RESET + " ";
        bottoms += sc + "\u2514\u2500\u2500\u2500\u2518" + Colors::RESET + " ";
    }

    std::cout << "    " << tops << "\n";
    std::cout << "    " << midRank << "\n";
    std::cout << "    " << midSuit << "\n";
    std::cout << "    " << bottoms << "\n";
}

void printGameTable(const BaccaratGame& game, BaccaratGame::Winner winner,
                    const Player& player, double netProfit) {
    std::string border = Colors::DIM + Colors::GOLD;

    std::cout << "\n";
    std::cout << "    " << border << "\u250c\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u252c\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2510" << Colors::RESET << "\n";

    std::cout << "    " << border << "\u2502" << Colors::RESET
              << Colors::BLUE << Colors::BOLD << " PLAYER ["
              << game.playerHandValue() << "]" << Colors::RESET;
    int pPad = 16 - 10;
    for (int i = 0; i < pPad; ++i) std::cout << " ";
    std::cout << border << "\u2502" << Colors::RESET
              << Colors::RED << Colors::BOLD << " BANKER ["
              << game.bankerHandValue() << "]" << Colors::RESET;
    int bPad = 16 - 10;
    for (int i = 0; i < bPad; ++i) std::cout << " ";
    std::cout << border << "\u2502" << Colors::RESET << "\n";

    std::cout << "    " << border << "\u2502" << Colors::RESET << " ";

    auto ph = game.playerHand();
    for (const auto& c : ph) {
        std::string sc = suitColor(c.suit());
        std::string r = c.rankSymbol();
        std::string pad = r.size() > 1 ? "" : " ";
        std::cout << sc << "[" << Colors::BOLD << r << pad << c.suitSymbol() << Colors::RESET << sc << "]" << Colors::RESET;
    }
    int pCardSpace = 25 - static_cast<int>(ph.size()) * 5;
    for (int i = 0; i < pCardSpace; ++i) std::cout << " ";

    std::cout << border << "\u2502" << Colors::RESET << " ";

    auto bh = game.bankerHand();
    for (const auto& c : bh) {
        std::string sc = suitColor(c.suit());
        std::string r = c.rankSymbol();
        std::string pad = r.size() > 1 ? "" : " ";
        std::cout << sc << "[" << Colors::BOLD << r << pad << c.suitSymbol() << Colors::RESET << sc << "]" << Colors::RESET;
    }
    int bCardSpace = 25 - static_cast<int>(bh.size()) * 5;
    for (int i = 0; i < bCardSpace; ++i) std::cout << " ";

    std::cout << border << "\u2502" << Colors::RESET << "\n";

    std::cout << "    " << border << "\u251c\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2534\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2524" << Colors::RESET << "\n";

    std::string winnerStr;
    std::string winnerColor;
    switch (winner) {
        case BaccaratGame::Winner::PLAYER:
            winnerStr = "PLAYER WINS!";
            winnerColor = Colors::BLUE;
            break;
        case BaccaratGame::Winner::BANKER:
            winnerStr = "BANKER WINS!";
            winnerColor = Colors::RED;
            break;
        case BaccaratGame::Winner::TIE:
            winnerStr = "TIE GAME!";
            winnerColor = Colors::GREEN;
            break;
    }

    if (game.isNatural())
        winnerStr += " (NATURAL)";

    std::cout << "    " << border << "\u2502" << Colors::RESET
              << " " << Colors::BOLD << "\u00bb " << winnerColor << winnerStr << Colors::RESET;

    std::ostringstream profitStr;
    if (netProfit > 0)
        profitStr << Colors::GREEN << "+" << std::fixed << std::setprecision(0) << netProfit;
    else if (netProfit < 0)
        profitStr << Colors::RED << std::fixed << std::setprecision(0) << netProfit;
    else
        profitStr << Colors::DIM << "0";

    int resultLen = static_cast<int>(winnerStr.size()) + 4;
    int rightPad = 52 - resultLen;

    std::ostringstream balStr;
    balStr << "$" << std::fixed << std::setprecision(0) << player.balance();
    std::string balanceText = profitStr.str() + Colors::RESET + " " + Colors::GOLD + balStr.str() + Colors::RESET;

    int visibleProfitLen = 0;
    if (netProfit != 0) {
        std::ostringstream tmp;
        tmp << std::fixed << std::setprecision(0) << (netProfit > 0 ? netProfit : -netProfit);
        visibleProfitLen = static_cast<int>(tmp.str().size()) + 1;
    } else {
        visibleProfitLen = 1;
    }
    int visibleBalLen = static_cast<int>(balStr.str().size());
    int spacesNeeded = rightPad - visibleProfitLen - visibleBalLen - 2;
    if (spacesNeeded < 1) spacesNeeded = 1;

    for (int i = 0; i < spacesNeeded; ++i) std::cout << " ";
    std::cout << balanceText;
    std::cout << " " << border << "\u2502" << Colors::RESET << "\n";

    std::cout << "    " << border << "\u2514\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2518" << Colors::RESET << "\n";
}

void printScoreboard(const Scoreboard& board) {
    std::cout << "\n";
    auto bigRoad = board.renderBigRoad();
    for (auto& line : bigRoad)
        std::cout << "    " << line << "\n";

    std::cout << "\n";
    auto beadPlate = board.renderBeadPlate();
    for (auto& line : beadPlate)
        std::cout << "    " << line << "\n";

    std::cout << "\n    " << Colors::DIM << "Hands: " << board.totalHands()
              << "  " << Colors::BLUE << "●" << Colors::RESET << Colors::DIM << "=Player  "
              << Colors::RED << "●" << Colors::RESET << Colors::DIM << "=Banker  "
              << Colors::GREEN << "T" << Colors::RESET << Colors::DIM << "=Tie" << Colors::RESET << "\n";
}

void printStatistics(const Statistics& stats, double balance) {
    std::string border = Colors::DIM;

    std::cout << "\n";
    std::cout << "    " << border << "\u250c\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2510" << Colors::RESET << "\n";
    std::cout << "    " << border << "\u2502" << Colors::RESET << Colors::BOLD << "         SESSION STATISTICS         " << border << "\u2502" << Colors::RESET << "\n";
    std::cout << "    " << border << "\u251c\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2524" << Colors::RESET << "\n";

    auto printRow = [&](const std::string& label, const std::string& value) {
        std::cout << "    " << border << "\u2502" << Colors::RESET << " "
                  << std::left << std::setw(20) << label
                  << std::right << std::setw(14) << value
                  << " " << border << "\u2502" << Colors::RESET << "\n";
    };

    std::ostringstream oss;
    printRow("Hands Played", std::to_string(stats.handsPlayed()));

    oss.str(""); oss << stats.playerWins() << " (" << std::fixed << std::setprecision(1) << stats.playerWinPct() << "%)";
    printRow("Player Wins", oss.str());

    oss.str(""); oss << stats.bankerWins() << " (" << std::fixed << std::setprecision(1) << stats.bankerWinPct() << "%)";
    printRow("Banker Wins", oss.str());

    oss.str(""); oss << stats.tieWins() << " (" << std::fixed << std::setprecision(1) << stats.tieWinPct() << "%)";
    printRow("Ties", oss.str());

    std::cout << "    " << border << "\u251c\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2524" << Colors::RESET << "\n";

    printRow("Naturals", std::to_string(stats.naturalCount()));
    printRow("Player Pairs", std::to_string(stats.playerPairCount()));
    printRow("Banker Pairs", std::to_string(stats.bankerPairCount()));

    oss.str("");
    if (stats.currentStreak() > 0) {
        std::string streakLabel;
        switch (stats.streakType()) {
            case BaccaratGame::Winner::PLAYER: streakLabel = "P"; break;
            case BaccaratGame::Winner::BANKER: streakLabel = "B"; break;
            case BaccaratGame::Winner::TIE:    streakLabel = "T"; break;
        }
        oss << stats.currentStreak() << "x " << streakLabel;
    } else {
        oss << "-";
    }
    printRow("Current Streak", oss.str());
    printRow("Longest Streak", std::to_string(stats.longestStreak()));

    std::cout << "    " << border << "\u251c\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2524" << Colors::RESET << "\n";

    oss.str("");
    if (stats.totalProfit() >= 0)
        oss << Colors::GREEN << "+$" << std::fixed << std::setprecision(0) << stats.totalProfit() << Colors::RESET;
    else
        oss << Colors::RED << "-$" << std::fixed << std::setprecision(0) << -stats.totalProfit() << Colors::RESET;
    printRow("Net Profit", oss.str());

    oss.str(""); oss << Colors::GOLD << "$" << std::fixed << std::setprecision(0) << balance << Colors::RESET;
    printRow("Balance", oss.str());

    std::cout << "    " << border << "\u2514\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2518" << Colors::RESET << "\n";
}

void printBalanceBar(double balance) {
    std::cout << "\n    " << Colors::DIM << "Balance: " << Colors::RESET
              << Colors::GOLD << Colors::BOLD << "$" << std::fixed << std::setprecision(0) << balance
              << Colors::RESET << "\n";
}

void printBroke() {
    std::cout << "\n    " << Colors::RED << Colors::BOLD
              << "RUN TO THE ATM BROKIE" << Colors::RESET << "\n";
}

void printGoodbye() {
    std::cout << "\n    " << Colors::GOLD << "Thank you for gambling your life savings!" << Colors::RESET << "\n\n";
}

void printNewShoe() {
    std::cout << "\n    " << Colors::CYAN << "Shuffling new shoe..." << Colors::RESET;
    delay(500);
    std::cout << " " << Colors::GREEN << "Ready!" << Colors::RESET << "\n";
}

void printInvalidInput() {
    std::cout << "    " << Colors::RED << "Invalid input." << Colors::RESET << "\n";
}

}
