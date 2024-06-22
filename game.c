//
// Created by Mathi on 6/18/2024.
//

#include "game.h"

void printMapAndPlayer(Player firstPlayer, int map[25][24]) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    for (int i = 0; i < 25; i++) {
        for (int j = 0; j < 24; j++) {
            if (firstPlayer.playerPos.posX == i && firstPlayer.playerPos.posY == j) {
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
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
    srand(time(NULL));
    return rand()%11 + 1;
}