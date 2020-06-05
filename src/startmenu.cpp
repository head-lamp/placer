#include "game.hpp"

SDL_Texture *startup_texture;

Uint32 exit_startup_callback(Uint32 interval, void* param) {
    change_main_state((GameState)(uintptr_t)param);

    return 0;
}

int8_t init_startup(void) {
    startup_texture = load_texture(
        "assets/images/test_logo.png"
    );
    SDL_TimerID timer = SDL_AddTimer(5 * 1000, exit_startup_callback, (void *)GAME);
    return 0;
}

int8_t update_startup(SDL_Event *e, int dt) {
    // exit_startup(GAME);
    return 0;
}

extern SDL_Renderer *renderer;
int8_t draw_startup(SDL_Event *e, int dt) {
    SDL_Rect rect = {0, 0, 640, 480};
    SDL_RenderCopy(renderer, startup_texture, NULL, &rect);
    return 0;
}

