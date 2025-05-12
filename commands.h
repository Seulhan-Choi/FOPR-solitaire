#include "structs.h"

void discardCard(vector<Card> &Stack);
void moveCards(vector<vector<Card>> &Columns, vector<Card> &Stack, Storage Foundations[4], int sourceColumnIndex, int targetColumnIndex, int cardIndex);
void showGameState(const vector<vector<Card>> &Columns, const vector<Card> &Stack, const Storage Foundations[4]);

