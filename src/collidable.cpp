#include "game.hpp"

struct collidable {
    SDL_Rect *coll_shapes;
    int active_shape;
    int num_shapes;
};
