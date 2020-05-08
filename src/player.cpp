#include "game.hpp"
/*
 * TODO
 * Player right now is useless
 * we need to have a ECS actually fuck that
 * its simply better
 * https://gamedev.stackexchange.com/questions/172584/how-could-i-implement-an-ecs-in-c
 * theres gonna be some crazy shit to get this ecs to work
 * hope it doesn't suck
 */
Player create_player(int x, int y) {
    // need a function to init the data from a file
    // that way these values can get dynamically loaded
    Player p;
    p.physical.x = x;
    p.physical.y = y;
    p.physical.mass = 1; // need to decide values
    // p->physical.coll_shapes = {};
    p.physical.active_shape = 0;
    p.physical.num_shapes = 0;

    const char *path = "assets/sprites/test_sprites/example_player.png";
    p.renderable.sprite_sheet_path = path;
    p.renderable.active_frame = 0;
    p.renderable.num_frames = 0;

    // p->renderable.clips = {};

    return p;
}
