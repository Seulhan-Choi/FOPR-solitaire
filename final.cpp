#include <iostream>
#include <vector>
#include <string>

using namespace std;

//---------------------------------------------------------------------------------------------
// STRUCTS
struct Card {
    int value;  // 1-13 (Ace-King)
    int suit;   // 0-3 ( ♥, ♦, ♠, ♣)s
};

struct Storage {
    int lastCardID = 0;
    int suit;
};
//---------------------------------------------------------------------------------------------
// FUNCTIONS
void readInit(vector<vector<Card>>& columns, vector<Card>& stack, Storage (&storage)[4]) {
    // Initialize the game state and read the initial configuration from input
    // This function should set up the game board, including the stack and columns


    for (int i = 0; i < 7; ++i) {   // Initialize 7 columns
        int n;
        cin >> n;
        for (int j = 0; j < n; ++j) {
            string input;
            cin >> input;
            columns[i].push_back(readCard(input));
        }
    }

    for (int i = 0; i < 4; ++i) {   // Initialize 4 storage
        int n;
        cin >> n;
        storage[i].lastCardID = n; // Initialize the top card ID for each foundation
        storage[i].suit = i;
        for (int j = 0; j < n; ++j) { // We dont have to process each card,  as the initial foundations are always in order.
            string dummy;
            cin >> dummy; // Read and discard the actual card string
        }
    }

    int n;
	cin >> n; // Read the number of cards in the stack
    for (int i = 0; i < n; i++)    { // Initialize the stack with the remaining cards
        string input;
        cin >> input;
        stack.insert(stack.begin(), readCard(input));
    }

    /*for (int i = 0; i < stack.size(); i++) {
		cout << printCard(stack[i]) << " ";
    }
    cout << endl;*/
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
        //cout << "Card moved successfully to storage " << destinationNum << endl; // Debug message
        return true;
    }
}
bool moveCardsAux_toC(Card temp, vector<vector<Card>>& columns, int num, int destinationNum)    {
    if (columns[destinationNum - 1].empty())    {
        if (temp.value == 13)   {
            columns[destinationNum - 1].push_back(temp);
            //cout << "Card moved successfully to column " << destinationNum << endl; // Debug message
        }
        else
        {
            cout << "Error: No hi ha concordança de valor i/o pal" << endl;
            //cout << "You can only put a king in an empty column" << endl; // Debug message
            return false;
        }
    }
    else
    {
        Card topCard = columns[destinationNum - 1].back();
        if (topCard.suit % 2  != temp.suit % 2 && topCard.value - temp.value == 1)  {
            columns[destinationNum - 1].push_back(temp);
            //cout << "Card moved successfully to column " << destinationNum << endl; // Debug message
            return true;
        }
        else
        {
            cout << "Error: No hi ha concordança de valor i/o pal" << endl;
            return false;
        }
    }
    
}

string printCard(const Card& card) {
     // Print the card in a readable format
    char outputValue = ' ';
    if (card.value == 1) outputValue = 'A';
    else if (card.value == 11) outputValue = 'J';
    else if (card.value == 12) outputValue = 'Q';
    else if (card.value == 13) outputValue = 'K';
    else outputValue = card.value + '0'; // Convert int to char
    string output;

    switch (card.suit) {
        case 0: output = outputValue + string("\033[0;31m\u2665\033[0m"); break; // Hearts
        case 1: output = outputValue + string("\033[0;31m\u2666\033[0m"); break; // Diamonds
        case 2: output = outputValue + string("\u2660"); break; // Spades
        case 3: output = outputValue + string("\u2663"); break; // Clubs
        default: output = outputValue; break;
    }
    return output;
}
bool checkEndGame(Storage(&storage)[4], char& commandChar, int& moveCounter) {
    if (storage[0].lastCardID == 13 && storage[1].lastCardID == 13 && storage[2].lastCardID == 13 && storage[3].lastCardID == 13) {
        cout << "Felicitats has guanyat!! Ho has fet en " <<  moveCounter;
        if (moveCounter == 1) {
            cout << " moviment." << endl;
        }
        else {
            cout << " moviments." << endl;
        }
        commandChar = 'Z'; // Set commandChar to 'Z' to exit the game loop
        return true;
    }
    return false;
}
//---------------------------------------------------------------------------------------------
// COMMANDS
void discardCard(vector<Card> &stack) {
    // Discard the top card from the stack
    Card discardedCard = stack.back();
    stack.pop_back();
    stack.emplace(stack.begin(), discardedCard); // Move the discarded card to the back of the stack

    cout << "discardCard" << endl;
}

