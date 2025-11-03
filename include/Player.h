#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <iostream>
using namespace std;
class Player {
private:
    string name;
    int score;

public:
    Player(string pn);
    string getName() const;
    int getScore() const;
    void increaseScore(int points);
    void decreaseScore(int points);
    void displayScore() const;
};

#endif // PLAYER_H
