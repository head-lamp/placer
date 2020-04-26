#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

int init(void);
int load_media(void);
void close(void);
SDL_Surface* loadSurface(const char*);

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window* window = NULL;
SDL_Surface* screenSurface = NULL;
SDL_Surface* helloWorld = NULL;
SDL_Surface* currentSurface = NULL;

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

    screenSurface = SDL_GetWindowSurface(window);
    return 1;
}

int load_media(void) {
    helloWorld = loadSurface("assets/stretch.bmp");
    if (helloWorld == NULL) {
        return 0;
    }

    return 1;
}

SDL_Surface* loadSurface(const char* path) {
    SDL_Surface* optimizedSurface = NULL;
    SDL_Surface* loadedSurface = SDL_LoadBMP(path);
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
    helloWorld = NULL;
    SDL_DestroyWindow(window);
    window = NULL;
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
        stretchRect.x = 0;
        stretchRect.y = 0;
        stretchRect.w = SCREEN_WIDTH;
        stretchRect.h = SCREEN_HEIGHT;
        SDL_BlitScaled(currentSurface, NULL, screenSurface, &stretchRect);
        SDL_UpdateWindowSurface(window);
    }

    close();

    return 0;
}
