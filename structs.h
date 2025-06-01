#ifndef STRUCTS_H
#define STRUCTS_H

enum Suit {
    CLUBS = 0,    // ♣
    SPADES = 1,   // ♠
    HEARTS = 2,   // ♥
    DIAMONDS = 3  // ♦
};

const int NUM_COLUMNS = 7; // Number of columns in the game
const int NUM_FOUNDATIONS = 4; // Number of foundations in the game

const int ACE_VALUE = 1;
const int JACK_VALUE = 11;
const int QUEEN_VALUE = 12;
const int KING_VALUE = 13;
//---------------------------------------------------------------------------------------------
// STRUCTS
struct Card {
    int value;
    Suit suit;
};

struct Foundation {
    int lastCardID = 0;
    Suit suit = CLUBS; // Initialize with a default value
};

#endif