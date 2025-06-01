#ifndef COMMANDS_H
#define COMMANDS_H

#include "structs.h"
#include "functions.h"
#include <vector>
#include <iostream>

using namespace std;

// Function declarations for game commands
void discardCard(vector<Card> &stack);

void moveCards(vector<vector<Card>>& columns, vector<Card>& stack, Foundation (&foundations)[NUM_FOUNDATIONS]);

void showGameState(const vector<vector<Card>>& columns, const vector<Card>& stack, const Foundation foundations[NUM_FOUNDATIONS]);

#endif // COMMANDS_H