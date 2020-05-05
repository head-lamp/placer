#ifndef PHYSICAL_HEADER
#define PHYSICAL_HEADER

struct Physical {
    int entity_id;
    int x;
    int y;
    int mass;
    float vx;
    float vy;

    SDL_Rect *coll_shapes;
    int active_shape;
    int num_shapes;
};

#endif
