#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "structs.h"

#include <iostream>
#include <vector>
#include <string>

using namespace std;

void readInit(vector<vector<Card>>& Columns, vector<Card>& Stack, Storage (&Foundations)[4]);
void checkEndGame(vector<vector<Card>>& Columns, vector<Card>& Stack, Storage (&Foundations)[4]);
Card readCard(string input);
#endif // FUNCTIONS_H