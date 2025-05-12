#include "functions.h"

void readInit(vector<vector<Card>> &Columns) {
    // Initialize the game state and read the initial configuration from input
    // This function should set up the game board, including the stack and columns
    // For example, you might read the number of cards in each column and their values
    // You can use cin to read from standard input or any other method as needed
    for (int i = 0; i < 7; ++i) {
        int n;
        cin >> n;
        for (int j = 0; j < n; ++j) {
            string input;
            cin >> input;

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
            
            Columns[i].emplace_back(value, suit);
        }
    }
}