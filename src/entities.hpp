#ifndef COMPONENT_HEADER
#define COMPONENT_HEADER

#define INITIAL_COMPONENT_SIZE 100
struct ComponentList {
    Physical phys_components[INITIAL_COMPONENT_SIZE];
    Renderable rend_components[INITIAL_COMPONENT_SIZE];
    Position pos_components[INITIAL_COMPONENT_SIZE];
    PlayerInput plyr_componets[INITIAL_COMPONENT_SIZE];
};

enum Components {
    POSITION,
    PHYSICAL,
    RENDERABLE,
    PLAYER_INPUT,
    COMPONENTS_TOTAL
};

enum ENTITIES {
    PLAYER,
    WALL,
};

Components get_comp_id(const char *name);
#endif
