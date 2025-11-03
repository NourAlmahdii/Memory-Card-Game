#ifndef DECK_H
#define DECK_H

#include "Card.h"

class Deck {
private:
    Card** cards;
    int size;

public:
     Deck(int s);
    ~Deck();
    void shuffle();
    void displayGrid() const;
    void turn(Player& player);
    bool allCardsMatched() const;
    Card** getCard() const { return cards; }
};

#endif // DECK_H
