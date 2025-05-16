#include "functions.h"

void readInit(vector<vector<Card>>& Columns, vector<Card>& Stack, Storage (&Foundations)[4]) {
    // Initialize the game state and read the initial configuration from input
    // This function should set up the game board, including the stack and columns
    int usedCards = 0; // Total number of cards used

    for (int i = 0; i < 7; ++i) {   // Initialize 7 columns
        int n;
        cin >> n;
        for (int j = 0; j < n; ++j) {
            string input;
            cin >> input;
            Columns[i].push_back(readCard(input));
            usedCards++;
        }
    }

    for (int i = 0; i < 4; ++i) {   // Initialize 4 foundations
        int n;
        cin >> n;
        Foundations[i].lastCardID = n; // Initialize the top card ID for each foundation
        Foundations[i].suit = i;
        usedCards += n;
    }

    for (int i = 0; i < 52 - usedCards; i++)    { // Initialize the stack with the remaining cards
        string input;
        cin >> input;
        Stack.push_back(readCard(input));
    }
}
    
Card readCard(string input) {
    int value;
    char suitChar = input.back();   // Parses last character for suit
    
    // Turns any possible character into its corresponding number
    if (input[0] == 'A') value = 1;
    else if (input[0] == 'J') value = 11;
    else if (input[0] == 'Q') value = 12;
    else if (input[0] == 'K') value = 13;
    else if (input[0] == '1' && input.size() > 1 && input[1] == '0') value = 10; // Handle 10. As value = 1 its input = A, the only number possible is 10.
    else value = input[0] - '0'; // Convert char to int (1-9)

    int suit;
    switch (suitChar) {
        case 'C': suit = 0; break;
        case 'D': suit = 1; break;
        case 'P': suit = 2; break;
        case 'T': suit = 3; break;
    }
    Card card;
    card.value = value;
    card.suit = suit;
    return card;
}