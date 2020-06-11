#ifndef EDITOR_HEADER
#define EDITOR_HEADER

enum EDITOR_BUTTONS {
    WALL,
    PLAYER_SPAWN,
    EDITOR_BUTTONS_TOTAL
};

// ah the simplest way to do this
// is (drumroll) ECS
#define INITIAL_COMPONENT_SIZE 100
struct Editor {
    EDITOR_BUTTONS *buttons;
    int entity_list[INITIAL_COMPONENT_SIZE];
    int entities_total;
    ComponentList comps;
};

int8_t init_editor(void);
int8_t update_editor(SDL_Event *e, int dt);
int8_t draw_editor(SDL_Event *e, int dt);
#endif
