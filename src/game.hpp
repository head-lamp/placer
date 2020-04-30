#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>

bool save_game(char *path);
bool load_game(char *path);

enum GameState{
    STARTUP,
    START_MENU,
    GAME_OPTIONS,
    CREDITS,
    LEVEL_START,
    GAME,
    LEVEL_CLEAR,
    GAMESTATE_TOTAL
};
