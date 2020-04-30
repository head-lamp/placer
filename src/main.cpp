#include "game.hpp"

int init(void);

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;


// init is going to need to make sure sdl is working,
// spawn a global window and renderer (for now?)
// make sure there is a config.txt
// create saves dir
int init(void) {
    // sdl stuff
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL couldn't initialize SDL err: %s\n", SDL_GetError());
        return 0;
    }

    window = SDL_CreateWindow("rocket placer", SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("window couldn't be created SDL err: %s\n", SDL_GetError());
        return 0;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("could not create render SDL err: %s\n", SDL_GetError());
        return 0;
    }

    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    int imgflags = IMG_INIT_PNG;
    if (!(IMG_Init(imgflags) & imgflags)) {
        printf("couldn't init sdl_image SDL err: %s\n", IMG_GetError());
        return 0;
    }

    //TODO still need to do SDL_mixer here
    // and check the config file

    return 1;
}

int load_media(void) {
    return 1;
}

SDL_Texture* load_texture(const char* path) {
    SDL_Texture *tex = NULL;
    SDL_Surface *surf = IMG_Load(path);
    if (surf == NULL) {
        printf("unable to load img %s SDL_image err: %s\n",
            path, IMG_GetError());
    }
    tex = SDL_CreateTextureFromSurface(renderer, surf);
    if (tex == NULL) {
        printf("unable to create texture from %s SDL err: %s\n",
            path, SDL_GetError());
    }
    SDL_FreeSurface(surf);

    return tex;
}

void close(void) {
}

int main(int argc, char* args[]) {

    int res = init();
    if (!res) {
        exit(1);
    }

    res = load_media();
    if (!res) {
        exit(1);
    }

    bool quit = false;

    SDL_Event e;
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            else if (e.type == SDL_KEYDOWN) {
            }
        }
        SDL_RenderPresent( renderer );
    }

    close();

    return 0;
}
