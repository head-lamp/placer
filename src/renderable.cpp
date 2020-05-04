#include "game.hpp"

struct renderable {
    int entity_id;
    char *sprite_sheet_path;
    int active_frame;
    int num_frames;
    SDL_Rect *clips;
};
