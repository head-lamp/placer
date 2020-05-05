struct Renderable {
    int entity_id;
    const char *sprite_sheet_path;
    int active_frame;
    int num_frames;
    SDL_Rect *clips;
};
