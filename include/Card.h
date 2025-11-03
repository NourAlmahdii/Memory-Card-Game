#ifndef CARD_H
#define CARD_H

#include <iostream>
using namespace std;

class Card {
private:
    int cardNumber;
    bool faceUp;

public:
    Card();
    Card(int num);
    virtual ~Card();
    void flip();
    void setCardNumber(int number);
    int getCardNumber() const;
    bool isFaceUp() const;
    virtual void display() const;
};

#endif // CARD_H
