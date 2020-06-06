#include "game.hpp"

SDL_Texture *startup_texture;

Uint32 exit_startup_callback(Uint32 interval, void* param) {
    SDL_DestroyTexture(startup_texture);
    startup_texture = NULL;
    change_main_state((GameState)(uintptr_t)param);

    return 0;
}

int8_t init_startup(void) {
    startup_texture = load_texture(
        "assets/images/test_logo.png"
    );
    SDL_TimerID timer = SDL_AddTimer(5 /* * 1000*/, exit_startup_callback, (void *)START_MENU);
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


int8_t init_startmenu(void) {
    return 0;
}

int8_t update_startmenu(SDL_Event *e, int dt) {
    return 0;
}

SDL_Texture *menu_texture = NULL;
extern TTF_Font *nfont;
int8_t draw_startmenu(SDL_Event *e, int dt) {
    SDL_Color color = {0, 0, 0};
    menu_texture = get_texture_from_text("YOYOYOO WHAT UP", color, nfont);
    int w, h;
    SDL_QueryTexture(menu_texture, NULL, NULL, &w, &h);
    SDL_Rect rect = {100, 100, w, h};
    SDL_RenderCopy(renderer, menu_texture, NULL, &rect);
    return 0;
}
