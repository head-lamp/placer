#include "game.hpp"
// extern SDL_Window *window;

extern SDL_Window *window;
extern SDL_Renderer *renderer;

void tick(SDL_Event *e) {
    float dt;
    update(e, dt);
}

void update(SDL_Event *e, float dt) {
}

void draw(SDL_Event *, float dt) {
    // clear at the start of the step?
    SDL_RenderClear(renderer);

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
        printf("%d\n", dt);
        update(&e, dt);
        draw(&e, dt);

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
