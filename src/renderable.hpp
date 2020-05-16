#ifndef RENDERABLE_HEADER
#define RENDERABLE_HEADER
struct Renderable {
    int entity_id;
    const char *sprite_sheet_path;
    int active_frame;
    int num_frames;
    SDL_Rect *clips;
    SDL_Texture *texture;
};
#endif
