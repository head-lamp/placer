#include "game.hpp"

SDL_Texture *log_texture = NULL;

extern TTF_Font *nfont;

void log(const char *text) {
    SDL_Color color = {0,0,0};
    log_texture = get_texture_from_text(text, color, nfont);
}

void update_log(SDL_Event *e, int dt) {
}

void draw_log(SDL_Renderer *rndr, int dt) {
    SDL_RenderCopy(rndr, log_texture, NULL, NULL);
}
