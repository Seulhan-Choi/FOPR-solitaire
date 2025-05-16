#ifndef COMMANDS_H
#define COMMANDS_H

#include "structs.h"
#include "functions.h"
#include <vector>
#include <iostream>

using namespace std;

void discardCard(vector<Card> &stack);
void moveCards(vector<vector<Card>>& columns, vector<Card>& stack, Storage (&storage)[4]);
void showGameState(const vector<vector<Card>> &columns, const vector<Card> &stack, const Storage storage[4]);

#endif // COMMANDS_H