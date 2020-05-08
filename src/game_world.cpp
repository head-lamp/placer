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
    printf("%d\n", gw->comps->phys_components[0].x);
}
