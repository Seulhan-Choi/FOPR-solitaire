#include "commands.h"

void discardCard(vector<Card> &stack) {
    // Discard the top card from the stack
    Card discardedCard = stack.back();
    stack.pop_back();
    stack.emplace(stack.begin(), discardedCard); // Move the discarded card to the back of the stack

    cout << "discardCard" << endl;
}

void moveCards(vector<vector<Card>>& columns, vector<Card>& stack, Storage (&storage)[4]) {
    string origin, destination;
	int num;

	cin >> origin >> num >> destination;
	if (destination == "P") {
		cout << "Error: No es poden moure cartes a la pila" << endl;
	}
    else if (origin == "P") {
		if (destination.front() == 'M') {
			// Move from stack to foundation
			if (moveCardsAux_toM(stack.back(), storage, num, destination.back()))	stack.pop_back();
		}
		else if (destination.front() == 'C') {
			// Move from stack to column
			if (moveCardsAux_toC(stack.back(), columns, num, destination.back()))	stack.pop_back();
		}
    }
	else if (origin.front() == 'C') {
		if (destination.front() == 'M') {
			// Move from column to foundation
			if (moveCardsAux_toM(columns[origin.back() - 1].back(), storage, num, destination.back()))	columns[origin.back() - 1].pop_back();
			
		}
		else if (destination.front() == 'C') {
			// Move from column to column
			if (moveCardsAux_toC(columns[origin.back() - 1].back(), columns, num, destination.back()))	columns[origin.back() - 1].pop_back();
		}
	}
	else if (origin.front() == 'M') {
		if (destination.front() == 'C') {
			// Move from foundation to column
			Card temp;
			temp.value = storage[origin.back() - 1].lastCardID;
			temp.suit = storage[origin.back() - 1].suit;
			if (moveCardsAux_toC(temp, columns, num, destination.back()))	storage[origin.back() - 1].lastCardID--;
		}
	}

    
    cout << "moveCards" << endl;
}


void showGameState(const vector<vector<Card>> &columns, const vector<Card> &stack, const Storage storage[4]) {
    cout << "showGameState" << endl;
}