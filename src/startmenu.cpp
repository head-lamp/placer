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
    SDL_TimerID timer = SDL_AddTimer(1 * 1000, exit_startup_callback, (void *)START_MENU);
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


// TODO move this out to game.cpp :)
// note this only works for keyboards for now :')
bool KEYS[322];
int8_t init_startmenu(void) {
    for (int i = 0; i < 322; i++) {
        KEYS[i] = false;
    }
    return 0;
}

enum STARTMENU_OPTIONS {
    NEW_GAME,
    FOO,
    BAR,
    BAZ,
    STARTMENU_OPTIONS_TOTAL,
};

size_t selected_option = 0;
int8_t update_startmenu(SDL_Event *e, int dt) {
    const Uint8 *keystate = SDL_GetKeyboardState(NULL);
    if (keystate[SDL_SCANCODE_W]) {
        if (!KEYS[SDL_SCANCODE_W]) {
            selected_option = (selected_option - 1) % STARTMENU_OPTIONS_TOTAL;
            KEYS[SDL_SCANCODE_W] = true;
        }
    }
    if (!keystate[SDL_SCANCODE_W]&& KEYS[SDL_SCANCODE_W]) {
        KEYS[SDL_SCANCODE_W] = false;
    }
    if (keystate[SDL_SCANCODE_S]) {
        if (!KEYS[SDL_SCANCODE_S]) {
            selected_option = (selected_option + 1) % STARTMENU_OPTIONS_TOTAL;
            KEYS[SDL_SCANCODE_S] = true;
        }
    }
    if (!keystate[SDL_SCANCODE_S]&& KEYS[SDL_SCANCODE_S]) {
        KEYS[SDL_SCANCODE_S] = false;
    }

    if (keystate[SDL_SCANCODE_SPACE])  {
        switch(selected_option) {
            case NEW_GAME:
                change_main_state(GAME);
            default:
                break;
        }
    }
    return 0;
}

SDL_Texture *menu_texture = NULL;
extern TTF_Font *nfont;
int8_t draw_startmenu(SDL_Event *e, int dt) {
    SDL_Color Black;
    SDL_Color Red;
    int offset = 24;

    const char *startup_options[] = {
        "new_game",
        "foo", "bar", "baz"
    };
    SDL_Color color;

    for (size_t i=0; i < STARTMENU_OPTIONS_TOTAL; i++) {
        int w, h;
        color = Black;
        if (selected_option == i) {
            color = Red;
        }
        menu_texture = get_texture_from_text(startup_options[i], color, nfont);
        SDL_QueryTexture(menu_texture, NULL, NULL, &w, &h);
        SDL_Rect rect = {100, 25 + (offset * ((int8_t)i+1)), w, h};
        SDL_RenderCopy(renderer, menu_texture, NULL, &rect);
    }
    return 0;
}
