#include "functions.h"

void readInit(vector<vector<Card>>& columns, vector<Card>& stack, Storage (&storage)[4]) {
    // Initialize the game state and read the initial configuration from input
    // This function should set up the game board, including the stack and columns
    int usedCards = 0; // Total number of cards used

    for (int i = 0; i < 7; ++i) {   // Initialize 7 columns
        int n;
        cin >> n;
        for (int j = 0; j < n; ++j) {
            string input;
            cin >> input;
            columns[i].push_back(readCard(input));
            usedCards++;
        }
    }

    for (int i = 0; i < 4; ++i) {   // Initialize 4 storage
        int n;
        cin >> n;
        storage[i].lastCardID = n; // Initialize the top card ID for each foundation
        storage[i].suit = i;
        usedCards += n;
    }

    for (int i = 0; i < 52 - usedCards; i++)    { // Initialize the stack with the remaining cards
        string input;
        cin >> input;
        stack.push_back(readCard(input));
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

    int suit = 4;
    switch (suitChar) {
        case 'C': suit = 0; break;
        case 'D': suit = 1; break;
        case 'P': suit = 2; break;
        case 'T': suit = 3; break;
		default:
			suit = 4;
    }
    Card card;
    card.value = value;
    card.suit = suit;
    return card;
}

bool moveCardsAux_toM(Card temp, Storage (&storage)[4], int num, int destinationNum)    {
    if (num != 1) {
        cout << "Error: Nombre de cartes a moure incorrecte" << endl;
        return false;
    }
    else if (storage[destinationNum - 1].lastCardID == 0 && temp.value != 1) {
        cout << "Error: A un magatzem buit sols es pot moure un as" << endl;
        return false;
    }
    else if (storage[destinationNum - 1].suit != temp.suit || temp.value != storage[destinationNum - 1].lastCardID + 1) {
        cout << "Error: No hi ha concordança de valor i/o pal" << endl;
        return false;
    }
    else {
        storage[destinationNum - 1].lastCardID++;
        cout << "Card moved successfully to storage " << destinationNum << endl; // Debug message
        return true;
    }
}
bool moveCardsAux_toC(Card temp, vector<vector<Card>>& columns, int num, int destinationNum)    {
    if (columns[destinationNum - 1].empty())    {
        if (temp.value == 13)   {
            columns[destinationNum - 1].push_back(temp);
            cout << "Card moved successfully to column " << destinationNum << endl; // Debug message
        }
        else
        {
            cout << "Error: No hi ha concordança de valor i/o pal" << endl;
            cout << "You can only put a king in an empty column" << endl; // Debug message
            return false;
        }
    }
    else
    {
        Card topCard = columns[destinationNum - 1].back();
        if (topCard.suit % 2  != temp.suit % 2 && topCard.value - temp.value == 1) {
            columns[destinationNum - 1].push_back(temp);
            cout << "Card moved successfully to column " << destinationNum << endl; // Debug message
            return true;
        }
        else
        {
            cout << "Error: No hi ha concordança de valor i/o pal" << endl;
            return false;
        }
    }
    
}

void checkEndGame(vector<vector<Card>>& columns, vector<Card>& stack, Storage(&storage)[4]) {
    cout << "checkEndGame" << endl;
}