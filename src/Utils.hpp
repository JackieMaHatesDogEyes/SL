#pragma once

#include <cstdlib>
#include <cstdio>

static inline char* LoadFile(const char* filename) {
    FILE* file = fopen(filename, "rb");

    if (!file) {
        printf("Failed to open file %s\n", filename);
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    rewind(file);

    char* buffer = (char*)malloc(size + 1);
    buffer[size] = '\0';

    fread(buffer, sizeof(char), size, file);

    fclose(file);

    return buffer;
}