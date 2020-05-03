#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "config.hpp"
#include "log.hpp"
#include "graphics.hpp"

void run_game(void);
bool save_game(char *path);
bool load_game(char *path);

void render_startup(void);
void log(char *text);
/*
void render_start_menu(void);
void render_options(void);// probably not necessary
void render_credits(void);
void render_game(void);// probably want dt time for all of these
*/

void tick(SDL_Event *);
void update(SDL_Event *, float);

void draw(SDL_Event *, float);

void close(void);

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