void moveCards(vector<vector<Card>>& columns, vector<Card>& stack, Storage (&storage)[4]) {
    string origin, destination;
	int num;

	cin >> origin >> num >> destination;
	int destIdx = destination.back() - '0';
	int origIdx = origin.back() - '0';
	if (destination == "P") {
		cout << "Error: No es poden moure cartes a la pila" << endl;
	}
    else if (origin == "P") {
		if (destination.front() == 'M') {
			// Move from stack to foundation
			if (moveCardsAux_toM(stack.back(), storage, num, destIdx))	stack.pop_back();
		}
		else if (destination.front() == 'C') {
			// Move from stack to column
			if (moveCardsAux_toC(stack.back(), columns, num, destIdx))	stack.pop_back();
		}
    }
	else if (origin.front() == 'C') {
		if (destination.front() == 'M') {
			// Move from column to foundation
			if (moveCardsAux_toM(columns[origIdx - 1].back(), storage, num, destIdx))	columns[origIdx - 1].pop_back();
			
		}
		else if (destination.front() == 'C') {
			// Move from column to column
			if (moveCardsAux_toC(columns[origIdx - 1].back(), columns, num, destIdx))	columns[origIdx - 1].pop_back();
		}
	}
	else if (origin.front() == 'M') {
		if (destination.front() == 'C') {
			// Move from foundation to column
			Card temp;
			temp.value = storage[origIdx - 1].lastCardID;
			temp.suit = storage[origIdx - 1].suit;
			if (moveCardsAux_toC(temp, columns, num, destIdx))	storage[origIdx - 1].lastCardID--;
		}
	}

    
    cout << "moveCards" << endl;
}


void showGameState(const vector<vector<Card>> &columns, const vector<Card> &stack, const Storage storage[4]) {
	// Show the game state
	cout << "Pila:";
	if (stack.empty())	{
		cout << " -" << endl;
	}
	else
	{
		cout << " " << printCard(stack.back()) << endl;
	}
	
	
	for (int i = 0; i < 4; ++i) {
		cout << "Mag " << i + 1 << ":";
		if (storage[i].lastCardID == 0) {
			cout << " -" << endl;
		}
		else
		{
			for (int j = 0; j < storage[i].lastCardID; ++j) {
				Card temp;
				temp.value = j + 1;
				temp.suit = storage[i].suit;
				cout << " " << printCard(temp);
			}
			cout << endl;
		}
		
	}
	
	for (int i = 0; i < 7; ++i) {
		cout << "Col " << i + 1 << ":";
		if (columns[i].empty()) {
			cout << " -" << endl;
		}
		else
		{
			for (int j = 0; j < columns[i].size(); ++j) {
				cout << " " << printCard(columns[i][j]);
			}
			cout << endl;
		}
		
	}
	cout << "---" << endl;
    cout << "showGameState" << endl;
}
//---------------------------------------------------------------------------------------------
int main() {
    // Define data structures
    vector<Card> stack; // stack of cards
    vector<vector<Card>> columns(7);    // 7 columns for the game

    Storage storage[4]; // 4 suits for each foundation
    storage[0].suit = 0; // ♥
    storage[1].suit = 1; // ♦
    storage[2].suit = 2; // ♠
    storage[3].suit = 3; // ♣

    // Reading cards from input
    readInit(columns, stack, storage);

    // Clear any leftover input in the buffer
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    char commandChar = ' '; // Initialize command character
    int moveCounter = 0; // Initialize move counter
    while (commandChar != 'Z')  {
        cin >> commandChar; // Read command character

        switch (commandChar) {
            case 'D':
                discardCard(stack);
                moveCounter++; // Increment move counter
                break;
            case 'M':
                moveCards(columns, stack, storage);
                moveCounter++; // Increment move counter
                break;
            case 'S':
                showGameState(columns, stack, storage);
                break;
            case 'Z':
                if (!checkEndGame(storage, commandChar, moveCounter))   {
                    cout << "No has guanyat i has fet " << moveCounter;
                    if (moveCounter == 1) {
                        cout << " moviment." << endl;
                    }
                    else {
                        cout << " moviments." << endl;
                    }
                }
                break;
        }
        checkEndGame(storage, commandChar, moveCounter);
    }

}
