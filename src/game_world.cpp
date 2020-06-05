#include "game.hpp"
#include <string.h>

// this function
void init_game_world(GameWorld *gw) {

    // init struct
    printf("init'ing game world\n");

    printf("testotesto\n");

    // go through components and mark em all as null


    gw->entities_total = 0;

    load_map("assets/maps/test_maps/test_map0.json");

    // add entities
    // todo this will eventually be a loop
    // int id = gw->entities_total++;
    load_ent(gw, "ents/player.json");
    gw->player_id = gw->entities_total - 1;
    printf("%d\n", gw->entities_total);

    load_ent(gw, "ents/wall.json");
    init_ent_graphics(gw);
    // init graphics
    // set textures etc
}

// TODO
// i just realized i don't have a way to access
// entities
// oops
// time for ecs?
void game_world_update(GameWorld *gw, SDL_Event *e, int dt) {

    // will set vx and vy on pos components for the player
    update_player(gw, e, dt);
    move_ents(gw, dt);
    handle_collisions(gw, dt);
}

/*
TODO profile this function using references vs not using references
for the rend or pos
if we can afford the cycles and space we can get rid of the pointers here
 */
extern SDL_Renderer *renderer;
int8_t game_world_draw(GameWorld *gw, SDL_Event *e, int dt) {
    SDL_RenderClear(renderer);
    Renderable *rend;
    Physical *phys;
    SDL_Rect rect;
    for (size_t i = 0; i < gw->entities_total; i++) {
        rend = &gw->comps.rend_components[i];
        phys = &gw->comps.phys_components[i];
        // SDL_Rect rect; // = {12, 12, 32, 64};
        if (rend->entity_id == i && phys->entity_id == i) {
            rect.x = phys->x;
            rect.y = phys->y;
            rect.w = rend->w;
            rect.h = rend->h;
            SDL_RenderCopy(renderer, (*rend).texture, NULL, &rect);
        }
    }

    SDL_RenderPresent(renderer);
    return 0;
}

/*
TODO
I have a hunch that this function will likely be super duper slow
run a debugger here and step through the function and see just how bad it gets
 */
int8_t load_ent(GameWorld *gw, const char *path) {
    int ent_id = gw->entities_total;
    const char *entdata_file;
    entdata_file = read_file(path);
    const cJSON *entdata = cJSON_Parse(entdata_file);
    if (entdata == NULL) {
        printf("cjson err: %s\n", cJSON_GetErrorPtr());
        return 1;
    }
    const cJSON *components = cJSON_GetObjectItem(entdata, "components");
    if (components == NULL) {
        return 2;
    }

    // is valid? increase entities_total
    gw->entities_total++;

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
        comp = cJSON_GetArrayItem(components, i);
        load_component(gw, comp, ent_id);
    }
    free((char *)entdata_file);
    printf("entdata file = %s\n", entdata_file);
    return 0;
}

// TODO watch memory useage here
// NOTE: will increase entities_total
int8_t load_component(GameWorld *gw, const cJSON *comp, int  ent_id) {
    cJSON *item = cJSON_GetObjectItem(comp, "name");
    char *comp_name = cJSON_GetStringValue(item);
    Components comp_id = get_comp_id(comp_name);
    switch(comp_id) {
        case POSITION:
            printf("case: position\n");
            Position pos;
            pos.entity_id = ent_id;
            gw->comps.pos_components[ent_id] = pos;
        case PHYSICAL:
            printf("case: phsyical\n");
            Physical phys;
            phys.entity_id = ent_id;
            phys.mass = get_json_int(comp, "mass");
            phys.num_shapes = get_json_int(comp, 0);
            phys.velocity = get_json_float(comp, "velocity");
            phys.v = phys.velocity;
            phys.max_velocity = get_json_float(comp, "max_velocity");
            phys.coll_shapes = get_rects(comp, "coll_shapes");
            phys.active_shape = 0;
            phys.x = get_json_float(comp, "x");
            phys.y = get_json_float(comp, "y");
            phys.vx = get_json_float(comp, "vx");
            phys.vy = get_json_float(comp, "vy");

            gw->comps.phys_components[ent_id] = phys;
            break;
        case RENDERABLE:
            printf("case: renderable\n");
            Renderable rend;
            rend.entity_id = ent_id;
            rend.w = get_json_int(comp, "w");
            rend.h = get_json_int(comp, "h");
            rend.sprite_sheet_path = get_json_string(comp, "sprite_sheet_path");
            // rend.sprite_sheet_path = "assets/sprites/test_sprites/example_player.png";
            printf("id %d, path %s\n", ent_id, rend.sprite_sheet_path);
            rend.active_frame = get_json_int(comp, "active_frame");
            rend.num_frames = get_json_int(comp, "num_frames");

            gw->comps.rend_components[ent_id] = rend;
            break;
        case PLAYER_INPUT:
            printf("case: player_input\n");
            PlayerInput plyr;
            plyr.entity_id = ent_id;
            gw->comps.plyr_componets[ent_id] = plyr;
        case COMPONENTS_TOTAL:
            printf("didn't find anything basically\n");
            break;
        default:
            break;
    }
    item = NULL;
    comp_name = NULL;
    comp_name = NULL;

    return 0;
}

