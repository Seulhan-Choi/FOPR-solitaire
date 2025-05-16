#include "commands.h"

void discardCard(vector<Card> &Stack) {
    // Discard the top card from the stack
    Card discardedCard = Stack.back();
    Stack.pop_back();
    Stack.emplace(Stack.begin(), discardedCard); // Move the discarded card to the back of the stack
}

void moveCards(vector<vector<Card>>& Columns, vector<Card>& Stack, Storage (&Foundations)[4]) {
    cout << "test" << endl;
}

void showGameState(const vector<vector<Card>> &Columns, const vector<Card> &Stack, const Storage Foundations[4]) {
    cout << "test" << endl;
}