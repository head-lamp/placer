#ifndef EDITOR_HEADER
#define EDITOR_HEADER

enum EDITOR_BUTTONS {
    WALL,
    PLAYER_SPAWN,
    EDITOR_BUTTONS_TOTAL
};

struct Button {
    EDITOR_BUTTONS button_id;
    SDL_Rect pos;
};

// ah the simplest way to do this
// is (drumroll) ECS
#define INITIAL_COMPONENT_SIZE 100
#define BUTTON_AMOUNT
struct Editor {
    Button buttons[64];
    int entity_list[INITIAL_COMPONENT_SIZE];
    int entities_total;
    ComponentList comps;
};

int8_t init_editor(Editor *ed);
int8_t update_editor(SDL_Event *e, int dt);
int8_t draw_editor(SDL_Event *e, int dt);
#endif
