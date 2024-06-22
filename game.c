//
// Created by Mathi on 6/18/2024.
//

#include "game.h"

void printMapAndPlayer(Player firstPlayer, int map[25][24], Game newGame) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int printPlayer;
    for (int i = 0; i < 25; i++) {
        for (int j = 0; j < 24; j++) {
            printPlayer = 0;
            for (int k = 0; k < newGame.numberOfPlayer; k++) {
                if (newGame.allThePlayers[k]->playerPos.posX == i && newGame.allThePlayers[k]->playerPos.posY == j) {
                    switch (newGame.allThePlayers[k]->name) {

                        case MOUTARDE:
                            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
                            break;
                        case OLIVE:
                            SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
                            break;
                        case VIOLET:
                            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                            break;
                        case PERVENCHE:
                            SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
                            break;
                        case ROSE:
                            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
                            break;
                        case LEBLANC:
                            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                            break;
                    }
                    printPlayer = 1;
                }
            }
            for (int k = 0; k < newGame.numberOfNPCs; k++) {
                if (newGame.NPCs[k]->playerPos.posX == i && newGame.NPCs[k]->playerPos.posY == j) {
                    switch (newGame.NPCs[k]->name) {
                        case MOUTARDE:
                            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
                            break;
                        case OLIVE:
                            SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
                            break;
                        case VIOLET:
                            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                            break;
                        case PERVENCHE:
                            SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
                            break;
                        case ROSE:
                            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
                            break;
                        case LEBLANC:
                            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                            break;
                    }
                    printPlayer = 1;
                }
            }
            if (printPlayer) {
                printf("X");
            } else {
                if (map[i][j] == 2) {
                    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                    printf("#");
                }
                if (map[i][j] == 1) {
                    SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                    printf("0");
                }
                if (map[i][j] == 0) {
                    printf(" ");
                }
                if (map[i][j] >= 3) {
                    SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
                    printf("|");
                }
            }
        }
        printf("\n");
        switch (firstPlayer.name) {
            case MOUTARDE:
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
                break;
            case OLIVE:
                SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
                break;
            case VIOLET:
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                break;
            case PERVENCHE:
                SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
                break;
            case ROSE:
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
                break;
            case LEBLANC:
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                break;
        }
    }
}

void resetMovementPossibilities(int moveArray[4]) {
    for (int i = 0; i<4; i++) {
        moveArray[i] = 0;
    }
}

void updateMovementPossibilities(int moveArray[4], int i, int j, int map[25][24]) {
    if (i > 0) {
        if (map[i-1][j] == 1 || map[i-1][j] >= 13) {
            moveArray[0] = 1;
        }
    }
    if (j < 24) {
        if (map[i][j+1] == 1 || map[i][j+1] >= 13) {
            moveArray[1] = 1;
        }
    }
    if (i < 25) {
        if (map[i+1][j] == 1 || map[i+1][j] >= 13) {
            moveArray[2] = 1;
        }
    }
    if (j > 0) {
        if (map[i][j-1] == 1 || map[i][j-1] >= 13) {
            moveArray[3] = 1;
        }
    }
}

void printPossibilities(int moveArray[4]) {
    printf("Choose your next movement :\n");
    if (moveArray[0] == 1) {
        printf("You can go UP -> 1\n");
    }
    if (moveArray[1] == 1) {
        printf("You can go RIGHT -> 2\n");
    }
    if (moveArray[2] == 1) {
        printf("You can go DOWN -> 3\n");
    }
    if (moveArray[3] == 1) {
        printf("You can go LEFT -> 4\n");
    }
}

int rollTheDice() {
    return rand()%11 + 1;
}

