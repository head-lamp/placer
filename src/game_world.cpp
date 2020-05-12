#include "game.hpp"

// this function
void init_game_world(GameWorld *gw) {

    // init struct
    printf("init'ing game world\n");


    // go through components and mark em all as null


    gw->entities_total = 0;

    // add entities
    // todo this will eventually be a loop
    int id = gw->entities_total++;
    read_ent(gw, "ents/player.json");
    printf("id %d\n", id);
    // p.entity_id = id;
    // for now 1 for alive 0 for dead?
    Physical phys = {
        id, 9, 9, 1, 1.0, 1.0,
        NULL, 0, 0
    };
    gw->comps->phys_components[id] = phys;
    Renderable rend = {
        id,
        "assets/sprites/test_sprites/example_player.png",
        0, 0
    };
    gw->comps->rend_components[id] = rend;
}

// TODO
// i just realized i don't have a way to access
// entities
// oops
// time for ecs?
void game_world_update(GameWorld *gw, SDL_Event *e, int dt) {
    //printf("%d\n", gw->comps->phys_components[0].x);
}

/*
TODO
I have a hunch that this function will likely be super duper slow
run a debugger here and step through the function and see just how bad it gets
 */
void read_ent(GameWorld *gw, const char *path) {
    const char *entdata_file;
    entdata_file = read_file(path);
    printf("%s\n", entdata_file);
    const cJSON *entdata = cJSON_Parse(entdata_file);
    if (entdata == NULL) {
        printf("cjson err: %s\n", cJSON_GetErrorPtr());
    }
    const cJSON *components = cJSON_GetObjectItem(entdata, "components");
    cJSON *item;
    cJSON *comp = NULL;
    char *comp_name;
    for (int i = 0; i < cJSON_GetArraySize(components); i++) {
        printf("%d\n", i);
        comp = cJSON_GetArrayItem(components, i);
        item = cJSON_GetObjectItem(comp, "name");
        printf("item: %s\n", cJSON_GetStringValue(item));
    }
}
