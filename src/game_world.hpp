#ifndef GAMEWORLD_HEADER
#define GAMEWORLD_HEADER

#define INITIAL_COMPONENT_SIZE 100
struct GameWorld {
    int entity_list[INITIAL_COMPONENT_SIZE];
    int entities_total;
    ComponentList comps;

    int player_id;
};


void game_world_update(GameWorld *gw, SDL_Event *e, int dt); int8_t game_world_draw(GameWorld *gw, SDL_Event *e, int dt);

/* TODO
this will likely need moreargs or something
level loading will likely be done in a similar fashion to doom
 */
void init_game_world(GameWorld *gw);

/*
gw:
 stick data into comp list

path:
 dir path to ents to load in
 */
int8_t load_ent(GameWorld *gw, const char *path);
int8_t load_component(GameWorld *gw, const cJSON *comp, int ent_id);

int8_t init_ent_graphics(GameWorld *gw);

int8_t update_player(GameWorld *gw, SDL_Event *e, int dt);
const SDL_Rect translate_rect(SDL_Rect *rect, Physical *phys);

int8_t handle_collisions(GameWorld *gw, int dt);
int8_t move_ents(GameWorld *gw, int dt);

#endif
