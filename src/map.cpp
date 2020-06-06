#include "game.hpp"

int8_t load_map(const char *path) {
    const char *map_file = read_file(path);
    // printf("map_file = %s\n", map_file);
    size_t map_file_len = strlen(map_file);
    printf("map_file_len = %lu\n", map_file_len);
    const cJSON *map_data = cJSON_ParseWithOpts(map_file, 0, 1);
    if (map_data == NULL) {
        printf("map data is null\n");
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL) {
            printf("Error before: %s\n", error_ptr);
        }
    }

    // load tile_sets from tmx to json :)
    const cJSON *tile_sets_tmx = cJSON_GetObjectItem(map_data, "tilesets");
    size_t tile_sets_tmx_size = cJSON_GetArraySize(tile_sets_tmx);
    for (size_t i=0; i < tile_sets_tmx_size; i++) {
        // TODO load the json tilesets ?
        cJSON *tile_set_tmx = cJSON_GetArrayItem(tile_sets_tmx, i);
        char *tmx_name =  cJSON_GetStringValue(cJSON_GetObjectItem(tile_set_tmx, "source"));
        printf("strip_exts res = %s\n", strip_exts(tmx_name));
        printf("tmx_name = %s\n", tmx_name);
        // char *file_name = cJSON_GetStringValue(cJSON_GetArrayItem(tile_sets_tmx, i));
    }

    printf("tile_sets_size = %lu\n",tile_sets_tmx_size);

    const cJSON *layers = cJSON_GetObjectItem(map_data, "layers");
    size_t layers_size = cJSON_GetArraySize(layers);
    for (size_t i=0; i < layers_size; i++) {
        cJSON *layer = cJSON_GetArrayItem(layers, i);
        char *layer_name = cJSON_GetStringValue(cJSON_GetObjectItem(layer, "name"));
        Layers layer_id = get_layer_id(layer_name);
        switch(layer_id) {
            case LAYOUT:
                break;
            case OBJECTS:
                break;
            case LAYERS_TOTAL:
                break;
        }
    }
    // iterate through walls and shit

    // iterate trhough object lists?


    if (map_data == NULL) {
        return 1;
    }
    free((char *)map_file);
    return 0;
}

const char *LAYER_NAMES[] = {
    "layout",
    "objects"
};

// TODO 1:1 copy of get_comp_id
Layers get_layer_id(const char *layer_name) {
    char *cn;
    for (int i=0; i < LAYERS_TOTAL; i++) {
        if (strcmp(LAYER_NAMES[i], layer_name) == 0) {
            return (Layers)i;
        }
    }
    return LAYERS_TOTAL;
}
