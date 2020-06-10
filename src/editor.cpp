#include "game.hpp"

struct Editor {
};

int8_t init_editor(void) {
    return 0;
}

SDL_Rect camera;
int8_t update_editor(SDL_Event *e, int dt) {

    int x, y;
    SDL_GetMouseState(&x, &y);
    printf("x %d, y %d\n", x, y);
    if (x > 600) {
        camera.x -= 2;
    }
    if (x < 40) {
        camera.x += 2;
    }
    if (y > 440) {
        camera.y -= 2;
    }
    if (y < 40) {
        camera.y += 2;
    }

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
        SDL_RenderDrawLine(renderer, i + camera.x, 0, i + camera.x, 480);
    }
    for (int i = -480; i < 480; i += 64) {
        SDL_RenderDrawLine(renderer, 0, i + camera.y, 640, i + camera.y);
    }
    return 0;

    // draw buttons
}
