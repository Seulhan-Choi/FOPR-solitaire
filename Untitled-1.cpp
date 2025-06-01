#include <iostream>
#include <vector>
#include <string>

using namespace std;

//---------------------------------------------------------------------------------------------
// STRUCTS
struct Card {
    int value;  // 1-13 (As-Rei)
    int suit;   // 0-3 ( ♥, ♦, ♠, ♣)
};

struct Storage {
    int lastCardID = 0;
    int suit;
};
//---------------------------------------------------------------------------------------------
// FUNCTIONS

// PRE: columns és buit, stack és buit, storage està inicialitzat amb els pals corresponents (0-3).
// POST: columns, stack i storage queden plens amb les cartes inicials llegides de l’entrada.
void readInit(vector<vector<Card>>& columns, vector<Card>& stack, Storage (&storage)[4]) {
    for (int i = 0; i < 7; ++i) {   
        // Inv: S’han inicialitzat les primeres i columnes amb les cartes llegides de l’entrada.
        int n;
        cin >> n;
        for (int j = 0; j < n; ++j) {
            // Inv: La columna i conté les j primeres cartes llegides, en l’ordre d’entrada.
            string input;
            cin >> input;
            columns[i].push_back(readCard(input));
        }
    }

    for (int i = 0; i < 4; ++i) { 
        // Inv: S’han inicialitzat els primers i magatzems amb el nombre de cartes corresponents.
        int n;
        cin >> n;
        storage[i].lastCardID = n;
        storage[i].suit = i;
        for (int j = 0; j < n; ++j) {
            // Inv: S’han llegit i descartat j cartes per al magatzem i.
            string dummy;
            cin >> dummy;
        }
    }

    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        // Inv: stack conté les i primeres cartes llegides, en ordre invers (lúltima carta llegida al davant).
        string input;
        cin >> input;
        stack.insert(stack.begin(), readCard(input));
    }
}

// PRE: input és una string representant una carta vàlida, com "AS" o "10C".
// POST: retorna un Card amb el valor i pal corresponent.
Card readCard(string input) {
    int value;
    char suitChar = input.back();
    if (input[0] == 'A') value = 1;
    else if (input[0] == 'J') value = 11;
    else if (input[0] == 'Q') value = 12;
    else if (input[0] == 'K') value = 13;
    else if (input[0] == '1' && input.size() > 1 && input[1] == '0') value = 10;
    else value = input[0] - '0';

    int suit = 4;
    switch (suitChar) {
        case 'C': suit = 0; break;
        case 'D': suit = 1; break;
        case 'P': suit = 2; break;
        case 'T': suit = 3; break;
        default: suit = 4;
    }
    return {value, suit};
}

// PRE: temp és una carta vàlida, num és 1, destinationNum ∈ [1,4].
// POST: retorna true si la carta es pot moure al magatzem corresponent i actualitza storage. Retorna false si no es pot.
bool moveCardsAux_toM(Card temp, Storage (&storage)[4], int num, int destinationNum) {
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
        return true;
    }
}

// PRE: temp és una carta vàlida, num és 1, destinationNum ∈ [1,7].
// POST: retorna true si la carta es pot moure a la columna corresponent i s’afegeix; false si no.
bool moveCardsAux_toC(Card temp, vector<vector<Card>>& columns, int num, int destinationNum) {
    if (columns[destinationNum - 1].empty()) {
        if (temp.value == 13) {
            columns[destinationNum - 1].push_back(temp);
        }
        else {
            cout << "Error: No hi ha concordança de valor i/o pal" << endl;
            return false;
        }
    }
    else {
        Card topCard = columns[destinationNum - 1].back();
        if (topCard.suit % 2 != temp.suit % 2 && topCard.value - temp.value == 1) {
            columns[destinationNum - 1].push_back(temp);
            return true;
        }
        else {
            cout << "Error: No hi ha concordança de valor i/o pal" << endl;
            return false;
        }
    }
}

// PRE: card és una carta vàlida.
// POST: retorna una representació en string de la carta, amb símbol i color.
string printCard(const Card& card) {
    char outputValue = ' ';
    if (card.value == 1) outputValue = 'A';
    else if (card.value == 11) outputValue = 'J';
    else if (card.value == 12) outputValue = 'Q';
    else if (card.value == 13) outputValue = 'K';
    else outputValue = card.value + '0';
    string output;
    switch (card.suit) {
        case 0: output = outputValue + string("\033[0;31m♥\033[0m"); break;
        case 1: output = outputValue + string("\033[0;31m♦\033[0m"); break;
        case 2: output = outputValue + string("♠"); break;
        case 3: output = outputValue + string("♣"); break;
        default: output = outputValue; break;
    }
    return output;
}

// PRE: storage conté els valors finals dels magatzems, commandChar conté l’última acció, moveCounter ≥ 0.
// POST: mostra el missatge de victòria si s’han col·locat totes les cartes. Retorna true o false.
bool checkEndGame(Storage(&storage)[4], char& commandChar, int& moveCounter) {
    if (storage[0].lastCardID == 13 && storage[1].lastCardID == 13 && storage[2].lastCardID == 13 && storage[3].lastCardID == 13) {
        cout << "Felicitats has guanyat!! Ho has fet en " <<  moveCounter;
        if (moveCounter == 1) cout << " moviment." << endl;
        else cout << " moviments." << endl;
        commandChar = 'Z';
        return true;
    }
    return false;
}

// PRE: stack no és buit.
// POST: mou la carta superior del stack al fons del mateix.
void discardCard(vector<Card> &stack) {
    Card discardedCard = stack.back();
    stack.pop_back();
    stack.emplace(stack.begin(), discardedCard);
    cout << "discardCard" << endl;
}

// PRE: es llegeix de l’entrada una ordre de moviment vàlida amb origen, num i destí.
// POST: si el moviment és vàlid segons les regles del joc, mou la carta i actualitza l'estat.
void moveCards(vector<vector<Card>>& columns, vector<Card>& stack, Storage (&storage)[4]) {
    ...
}

// PRE: columns conté les 7 columnes, stack i storage reflecteixen l’estat actual del joc.
// POST: mostra per pantalla l’estat actual del joc.
void showGameState(const vector<vector<Card>> &columns, const vector<Card> &stack, const Storage storage[4]) {
    for (int i = 0; i < 4; ++i) {
        // Inv: S’han mostrat per pantalla els magatzems de l’1 fins a l’i.
        for (int j = 0; j < storage[i].lastCardID; ++j) {
            // Inv: S’han mostrat les j primeres cartes del magatzem i.
            ...
        }
    }
    for (int i = 0; i < 7; ++i) {
        // Inv: S’han mostrat les columnes de l’1 fins a la i.
        for (int j = 0; j < columns[i].size(); ++j) {
            // Inv: S’han mostrat les j primeres cartes de la columna i.
            ...
        }
    }
}

//---------------------------------------------------------------------------------------------
// MAIN

// PRE: L’entrada està correctament formatejada segons el joc (columnes, magatzems, pila, comandes).
// POST: executa el bucle del joc fins que s’introdueixi la comanda 'Z'.
int main() {
    ...
    while (commandChar != 'Z') {
        // Inv: L’estat del joc reflecteix correctament totes les comandes llegides fins ara,
        // i moveCounter conté el nombre de moviments realitzats.
        ...
    }
}
