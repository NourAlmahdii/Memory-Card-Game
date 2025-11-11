Memory Match Card Game

Programming III – Milestone 02 Winter Semester 2024/2025

Overview

This project implements the core gameplay for the Memory Match Card Game, developed as part of Milestone 02 in the Programming III course.

The game is a two-player turn-based card matching game where players take turns flipping two cards from a grid. Based on the revealed cards, different scoring and gameplay rules are applied. The game continues until all pairs are matched and removed from the grid. The player with the highest score at the end wins.

Game Features

Player Turns and Card Flipping
Two players take alternating turns.

On each turn, a player selects two cards by entering their coordinates.

The selected cards are revealed and displayed on the grid.

Scoring Rules Standard Cards
If both revealed cards are standard cards with the same number:

Player gains 1 point.

Player takes another turn.

Both cards are removed from the grid.

If the cards do not match:

No points are awarded.

The cards are flipped back, and the next player takes their turn.

Bonus Card (Number 7)

If one bonus card and one standard card are revealed:

Player gains +1 point.

The bonus card is removed from the grid, and the standard card is hidden again.

If both revealed cards are bonus cards:

Player can choose between:

Gaining +2 points, or

Gaining +1 point and taking another turn.

Both bonus cards are removed from the grid.

Penalty Card (Number 8)

If one penalty card and one standard card are revealed:

Player loses 1 point.

If both revealed cards are penalty cards:

Player can choose between:

Losing 2 points, or

Losing 1 point and skipping the next turn.

Bonus and Penalty Combination

If one bonus card and one penalty card are revealed:

No scoring effect occurs.

Both cards are removed from the grid.

Game End and Winner Determination

The game ends when all cards are matched and removed from the grid.

The player with the highest score is declared the winner.

If both players have the same score, the game ends in a tie.

Class Structure Card Class and Subclasses

Classes: StandardCard, BonusCard, and PenaltyCard.

Each class defines its own behavior for scoring and special effects.

Common methods include:

reveal() – Reveals the card’s value.

hide() – Hides the card and replaces it with * on the grid.

display() – Displays the current visible state of the card.

Player Class

Manages player-related data such as name and score.

Provides methods to increase or decrease the score based on card effects.

Deck Class

Handles the grid of cards and their states.

Responsible for:

Displaying the current grid.

Resetting the grid to its hidden (*) format.

Removing cards when matched or affected by special rules.

Game Class

Controls the main game flow and turn-based logic.

Handles player turns, card selections, and score updates.

Manages special card effects and game-end conditions.

Determines the final winner or tie.

Game Flow

Initialize Game
Display the grid with all cards hidden (*).

Display player names and initial scores.

Player Turn
The current player selects two cards by entering their coordinates.

The chosen cards are revealed and evaluated.

Scores are updated based on the card rules.

Turn Change
The current player presses Enter to hide the cards again.

The turn switches to the next player unless a bonus or penalty effect applies.

Game Continuation
The process repeats until the grid is empty (all cards removed).

Game End
The game announces that all pairs have been matched.

The final scores are displayed and the winner (or tie) is announced.
