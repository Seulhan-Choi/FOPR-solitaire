#include "functions.h"


// PRE: suit és un valor vàlid de l'enumeració Suit.
// POST: retorna true si suit correspon a HEARTS o DIAMONDS, false en cas contrari. 
bool isRed(Suit& suit) {
    return suit == HEARTS || suit == DIAMONDS;
}

// PRE: card és una carta vàlida.
// POST: retorna una representació en string de la carta, amb símbol i color.
string printableCard(const Card& card) {

    string output;
    switch (card.value) {
    case ACE_VALUE:   output = 'A'; break;
    case JACK_VALUE:  output = 'J'; break;
    case QUEEN_VALUE: output = 'Q'; break;
    case KING_VALUE:  output = 'K'; break;
    case 10:          output = "10"; break;
    default:          output = card.value + '0'; break;
    }

    //switch (card.suit) {
    //case HEARTS: output = output + string("\033[0;31m\u2665\033[0m"); break; // Hearts
    //case DIAMONDS: output = output + string("\033[0;31m\u2666\033[0m"); break; // Diamonds
    //case SPADES: output = output + string("\u2660"); break; // Spades
    //case CLUBS: output = output + string("\u2663"); break; // Clubs
    //default: output = output; break;
    //}
    switch (card.suit) {
    case HEARTS: output = output + string("C"); break; // Hearts
    case DIAMONDS: output = output + string("D"); break; // Diamonds
    case SPADES: output = output + string("P"); break; // Spades
    case CLUBS: output = output + string("T"); break; // Clubs
    default: output = output; break;
    }
    return output;
}

// PRE: input és una string representant una carta vàlida, com "AS" o "10C".
// POST: retorna un Card amb el valor i pal corresponent.
Card readCard(string input) {
    int value;
    char suitChar = input.back();   // Parses last character for suit

    if (input[0] == '1' && input.size() > 2 && input[1] == '0') { // Handle 10 as its the only 2-digit input number possible is 10.
        value = 10;
    }
    else {
        switch (input[0]) {
        case 'A': value = ACE_VALUE; break;
        case 'J': value = JACK_VALUE; break;
        case 'Q': value = QUEEN_VALUE; break;
        case 'K': value = KING_VALUE; break;
        default:  value = input[0] - '0'; break; // Convert char to int (2-9)
        }
    }

    Suit suit;
    switch (suitChar) {
    case 'C': suit = HEARTS; break;  // C is for hearts (corazón in Spanish)
    case 'D': suit = DIAMONDS; break; // D is for diamonds
    case 'P': suit = SPADES; break;   // P is for spades (picas in Spanish)
    case 'T': suit = CLUBS; break;    // T is for clubs (tréboles in Spanish)
    default: suit = HEARTS;
    }
    Card card;
    card.value = value;
    card.suit = suit;
    return card;
}

// PRE: columns(columnes) és buit, stack(pila) és buit, foundations(magatzems) està inicialitzat amb els pals corresponents (0-3).
// POST: columns(columnes), stack(pila) i foundations(magatzems) queden plens amb les cartes inicials llegides de l’entrada.
void readInit(vector<vector<Card>>& columns, vector<Card>& stack, Foundation(&foundations)[NUM_FOUNDATIONS]) {
    // Read the initial configuration of the columns
    for (int i = 0; i < NUM_COLUMNS; ++i) {
        // Inv: S’han inicialitzat les primeres i columnes amb les cartes llegides de l’entrada.
        int numCards;
        cin >> numCards;
        for (int j = 0; j < numCards; ++j) {
            // Inv: La columna i conté les j cartes llegides, en ordre d’entrada.
            string input;
            cin >> input;
            columns[i].push_back(readCard(input));
        }
    }

    // Read the initial configuration of the foundations
    // I used a struct with 2 integer values in stead of storing each card in a vector
    // because the foundations are always ordered, so I only have to track the last card ID and the suit of the foundation.
    for (int i = 0; i < NUM_FOUNDATIONS; ++i) {
        // Inv: S’han inicialitzat i magatzems amb el nombre de cartes corresponents.
        int numCards;
        cin >> numCards;
        foundations[i].lastCardID = numCards; // Initialize the top card ID for each foundation
        string dummy;
        if (numCards > 0) {
            // Read the suit of the foundation
            string input;
            cin >> input;
            foundations[i].suit = readCard(input).suit; // Store the suit of the foundation
            for (int j = 0; j < numCards - 1; ++j) { // Discard the cards read for the foundation
                // Inv: S’han llegit i descartat j cartes per al magatzem i.
                cin >> dummy;
            }
        }
        else {
            for (int j = 0; j < numCards; ++j) { // Discard the cards read for the foundation
                // Inv: S’han llegit i descartat j cartes per al magatzem i.
                cin >> dummy;
            }
		}
        
    }


    int numCards;
    cin >> numCards; // Read the number of cards in the stack


    string input;
    for (int i = 0; i < numCards; i++) {
        // Inv: stack conté les i primeres cartes llegides en ordre.
        cin >> input;
        stack.push_back(readCard(input));
    }
    reverse(stack.begin(), stack.end());

}

