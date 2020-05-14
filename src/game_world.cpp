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
    load_ent(gw, "ents/player.json");
    printf("id %d\n", id);
    // p.entity_id = id;
    // for now 1 for alive 0 for dead?
    Physical phys = {
        id, 9, 9, 1, 1.0, 1.0,
        NULL, 0, 0
    };
    gw->comps->phys_components[id] = phys;
    Renderable rend = { id,
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
void load_ent(GameWorld *gw, const char *path) {
    const char *entdata_file;
    entdata_file = read_file(path);
    printf("%s\n", entdata_file);
    const cJSON *entdata = cJSON_Parse(entdata_file);
    if (entdata == NULL) {
        printf("cjson err: %s\n", cJSON_GetErrorPtr());
    }
    const cJSON *components = cJSON_GetObjectItem(entdata, "components");
    cJSON *comp = NULL;
    char *comp_name;

    // TODO FIXME
    // this routine is kinda rough?
    // get_comp_id needs to find a component in
    // COMPONENTS_NAMES / first loop
    // which matches the str / second loop
    // which then returns an int from Components?
    // all in all this is a bit silly
    // this needs to be a map or something
    // that way it can just match the string against
    // and get back an INT
    //
    // another idea (maybe terrible)
    // is to just match against the int values from adding all the ascii chars together?
    // idk if that has legs or not lol
    // maybe the ids could just be in the data file?
    // do this check offline basically?
    // idk
    for (int i = 0; i < cJSON_GetArraySize(components); i++) {
        printf("%d\n", i);
        comp = cJSON_GetArrayItem(components, i);
        load_component(gw, comp);
    }
}

// TODO watch memory useage here
void load_component(GameWorld *gw, const cJSON *comp) {
    cJSON *item = cJSON_GetObjectItem(comp, "name");
    char *comp_name = cJSON_GetStringValue(item);
    Components id = get_comp_id(comp_name);
    switch(id) {
        case PHYSICAL:
            printf("case: phsyical\n");
            Physical phys;
            phys.x = get_json_int(comp, "x");
            phys.y = get_json_int(comp, "y");
            phys.mass = get_json_int(comp, "mass");
            phys.vx = get_json_float(comp, "vx");
            phys.vy = get_json_float(comp, "vy");
            phys.num_shapes = get_json_float(comp, 0);

            printf("x: %d\n", get_json_int(comp, "x"));
            printf("y: %d\n", get_json_int(comp, "x"));
            printf("mass: %d\n", get_json_int(comp, "x"));
            printf("mass: %d\n", get_json_int(comp, "x"));
            break;
        case RENDERABLE:
            printf("case: renderable\n");
            Renderable rend;
            rend.sprite_sheet_path = get_json_string(comp, "sprite_sheet_path");
            rend.active_frame = get_json_int(comp, "active_frame");
            rend.num_frames = get_json_int(comp, "num_frames");

            printf("sprite sheet path: %s\n", get_json_string(comp, "sprite_sheet_path"));

            break;
        case COMPONENTS_TOTAL:
            printf("didn't find anything basically\n");
            break;
        default:
            break;
    }
}

const char *COMPONENTS_NAMES[] = {
    "physical",
    "renderable",
};

// TODO: slow?
// yes it's slow
// need to kinda fix it
Components get_comp_id(const char *comp_name) {
    char * cn;

    printf("k lets hope this shit works\n");
    for (int i=0; i < COMPONENTS_TOTAL; i++) {
        if (strcmp(COMPONENTS_NAMES[i], comp_name) == 0) {
            return (Components)i;
        }
    }

    // couldn't find it?
    // just return the total
    return COMPONENTS_TOTAL;
}
