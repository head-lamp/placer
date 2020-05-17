#include "game.hpp"
// extern SDL_Window *window;

// TODO FIXME stop using switch statements

extern SDL_Window *window;
extern SDL_Renderer *renderer;
extern TTF_Font *nfont;



int game_state = GAME;

void tick(SDL_Event *e) {
    float dt;
}

void update(SDL_Event *e, int dt) {
    switch(game_state) {
        case STARTUP:
            break;
        case START_MENU:
            break;
        case GAME_OPTIONS:
            break;
        case CREDITS:
            break;
        case GAME:
            break;
        default:
            printf("no state?");
            break;
    }
}

void change_main_state(GameState state) {
}

void draw(SDL_Event *e, int dt) {
    // clear at the start of the step?
    SDL_RenderClear(renderer);
    /*
    // cycle through possible parts of game
    // and let those components draw
    // this will likely be functions like `draw_game()` or 
    // function pointers on structs
    switch(game_state) {
        case STARTUP:
            break;
        case START_MENU:
            break;
        case GAME_OPTIONS:
            break;
        case CREDITS:
            break;
        case GAME:
            break;
        default:
            printf("no state?");
            break;
    }

    */
    // i guess for now always draw the log?
    draw_log(renderer, dt);

    SDL_RenderPresent( renderer );
}

void run_game() {
    // startup stuff
    load_config();
    printf("hello\n");

    int last_time = SDL_GetTicks();
    int current_time = 0;
    int dt = 0;

    SDL_Event e;

    // test player
    // Player *p = (struct Player*)malloc(sizeof(Player));
    // p->physical.x = 0;
    GameWorld gw;
    init_game_world(&gw);
    bool running = true;
    while (running) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                running = false;
            }
        }
        current_time = SDL_GetTicks();
        dt = current_time - last_time;
        last_time = current_time;
        // printf("%d\n", dt);
        if (game_state != GAME) {
            update(&e, dt);
        }
        else {
            game_world_update(&gw, &e, dt);
        }

        if (game_state != GAME) {
            draw(&e, dt);
        }
        else {
            game_world_draw(&gw, &e, dt);
        }

        // always sleep for 1 ms _for now_
        // so max fps is 1000
        while(!SDL_TICKS_PASSED(SDL_GetTicks(), last_time+1));
    }

    close();
}

void close(void) {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    window = NULL;
    renderer= NULL;
    IMG_Quit();
    SDL_Quit();
}