// PRE: card és una carta vàlida, num és 1, destinationNum ∈ [1,4].
// POST: retorna true si la carta es pot moure al magatzem corresponent; en aquest cas actualitza foundations(magatzems). Retorna false si no es pot.
bool moveCardsAux_toM(vector<Card>& originVector, Foundation(&foundations)[NUM_FOUNDATIONS], int num, int destinationNum) {
    if (num != 1) {
        cout << "Error: Nombre de cartes a moure incorrecte" << endl;
        return false;
    }
    else if (foundations[destinationNum - 1].lastCardID == 0) {
        if (originVector.back().value != 1) {
            cout << "Error: A un magatzem buit sols es pot moure un as" << endl;
            return false;
        }
        else
        {
            foundations[destinationNum - 1].suit = originVector.back().suit;
            foundations[destinationNum - 1].lastCardID++;
            originVector.pop_back();
            return true;
        }
    }
    else if (foundations[destinationNum - 1].suit != originVector.back().suit || originVector.back().value != foundations[destinationNum - 1].lastCardID + 1) {
        cout << "Error: No hi ha concordança de valor i/o pal" << endl;
        return false;
    }
    else {
        foundations[destinationNum - 1].lastCardID++;
        originVector.pop_back();
        return true;
    }
}


// PRE: card és una carta vàlida, num és 1, destinationNum ∈ [1,7].
// POST: retorna true si la carta es pot moure a la columna corresponent; en aquest cas afegeix la carta a la columna. Retorna false si no es pot.
bool moveCardsAux_toC(vector<Card>& originVector, vector<vector<Card>>& columns, int num, int originNum, int destinationNum) {
    // Check if origin column has enough cards when moving multiple cards
    if (num == 1) {
        if (columns[destinationNum - 1].empty()) {
            if (originVector.back().value == KING_VALUE) {
                columns[destinationNum - 1].push_back(originVector.back());
                originVector.pop_back();
                return true;
            }
            else
            {
                cout << "Error: A una columna buida sols es pot moure un rei" << endl;
                return false;
            }
            
        }
        else if (originVector.back().value != columns[destinationNum - 1].back().value - 1 || isRed(originVector.back().suit) == isRed(columns[destinationNum - 1].back().suit))
        {
            cout << "Error: No hi ha concordanc¸a de valor i/o pal" << endl;
            return false;
        }
        else
        {
            columns[destinationNum - 1].push_back(originVector.back());
            originVector.pop_back();
            return true;
        }
    }
    else
    {
        
        vector<Card> cardsToMove;
        // Get the cards that will be moved
        int startIdx = originVector.size() - num;
        for (int i = startIdx; i < originVector.size(); i++) {
            cardsToMove.push_back(originVector[i]);
        }

        // Check if they form a valid sequence
        for (int i = 0; i < cardsToMove.size(); i++) {
            if (i > 0) {
                if (cardsToMove[i].value != cardsToMove[i - 1].value - 1 || isRed(cardsToMove[i].suit) == isRed(cardsToMove[i - 1].suit)) {
                    cout << "Error: El pilo indicat no es pot moure" << endl;
                    return false;
                }
            }
        }


        if (columns[destinationNum - 1].empty() && cardsToMove[0].value != KING_VALUE) {
            cout << "Error: A una columna buida sols es pot moure un rei" << endl;
            return false;
        }
        else if (cardsToMove[0].value != columns[destinationNum - 1].back().value - 1 || isRed(cardsToMove[0].suit) == isRed(columns[destinationNum - 1].back().suit))
        {
            cout << "Error: No hi ha concordança de valor i/o pal" << endl;
            return false;
        }
        else
        {
            // Move the cards
            for (int i = 0; i < cardsToMove.size(); i++) {
                columns[destinationNum - 1].push_back(cardsToMove[i]);
            }
            // Remove cards from origin
            for (int i = 0; i < num; i++) {
                columns[originNum - 1].pop_back();
            }
            return true;
        }
    }
}

// PRE: foundations(magatzems) conté els valors finals dels magatzems, commandChar conté l’última acció, moveCounter ≥ 0.
// POST: si tots els magatzems tenen 13 cartes, mostra el missatge de victòria, posa commandChar a 'Z' i retorna true; si no, retorna false.
bool checkEndGame(Foundation(&foundations)[NUM_FOUNDATIONS], char& commandChar, int& moveCounter) {
    if (foundations[0].lastCardID == KING_VALUE && foundations[1].lastCardID == KING_VALUE && foundations[2].lastCardID == KING_VALUE && foundations[3].lastCardID == KING_VALUE) {
        showGameState(columns, stack, foundations);
        cout << "Felicitats has guanyat!! Ho has fet en " << moveCounter;
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