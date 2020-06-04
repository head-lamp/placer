#include "game.hpp"

int8_t init_startup(void) {
    return 0;
}

int8_t exit_startup(GameState state) {
    change_main_state(state);
    return 0;
}

int8_t update_startup(SDL_Event *e, int dt) {
    printf("yoyoyo");
    exit_startup(GAME);
    return 0;
}

int8_t draw_startup(SDL_Event *e, int dt) {
    return 0;
}

