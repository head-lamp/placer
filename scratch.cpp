#include "lib/cJSON.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    FILE *f = fopen("assets/maps/test_maps/test_map0.json","r");
    if (f == NULL) {
        printf("couldn't open");
        return 1;
    }
    fseek(f, 0, SEEK_END);
    long numbytes = ftell(f);
    printf("bytesize: %ld\n", numbytes);
    char *buffer = (char *)calloc(numbytes, sizeof(char));
    if (buffer == NULL) {
        printf("can't load");
        return 1;
    }
    fseek(f, 0, SEEK_SET);
    fread(buffer, sizeof(char), numbytes, f);
    printf("file_content\n%s\n", buffer);
    fclose(f);
}
