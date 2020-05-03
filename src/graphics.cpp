#include "game.hpp"

extern SDL_Renderer *renderer;

SDL_Texture* get_texture_from_text(const char *text, SDL_Color color, TTF_Font *font) {
    SDL_Surface *srf = TTF_RenderText_Solid(font, text, color);
    if (srf == NULL) {
        printf("couldn't create surface SDL err: %s\n", SDL_GetError());
        return NULL;
    }
    SDL_Texture *txt_text = NULL;
    txt_text = SDL_CreateTextureFromSurface(renderer, srf);
    if (txt_text == NULL) {
        printf("can't create texture SDL err %s\n", SDL_GetError());
    }

    free(srf);
    return txt_text;
}

SDL_Texture* get_texture() {
    return NULL;
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
