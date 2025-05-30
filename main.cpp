#include <iostream>
#include <vector>
#include <string> // for string handling
#include <stdexcept> // for error handling
#include "structs.h"
#include "functions.h"
#include "commands.h"

using namespace std;


int main() {
    // Define data structures
    vector<Card> stack; // stack of cards
    vector<vector<Card>> columns(7);    // 7 columns for the game

    Storage storage[4]; // 4 suits for each foundation
    storage[0].suit = 0; // ♥
    storage[1].suit = 1; // ♦
    storage[2].suit = 2; // ♠
    storage[3].suit = 3; // ♣

    // Reading cards from input
    readInit(columns, stack, storage);

    // Clear any leftover input in the buffer
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    char commandChar = ' '; // Initialize command character
    int moveCounter = 0; // Initialize move counter
    while (commandChar != 'Z')  {
        cin >> commandChar; // Read command character

        switch (commandChar) {
            case 'D':
                discardCard(stack);
                moveCounter++; // Increment move counter
                break;
            case 'M':
                moveCards(columns, stack, storage);
                moveCounter++; // Increment move counter
                break;
            case 'S':
                showGameState(columns, stack, storage);
                break;
            case 'Z':
                if (!checkEndGame(storage, commandChar, moveCounter))   {
                    cout << "No has guanyat i has fet " << moveCounter;
                    if (moveCounter == 1) {
                        cout << " moviment." << endl;
                    }
                    else {
                        cout << " moviments." << endl;
                    }
                }
                break;
        }
        checkEndGame(storage, commandChar, moveCounter);
    }

}