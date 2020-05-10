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
TODO
currently there is concept of game packs which i want to change
I'd like this game to be like doom, blood, duke, or quake
where you go through episodes and maybe making more of the game would
be as simple as just pointing to a pack of levels etc
this will likely be a bit tougher but who cares

right now though there is only one game with no extensibility
so path is basically going to only be used for the `ents/` dir and nothing else
 */
void read_ents(GameWorld *gw, const char *path);
