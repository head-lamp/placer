#ifndef PHYSICAL_HEADER
#define PHYSICAL_HEADER

struct Physical {
    int entity_id;
    int mass;
    // initial velocity
    float velocity;
    float v;
    float max_velocity;

    SDL_Rect *coll_shapes;
    int active_shape;
    int num_shapes;

    float x;
    float y;
    float vx;
    float vy;
};

#endif
