int8_t load_map(const char *path);

struct Map {
    cJSON *tile_sets;
};

enum Layers {
    LAYOUT,
    OBJECTS,
    LAYERS_TOTAL,
};

Layers get_layer_id(const char *layer_name);
