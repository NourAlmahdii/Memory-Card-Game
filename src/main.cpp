#include <iostream>
#include <limits>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <vector>
#include <algorithm>

using namespace std;

const int gridSize = 16;

class Card {
protected:
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

Card::Card() : cardNumber(0), faceUp(false) {}

Card::Card(int num) : cardNumber(num), faceUp(false) {}

Card::~Card() {}

void Card::flip() { faceUp = !faceUp; }

void Card::setCardNumber(int number) { cardNumber = number; }

int Card::getCardNumber() const { return cardNumber; }

bool Card::isFaceUp() const { return faceUp; }

void Card::display() const {
    if (faceUp)
        cout << cardNumber << "   ";
    else
        cout << " * ";
}

class StandardCard : public Card {
public:
    StandardCard(int num) : Card(num) {}
};

class BonusCard : public Card {
public:
    BonusCard(int num) : Card(num) {}
};

class PenaltyCard : public Card {
public:
    PenaltyCard(int num) : Card(num) {}
};

class Player {
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

Player::Player(string pn) : name(pn), score(0) {}

string Player::getName() const { return name; }

int Player::getScore() const { return score; }

void Player::increaseScore(int points) { score += points; }

void Player::decreaseScore(int points) { score -= points; }

void Player::displayScore() const { cout << name << ": " << score << " points" << endl; }

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

Deck::Deck(int s) : size(s) {
    vector<int> numbers;

    // Generate pairs of numbers for StandardCards (1 to 8)
    for (int i = 1; i <= (size - 4) / 2; i++) {
        numbers.push_back(i);
        numbers.push_back(i);
    }

    // Add 2 BonusCards (value 7) and 2 PenaltyCards (value 8)
    numbers.push_back(7);
    numbers.push_back(7);
    numbers.push_back(8);
    numbers.push_back(8);

    // Shuffle the numbers
    random_shuffle(numbers.begin(), numbers.end());

    // Allocate memory for the cards
    cards = new Card*[size];
    for (int i = 0; i < size; i++) {
        if (numbers[i] == 7)
            cards[i] = new BonusCard(numbers[i]);
        else if (numbers[i] == 8)
            cards[i] = new PenaltyCard(numbers[i]);
        else
            cards[i] = new StandardCard(numbers[i]);
    }

    shuffle();
}


Deck::~Deck() {
    for (int i = 0; i < size; i++)
        delete cards[i];
    delete[] cards;
}

void Deck::shuffle() {
    for (int i = 0; i < size; i++) {
        int j = rand() % size;
        swap(cards[i], cards[j]);
    }
}


void Deck::displayGrid() const {
    const int width = 5;
    cout << "     1    2    3    4\n"
         << "  ---------------------\n";

    for (int i = 0; i < 4; i++) {
        cout << i + 1 << "|";

        for (int j = 0; j < 4; j++) {
            int idx = i * 4 + j;
            if (cards[idx] != nullptr) {
                if (cards[idx]->isFaceUp()) {
                    cout << setw(width) << cards[idx]->getCardNumber();
                } else {
                    cout << setw(width) << "*";
                }
            } else {
                cout << setw(width) << " ";
            }
        }
        cout << endl;
    }
}

bool Deck::allCardsMatched() const {
    for (int i = 0; i < size; i++) {
        if (cards[i] != nullptr)
            return false;
    }
    return true;
}

bool isValidCoordinate(int x, int y) {
    return x >= 1 && x <= 4 && y >= 1 && y <= 4;
}

void Deck::turn(Player& player) {
    bool extraTurn = false;

    do {
        int x1, y1, x2, y2;
        char comma;
        extraTurn = false;

        cout << player.getName() << "'s turn!" << endl;

        int idx1, idx2;

        // Choose first card
        while (true) {
            cout << "Enter coordinates of the first card (x,y): ";
            cin >> x1 >> comma >> y1;

            if (cin.fail() || comma != ',' || !isValidCoordinate(x1, y1)) {
                cin.clear(); // Clear error flags
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Try again!" << endl;
                continue;
            }

            idx1 = (x1 - 1) * 4 + (y1 - 1);

            if (cards[idx1] != nullptr && !cards[idx1]->isFaceUp()) {
                cards[idx1]->flip();
                break;
            } else {
                cout << "Card already flipped or invalid. Choose again." << endl;
            }
        }
        displayGrid();

        // Choose second card
        while (true) {
            cout << "Enter coordinates of the second card (x,y): ";
            cin >> x2 >> comma >> y2;

            if (cin.fail() || comma != ',' || !isValidCoordinate(x2, y2)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Try again!" << endl;
                continue;
            }

            idx2 = (x2 - 1) * 4 + (y2 - 1);

            if (cards[idx2] != nullptr && !cards[idx2]->isFaceUp() && idx1 != idx2) {
                cards[idx2]->flip();
                break;
            } else {
                cout << "Card already flipped or invalid. Choose again." << endl;
            }
        }
        displayGrid();

        int card1Value = cards[idx1]->getCardNumber();
        int card2Value = cards[idx2]->getCardNumber();

        // Matching logic
        if (card1Value == card2Value && card1Value != 7 && card1Value != 8) {
            // Standard Card Match
            cout << "It's a match! +1 point" << endl;
            player.increaseScore(1);
            delete cards[idx1];
            delete cards[idx2];
            cards[idx1] = nullptr;
            cards[idx2] = nullptr;
            extraTurn = true;
        } else if (card1Value == 7 && card2Value == 7) {
            // Both Bonus Cards
            cout << "Two Bonus Cards revealed! Choose an option:\n";
            cout << "1) Gain 2 points\n2) Gain 1 point and take another turn" << endl;
            int choice;
            cin >> choice;

            if (choice == 1) {
                player.increaseScore(2);
            } else {
                player.increaseScore(1);
                extraTurn = true;
            }
            delete cards[idx1];
            delete cards[idx2];
            cards[idx1] = nullptr;
            cards[idx2] = nullptr;
        } else if (card1Value == 8 && card2Value == 8) {
            // Both Penalty Cards
            cout << "Two Penalty Cards revealed! Choose an option:\n";
            cout << "1) Lose 2 points\n2) Lose 1 point and skip the next turn" << endl;
            int choice;
            cin >> choice;

            if (choice == 1) {
                player.decreaseScore(2);
            } else {
                player.decreaseScore(1);
                return; // Skip the next turn
            }
            delete cards[idx1];
            delete cards[idx2];
            cards[idx1] = nullptr;
            cards[idx2] = nullptr;
        } else if ((card1Value == 7 && card2Value != 8) || (card2Value == 7 && card1Value != 8)) {
            // One Bonus Card and one Standard Card
            cout << "A Bonus Card and a Standard Card revealed! +1 point." << endl;
            player.increaseScore(1);
            if (card1Value == 7) {
                delete cards[idx1];
                cards[idx1] = nullptr;
                cards[idx2]->flip(); // Keep Standard Card hidden
            } else {
                delete cards[idx2];
                cards[idx2] = nullptr;
                cards[idx1]->flip(); // Keep Standard Card hidden
            }
        } else if ((card1Value == 8 && card2Value != 7) || (card2Value == 8 && card1Value != 7)) {
            // One Penalty Card and one Standard Card
            cout << "A Penalty Card and a Standard Card revealed! Lose 1 point." << endl;
            player.decreaseScore(1);
            if (card1Value == 8) {
                delete cards[idx1];
                cards[idx1] = nullptr;
                cards[idx2]->flip(); // Keep Standard Card hidden
            } else {
                delete cards[idx2];
                cards[idx2] = nullptr;
                cards[idx1]->flip(); // Keep Standard Card hidden
            }
        } else if ((card1Value == 7 && card2Value == 8) || (card1Value == 8 && card2Value == 7)) {
            // One Bonus Card and one Penalty Card
            cout << "A Bonus Card and a Penalty Card revealed! No effect on the game." << endl;
            delete cards[idx1];
            delete cards[idx2];
            cards[idx1] = nullptr;
            cards[idx2] = nullptr;
        } else {
            // Not a match
            cout << "Not a match. Cards will be flipped back." << endl;
            cards[idx1]->flip();
            cards[idx2]->flip();
        }

        // Show updated scores after the turn
        cout << "\nUpdated Scores:\n";
        player.displayScore();

        if (!extraTurn) {
            cout << "\nPress Enter to hide the cards and switch turns..." << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
            cin.get(); // Wait for Enter key
        }

    } while (extraTurn);

    displayGrid();
}



class Game {
    Deck deck;
    Player player1, player2;
    bool player1Turn;

public:
    Game(string p1Name, string p2Name);
    void play();
};

Game::Game(string p1Name, string p2Name)
    : deck(gridSize), player1(p1Name), player2(p2Name), player1Turn(true) {
    deck.shuffle();
}

void Game::play() {
    cout << "Game Started!" << endl;
    deck.displayGrid();

    while (!deck.allCardsMatched()) {
        if (player1Turn) {
            deck.turn(player1);
        } else {
            deck.turn(player2);
        }

        player1Turn = !player1Turn;
    }

    cout << "\nGame Over! All cards have been matched.\n" << endl;

    // Display final scores
    cout << "Final Scores:\n";
    player1.displayScore();
    player2.displayScore();

    // Announce the winner
    if (player1.getScore() > player2.getScore()) {
        cout << "\nCongratulations, " << player1.getName() << "! You are the winner!" << endl;
    } else if (player2.getScore() > player1.getScore()) {
        cout << "\nCongratulations, " << player2.getName() << "! You are the winner!" << endl;
    } else {
        cout << "\nIt's a tie! Great game, both players!" << endl;
    }
}




int main() {
    srand(time(nullptr));

    string p1, p2;
    cout << "Enter Player 1's name: ";
    cin >> p1;
    cout << "Enter Player 2's name: ";
    cin >> p2;

    Game game(p1, p2);
    game.play();
    return 0;
}