void playerMovement(Player *player, int map[25][24], Game newGame) {
    int diceNumber = rollTheDice();
    int choice;
    int movePossibilities[4];
    printf("%d\n", diceNumber);
    printMapAndPlayer((*player), map, newGame);
    while (diceNumber > 0) {
        resetMovementPossibilities(movePossibilities);
        updateMovementPossibilities(movePossibilities, (*player).playerPos.posX, (*player).playerPos.posY, map);
        printPossibilities(movePossibilities);
        if (map[(*player).playerPos.posX][(*player).playerPos.posY] >= 3) {
            if ((*player).roomIndexIn == -1) {
                printf("Enter the room -> 5\n");
            } else {
                printf("Exit the room -> 5\n");
            }
        }
        printf("\n\n\n\n\n\n\n\n\n");
        scanf("%d", &choice);
        printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
        switch (choice) {
            case 1:
                if (movePossibilities[0] == 1) {
                    (*player).playerPos.posX -= 1;
                    diceNumber--;
                } else {
                    printf("MOVEMENT NOT POSSIBLE\n");
                }
                break;
            case 2:
                if (movePossibilities[1] == 1) {
                    (*player).playerPos.posY += 1;
                    diceNumber--;
                } else {
                    printf("MOVEMENT NOT POSSIBLE\n");
                }
                break;
            case 3:
                if (movePossibilities[2] == 1) {
                    (*player).playerPos.posX += 1;
                    diceNumber--;
                } else {
                    printf("MOVEMENT NOT POSSIBLE\n");
                }
                break;
            case 4:
                if (movePossibilities[3] == 1) {
                    (*player).playerPos.posY -= 1;
                    diceNumber--;
                } else {
                    printf("MOVEMENT NOT POSSIBLE\n");
                }
                break;
            case 5:
                if (map[(*player).playerPos.posX][(*player).playerPos.posY] >= 13) {
                    if ((*player).roomIndexIn == -1) {
                        (*player).roomIndexIn = map[(*player).playerPos.posX][(*player).playerPos.posY] - 13;
                    } else {
                        (*player).roomIndexIn = -1;
                    }
                    diceNumber--;
                } else {
                    printf("MOVEMENT NOT POSSIBLE\n");
                }
                break;
            default:
                printf("MOVEMENT NOT POSSIBLE\n");
                break;
        }
        printf("Movement Left : %d\n", diceNumber);
        printMapAndPlayer((*player), map, newGame);
    }
}

void createANewGame(const Position *startersPos, Game *newGame) {
    int choice, error;
    char* allNames[6] = {"MOUTARDE", "OLIVE", "VIOLET", "PERVENCHE", "ROSE", "LEBLANC"};
    int allNamesIndex[6] = {0, 1, 2, 3, 4, 5};
    (*newGame).allTheRooms = (Room**) malloc(sizeof(Room*) * 9);
    for (int i = 0; i<9; i++) {
        (*newGame).allTheRooms[i] = (Room*) malloc(sizeof(Room));
        (*newGame).allTheRooms[i]->name = i;
        (*newGame).allTheRooms[i]->secretWay = NULL;
        (*newGame).allTheRooms[i]->allDoors = NULL;
    }
    printf("Choose number of player :");
    scanf("%d", &choice);
    (*newGame).numberOfPlayer = choice;
    (*newGame).allThePlayers = (Player**) malloc(sizeof(Player*) * newGame->numberOfPlayer);
    for (int i = 0; i < (*newGame).numberOfPlayer; i++) {
        (*newGame).allThePlayers[i] = (Player*) malloc(sizeof(Player));
        do {
            printf("Choose your player :\n");
            //List of all the characters available
            for (int j = 0; j<6-i; j++) {
                printf("%d -> %s\n", allNamesIndex[j], allNames[allNamesIndex[j]]);
            }
            error = scanf("%d", &choice);
        } while (choice < 0 || choice > 6 || error == 0);
        //Delete index of names for the listing
        for (int j = 0; j<6-i-1; j++) {
            if (allNamesIndex[j] >= choice) {
                allNamesIndex[j] = allNamesIndex[j+1];
            }
        }
        //Init the player
        (*newGame).allThePlayers[i]->name = choice;
        (*newGame).allThePlayers[i]->playerPos.posX = startersPos[choice].posX;
        (*newGame).allThePlayers[i]->playerPos.posY = startersPos[choice].posY;
        (*newGame).allThePlayers[i]->roomIndexIn = -1;
    }
    int isAPlayer;
    newGame->numberOfNPCs = 6 - newGame->numberOfPlayer;
    newGame->NPCs = (Player**) malloc(sizeof(Player*)*newGame->numberOfNPCs);
    int indexOfNPCs = 0;
    for (int i = 0; i<6; i++) {
        //Search if the character is a player
        isAPlayer = 0;
        for (int j = 0; j<newGame->numberOfPlayer; j++) {
            if (newGame->allThePlayers[j]->name == i) {
                isAPlayer = 1;
            }
        }
        //If not, adding him to the NPCs array
        if (!isAPlayer) {
            newGame->NPCs[indexOfNPCs] = (Player*) malloc(sizeof(Player));
            newGame->NPCs[indexOfNPCs]->name = i;
            (*newGame).NPCs[indexOfNPCs]->playerPos.posX = startersPos[i].posX;
            (*newGame).NPCs[indexOfNPCs]->playerPos.posY = startersPos[i].posY;
            indexOfNPCs++;
        }
    }
}