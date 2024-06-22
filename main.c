#include <stdio.h>
#include <windows.h>
#include "game.h"

int main(void) {
    int choice;
    int error;
    int diceNumber;
    Player firstPlayer;
    int movePossibilities[4];
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    int map[25][24] = {
        {
            2, 2, 2, 2, 2, 2, 1, 0, 0, 0, 0, 2, 2, 0, 0, 0, 1, 0, 2, 2, 2, 2, 2, 2
        },
        {
                2, 2, 2, 2, 2, 2, 1, 1, 1, 2, 2, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 2, 2, 2
        },
        {
                2, 2, 2, 2, 2, 2, 1, 1, 1, 2, 2, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 2, 2, 2
        },
        {
                2, 2, 2, 2, 2, 11, 1, 1, 1, 2, 2, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 2, 2, 2
        },
        {
                0, 1, 1, 1, 1, 21, 1, 1, 1, 2, 2, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 2, 2, 2
        },
        {
                1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 1, 1, 14, 2, 2, 2, 2, 2, 2
        },
        {
                0, 2, 2, 2, 2, 2, 1, 1, 1, 2, 2, 3, 3, 2, 2, 1, 1, 4, 1, 1, 1, 1, 1, 0
        },
        {
                2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 13, 13, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
        },
        {
                2, 2, 2, 2, 2, 2, 10, 20, 1, 2, 2, 2, 2, 2, 1, 1, 1, 15, 1, 1, 1, 1, 1, 0
        },
        {
                2, 2, 2, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 2, 1, 1, 2, 5, 2, 2, 2, 2, 2, 2
        },
        {
                0, 2, 2, 10, 2, 2, 1, 1, 1, 2, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2
        },
        {
                0, 19, 1, 20, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2
        },
        {
                2, 9, 2, 2, 2, 2, 1, 1, 1, 2, 2, 2, 2, 2, 1, 15, 5, 2, 2, 2, 2, 2, 2, 2
        },
        {
                2, 2, 2, 2, 2, 2, 1, 1, 1, 2, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2
        },
        {
                2, 2, 2, 2, 2, 2, 1, 1, 1, 2, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2
        },
        {
                2, 2, 2, 2, 2, 9, 19, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2
        },
        {
                2, 2, 2, 2, 2, 2, 1, 1, 1, 17, 1, 1, 1, 1, 17, 1, 1, 1, 1, 1, 1, 1, 1, 0
        },
        {
                0, 1, 1, 1, 1, 1, 1, 1, 2, 7, 2, 2, 2, 2, 7, 2, 1, 1, 1, 16, 1, 1, 1, 1
        },
        {
                1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 2, 6, 2, 2, 2, 0
        },
        {
                0, 2, 2, 2, 8, 18, 1, 17, 7, 2, 2, 2, 2, 2, 2, 7, 17, 1, 2, 2, 2, 2, 2, 2
        },
        {
                2, 2, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 2, 2
        },
        {
                2, 2, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 2, 2
        },
        {
                2, 2, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 2, 2
        },
        {
                2, 2, 2, 2, 2, 2, 0, 1, 1, 1, 2, 2, 2, 2, 1, 1, 1, 0, 2, 2, 2, 2, 2, 2
        },
        {
                0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 2, 2, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
    };
    Position startersPos[6] = {{0, 6}, {0, 16}, {7, 23}, {18, 0}, {24, 9}, {24, 14}};
    do {
        printf("Choose your player :\n0 -> MOUTARDE\n1 -> OLIVE\n2 -> VIOLET\n3 -> PERVENCHE\n4 -> ROSE\n5 -> LEBLANC\n");
        error = scanf("%d", &choice);
    } while (choice < 0 || choice > 6 || error == 0);
    firstPlayer.name = choice;
    firstPlayer.playerPos.posX = startersPos[choice].posX;
    firstPlayer.playerPos.posY = startersPos[choice].posY;
    firstPlayer.roomIndexIn = -1;

    do {
        diceNumber = rollTheDice();
        printf("%d\n", diceNumber);
        printMapAndPlayer(firstPlayer, map);
        while (diceNumber > 0) {
            resetMovementPossibilities(movePossibilities);
            updateMovementPossibilities(movePossibilities, firstPlayer.playerPos.posX, firstPlayer.playerPos.posY, map);
            printPossibilities(movePossibilities);
            if (map[firstPlayer.playerPos.posX][firstPlayer.playerPos.posY] >= 3) {
                if (firstPlayer.roomIndexIn == -1) {
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
                        firstPlayer.playerPos.posX -= 1;
                    } else {
                        printf("MOVEMENT NOT POSSIBLE\n");
                    }
                    break;
                case 2:
                    if (movePossibilities[1] == 1) {
                        firstPlayer.playerPos.posY += 1;
                    } else {
                        printf("MOVEMENT NOT POSSIBLE\n");
                    }
                    break;
                case 3:
                    if (movePossibilities[2] == 1) {
                        firstPlayer.playerPos.posX += 1;
                    } else {
                        printf("MOVEMENT NOT POSSIBLE\n");
                    }
                    break;
                case 4:
                    if (movePossibilities[3] == 1) {
                        firstPlayer.playerPos.posY -= 1;
                    } else {
                        printf("MOVEMENT NOT POSSIBLE\n");
                    }
                    break;
                case 5:
                    if (map[firstPlayer.playerPos.posX][firstPlayer.playerPos.posY] >= 13) {
                        if (firstPlayer.roomIndexIn == -1) {
                            firstPlayer.roomIndexIn = map[firstPlayer.playerPos.posX][firstPlayer.playerPos.posY] - 13;
                        } else {
                            firstPlayer.roomIndexIn = -1;
                        }
                    } else {
                        printf("MOVEMENT NOT POSSIBLE\n");
                    }
                    break;
                default:
                    printf("MOVEMENT NOT POSSIBLE\n");
                    break;
            }
            diceNumber--;
            printf("Movement Left : %d\n", diceNumber);
            printMapAndPlayer(firstPlayer, map);
        }
        printf("Next choice : ");
        scanf("%d", &choice);
    } while (choice != -1);
    return 0;
}
