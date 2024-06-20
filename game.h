//
// Created by Mathi on 6/18/2024.
//

#include "characters.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#ifndef CLUEDO_GAME_H
#define CLUEDO_GAME_H

typedef struct {
    Killer killer;
    Player** allThePlayers;
    Room** allTheRooms;
} Game;

void printMapAndPlayer(Player firstPlayer, int map[25][24]);
void resetMovementPossibilities(int moveArray[4]);
void updateMovementPossibilities(int moveArray[4], int i, int j, int map[25][24]);
void printPossibilities(int moveArray[4]);
int rollTheDice();

#endif //CLUEDO_GAME_H
