#include "game.hpp"
// extern SDL_Window *window;

// TODO FIXME stop using switch statements

extern SDL_Window *window;
extern SDL_Renderer *renderer;
extern TTF_Font *nfont;

GameWorld gw;

int game_state;

void tick(SDL_Event *e) {
    float dt;
}

void update(SDL_Event *e, int dt) {
    switch(game_state) {
        case STARTUP:
            update_startup(e, dt);
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
    printf("GAME = %d\n", GAME);
    printf("gamestate? %d\n", state);
    printf("game == gamestate? %d\n", GAME==state);

    // enter new state
    switch(state) {
        case STARTUP:
            init_startup();
            break;
        case GAME:
            printf("switching to game world\n");
            init_game_world(&gw);
            break;
        default:
            break;
    }
    game_state = state;
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

    int dt = 0;

    int start = 0;
    int end = 0;

    // test player
    // Player *p = (struct Player*)malloc(sizeof(Player));
    // p->physical.x = 0;
    change_main_state(STARTUP);
    // init_game_world(&gw);
    bool running = true;
    int cap = 1000/60;
    SDL_Event e;
    while (running) {
        start = SDL_GetTicks();
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                running = false;
            }
            // printf("%d\n", dt);

        }
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
        /*
        while(!SDL_TICKS_PASSED(SDL_GetTicks(), last_time+16));
        */

        end = SDL_GetTicks();
        dt = end - start;
        // printf("cap = %d dt = %d\n", cap, dt);
        if (dt < 16) {
            // printf("16 - %d = %d\n", dt, 16 - dt);
            //printf("delaying, dt was %d\n", dt);
            SDL_Delay(16 - dt);
        }
        if (dt >= 16) {
            printf("target = 16, dt = %d\n", dt);

            printf("dt was %d\n", dt);
        }
        dt = 0;
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
