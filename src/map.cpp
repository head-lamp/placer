#include "game.hpp"

int8_t load_map(const char *path) {
    const char *map_file = read_file(path);
    const cJSON *map_data = cJSON_Parse(map_file);
    if (map_data == NULL) {
        printf("map data is null\n");
    }
    const cJSON *tile_sets = cJSON_GetObjectItem(map_data, "tilesets");
    size_t tile_sets_size = cJSON_GetArraySize(tile_sets);
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
    printf("tile_sets_size = %lu\n",tile_sets_size);
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
