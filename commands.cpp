#include "commands.h"

// PRE: stack(pila) no és buit.
// POST: mou la primera carta del vector stack(pila) al final del mateix.
void discardCard(vector<Card>& stack) {
    if (!stack.empty()) {
        Card discardedCard = stack.back();
        stack.pop_back();
        stack.insert(stack.begin(), discardedCard);
        cout << printableCard(stack.back()) << endl;
    }
}

// PRE: es llegeix de l’entrada una ordre de moviment vàlida amb origen, num i destí.
// POST: si el moviment és vàlid segons les regles del joc, mou la carta i actualitza l'estructura corresponent.
void moveCards(vector<vector<Card>>& columns, vector<Card>& stack, Foundation(&foundations)[NUM_FOUNDATIONS]) {
    string origin, destination;
    int num;

    cin >> origin >> num >> destination;
    int destinationIndex = destination.back() - '0';
    int originIndex = origin.back() - '0';
    if (destination == "P") {
        cout << "Error: No es poden moure cartes a la pila" << endl;
    }
    else if (origin == "P") {
        if (destination.front() == 'M') {
            // Move from stack to foundation
            moveCardsAux_toM(stack, foundations, num, destinationIndex);
        }
        else if (destination.front() == 'C') {
            // Move from stack to column
            if (num != 1) {
                cout << "Error: Nombre de cartes a moure incorrecte" << endl;
            }
            else (moveCardsAux_toC(stack, columns, num, originIndex, destinationIndex));
        }
    }
    else if (origin.front() == 'C') {
        if (destination.front() == 'M') {
            // Move from column to foundation
            moveCardsAux_toM(columns[originIndex - 1], foundations, num, destinationIndex);
        }
        else if (destination.front() == 'C') {
            // Move from column to column
            moveCardsAux_toC(columns[originIndex - 1], columns, num, originIndex, destinationIndex);
        }
    }
    else if (origin.front() == 'M') {
        if (destination.front() == 'C') {
            // Move from foundation to column
            Card card;
			vector<Card> tempStack;
            card.value = foundations[originIndex - 1].lastCardID;
            card.suit = foundations[originIndex - 1].suit;
			tempStack.push_back(card);
            if (num != 1) {
                cout << "Error: Nombre de cartes a moure incorrecte" << endl;
			}
            else if (moveCardsAux_toC(tempStack, columns, num, originIndex, destinationIndex))	foundations[originIndex - 1].lastCardID--;
        }
    }
    // cout << "moveCards" << endl;
}

// PRE: columns(columnes) conté les 7 columnes, stack(pila) i foundations(magatzems) reflecteixen l’estat actual del joc.
// POST: mostra per pantalla l’estat actual del joc: pila, magatzems i columnes.
void showGameState(const vector<vector<Card>>& columns, const vector<Card>& stack, const Foundation foundations[NUM_FOUNDATIONS]) {
    // Show the game state
    cout << "Pila:";
    if (stack.empty()) {
        cout << " -" << endl;
    }
    else
    {
        cout << " " << printableCard(stack.back()) << endl;
    }

    for (int i = 0; i < NUM_FOUNDATIONS; ++i) {
        cout << "Mag " << i + 1 << ":";
        if (foundations[i].lastCardID == 0) {
            cout << " -" << endl;
        }
        else
        {
            for (int j = 0; j < foundations[i].lastCardID; ++j) {
                // Inv: S’han mostrat les j primeres cartes del magatzem i.
                Card card;
                card.value = j + 1;
                card.suit = foundations[i].suit;
                cout << " " << printableCard(card);
            }
            cout << endl;
        }
    }

    for (int i = 0; i < NUM_COLUMNS; ++i) {
        cout << "Col " << i + 1 << ":";
        if (columns[i].empty()) {
            cout << " -" << endl;
        }
        else
        {
            for (int j = 0; j < columns[i].size(); ++j) {
                // Inv: S’han mostrat les j primeres cartes de la columna i.
                cout << " " << printableCard(columns[i][j]);
            }
            cout << endl;
        }
    }
    cout << "---" << endl;
    //  cout << "showGameState" << endl;
}