int8_t init_ent_graphics(GameWorld *gw) {
    printf("%s\n", gw->comps.rend_components[0].sprite_sheet_path);
    for (int i = 0; i < gw->entities_total; i++) {
        if (gw->comps.rend_components[i].entity_id == i) {
            printf("id = %d\n", i);
            printf("path: %s\n", gw->comps.rend_components[i].sprite_sheet_path);
            gw->comps.rend_components[i].texture = load_texture(
                gw->comps.rend_components[i].sprite_sheet_path
            );
        }
    }
    return 0;
}

const char *COMPONENTS_NAMES[] = {
    "position",
    "physical",
    "renderable",
    "player_input",
};

// TODO: slow?
// yes it's slow
// need to kinda fix it
Components get_comp_id(const char *comp_name) {
    char * cn;

    for (int i=0; i < COMPONENTS_TOTAL; i++) {
        if (strcmp(COMPONENTS_NAMES[i], comp_name) == 0) {
            return (Components)i;
        }
    }

    // couldn't find it?
    // just return the total
    return COMPONENTS_TOTAL;
}

/*
TODO right now just finds the player object and does stuff to that directly
this could be decoupled probably
who knows
 */
int8_t update_player(GameWorld *gw, SDL_Event *e, int dt) {
    int p_id=gw->player_id;
    // Position *pos = &gw->comps.pos_components[p_id];
    Physical *phys = &gw->comps.phys_components[p_id];
    const Uint8 *keystate = SDL_GetKeyboardState(NULL);
    phys->vx = 0;
    phys->vy = 0;

    if (keystate[SDL_SCANCODE_W]) {
        phys->vy -= phys->v + dt;
    }
    if (keystate[SDL_SCANCODE_S]) {
        phys->vy += phys->v + dt;
    }
    if (!keystate[SDL_SCANCODE_S]&&!keystate[SDL_SCANCODE_W]) {
        phys->vy = 0;
    }
    if (keystate[SDL_SCANCODE_A]) {
        phys->vx -= phys->v + dt;
    }
    if (keystate[SDL_SCANCODE_D]) {
        phys->vx += phys->v + dt;
    }
    if (!keystate[SDL_SCANCODE_A] && !keystate[SDL_SCANCODE_D]) {
        phys->vx = 0;
    }

    return 0;
}


/*
TODO FIXME:
    this branching in the nested for loop
    might be _super dangerous and slow_
 */
int8_t handle_collisions(GameWorld *gw, int dt) {
    size_t total_ents = gw->entities_total;
    Physical *phys_a = NULL;
    Physical *phys_b = NULL;

    for (size_t a=0; a < gw->entities_total; a++) {
        phys_a = &gw->comps.phys_components[a];
        if (phys_a->entity_id != a) {
            continue;
        }
        const SDL_Rect rect_a = translate_rect(&phys_a->coll_shapes[phys_a->active_shape], phys_a);
        // const SDL_Rect rect_a = phys_a->coll_shapes[phys_a->active_shape];

        for (size_t b=0; b < gw->entities_total; b++) {
            phys_b = &gw->comps.phys_components[b];
            if (phys_b->entity_id != b || a == b) {
                continue;
            }
            const SDL_Rect rect_b = translate_rect(&phys_b->coll_shapes[phys_b->active_shape], phys_b);
            // const SDL_Rect rect_b = phys_b->coll_shapes[phys_b->active_shape];
            if (SDL_HasIntersection(&rect_a, &rect_b) == true) {
                // phys_a->v = -phys_a->v;
                printf("before phys_a->x = %f\n", phys_a->x);
                printf("before phys_a->vx = %f\n", phys_a->vx);
                phys_a->x -= 1 * phys_a->vx;
                phys_a->y -= 1 * phys_a->vy;
                printf("after phys_a->x = %f\n", phys_a->x);
                printf("after phys_a->vx = %f\n", phys_a->vx);
            }
            else {
                phys_a->v = phys_a->velocity;
            }
        }
    }

    return 0;
}

const SDL_Rect translate_rect(SDL_Rect *rect, Physical *phys) {
    SDL_Rect const res = {
        rect->x + (int)phys->x,
        rect->y + (int)phys->y,
        rect->w,
        rect->h
    };
    return res;
}

int8_t move_ents(GameWorld *gw, int dt) {
    Physical *phys;
    for (size_t i=0; i < gw->entities_total; i++) {
        phys = &gw->comps.phys_components[i];
        if (phys->entity_id != i) {
            continue;
        }
        phys->x += phys->vx;
        phys->y += phys->vy;
    }
    return 0;
}
