#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <vector>
#include <string>

#include "structs.h"

using namespace std;


void readInit(vector<vector<Card>>& Columns);
void checkEndGame(vector<vector<Card>>& Columns, vector<Card>& Stack, Storage (&Foundations)[4]);

#endif // FUNCTIONS_H