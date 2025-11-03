#ifndef GAME_H
#define GAME_H

#include "Deck.h"
#include "Player.h"

class Game {
private:
    Deck deck;
    Player player1, player2;
    bool player1Turn;

public:
    Game(string p1Name, string p2Name);
    void play();
};

#endif // GAME_H
