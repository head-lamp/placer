#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

int init(void);
int load_media(void);
void close(void);
SDL_Surface* load_surface(const char*);
SDL_Texture* load_texture(const char*);

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window* window = NULL;
SDL_Surface* screenSurface = NULL;
SDL_Surface* helloWorld = NULL;
SDL_Surface* currentSurface = NULL;
SDL_Renderer* renderer = NULL;
SDL_Texture* texture = NULL;

int init(void) {
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

    return 1;
}

int load_media(void) {
    //helloWorld = load_surface("assets/loaded.png");
    texture = load_texture("assets/loaded.png");
    if (texture == NULL) {
        printf("failed to load texture image\n");
        return 0;
    }
    /*
    if (helloWorld == NULL) {
        return 0;
    }

    */
    return 1;
}

SDL_Texture* load_texture(const char* path) {
    SDL_Texture *new_texture = NULL;
    SDL_Surface *loaded_surface = IMG_Load(path);
    if (loaded_surface == NULL) {
        printf("unable to load img %s SDL_image err: %s\n",
            path, IMG_GetError());
    }
    new_texture = SDL_CreateTextureFromSurface(renderer, loaded_surface);
    if (new_texture == NULL) {
        printf("unable to create texture from %s SDL err: %s\n",
            path, SDL_GetError());
    }
    SDL_FreeSurface(loaded_surface);

    return new_texture;
}

SDL_Surface* load_surface(const char* path) {
    SDL_Surface* optimizedSurface = NULL;
    // SDL_Surface* loadedSurface = SDL_LoadBMP(path);
    SDL_Surface* loadedSurface = IMG_Load(path);
    if (loadedSurface == NULL) {
        printf("unable to load image %s SDL err: %s\n", path, SDL_GetError());
    }
    optimizedSurface = SDL_ConvertSurface(loadedSurface, screenSurface->format, 0);
    if (optimizedSurface == NULL) {
        printf("can't optimize image %s, sdl err: %s\n", path, SDL_GetError());
    }
    SDL_FreeSurface(loadedSurface);
    return optimizedSurface;
}

void close(void) {
    SDL_FreeSurface(helloWorld);
    SDL_DestroyTexture(texture);
    texture = NULL;
    // helloWorld = NULL;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    window = NULL;
    renderer= NULL;
    IMG_Quit();
    SDL_Quit();
}

int main(int argc, char* args[]) {
    printf("fuck you\n");

    int res = init();
    if (!res) {
        exit(1);
    }

    res = load_media();
    if (!res) {
        exit(1);
    }

    /*
    SDL_FillRect(screenSurface, NULL, SDL_MapRGB( screenSurface->format,
        0xFF, 0xFF, 0xFF));
    */

    bool quit = false;
    SDL_Event e;
    currentSurface = helloWorld;
    SDL_Rect stretchRect;
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            else if (e.type == SDL_KEYDOWN) {
            }
        }
        SDL_RenderClear(renderer);

        SDL_RenderCopy(renderer, texture, NULL, NULL);

        SDL_RenderPresent(renderer);
    }

    close();

    return 0;
}
