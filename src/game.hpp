#ifndef GAME_HEADER
#define GAME_HEADER
enum GameState{
    STARTUP,
    START_MENU,
    GAME_OPTIONS,
    CREDITS,
    LEVEL_START,
    GAME,
    LEVEL_CLEAR,
    EDITOR,
    GAMESTATE_TOTAL
};

// std lib
// apparently i shouldn't use this
// i dont want to write a few of these functions myself though
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h> // bleh?
#include <limits.h>
#include <time.h>

// libs i didn't write
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "lib/cJSON.h"

// my libs
#include "util.hpp"
#include "map.hpp"

// components
#include "physical.hpp"
#include "renderable.hpp"
#include "position.hpp"
#include "player_input.hpp"

#include "entities.hpp"

// systems
#include "config.hpp"
#include "log.hpp"
#include "graphics.hpp"
#include "startmenu.hpp"
#include "editor.hpp"
#include "game_world.hpp"


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
void change_main_state(GameState state);
#endif
