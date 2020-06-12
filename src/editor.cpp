#include "game.hpp"

#define BUTTON_SIZE 64
SDL_Rect button_pos(int x, int y) {
    SDL_Rect rect = {
        x,
        y,
        x+BUTTON_SIZE,
        y+BUTTON_SIZE,
    };

    return rect;
}

/*
so here is the deal
the screen size is 640
tile size is 640 (FOR NOW)
so there can be 10 TILES per one row before you need to change columns
so here is a bit of math to do that :)
 */
int8_t make_button(Editor *ed, size_t pos, EDITOR_BUTTONS button_id) {
    // TODO this might need to be 10?
    int xoffset = BUTTON_SIZE * (pos % 10);

    int yoffset = BUTTON_SIZE * (pos / 10);
    SDL_Rect button_position = button_pos(xoffset,yoffset);
    printf("yoyo\n");
    printf("pos = %lu\n", pos);
    ed->buttons[0].button_id = button_id;
    ed->buttons[0].pos = button_position;

    return 0;
}

int8_t init_editor(Editor *ed) {
    make_button(ed, 0, PLAYER_SPAWN);
    return 0;
}

SDL_Rect camera;
int8_t update_editor(SDL_Event *e, int dt) {

    int x, y;
    SDL_GetMouseState(&x, &y);
    // TODO use wasd
    const Uint8 *keystate = SDL_GetKeyboardState(NULL);
    if (keystate[SDL_SCANCODE_A]) {
        camera.x += 2;
    }
    if (keystate[SDL_SCANCODE_D]) {
        camera.x -= 2;
    }
    if (keystate[SDL_SCANCODE_W]) {
        camera.y += 2;
    }
    if (keystate[SDL_SCANCODE_S]) {
        camera.y -= 2;
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

    // draw buttons
    // SDL_SetRenderDrawColor(renderer, 0, 0, 255, 0xFF);
    // int res = SDL_RenderDrawRect(renderer, &rect);

    return 0;
}
