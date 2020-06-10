#include "game.hpp"

struct Editor {
};

int8_t init_editor(void) {
    return 0;
}

int8_t update_editor(SDL_Event *e, int dt) {
    // look for click events,
    // see what button was pressed
    // do stuff
    return 0;
}

// TODO just expose the renderer variable in game.cpp/draw
// because right now this extern renderer crap is awful
extern SDL_Renderer* renderer;
int8_t draw_editor(SDL_Event *e, int dt) {

    SDL_SetRenderDrawColor(renderer, 207, 205, 200, 0xFF);
    SDL_RenderClear(renderer);
    // move this shit to macros
    SDL_SetRenderDrawColor(renderer, 122, 251, 255, 0xFF);
    for (int i = -640; i < 640; i += 64) {
        SDL_RenderDrawLine(renderer, i, 0, i, 480);
    }
    for (int i = -480; i < 480; i += 64) {
        SDL_RenderDrawLine(renderer, 0, i, 640, i);
    }
    return 0;

    // draw buttons
}
