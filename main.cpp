#include <iostream>
#include <vector>
#include <string> // for string handling

#include "structs.h"
#include "functions.h"
#include "commands.h"

using namespace std;


int main() {
    // Define data structures
    vector<Card> stack; // stack of cards
    vector<vector<Card>> columns(NUM_COLUMNS);    // 7 columns

    Foundation foundations[NUM_FOUNDATIONS]; // 4 foundations

    // Reading cards from input
    readInit(columns, stack, foundations);

    // Clear any leftover input in the buffer
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    char commandChar = ' '; // Initialize command character
    int moveCounter = 0; // Initialize move counter
    while (commandChar != 'Z') {
        // Inv: L’estat del joc reflecteix correctament totes les comandes llegides fins ara,
        // i moveCounter conté el nombre de moviments realitzats.
        cin >> commandChar; // Read command character

        switch (commandChar) {
        case 'D':
            discardCard(stack);
            moveCounter++; // Increment move counter
            checkEndGame(foundations, commandChar, moveCounter);
            break;
        case 'M':
            moveCards(columns, stack, foundations);
            moveCounter++; // Increment move counter
            checkEndGame(foundations, commandChar, moveCounter);
            break;
        case 'S':
            showGameState(columns, stack, foundations);
            break;
        case 'Z':
            if (!checkEndGame(foundations, commandChar, moveCounter)) {
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
    }
}