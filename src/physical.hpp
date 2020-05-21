#ifndef PHYSICAL_HEADER
#define PHYSICAL_HEADER

struct Physical {
    int entity_id;
    int mass;
    float velocity;

    SDL_Rect *coll_shapes;
    int active_shape;
    int num_shapes;
};

#endif
