#pragma once

#include <stdio.h>
#include <stdlib.h>

const char* readFile(const char* filename) {
    FILE* fp;
    char* buffer;
    long size;

    fp = fopen(filename, "rb"); // open file in binary read mode
    if (fp == NULL) {
        fprintf(stderr, "Error: file not found\n");
        return NULL;
    }

    fseek(fp, 0, SEEK_END); // seek to end of file
    size = ftell(fp); // get current file pointer position, which is the file size
    rewind(fp); // rewind file pointer to beginning of file

    buffer = (char*)malloc(size + 1); // allocate memory for buffer
    if (buffer == NULL) {
        fprintf(stderr, "Error: memory allocation failed\n");
        fclose(fp);
        return NULL;
    }

    fread(buffer, 1, size, fp); // read entire file into buffer
    buffer[size] = '\0'; // add null terminator at end of buffer

    fclose(fp); // close file
    return buffer;
}