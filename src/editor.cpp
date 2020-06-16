#include "game.hpp"

#define BUTTON_SIZE 64
SDL_Rect button_pos(int x, int y) {
    SDL_Rect rect = {
        x,
        y,
        BUTTON_SIZE,
        BUTTON_SIZE,
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
int8_t make_button(Editor *ed, EDITOR_BUTTONS button_id) {
    // TODO this might need to be 10?
    int xoffset = BUTTON_SIZE * (ed->buttons_total % 10);
    int yoffset = BUTTON_SIZE * (ed->buttons_total / 10);

    SDL_Rect button_position = button_pos(xoffset,yoffset);

    ed->buttons[ed->buttons_total].button_id = button_id;
    ed->buttons[ed->buttons_total].pos = button_position;
    ed->buttons_total++;

    return 0;
}

int8_t init_editor(Editor *ed) {
    ed->buttons_total = 0;
    make_button(ed, ED_PLAYER_SPAWN);
    make_button(ed, ED_WALL);
    printf("ed->buttons_total = %lu\n", ed->buttons_total);
    printf("%lu\n", ed->buttons_total);
    printf("x %d, y %d, w %d, h %d\n", ed->buttons[0].pos.x, ed->buttons[0].pos.y, ed->buttons[0].pos.w, ed->buttons[0].pos.h);
    printf("x %d, y %d, w %d, h %d\n", ed->buttons[1].pos.x, ed->buttons[1].pos.y, ed->buttons[1].pos.w, ed->buttons[1].pos.h);
    return 0;
}

int8_t place_entity(Editor *ed, SDL_Rect *mouse_pos) {
    int x_pos = snap_64(mouse_pos->x);
    int y_pos = snap_64(mouse_pos->y);

    return 0;
}

SDL_Rect camera;
int8_t update_editor(Editor *ed, SDL_Event *e, int dt) {

    int x, y;
    SDL_GetMouseState(&x, &y);
    // left_clicking
    if (SDL_GetMouseState(NULL, NULL) && SDL_BUTTON(SDL_BUTTON_LEFT)) {
        // printf("mouse left button\n");
        SDL_Rect mouse_pos = {x,y,1,1};

        bool selecting_a_button = false;
        // see if clicking a button
        for (size_t i=0; i < ed->buttons_total; i++) {
            if (SDL_HasIntersection(&ed->buttons[i].pos, &mouse_pos)) {
                ed->active_button = ed->buttons[i].button_id;
                selecting_a_button = true;
            }
        }
        if (!selecting_a_button) {
            place_entity(ed, &mouse_pos);
        }
    }
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

    if (keystate[SDL_SCANCODE_G]) {
        ed->active_button = ED_SELECT;
    }
    // look for click events,
    // see what button was pressed
    // do stuff

    // printf("active_button = %d", ed->active_button);
    return 0;
}


// TODO just expose the renderer variable in game.cpp/draw
// because right now this extern renderer crap is awful
extern SDL_Renderer* renderer;
int8_t draw_editor(Editor *ed, SDL_Event *e, int dt) {


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
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0xFF);
    for (size_t i=0; i < ed->buttons_total; i++) {
        SDL_RenderDrawRect(renderer, &ed->buttons[i].pos);
    }
    // SDL_SetRenderDrawColor(renderer, 0, 0, 255, 0xFF);
    // int res = SDL_RenderDrawRect(renderer, &rect);

    return 0;
}
