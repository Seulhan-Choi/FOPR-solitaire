#include <iostream>
#include <vector>
#include <string> // for string handling
using namespace std;

enum Suit {
    CLUBS = 0,
    SPADES = 1,
    HEARTS = 2,
    DIAMONDS = 3
    };

const int NUM_COLUMNS = 7;
const int NUM_FOUNDATIONS = 4;

const int ACE_VALUE = 1;
const int JACK_VALUE = 11;
const int QUEEN_VALUE = 12;
const int KING_VALUE = 13;

struct Card {
    int value;
    Suit suit;
    };

struct Foundation {
    int lastCardID = 0;
    Suit suit = CLUBS;
    };

//---------------------------------------------------------------------------------------------
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
    switch (card.suit) {
        case HEARTS: output = output + string("\033[0;31m\u2665\033[0m"); break;
        case DIAMONDS: output = output + string("\033[0;31m\u2666\033[0m"); break;
        case SPADES: output = output + string("\u2660"); break;
        case CLUBS: output = output + string("\u2663"); break;
        default: output = output; break;
        }
    return output;
    }

// PRE: input és una string representant una carta vàlida, com "AS" o "10C".
// POST: retorna un Card amb el valor i pal corresponent.
Card readCard(string input) {
    int value;
    char suitChar = input.back();

    if (input[0] == '1' && input.size() > 2 && input[1] == '0') {
        value = 10;
        }
    else {
        switch (input[0]) {
            case 'A': value = ACE_VALUE; break;
            case 'J': value = JACK_VALUE; break;
            case 'Q': value = QUEEN_VALUE; break;
            case 'K': value = KING_VALUE; break;
            default:  value = input[0] - '0'; break;
            }
        }

    Suit suit;
    switch (suitChar) {
        case 'C': suit = HEARTS; break;
        case 'D': suit = DIAMONDS; break;
        case 'P': suit = SPADES; break;
        case 'T': suit = CLUBS; break;
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

    for (int i = 0; i < NUM_FOUNDATIONS; ++i) {
        // Inv: S'han inicialitzat i magatzems amb el nombre de cartes corresponents.
        int numCards;
        cin >> numCards;
        foundations[i].lastCardID = numCards;
        string dummy;
        if (numCards > 0) {
            string input;
            cin >> input;
            foundations[i].suit = readCard(input).suit;
            for (int j = 0; j < numCards - 1; ++j) {
                // Inv: S'han llegit i descartat j cartes per al magatzem i.
                cin >> dummy;
                }
            }
        else {
            for (int j = 0; j < numCards; ++j) {
                // Inv: S'han llegit i descartat j cartes per al magatzem i.
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
        int startIdx = originVector.size() - num;
        for (int i = startIdx; i < originVector.size(); i++) {
            cardsToMove.push_back(originVector[i]);
            }

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
            for (int i = 0; i < cardsToMove.size(); i++) {
                columns[destinationNum - 1].push_back(cardsToMove[i]);
                }
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
    if (foundations[0].lastCardID == KING_VALUE && foundations[1].lastCardID == KING_VALUE && foundations[2].lastCardID == KING_VALUE && foundations[3].lastCardID == KING_VALUE)   return true;
    return false;
    }

// PRE: stack(pila) no és buit.
// POST: mou la primera carta del vector stack(pila) al final del mateix.
void discardCard(vector<Card>& stack) {
    if (!stack.empty()) {
        Card discardedCard = stack.back();
        stack.pop_back();
        stack.insert(stack.begin(), discardedCard);
        cout << printableCard(stack.back()) << endl;
        }
    }

// PRE: es llegeix de l’entrada una ordre de moviment vàlida amb origen, num i destí.
// POST: si el moviment és vàlid segons les regles del joc, mou la carta i actualitza l'estructura corresponent.
void moveCards(vector<vector<Card>>& columns, vector<Card>& stack, Foundation(&foundations)[NUM_FOUNDATIONS]) {
    string origin, destination;
    int num;

    cin >> origin >> num >> destination;
    int destinationIndex = destination.back() - '0';
    int originIndex = origin.back() - '0';
    if (destination == "P") {
        cout << "Error: No es poden moure cartes a la pila" << endl;
        }
    else if (origin == "P") {
        if (destination.front() == 'M') {
            moveCardsAux_toM(stack, foundations, num, destinationIndex);
            }
        else if (destination.front() == 'C') {
            if (num != 1) {
                cout << "Error: Nombre de cartes a moure incorrecte" << endl;
                }
            else (moveCardsAux_toC(stack, columns, num, originIndex, destinationIndex));
            }
        }
    else if (origin.front() == 'C') {
        if (destination.front() == 'M') {
            moveCardsAux_toM(columns[originIndex - 1], foundations, num, destinationIndex);
            }
        else if (destination.front() == 'C') {
            moveCardsAux_toC(columns[originIndex - 1], columns, num, originIndex, destinationIndex);
            }
        }
    else if (origin.front() == 'M') {
        if (destination.front() == 'C') {
            Card card;
            vector<Card> tempStack;
            card.value = foundations[originIndex - 1].lastCardID;
            card.suit = foundations[originIndex - 1].suit;
            tempStack.push_back(card);
            if (num != 1) {
                cout << "Error: Nombre de cartes a moure incorrecte" << endl;
                }
            else if (moveCardsAux_toC(tempStack, columns, num, originIndex, destinationIndex))	foundations[originIndex - 1].lastCardID--;
            }
        }
    }

// PRE: columns(columnes) conté les 7 columnes, stack(pila) i foundations(magatzems) reflecteixen l’estat actual del joc.
// POST: mostra per pantalla l’estat actual del joc: pila, magatzems i columnes.
void showGameState(const vector<vector<Card>>& columns, const vector<Card>& stack, const Foundation foundations[NUM_FOUNDATIONS]) {
    cout << "Pila:";
    if (stack.empty()) {
        cout << " -" << endl;
        }
    else
        {
        cout << " " << printableCard(stack.back()) << endl;
        }

    for (int i = 0; i < NUM_FOUNDATIONS; ++i) {
        cout << "Mag " << i + 1 << ":";
        if (foundations[i].lastCardID == 0) {
            cout << " -" << endl;
            }
        else
            {
            for (int j = 0; j < foundations[i].lastCardID; ++j) {
                // Inv: S’han mostrat les j primeres cartes del magatzem i.
                Card card;
                card.value = j + 1;
                card.suit = foundations[i].suit;
                cout << " " << printableCard(card);
                }
            cout << endl;
            }
        }

    for (int i = 0; i < NUM_COLUMNS; ++i) {
        cout << "Col " << i + 1 << ":";
        if (columns[i].empty()) {
            cout << " -" << endl;
            }
        else
            {
            for (int j = 0; j < columns[i].size(); ++j) {
                // Inv: S’han mostrat les j primeres cartes de la columna i.
                cout << " " << printableCard(columns[i][j]);
                }
            cout << endl;
            }
        }
    cout << "---" << endl;
    }
int main() {
    vector<Card> stack;
    vector<vector<Card>> columns(NUM_COLUMNS);
    Foundation foundations[NUM_FOUNDATIONS];

    readInit(columns, stack, foundations);

    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    char commandChar = ' ';
    int moveCounter = 0;
    while (commandChar != 'Z') {
        // Inv: L'estat del joc reflecteix correctament totes les comandes llegides fins ara,
        // i moveCounter conté el nombre de moviments realitzats.
        cin >> commandChar;

        switch (commandChar) {
            case 'D':
            discardCard(stack);
            moveCounter++;
            if (checkEndGame(foundations, commandChar, moveCounter)) {
                showGameState(columns, stack, foundations);
                cout << "Felicitats has guanyat!! Ho has fet en " << moveCounter;
                if (moveCounter == 1) {
                    cout << " moviment." << endl;
                    }
                else {
                    cout << " moviments." << endl;
                    }
                commandChar = 'Z';
                }
            break;
            case 'M':
            moveCards(columns, stack, foundations);
            moveCounter++;
            if (checkEndGame(foundations, commandChar, moveCounter)) {
                showGameState(columns, stack, foundations);
                cout << "Felicitats has guanyat!! Ho has fet en " << moveCounter;
                if (moveCounter == 1) {
                    cout << " moviment." << endl;
                    }
                else {
                    cout << " moviments." << endl;
                    }
                commandChar = 'Z';
                }
            break;
            case 'S':
            showGameState(columns, stack, foundations);
            break;
            case 'Z':
            if (!checkEndGame(foundations, commandChar, moveCounter)) {
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
        }
    }