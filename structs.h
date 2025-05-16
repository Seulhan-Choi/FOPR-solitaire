#ifndef STRUCTS_H
#define STRUCTS_H

struct Card {
    int value;  // 1-13 (Ace-King)
    int suit;   // 0-3 ( ♥, ♦, ♠, ♣)
};

struct Storage {
    int availableID = 1; // Start from Ace (1)
    int suit;
};

#endif