#include "game.hpp"

int8_t load_map(const char *path) {
    const char *map_file = read_file(path);
    const cJSON *map_data = cJSON_Parse(map_file);
    if (map_data == NULL) {
        printf("map data is null\n");
    }
    const cJSON *tile_sets = cJSON_GetObjectItem(map_data, "tilesets");
    if (map_data == NULL) {
        printf("tilesets is null\n");
    }
    size_t tile_sets_size = cJSON_GetArraySize(tile_sets);
    printf("tile_sets_size = %lu\n",tile_sets_size);
    // need to grab all the tile maps

    // iterate through walls and shit

    // iterate trhough object lists?


    if (map_data == NULL) {
        return 1;
    }
    free((char *)map_file);
    return 0;
}
