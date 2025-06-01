#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "structs.h"

#include <iostream>
#include <vector>
#include <string>

using namespace std;

bool isRed(Suit& suit);
string printableCard(const Card& card);

Card readCard(string input);
void readInit(vector<vector<Card>>& columns, vector<Card>& stack, Foundation(&foundations)[NUM_FOUNDATIONS]);

bool moveCardsAux_toM(vector<Card>& originVector, Foundation (&foundations)[NUM_FOUNDATIONS], int num, int destinationNum);

bool moveCardsAux_toC(vector<Card>& originVector, vector<vector<Card>>& columns, int num, int originNum, int destinationNum);
bool checkEndGame(Foundation (&foundations)[NUM_FOUNDATIONS], char& commandChar, int& moveCounter);
#endif // FUNCTIONS_H