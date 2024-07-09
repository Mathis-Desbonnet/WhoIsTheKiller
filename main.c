#include <stdio.h>
#include <windows.h>
#include "game.h"
#include <SDL.h>

int main(int argc, char *argv[]) {
    SDL_Init(SDL_INIT_EVERYTHING);
    srand(time(NULL));
    int choice;
    int maxFirstDiceRoll;
    int temp;
    int indexOfNextPlayer;
    int running = 1;
    Player firstPlayer;
    Game newGame;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    int map[25][24] = {
            {
                    -2, -2, -2, -2, -2, -2, 1,  0,  0,  0,   0,   -10, -10, 0,   0,   0,  1,  0,  -9, -9, -9, -9, -9, -9
            },
            {
                    -2, -2, -2, -2, -2, -2, 1,  1,  1,  -10, -10, -10, -10, -10, -10, 1,  1,  -9, -9, -9, -9, -9, -9, -9
            },
            {
                    -2, -2, -2, -2, -2, -2, 1,  1,  1,  -10, -10, -10, -10, -10, -10, 1,  1,  -9, -9, -9, -9, -9, -9, -9
            },
            {
                    -2, -2, -2, -2, -2, 11, 1,  1,  1,  -10, -10, -10, -10, -10, -10, 1,  1,  -9, -9, -9, -9, -9, -9, -9
            },
            {
                    0,  1,  1,  1,  1,  21, 1,  1,  1,  -10, -10, -10, -10, -10, -10, 1,  1,  -9, -9, -9, -9, -9, -9, -9
            },
            {
                    1,  1,  1,  1,  1,  1,  1,  1,  1,  -10, -10, -10, -10, -10, -10, 1,  1,  4,  -9, -9, -9, -9, -9, -9
            },
            {
                    0,  -3, -3, -3, -3, -3, 1,  1,  1,  -10, -10, 3,   3,   -10, -10, 1,  1,  14, 1,  1,  1,  1,  1,  0
            },
            {
                    -3, -3, -3, -3, -3, -3, -3, 1,  1,  1,   1,   13,  13,  1,   1,   1,  1,  1,  1,  1,  1,  1,  1,  1
            },
            {
                    -3, -3, -3, -3, -3, -3, 10, 20, 1,  2,   2,   2,   2,   2,   1,   1,  1,  15, 1,  1,  1,  1,  1,  0
            },
            {
                    -3, -3, -3, -3, -3, -3, -3, 1,  1,  2,   2,   2,   2,   2,   1,   1,  -8, 5,  -8, -8, -8, -8, -8, -8
            },
            {
                    0,  -3, -3, 10, -3, -3, 1,  1,  1,  2,   2,   2,   2,   2,   1,   1,  -8, -8, -8, -8, -8, -8, -8, -8
            },
            {
                    0,  19, 1,  20, 1,  1,  1,  1,  1,  2,   2,   2,   2,   2,   1,   1,  -8, -8, -8, -8, -8, -8, -8, -8
            },
            {
                    -4, 9,  -4, -4, -4, -4, 1,  1,  1,  2,   2,   2,   2,   2,   1,   15, 5,  -8, -8, -8, -8, -8, -8, -8
            },
            {
                    -4, -4, -4, -4, -4, -4, 1,  1,  1,  2,   2,   2,   2,   2,   1,   1,  -8, -8, -8, -8, -8, -8, -8, -8
            },
            {
                    -4, -4, -4, -4, -4, -4, 1,  1,  1,  2,   2,   2,   2,   2,   1,   1,  -8, -8, -8, -8, -8, -8, -8, -8
            },
            {
                    -4, -4, -4, -4, -4, 9,  19, 1,  1,  1,   1,   1,   1,   1,   1,   1,  1,  1,  1,  -8, -8, -8, -8, -8
            },
            {
                    -4, -4, -4, -4, -4, -4, 1,  1,  1,  17,  1,   1,   1,   1,   17,  1,  1,  1,  1,  1,  1,  1,  1,  0
            },
            {
                    0,  1,  1,  1,  1,  1,  1,  1,  -6, 7,   -6,  -6,  -6,  -6,  7,   -6, 1,  1,  1,  16, 1,  1,  1,  1
            },
            {
                    1,  1,  1,  1,  1,  1,  1,  1,  -6, -6,  -6,  -6,  -6,  -6,  -6,  -6, 1,  1,  -7, 6,  -7, -7, -7, 0
            },
            {
                    0,  -5, -5, -5, 8,  18, 1,  17, 7,  -6,  -6,  -6,  -6,  -6,  -6,  7,  17, 1,  -7, -7, -7, -7, -7, -7
            },
            {
                    -5, -5, -5, -5, -5, -5, 1,  1,  -6, -6,  -6,  -6,  -6,  -6,  -6,  -6, 1,  1,  -7, -7, -7, -7, -7, -7
            },
            {
                    -5, -5, -5, -5, -5, -5, 1,  1,  -6, -6,  -6,  -6,  -6,  -6,  -6,  -6, 1,  1,  -7, -7, -7, -7, -7, -7
            },
            {
                    -5, -5, -5, -5, -5, -5, 1,  1,  -6, -6,  -6,  -6,  -6,  -6,  -6,  -6, 1,  1,  -7, -7, -7, -7, -7, -7
            },
            {
                    -5, -5, -5, -5, -5, -5, 0,  1,  1,  1,   -6,  -6,  -6,  -6,  1,   1,  1,  0,  -7, -7, -7, -7, -7, -7
            },
            {
                    0,  0,  0,  0,  0,  0,  0,  0,  0,  1,   2,   2,   2,   2,   1,   0,  0,  0,  0,  0,  0,  0,  0,  0
            },
    };
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event newEvent;
    const Uint8* keyState = SDL_GetKeyboardState(NULL);
    SDL_Log("--------------------||WELCOME TO CLUEDO||--------------------\n");
    Position startersPos[6] = {{0, 6}, {0, 16}, {7, 23}, {18, 0}, {24, 9}, {24, 14}};
    createANewGame(startersPos, &newGame, map);
    maxFirstDiceRoll = 0;
    indexOfNextPlayer = 0;
    for (int i = 0; i<newGame.numberOfPlayer; i++) {
        temp = rollTheDice();
        SDL_Log("Player %d : %d\n", i+1, temp);
        if (temp > maxFirstDiceRoll) {
            maxFirstDiceRoll = temp;
            indexOfNextPlayer = i;
        }
    }
    while (running) {
        SDL_CreateWindowAndRenderer(960, 1000, SDL_WINDOW_SHOWN, &window, &renderer);
        SDL_PollEvent(&newEvent);
        if (newEvent.type == SDL_QUIT || keyState[SDL_GetScancodeFromKey(SDLK_ESCAPE)]) {
            SDL_Quit();
            running = 0;
        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        printMapAndPlayer(*newGame.allThePlayers[indexOfNextPlayer], map, newGame, renderer);
        SDL_RenderPresent(renderer);
        SDL_Log("It's time for player %d\n", indexOfNextPlayer+1);
        playerMovement(newGame.allThePlayers[indexOfNextPlayer], map, newGame, renderer);
        indexOfNextPlayer++;
        indexOfNextPlayer = indexOfNextPlayer%newGame.numberOfPlayer;
        SDL_Delay(20);
    }
    free(newGame.allTheRooms);
    free(newGame.allThePlayers);
    SDL_Log("GOOD BYE!");
    return EXIT_SUCCESS;
}
