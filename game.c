//
// Created by Mathi on 6/18/2024.
//

#include "game.h"

void printMapAndPlayer(Player firstPlayer, int map[25][24], Game newGame, SDL_Renderer* renderer) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SDL_Rect tempRect;
    tempRect.w = 40;
    tempRect.h = 40;
    int printPlayer;
    for (int i = 0; i < 25; i++) {
        for (int j = 0; j < 24; j++) {
            printPlayer = 0;
            for (int k = 0; k < newGame.numberOfPlayer; k++) {
                if (newGame.allThePlayers[k]->playerPos.posX == i && newGame.allThePlayers[k]->playerPos.posY == j) {
                    switch (newGame.allThePlayers[k]->name) {
                        case MOUTARDE:
                            SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
                            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
                            break;
                        case OLIVE:
                            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
                            SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
                            break;
                        case VIOLET:
                            SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
                            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                            break;
                        case PERVENCHE:
                            SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
                            SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
                            break;
                        case ROSE:
                            SDL_SetRenderDrawColor(renderer, 255, 125, 125, 255);
                            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
                            break;
                        case LEBLANC:
                            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
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
                            SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
                            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
                            break;
                        case OLIVE:
                            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
                            SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
                            break;
                        case VIOLET:
                            SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
                            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                            break;
                        case PERVENCHE:
                            SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
                            SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
                            break;
                        case ROSE:
                            SDL_SetRenderDrawColor(renderer, 255, 125, 125, 255);
                            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
                            break;
                        case LEBLANC:
                            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                            break;
                    }
                    printPlayer = 1;
                }
            }
            tempRect.x = j*40;
            tempRect.y = i*40;
            if (printPlayer) {
            } else {
                if (map[i][j] == 2 || map[i][j]<0) {
                    SDL_SetRenderDrawColor(renderer, 125, 125, 125, 255);
                    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                }
                if (map[i][j] == 1) {
                    SDL_SetRenderDrawColor(renderer, 255, 125, 255, 255);
                    SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                }
                if (map[i][j] == 0) {
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                }
                if (map[i][j] >= 3) {
                    SDL_SetRenderDrawColor(renderer, 125, 255, 125, 255);
                    SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
                }
            }
            SDL_RenderFillRect(renderer, &tempRect);
        }
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
    SDL_Log("Choose your next movement :\n");
    if (moveArray[0] == 1) {
        SDL_Log("You can go UP -> 1\n");
    }
    if (moveArray[1] == 1) {
        SDL_Log("You can go RIGHT -> 2\n");
    }
    if (moveArray[2] == 1) {
        SDL_Log("You can go DOWN -> 3\n");
    }
    if (moveArray[3] == 1) {
        SDL_Log("You can go LEFT -> 4\n");
    }
}

int rollTheDice() {
    return rand()%11 + 1;
}

