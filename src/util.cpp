// please never call anything from the std lib
// during gameplay
// fopen fseek and ftell will all need to be reimplemented
// if these functions are too slow or take up too much
// memory
// todo read malloc and maybe write my own :|
#include <stdlib.h> // TODO replace std lib fns
#include <stdio.h> // TODO replace stdio.h fns

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
