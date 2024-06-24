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
    Player** NPCs;
    Room** allTheRooms;
    int numberOfPlayer;
    int numberOfNPCs;
} Game;

void printMapAndPlayer(Player firstPlayer, int map[25][24], Game newGame);
void resetMovementPossibilities(int moveArray[4]);
void updateMovementPossibilities(int moveArray[4], int i, int j, int map[25][24]);
void printPossibilities(int moveArray[4]);
int rollTheDice();

void playerMovement(Player *player, int map[25][24], Game newGame);
void createANewGame(const Position *startersPos, Game *newGame, int map[25][24]);
void removeFromAnArray(int* indexArray, int startingPos, int length);
void initPlayer(Player* player, int choice, int posX, int posY);
void createRoomsExitDoor(const Game *newGame);
void printCardForAPlayer(const Player *player);

int chooseAPlayer(int index);
void printNameWithInt(CharactersName name);
void printWeaponsWithInt(Weapons weaponsName);
void printRoomsWithInt(RoomsName roomsName);

void createRooms(const Game *newGame, int i);
void movePlayerToRandomPosInARoom(Game *newGame, int indexPlayer, Player *playerToMove);

int getIndexByName(Game *newGame, CharactersName *nameChoice);
void ChoosePlayerAndWeapon(CharactersName *nameChoice, Weapons *weaponChoice);

#endif //CLUEDO_GAME_H
