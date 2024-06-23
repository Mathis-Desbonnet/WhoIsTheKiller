//
// Created by Mathi on 6/18/2024.
//

#include "game.h"

void createRooms(const Game *newGame, int i);

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
                if (map[i][j] == 2 || map[i][j]<0) {
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
    printf("Movement Left : %d\n", diceNumber);
    printMapAndPlayer((*player), map, newGame);
    while (diceNumber > 0) {
        resetMovementPossibilities(movePossibilities);
        if (player->roomIndexIn == -1) {
            updateMovementPossibilities(movePossibilities, (*player).playerPos.posX, (*player).playerPos.posY, map);
        }
        printPossibilities(movePossibilities);
        if (player->roomIndexIn != -1) {
            printf("Exit the room -> 5\n");
        } else if (map[(*player).playerPos.posX][(*player).playerPos.posY] >= 3) {
            printf("Enter the room -> 5\n");
        }
        printf("\n\n\n\n\n\n\n\n\n");
        scanf("%d", &choice);
        printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
        int randomPositionIntoTheRoom;
        int canGoInTheRoom = 1;
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
                        do {
                            randomPositionIntoTheRoom = rand()%newGame.allTheRooms[player->roomIndexIn]->roomPosLogSize;
                            canGoInTheRoom = 1;
                            for (int i = 0; i<newGame.numberOfPlayer; i++) {
                                if (newGame.allThePlayers[i]->playerPos.posX == newGame.allTheRooms[player->roomIndexIn]->roomPosition[randomPositionIntoTheRoom].posX && newGame.allThePlayers[i]->playerPos.posX == newGame.allTheRooms[player->roomIndexIn]->roomPosition[randomPositionIntoTheRoom].posY) {
                                    canGoInTheRoom = 0;
                                }
                            }
                        } while (!canGoInTheRoom);
                        player->playerPos.posX = newGame.allTheRooms[player->roomIndexIn]->roomPosition[randomPositionIntoTheRoom].posX;
                        player->playerPos.posY = newGame.allTheRooms[player->roomIndexIn]->roomPosition[randomPositionIntoTheRoom].posY;
                        diceNumber--;
                    }
                } else if (player->roomIndexIn != -1) {
                    for (int i = 0; i<newGame.allTheRooms[player->roomIndexIn]->numberOfDoors; i++) {
                        printf("Exit %d : %d-%d\n", i+1, newGame.allTheRooms[player->roomIndexIn]->allDoors[i].posXOut, newGame.allTheRooms[player->roomIndexIn]->allDoors[i].posYOut);
                    }
                    do {
                        printf("Choose your exit :");
                        scanf("%d", &choice);
                    } while (choice < 0 && choice >= newGame.allTheRooms[player->roomIndexIn]->numberOfDoors);
                    player->playerPos.posX = newGame.allTheRooms[player->roomIndexIn]->allDoors[choice-1].posXOut;
                    player->playerPos.posY = newGame.allTheRooms[player->roomIndexIn]->allDoors[choice-1].posYOut;
                    (*player).roomIndexIn = -1;
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

void createANewGame(const Position *startersPos, Game *newGame, int map[25][24]) {
    int choice;

    //Create all rooms
    (*newGame).allTheRooms = (Room**) malloc(sizeof(Room*) * 10);
    for (int i = 0; i<9; i++) {
        createRooms(newGame, i);
    }
    int index;
    //Append all position for all the rooms into their array
    for (int i = 0; i<25; i++) {
        for (int j = 0; j<24; j++) {
            index = map[i][j];
            if (index < 0) {
                (*newGame).allTheRooms[index+10]->roomPosition = (Position*) realloc((*newGame).allTheRooms[index+10]->roomPosition, ((*newGame).allTheRooms[index+10]->roomPosLogSize+1)*
                                                                                                                              sizeof(Position));
                newGame->allTheRooms[index+10]->roomPosition[(*newGame).allTheRooms[index+10]->roomPosLogSize].posX = i;
                newGame->allTheRooms[index+10]->roomPosition[(*newGame).allTheRooms[index+10]->roomPosLogSize].posY = j;
                (*newGame).allTheRooms[index+10]->roomPosLogSize += 1;
            }
        }
    }
    //Create exit Doors
    createRoomsExitDoor(newGame);

    //Creation of the killer

    int allIndex[21] = {0, 1, 2, 3, 4, 5, 10, 11, 12, 13, 14, 15, 20, 21, 22, 23, 24, 25, 26, 27, 28};

    newGame->killer.name = rand()%6;
    newGame->killer.weapons = rand()%6;
    newGame->killer.room = rand()%9;

    removeFromAnArray(allIndex, newGame->killer.name, 21);
    removeFromAnArray(allIndex, newGame->killer.weapons+5, 20);
    removeFromAnArray(allIndex, newGame->killer.room+10, 19);

    printNameWithInt(newGame->killer.name);
    printWeaponsWithInt(newGame->killer.weapons);
    printRoomsWithInt(newGame->killer.room);
    printf("\n");


    int indexPlayerGettingCard = 0;

    //Creation of players
    printf("Choose number of player :");
    scanf("%d", &choice);
    (*newGame).numberOfPlayer = choice;
    (*newGame).allThePlayers = (Player**) malloc(sizeof(Player*) * newGame->numberOfPlayer);
    for (int i = 0; i < (*newGame).numberOfPlayer; i++) {
        choice = chooseAPlayer(i);
        //Init the player
        (*newGame).allThePlayers[i] = (Player*) malloc(sizeof(Player));
        initPlayer(newGame->allThePlayers[i], choice, startersPos[choice].posX, startersPos[choice].posY);
    }

    //Create NPCs
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

    //Add Card for players
    int random;
    for (int i = 0; i<18; i++) {
        newGame->allThePlayers[indexPlayerGettingCard]->Card->playerCards = (int*) realloc(newGame->allThePlayers[indexPlayerGettingCard]->Card->playerCards,
                                                                                           sizeof(int)*(newGame->allThePlayers[indexPlayerGettingCard]->Card->numberOfCard+1));
        random = rand()%(18-i);
        newGame->allThePlayers[indexPlayerGettingCard]->Card->playerCards[newGame->allThePlayers[indexPlayerGettingCard]->Card->numberOfCard] = allIndex[random];
        for (int j = random; j<17-i; j++) {
            allIndex[j] = allIndex[j+1];
        }
        newGame->allThePlayers[indexPlayerGettingCard]->Card->numberOfCard += 1;
        indexPlayerGettingCard++;
        indexPlayerGettingCard = indexPlayerGettingCard%(newGame->numberOfPlayer);
    }

    //Print Card
    for (int i = 0; i<newGame->numberOfPlayer; i++) {
        printf("PLAYER %d, please look at your card, write them down, then enter to go to the other player !\n", i+1);
        printf("Enter something to continue :");
        scanf("%d", &choice);
        printf("\n\n\n\n");
        printf("Card of player %d : ", i+1);
        printCardForAPlayer(newGame->allThePlayers[i]);
        printf("\n\n\n\n");
        printf("\nEnter something to continue :");
        scanf("%d", &choice);
        printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    }
}

void createRooms(const Game *newGame, int i) {
    (*newGame).allTheRooms[i] = (Room*) malloc(sizeof(Room));
    (*newGame).allTheRooms[i]->name = i;
    (*newGame).allTheRooms[i]->secretWay = NULL;
    (*newGame).allTheRooms[i]->allDoors = NULL;
    (*newGame).allTheRooms[i]->roomPosition = NULL;
    (*newGame).allTheRooms[i]->roomPosLogSize = 0;
}

int chooseAPlayer(int index) {
    int error, choice;
    char* allNames[6] = {"MOUTARDE", "OLIVE", "VIOLET", "PERVENCHE", "ROSE", "LEBLANC"};
    int allNamesIndex[6] = {0, 1, 2, 3, 4, 5};
    do {
        printf("Choose your player :\n");
        //List of all the characters available
        for (int j = 0; j<6-index; j++) {
            printf("%d -> %s\n", allNamesIndex[j], allNames[allNamesIndex[j]]);
        }
        error = scanf("%d", &choice);
    } while (choice < 0 || choice > 6 || error == 0);
    //Delete index of names for the listing
    for (int j = 0; j<6-index-1; j++) {
        if (allNamesIndex[j] >= choice) {
            allNamesIndex[j] = allNamesIndex[j+1];
        }
    }
    return choice;
}

void initPlayer(Player* player, int choice, int posX, int posY) {
    player->name = choice;
    player->playerPos.posX = posX;
    player->playerPos.posY = posY;
    player->roomIndexIn = -1;
    player->Card = (Card*) malloc(sizeof(Card));
    player->Card->playerCards = NULL;
    player->Card->numberOfCard = 0;
}

void removeFromAnArray(int* indexArray, int startingPos, int length) {
    for (int i = startingPos; i<length-1; i++) {
        indexArray[i] = indexArray[i+1];
    }
}

void printCardForAPlayer(const Player *player) {
    for (int j = 0; j < player->Card->numberOfCard; j++) {
        if (player->Card->playerCards[j] < 10) {
            printNameWithInt(player->Card->playerCards[j]);
        } else if (player->Card->playerCards[j] < 20) {
            printWeaponsWithInt(player->Card->playerCards[j]-10);
        } else {
            printRoomsWithInt(player->Card->playerCards[j]-20);
        }
    }
}

void createRoomsExitDoor(const Game *newGame) {
    newGame->allTheRooms[HALL]->allDoors = (Doors*) malloc(sizeof(Doors) * 2);
    newGame->allTheRooms[HALL]->numberOfDoors = 2;
    newGame->allTheRooms[HALL]->allDoors[0].posXOut = 7;
    newGame->allTheRooms[HALL]->allDoors[0].posYOut = 11;
    newGame->allTheRooms[HALL]->allDoors[1].posXOut = 7;
    newGame->allTheRooms[HALL]->allDoors[1].posYOut = 12;

    newGame->allTheRooms[BAR]->allDoors = (Doors*) malloc(sizeof(Doors));
    newGame->allTheRooms[BAR]->numberOfDoors = 1;
    newGame->allTheRooms[BAR]->allDoors[0].posXOut = 6;
    newGame->allTheRooms[BAR]->allDoors[0].posYOut = 17;

    newGame->allTheRooms[SALLE_A_MANGER]->allDoors = (Doors*) malloc(sizeof(Doors)*2);
    newGame->allTheRooms[SALLE_A_MANGER]->numberOfDoors = 2;
    newGame->allTheRooms[SALLE_A_MANGER]->allDoors[0].posXOut = 8;
    newGame->allTheRooms[SALLE_A_MANGER]->allDoors[0].posYOut = 17;
    newGame->allTheRooms[SALLE_A_MANGER]->allDoors[1].posXOut = 12;
    newGame->allTheRooms[SALLE_A_MANGER]->allDoors[1].posYOut = 15;

    newGame->allTheRooms[CUISINE]->allDoors = (Doors*) malloc(sizeof(Doors));
    newGame->allTheRooms[CUISINE]->numberOfDoors = 1;
    newGame->allTheRooms[CUISINE]->allDoors[0].posXOut = 17;
    newGame->allTheRooms[CUISINE]->allDoors[0].posYOut = 19;

    newGame->allTheRooms[SALLE_DE_BALLE]->allDoors = (Doors*) malloc(sizeof(Doors)*4);
    newGame->allTheRooms[SALLE_DE_BALLE]->numberOfDoors = 4;
    newGame->allTheRooms[SALLE_DE_BALLE]->allDoors[0].posXOut = 19;
    newGame->allTheRooms[SALLE_DE_BALLE]->allDoors[0].posYOut = 7;
    newGame->allTheRooms[SALLE_DE_BALLE]->allDoors[1].posXOut = 16;
    newGame->allTheRooms[SALLE_DE_BALLE]->allDoors[1].posYOut = 9;
    newGame->allTheRooms[SALLE_DE_BALLE]->allDoors[2].posXOut = 16;
    newGame->allTheRooms[SALLE_DE_BALLE]->allDoors[2].posYOut = 14;
    newGame->allTheRooms[SALLE_DE_BALLE]->allDoors[3].posXOut = 19;
    newGame->allTheRooms[SALLE_DE_BALLE]->allDoors[3].posYOut = 16;

    newGame->allTheRooms[CONSERVATOIRE]->allDoors = (Doors*) malloc(sizeof(Doors));
    newGame->allTheRooms[CONSERVATOIRE]->numberOfDoors = 1;
    newGame->allTheRooms[CONSERVATOIRE]->allDoors[0].posXOut = 19;
    newGame->allTheRooms[CONSERVATOIRE]->allDoors[0].posYOut = 5;

    newGame->allTheRooms[BILLIARD]->allDoors = (Doors*) malloc(sizeof(Doors)*2);
    newGame->allTheRooms[BILLIARD]->numberOfDoors = 2;
    newGame->allTheRooms[BILLIARD]->allDoors[0].posXOut = 15;
    newGame->allTheRooms[BILLIARD]->allDoors[0].posYOut = 6;
    newGame->allTheRooms[BILLIARD]->allDoors[1].posXOut = 11;
    newGame->allTheRooms[BILLIARD]->allDoors[1].posYOut = 1;

    newGame->allTheRooms[BIBLIOTHEQUE]->allDoors = (Doors*) malloc(sizeof(Doors)*2);
    newGame->allTheRooms[BIBLIOTHEQUE]->numberOfDoors = 2;
    newGame->allTheRooms[BIBLIOTHEQUE]->allDoors[0].posXOut = 11;
    newGame->allTheRooms[BIBLIOTHEQUE]->allDoors[0].posYOut = 3;
    newGame->allTheRooms[BIBLIOTHEQUE]->allDoors[1].posXOut = 8;
    newGame->allTheRooms[BIBLIOTHEQUE]->allDoors[1].posYOut = 7;

    newGame->allTheRooms[BUREAU]->allDoors = (Doors*) malloc(sizeof(Doors));
    newGame->allTheRooms[BUREAU]->numberOfDoors = 1;
    newGame->allTheRooms[BUREAU]->allDoors[0].posXOut = 4;
    newGame->allTheRooms[BUREAU]->allDoors[0].posYOut = 5;
}

void printNameWithInt(CharactersName name) {
    switch (name) {
        case 0 :
            printf("Moutarde\t");
            break;
        case 1 :
            printf("Olive\t");
            break;
        case 2 :
            printf("Violet\t");
            break;
        case 3 :
            printf("Pervenche\t");
            break;
        case 4 :
            printf("Rose\t");
            break;
        case 5 :
            printf("Leblanc\t");
            break;
        default : printf("PROBLEMMMEE"); break;
    }
}

void printWeaponsWithInt(Weapons weaponsName) {
    switch (weaponsName) {
        case 0 :
            printf("POIGNARD\t");
            break;
        case 1 :
            printf("CHANDELIER\t");
            break;
        case 2 :
            printf("REVOLVER\t");
            break;
        case 3 :
            printf("CORDE\t");
            break;
        case 4 :
            printf("BARRE_DE_FER\t");
            break;
        case 5 :
            printf("CLE_A_MOLETTE\t");
            break;
        default : printf("PROBLEMMMEE"); break;
    }
}

void printRoomsWithInt(RoomsName roomsName) {
    switch (roomsName) {
        case 0 :
            printf("HALL\t");
            break;
        case 1 :
            printf("BAR\t");
            break;
        case 2 :
            printf("SALLE_A_MANGER\t");
            break;
        case 3 :
            printf("CUISINE\t");
            break;
        case 4 :
            printf("SALLE_DE_BALLE\t");
            break;
        case 5 :
            printf("CONSERVATOIRE\t");
            break;
        case 6 :
            printf("BILLIARD\t");
            break;
        case 7 :
            printf("BIBLIOTHEQUE\t");
            break;
        case 8 :
            printf("BUREAU\t");
            break;
        default : printf("PROBLEMMMEE"); break;
    }
}