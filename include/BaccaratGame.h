#ifndef BACCARAT_SIMULATOR_BACCARATGAME_H
#define BACCARAT_SIMULATOR_BACCARATGAME_H

#include "Card.h"
#include "Deck.h"
#include <vector>

class BaccaratGame {
public:
    enum class Winner { PLAYER, BANKER, TIE };

    BaccaratGame();

    Winner playHand();
    void resetShoe();

    [[nodiscard]] int playerHandValue() const;
    [[nodiscard]] int bankerHandValue() const;
    [[nodiscard]] const std::vector<Card>& playerHand() const { return playerHand_; }
    [[nodiscard]] const std::vector<Card>& bankerHand() const { return bankerHand_; }
    [[nodiscard]] bool isNatural() const;
    [[nodiscard]] bool isPlayerPair() const;
    [[nodiscard]] bool isBankerPair() const;
    [[nodiscard]] bool needsNewShoe() const { return deck_.needsReshuffle(); }

private:
    Deck deck_;
    std::vector<Card> playerHand_;
    std::vector<Card> bankerHand_;

    void clearHands();
    void dealInitialCards();
    void applyThirdCardRules();
    [[nodiscard]] int handValue(const std::vector<Card>& hand) const;
    [[nodiscard]] bool playerDrawsThird() const;
    [[nodiscard]] bool bankerDrawsThird(int playerThirdValue) const;
};

#endif
