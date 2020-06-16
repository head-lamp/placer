#ifndef EDITOR_HEADER
#define EDITOR_HEADER
#include "game.hpp"

enum EDITOR_BUTTONS {
    ED_SELECT,
    ED_WALL,
    ED_PLAYER_SPAWN,
    ED_EDITOR_BUTTONS_TOTAL
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
    size_t buttons_total;
    int entity_list[INITIAL_COMPONENT_SIZE];
    int entities_total;
    EDITOR_BUTTONS active_button;
    ComponentList comps;
};

int8_t init_editor(Editor *ed);
int8_t update_editor(Editor *ed, SDL_Event *e, int dt);
int8_t draw_editor(Editor *ed, SDL_Event *e, int dt);

int8_t place_entity(Editor *ed, SDL_Rect &mouse_pos);
#endif