void playerMovement(Player *player, int map[25][24], Game newGame, SDL_Renderer* renderer) {
    int diceNumber = rollTheDice();
    int choice;
    int movePossibilities[4];
    int indexPlayer;
    char* choiceText;
    CharactersName nameChoice;
    Weapons weaponChoice;
    RoomsName roomChoice;
    SDL_Log("Movement Left : %d\n", diceNumber);
    //printMapAndPlayer((*player), map, newGame);
    while (diceNumber > 0) {
        resetMovementPossibilities(movePossibilities);
        if (player->roomIndexIn == -1) {
            updateMovementPossibilities(movePossibilities, (*player).playerPos.posX, (*player).playerPos.posY, map);
        }
        printPossibilities(movePossibilities);
        if (player->roomIndexIn != -1) {
            SDL_Log("Exit the room -> 5\n");
        } else if (map[(*player).playerPos.posX][(*player).playerPos.posY] >= 3) {
            SDL_Log("Enter the room -> 5\n");
        }
        SDL_Log("Finish/Skip your turn -> 6\n");
        SDL_Log("If you want to accuse someone -> 7\n");
        SDL_Log("\n\n\n\n\n\n\n\n\n");
        int hasChoose = 0;
        while (!hasChoose) {
            SDL_Event newEvent;
            SDL_PollEvent(&newEvent);
            switch (newEvent.type) {
                case SDL_KEYDOWN:
                    switch (newEvent.key.keysym.sym) {
                        case SDLK_UP:
                            if (movePossibilities[0] == 1) {
                                (*player).playerPos.posX -= 1;
                                hasChoose = 1;
                                diceNumber--;
                            } else {
                                SDL_Log("MOVEMENT NOT POSSIBLE\n");
                            }
                            break;
                        case SDLK_RIGHT:
                            if (movePossibilities[1] == 1) {
                                (*player).playerPos.posY += 1;
                                hasChoose = 1;
                                diceNumber--;
                            } else {
                                SDL_Log("MOVEMENT NOT POSSIBLE\n");
                            }
                            break;
                        case SDLK_DOWN:
                            if (movePossibilities[2] == 1) {
                                (*player).playerPos.posX += 1;
                                hasChoose = 1;
                                diceNumber--;
                            } else {
                                SDL_Log("MOVEMENT NOT POSSIBLE\n");
                            }
                            break;
                        case SDLK_LEFT:
                            if (movePossibilities[3] == 1) {
                                (*player).playerPos.posY -= 1;
                                hasChoose = 1;
                                diceNumber--;
                            } else {
                                SDL_Log("MOVEMENT NOT POSSIBLE\n");
                            }
                            break;
                        case SDLK_e:
                            // If not in a room, but on a door
                            if (map[(*player).playerPos.posX][(*player).playerPos.posY] >= 13 && (*player).roomIndexIn == -1) {
                                (*player).roomIndexIn = map[(*player).playerPos.posX][(*player).playerPos.posY] - 13;

                                //Move to a random pos into the room
                                movePlayerToRandomPosInARoom(&newGame, indexPlayer, player);

                                SDL_Log("You can now make a request for someone !\n");
                                SDL_Log("If you want to make a request -> 1\nOr else -> 0\n");
                                choiceText = getInputStringFromPlayer();
                                sscanf(choiceText, "%d", &choice);
                                if (choice) {
                                    ChoosePlayerAndWeapon(&nameChoice, &weaponChoice);
                                    indexPlayer = getIndexByName(&newGame, &nameChoice);
                                    if (indexPlayer<10) {
                                        newGame.allThePlayers[indexPlayer]->roomIndexIn = player->roomIndexIn;

                                        //Move to a random pos into the room
                                        movePlayerToRandomPosInARoom(&newGame, indexPlayer, newGame.allThePlayers[indexPlayer]);
                                    } else {
                                        newGame.NPCs[indexPlayer-10]->roomIndexIn = player->roomIndexIn;

                                        //Move to a random pos into the room
                                        movePlayerToRandomPosInARoom(&newGame, indexPlayer, newGame.NPCs[indexPlayer-10]);
                                    }
                                }
                                diceNumber = 0;
                                hasChoose = 1;
                                //If in a room and want to exit
                            } else if (player->roomIndexIn != -1) {
                                for (int i = 0; i<newGame.allTheRooms[player->roomIndexIn]->numberOfDoors; i++) {
                                    SDL_Log("Exit %d : %d-%d\n", i+1, newGame.allTheRooms[player->roomIndexIn]->allDoors[i].posXOut, newGame.allTheRooms[player->roomIndexIn]->allDoors[i].posYOut);
                                }
                                do {
                                    SDL_Log("Choose your exit :");
                                    choiceText = getInputStringFromPlayer();
                                    sscanf(choiceText, "%d", &choice);
                                } while (choice < 0 && choice > newGame.allTheRooms[player->roomIndexIn]->numberOfDoors);
                                player->playerPos.posX = newGame.allTheRooms[player->roomIndexIn]->allDoors[choice-1].posXOut;
                                player->playerPos.posY = newGame.allTheRooms[player->roomIndexIn]->allDoors[choice-1].posYOut;
                                (*player).roomIndexIn = -1;
                                diceNumber--;
                                hasChoose = 1;
                                // If not in a room and NOT on a door
                            } else {
                                SDL_Log("MOVEMENT NOT POSSIBLE\n");
                            }
                            break;
                        case SDLK_s: // Skip a turn
                            diceNumber = 0;
                            hasChoose = 1;
                            break;
                        case SDLK_a: // Accuse someone
                            SDL_Log("WARNING : You are going to do an accusation. If you're sure about the killer you can continue. But if you're wrong, you will not be able to continue to play....\n");
                            SDL_Log("Continue -> 1\nExit -> 0");
                            choiceText = getInputStringFromPlayer();
                            sscanf(choiceText, "%d", &choice);
                            if (choice) {
                                SDL_Log("Choose the name of the killer:\n");
                                for (int i = 0; i<6; i++) {
                                    printNameWithInt(i);
                                    SDL_Log("-> %d\n", i);
                                }
                                choiceText = getInputStringFromPlayer();
                                sscanf(choiceText, "%d", &choice);
                                SDL_Log("Choose the weapon of the killer:\n");
                                for (int i = 0; i<6; i++) {
                                    printWeaponsWithInt(i);
                                    SDL_Log("-> %d\n", i);
                                }
                                choiceText = getInputStringFromPlayer();
                                sscanf(choiceText, "%d", &choice);
                                SDL_Log("Choose the room where M. LeNoir has been killed:\n");
                                for (int i = 0; i<9; i++) {
                                    printRoomsWithInt(i);
                                    SDL_Log("-> %d\n", i);
                                }
                                choiceText = getInputStringFromPlayer();
                                sscanf(choiceText, "%d", &choice);

                                SDL_Log("Keep the next screen secret, the identity of the killer will be revealed. If you're right, you'll win. Else, please, do not share any information !\n");
                                SDL_Log("Write something to continue:");
                                choiceText = getInputStringFromPlayer();
                                sscanf(choiceText, "%d", &choice);
                                SDL_Log("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
                                SDL_Log("The killer is :");
                                printNameWithInt(newGame.killer.name);
                                printWeaponsWithInt(newGame.killer.weapons);
                                printRoomsWithInt(newGame.killer.room);
                                if (newGame.killer.name == nameChoice && newGame.killer.weapons == weaponChoice && newGame.killer.room == roomChoice) {
                                    SDL_Log("You WIIINNN !!!!!!!!!!!!!!!!!!");
                                } else {
                                    SDL_Log("You Lose, do not share any information");
                                }
                            }
                            hasChoose = 1;
                            break;
                        default:
                            SDL_Log("MOVEMENT NOT POSSIBLE\n");
                            break;
                    }
            }
            SDL_FlushEvent(newEvent.type);
            SDL_Delay(100);
        }
        SDL_Log("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
        SDL_Log("Movement Left : %d\n", diceNumber);
        //printMapAndPlayer((*player), map, newGame);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        printMapAndPlayer(*player, map, newGame, renderer);
        SDL_RenderPresent(renderer);
    }
    SDL_Log("Before finishing your turn, you can accuse someone :");
//    choiceText = getInputStringFromPlayer();
//    sscanf(choiceText, "%d", &choice);
    SDL_Log("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
}

void ChoosePlayerAndWeapon(CharactersName *nameChoice, Weapons *weaponChoice) {
    char* choiceText;
    SDL_Log("Choose the player :\n");
    for (int i = 0; i <6; i++) {
        printNameWithInt(i);
        SDL_Log("->%d\n", i);
    }
    choiceText = getInputStringFromPlayer();
    sscanf(choiceText, "%d", nameChoice);
    SDL_Log("Choose the weapons :\n");
    for (int i = 0; i <6; i++) {
        printWeaponsWithInt(i);
        SDL_Log("->%d\n", i);
    }
    choiceText = getInputStringFromPlayer();
    sscanf(choiceText, "%d", weaponChoice);
}

int getIndexByName(Game *newGame, CharactersName *nameChoice) {
    int indexPlayer;
    for (int i = 0; i < (*newGame).numberOfPlayer; i++) {
        if ((*newGame).allThePlayers[i]->name == (*nameChoice)) {
            indexPlayer = i;
        }
    }
    for (int i = 0; i < (*newGame).numberOfNPCs; i++) {
        if ((*newGame).NPCs[i]->name == (*nameChoice)) {
            indexPlayer = i+10;
        }
    }
    return indexPlayer;
}

void movePlayerToRandomPosInARoom(Game *newGame, int indexPlayer, Player *playerToMove) {
    int canGoInTheRoom, randomPositionIntoTheRoom;
    do {
        randomPositionIntoTheRoom = rand() % (*newGame).allTheRooms[playerToMove->roomIndexIn]->roomPosLogSize;
        canGoInTheRoom = 1;
        for (int i = 0; i < (*newGame).numberOfPlayer; i++) {
            if ((*newGame).allThePlayers[i]->playerPos.posX ==
                (*newGame).allTheRooms[playerToMove->roomIndexIn]->roomPosition[randomPositionIntoTheRoom].posX &&
                (*newGame).allThePlayers[i]->playerPos.posY ==
                (*newGame).allTheRooms[playerToMove->roomIndexIn]->roomPosition[randomPositionIntoTheRoom].posY) {
                canGoInTheRoom = 0;
            }
        }
        for (int i = 0; i < (*newGame).numberOfNPCs; i++) {
            if ((*newGame).NPCs[i]->playerPos.posX ==
                (*newGame).allTheRooms[playerToMove->roomIndexIn]->roomPosition[randomPositionIntoTheRoom].posX &&
                (*newGame).NPCs[i]->playerPos.posY ==
                (*newGame).allTheRooms[playerToMove->roomIndexIn]->roomPosition[randomPositionIntoTheRoom].posY) {
                canGoInTheRoom = 0;
            }
        }
    } while (!canGoInTheRoom);
    playerToMove->playerPos.posX = (*newGame).allTheRooms[playerToMove->roomIndexIn]->roomPosition[randomPositionIntoTheRoom].posX;
    playerToMove->playerPos.posY = (*newGame).allTheRooms[playerToMove->roomIndexIn]->roomPosition[randomPositionIntoTheRoom].posY;
}

void createANewGame(const Position *startersPos, Game *newGame, int map[25][24]) {
    int choice;
    char* choiceText;

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

    SDL_Log("The killer has been choosen...........");
    SDL_Log("\n");


    int indexPlayerGettingCard = 0;

    //Creation of players
    SDL_Log("Choose number of player :");
    char *text = getInputStringFromPlayer();

    sscanf(text, "%d", &choice);
    SDL_Log("%d", choice);
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
        SDL_Log("PLAYER %d, please look at your card, write them down, then enter to go to the other player !\n", i+1);
        SDL_Log("Enter something to continue :");
        choiceText = getInputStringFromPlayer();
        sscanf(choiceText, "%d", &choice);
        SDL_Log("\n\n\n\n");
        SDL_Log("Card of player %d : ", i+1);
        printCardForAPlayer(newGame->allThePlayers[i]);
        SDL_Log("\n\n\n\n");
        SDL_Log("\nEnter something to continue :");
        choiceText = getInputStringFromPlayer();
        sscanf(choiceText, "%d", &choice);
        SDL_Log("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    }
}

char *getInputStringFromPlayer() {
    TTF_Init();
    SDL_StartTextInput();
    SDL_bool done = SDL_FALSE;
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_CreateWindowAndRenderer(960, 1000, SDL_WINDOW_SHOWN, &window, &renderer);
    SDL_RenderSetVSync(renderer, 60);
    SDL_Event newEvent;
    char *text = (char*) calloc(50, sizeof(char));
    TTF_Font* font = TTF_OpenFont("Roboto-Bold.ttf", 100);
    SDL_Color color = {255, 255, 30, 255};
    SDL_Surface* temp = TTF_RenderText_Solid(font, " ", color);
    SDL_Texture* textImage = SDL_CreateTextureFromSurface(renderer, temp);
    SDL_Rect rect = {20, 20, temp->w, temp->h};
    SDL_StartTextInput();
    SDL_FreeSurface(temp);
    temp = NULL;

    while (!done) {
        if (SDL_PollEvent(&newEvent)) {
            switch (newEvent.type) {
                case SDL_QUIT:
                    /* Quit */
                    done = SDL_TRUE;
                    break;
                case SDL_TEXTINPUT:
                    /* Add new text onto the end of our text */
                    strcat(text, newEvent.text.text);
                    if (textImage) {
                        SDL_DestroyTexture(textImage);
                        textImage = NULL;
                    }
                    temp = TTF_RenderText_Solid(font, text, color);
                    if (temp) {
                        textImage = SDL_CreateTextureFromSurface(renderer, temp);
                        rect.h = temp->h;
                        rect.w = temp->w;
                        SDL_FreeSurface(temp);
                        temp = NULL;
                    }
                    break;
                case SDL_KEYDOWN:
                    if (newEvent.key.keysym.sym == SDLK_BACKSPACE) {
                        text[strlen(text)-1] = '\0';
                    }
                    if (textImage) {
                        SDL_DestroyTexture(textImage);
                        textImage = NULL;
                    }
                    temp = TTF_RenderText_Solid(font, text, color);
                    if (temp) {
                        textImage = SDL_CreateTextureFromSurface(renderer, temp);
                        rect.h = temp->h;
                        rect.w = temp->w;
                        SDL_FreeSurface(temp);
                        temp = NULL;
                    }
                    if (newEvent.key.keysym.sym == SDLK_RETURN) {
                        done = SDL_TRUE;
                    }
                    break;
            }
        }
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, textImage, NULL, &rect);
        SDL_RenderPresent(renderer);
        SDL_Delay(20);
    }
    SDL_StopTextInput();
    SDL_FreeSurface(temp);
    SDL_DestroyTexture(textImage);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
    return text;
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
    char* text;
    int allNamesIndex[6] = {0, 1, 2, 3, 4, 5};
    do {
        SDL_Log("Choose your player :\n");
        //List of all the characters available
        for (int j = 0; j<6-index; j++) {
            SDL_Log("%d -> %s\n", allNamesIndex[j], allNames[allNamesIndex[j]]);
        }
        text = getInputStringFromPlayer();
        error = sscanf(text, "%d", &choice);
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
            SDL_Log("Moutarde\t");
            break;
        case 1 :
            SDL_Log("Olive\t");
            break;
        case 2 :
            SDL_Log("Violet\t");
            break;
        case 3 :
            SDL_Log("Pervenche\t");
            break;
        case 4 :
            SDL_Log("Rose\t");
            break;
        case 5 :
            SDL_Log("Leblanc\t");
            break;
        default : SDL_Log("PROBLEMMMEE"); break;
    }
}

void printWeaponsWithInt(Weapons weaponsName) {
    switch (weaponsName) {
        case 0 :
            SDL_Log("POIGNARD\t");
            break;
        case 1 :
            SDL_Log("CHANDELIER\t");
            break;
        case 2 :
            SDL_Log("REVOLVER\t");
            break;
        case 3 :
            SDL_Log("CORDE\t");
            break;
        case 4 :
            SDL_Log("BARRE_DE_FER\t");
            break;
        case 5 :
            SDL_Log("CLE_A_MOLETTE\t");
            break;
        default : SDL_Log("PROBLEMMMEE"); break;
    }
}

void printRoomsWithInt(RoomsName roomsName) {
    switch (roomsName) {
        case 0 :
            SDL_Log("HALL\t");
            break;
        case 1 :
            SDL_Log("BAR\t");
            break;
        case 2 :
            SDL_Log("SALLE_A_MANGER\t");
            break;
        case 3 :
            SDL_Log("CUISINE\t");
            break;
        case 4 :
            SDL_Log("SALLE_DE_BALLE\t");
            break;
        case 5 :
            SDL_Log("CONSERVATOIRE\t");
            break;
        case 6 :
            SDL_Log("BILLIARD\t");
            break;
        case 7 :
            SDL_Log("BIBLIOTHEQUE\t");
            break;
        case 8 :
            SDL_Log("BUREAU\t");
            break;
        default : SDL_Log("PROBLEMMMEE"); break;
    }
}