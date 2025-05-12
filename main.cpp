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
    vector<Card> Stack; // Stack of cards
    vector<vector<Card>> Columns(7);    // 7 columns for the game

    Storage Foundations[4]; // 4 suits for each foundation
    Foundations[0].suit = 0; // ♥
    Foundations[1].suit = 1; // ♦
    Foundations[2].suit = 2; // ♠
    Foundations[3].suit = 3; // ♣

    // Reading cards from input
    readInit(Columns);
    char commandChar;
    while (commandChar != 'Z')  {
        cin >> commandChar; // Read command character
        switch (commandChar) {
            case 'D':
                discardCard(Stack);
                break;
            case 'M':
                moveCards(Columns, Stack, Foundations);
                break;
            case 'S':
                showGameState(Columns, Stack, Foundations);
                break;
            case 'Z':
                cout << "Exiting game." << endl;
                break;
        }
        checkEndGame(Columns, Stack, Foundations);
    }

}