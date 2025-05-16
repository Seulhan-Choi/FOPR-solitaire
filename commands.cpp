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
	int destIdx = destination.back() - '0';
	int origIdx = origin.back() - '0';
	if (destination == "P") {
		cout << "Error: No es poden moure cartes a la pila" << endl;
	}
    else if (origin == "P") {
		if (destination.front() == 'M') {
			// Move from stack to foundation
			if (moveCardsAux_toM(stack.back(), storage, num, destIdx))	stack.pop_back();
		}
		else if (destination.front() == 'C') {
			// Move from stack to column
			if (moveCardsAux_toC(stack.back(), columns, num, destIdx))	stack.pop_back();
		}
    }
	else if (origin.front() == 'C') {
		if (destination.front() == 'M') {
			// Move from column to foundation
			if (moveCardsAux_toM(columns[origIdx - 1].back(), storage, num, destIdx))	columns[origIdx - 1].pop_back();
			
		}
		else if (destination.front() == 'C') {
			// Move from column to column
			if (moveCardsAux_toC(columns[origIdx - 1].back(), columns, num, destIdx))	columns[origIdx - 1].pop_back();
		}
	}
	else if (origin.front() == 'M') {
		if (destination.front() == 'C') {
			// Move from foundation to column
			Card temp;
			temp.value = storage[origIdx - 1].lastCardID;
			temp.suit = storage[origIdx - 1].suit;
			if (moveCardsAux_toC(temp, columns, num, destIdx))	storage[origIdx - 1].lastCardID--;
		}
	}

    
    cout << "moveCards" << endl;
}


void showGameState(const vector<vector<Card>> &columns, const vector<Card> &stack, const Storage storage[4]) {
	// Show the game state
	cout << "Pila:";
	if (stack.empty())	{
		cout << " -" << endl;
	}
	else
	{
		cout << " " << printCard(stack.back()) << endl;
	}
	
	
	for (int i = 0; i < 4; ++i) {
		cout << "Mag " << i + 1 << ":";
		if (storage[i].lastCardID == 0) {
			cout << " -" << endl;
		}
		else
		{
			for (int j = 0; j < storage[i].lastCardID; ++j) {
				Card temp;
				temp.value = j + 1;
				temp.suit = storage[i].suit;
				cout << " " << printCard(temp);
			}
			cout << endl;
		}
		
	}
	
	for (int i = 0; i < 7; ++i) {
		cout << "Col " << i + 1 << ":";
		if (columns[i].empty()) {
			cout << " -" << endl;
		}
		else
		{
			for (int j = 0; j < columns[i].size(); ++j) {
				cout << " " << printCard(columns[i][j]);
			}
			cout << endl;
		}
		
	}
	cout << "---" << endl;
    cout << "showGameState" << endl;
}