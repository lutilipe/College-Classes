#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include "card.h"

using namespace std;

#ifndef HAND_SIZE 
#define HAND_SIZE 5
#endif

enum CardRank {
    HighCard,
    OnePair,
    TwoPairs,
    ThreeOfAKind,
    Straight,
    Flush,
    FullHouse,
    FourOfAKind,
    StraightFlush,
    RoyalStraightFlush,
};

static const string CardRankStr[] = {
    "HC",
    "OP",
    "TP",
    "TK",
    "S",
    "F",
    "FH",
    "FK",
    "SF",
    "RSF",
};

class Player {
    private:
        string name;
        int amount;
        Card hand[HAND_SIZE];
        bool isPlaying = true;
        int bet = 0;

        void organizeHand();
    public:
        Player() { name = ""; amount = 0; };
        Player(string n, float a);
        Card* getHand() { return hand; };
        string getName() { return name; };
        bool getIsPlaying() { return isPlaying; };
        void setIsPlaying(bool playing) { isPlaying = playing; };
        int getAmount() { return amount; };
        void doAnte(int ante);
        void doBet();
        void setBet(int b) { bet = b; };
        int getBet() { return bet; };
        void setHand(ifstream* in);
        void printHand();

        CardRank getCardRank();
};

#endif