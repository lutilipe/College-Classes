#ifndef GAME_H
#define GAME_H

#include "player.h"
#include <fstream>

using namespace std;

class Game {
    private:
        int numberOfRounds = 0;
        int initialAmount = 0;
        int numberOfPlayersInRound = 0;
        int totalNumberOfPlayers = 0;
        int anteValue = 0;
        bool isRoundValid = true;
        ifstream in;

        Player** players;
        PlayerRef* playersInRound;

        void setRound(bool isFirstRound = false);
        void initPlayers();
        void getPlayerRoundInfo(string* name, int* bet);
        Player* createPlayer();

        void handleRound(bool isFirstRound = false);

        void setPlayersRank();
        void sortPlayersByRank();
        void checkForDraws();
        void handleDraws();
        void handleWinners();

        Hand::ComparationResult handleComparation(int i, int j);

        void mountPlayersInRound(bool isFirstRound = false);
    public:
        Game(string inFile);
        ~Game();

        int getNumberOfRounds() { return numberOfRounds; };
        int getInitialAmount() { return initialAmount; };

        void play();
};

#endif