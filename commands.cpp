#include "commands.h"

void discardCard(vector<Card> &Stack) {
    // Discard the top card from the stack
    Card discardedCard = Stack.back();
    Stack.pop_back();
    Stack.emplace(Stack.begin(), discardedCard); // Move the discarded card to the back of the stack
}