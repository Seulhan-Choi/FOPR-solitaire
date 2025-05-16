#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "structs.h"

#include <iostream>
#include <vector>
#include <string>

using namespace std;

void readInit(vector<vector<Card>>& columns, vector<Card>& stack, Storage (&storage)[4]);
Card readCard(string input);
bool moveCardsAux_toM(Card temp, Storage (&storage)[4], int num, int destinationNum);
bool moveCardsAux_toC(Card temp, vector<vector<Card>>& columns, int num, int destinationNum);
string printCard(const Card& card);
bool checkEndGame(Storage (&storage)[4], char& commandChar, int& moveCounter);
#endif // FUNCTIONS_H