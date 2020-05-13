struct GameWorld {
    int entity_list[100];
    int entities_total;
    ComponentList comps[100];
};

void game_world_update(GameWorld *gw, SDL_Event *e, int dt);

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
void load_ent(GameWorld *gw, const char *path);
void load_component(GameWorld *gw, const cJSON *comp);
