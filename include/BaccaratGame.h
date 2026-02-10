#ifndef BACCARAT_SIMULATOR_BACCARATGAME_H
#define BACCARAT_SIMULATOR_BACCARATGAME_H

#include "Card.h"
#include "Deck.h"
#include <vector>
#include <string>

class BaccaratGame {
public:
    enum class Winner {
        PLAYER,
        BANKER,
        TIE
    };

    BaccaratGame();

    Winner playHand();

    int getPlayerHandValue() const;
    int getBankerHandValue() const;

    std::vector<Card> getPlayerHand() const { return playerHand_; }
    std::vector<Card> getBankerHand() const { return bankerHand_; }

    std::string getHandSummary() const;

    bool needsNewShoe() const { return deck_.needsReshuffle(); }

private:
    Deck deck_;
    std::vector<Card> playerHand_;
    std::vector<Card> bankerHand_;

    void clearHands();
    void dealInitialCards();
    void applyThirdCardRules();
    int calculateHandValue(const std::vector<Card>& hand) const;

    bool playerDrawsThirdCard() const;
    bool bankerDrawsThirdCard(int playerThirdCardValue) const;
};

#endif //BACCARAT_SIMULATOR_BACCARATGAME_H