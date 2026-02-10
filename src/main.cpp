#include <iostream>
#include "Card.h"
#include "Deck.h"

int main() {
    std::cout << "=== Baccarat Simulator ===" << std::endl;
    std::cout << "Ready to gamble?" << std::endl;

    Deck deck(8);

    std::cout << "Dealing 10 test cards:" << std::endl;
    for (int i = 0; i < 10; ++i) {
        Card card = deck.dealCard();
        std::cout << card.toString() << " (Baccarat value: "
                  << card.getBaccaratValue() << ")" << std::endl;
    }

    return 0;
}
