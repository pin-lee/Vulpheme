#pragma once

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

typedef struct vector {
    size_t element_size;
    size_t size;
    size_t length;
    void* elements;
} vector;

#define vector_create(type) _vector_create(sizeof (type))
vector* _vector_create(size_t type_size) {
    return &(vector) {
        .size = 0,
        .element_size = type_size,
        .length = 0,
        .elements = NULL,
    };
}

void* vector_add(vector* vec, void* element) {
    puts("Made it here.\n");
    if (vec->element_size * (vec->length+1) >= vec->size) {
        puts("Reallocating vector.");
        vec->elements = realloc(vec->elements, vec->size += vec->size / 2);
        vec->size += vec->size / 2;
    }
    size_t cursor = vec->length * vec->element_size;
    char* byte_array = (char*) vec->elements; 
    memcpy(&byte_array[cursor], element, vec->element_size);
    vec->length++;
    return &(byte_array[cursor]);
}

void* vector_get(vector* vec, size_t index) {
    char* byte_array = (char*) vec->elements; 
    return &byte_array[index * vec->element_size];
}

void vector_free(vector* vec) {
    free(vec->elements);
}
