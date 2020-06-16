// please never call anything from the std lib
// during gameplay
// fopen fseek and ftell will all need to be reimplemented
// if these functions are too slow or take up too much
// memory
// todo read malloc and maybe write my own :|
#include <stdlib.h> // TODO replace std lib fns
#include <stdio.h> // TODO replace stdio.h fns

#include "game.hpp"

// slow
const char* read_file(const char *path) {
    char *txt;
    FILE *f = fopen(path, "r");
    if (f == NULL) {
        printf("couldn't open file%s\n", path);
    }
    fseek(f, 0, SEEK_END);
    size_t sz = ftell(f);
    fseek(f, 0, SEEK_SET);
    txt = (char *)malloc(sz + 1);
    fread(txt, sz, 1, f);
    txt[sz] = '\0';
    return txt;
}

const char* strip_exts(const char *path) {
    size_t i = 0;
    while (path[i] != '.' && path[i] != '\0') {
        i++;
    }
    // i will be at '.' now
    // malloc
    char *res = (char *)malloc(sizeof(char) * i);
    for (size_t x = 0; x < i; x++) {
        res[x] = path[x];
    }
    res[i] = '\0';
    printf("%s\n",res);
    return res;
}

// 0 is true here
int strcmp(char const *a, char const *b) {
    while (*a) {
        if (*a != *b) {
            break;
        }
        a++;
        b++;
    }
    return *a - *b;
}

size_t strlen(const char *path) {
    size_t i = 0;
    while (path[i] != '\0') {
        i++;
    }
    return i;
}

const char* strcat(const char *a, const char *b) {
    size_t a_len = strlen(a);
    size_t b_len = strlen(b);

    size_t len = a_len + b_len + 1;
    char* cat = (char *)malloc(sizeof(char) * len);

    for (size_t i = 0; i < a_len; i++) {
        cat[i] = a[i];
    }
    for (size_t i = 0; i < b_len; i++) {
        cat[i+a_len] = b[i];
    }

    cat[len] = '\0';

    return (const char *)cat;
}

const char *get_json_string(const cJSON *obj, const char *key) {
    cJSON *item = cJSON_GetObjectItem(obj, key);
    if (item == NULL) {
        return "";
    }
    return cJSON_GetStringValue(item);
}

const int get_json_int(const cJSON *obj, const char *key) {
    cJSON *item = cJSON_GetObjectItem(obj, key);
    if (item == NULL) {
        return 0;
    }
    return (int)cJSON_GetNumberValue(item);
}

const float get_json_float(const cJSON *obj, const char *key) {
    cJSON *item = cJSON_GetObjectItem(obj, key);
    if (item == NULL) {
        return (float)0;
    }
    return (float)cJSON_GetNumberValue(item);
}

SDL_Rect* get_rects(const cJSON *obj, const char *key) {
    cJSON *arrays = cJSON_GetObjectItem(obj, key);
    SDL_Rect *rects = NULL;
    if (arrays == NULL) {
        return rects;
    }
    size_t sz = cJSON_GetArraySize(arrays);
    rects = (SDL_Rect *)malloc(sizeof(SDL_Rect) * sz);
    printf("arr size = %lu\n", sz);
    for (size_t i=0; i < sz; i++) {
        cJSON *arr = cJSON_GetArrayItem(arrays, i);
        SDL_Rect rect = {};
        rect.x = (int)cJSON_GetNumberValue(cJSON_GetArrayItem(arr, 0));
        rect.y = (int)cJSON_GetNumberValue(cJSON_GetArrayItem(arr, 1));
        rect.w = (int)cJSON_GetNumberValue(cJSON_GetArrayItem(arr, 2));
        rect.h = (int)cJSON_GetNumberValue(cJSON_GetArrayItem(arr, 3));
        rects[i] = rect;
    }
    return rects;
}

const int snap_64(int n) {
    return (n + 0x20)&(~0x3f);
}
