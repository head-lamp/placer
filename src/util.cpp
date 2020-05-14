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
