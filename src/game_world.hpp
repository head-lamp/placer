struct GameWorld {
    int entity_list[100];
    int entities_total;
    ComponentList comps[100];
};

void game_world_update(GameWorld *gw, SDL_Event *e, int dt);
void init_game_world(GameWorld *gw);
