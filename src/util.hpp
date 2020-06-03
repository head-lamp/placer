#ifndef UTIL_HEADER
#define UTIL_HEADER
const char* read_file(const char *path);
const char* strip_exts(const char *path);
const char* strcat(const char *a, const char *b);
size_t strlen(const char *path);

const char *get_json_string(const cJSON *obj, const char *key);
const int get_json_int(const cJSON *obj, const char *key);
const float get_json_float(const cJSON *obj, const char *key);

SDL_Rect* get_rects(const cJSON *obj, const char *key);
#endif
