#ifndef COMMANDS_H
#define COMMANDS_H

#include "structs.h"
#include <vector>
using namespace std;

void discardCard(vector<Card> &Stack);
void moveCards(vector<vector<Card>>& Columns, vector<Card>& Stack, Storage (&Foundations)[4]);
void showGameState(const vector<vector<Card>> &Columns, const vector<Card> &Stack, const Storage Foundations[4]);

#endif // COMMANDS_H