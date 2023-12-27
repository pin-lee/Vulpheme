#pragma once

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

// growth factor
#define GR_F 1.5

// starting size
#define ST_S 8

typedef struct vector {
    size_t element_size;
    size_t size;
    size_t length;
    void* elements;
} vector;

#define vector_create(type) _vector_create(sizeof (type))
vector* _vector_create(size_t type_size) {
    return &(vector) {
        .element_size = type_size, .size = ST_S, .length = 0, .elements = 0 };
}

#define BYTE_ARRAY char* byte_array = (char*) vec->elements; 

void vector_add(vector* vec, void* element) {
    if (vec->element_size * (vec->length+1) >= vec->size) {
        vec = (vector*) realloc(vec->elements, vec->size * GR_F);
        vec->size *= GR_F;
    }
    size_t cursor = vec->length * vec->element_size;
    BYTE_ARRAY; memcpy(&byte_array[cursor], element, vec->element_size);
    vec->length++;
}

void* vector_get(vector* vec, size_t index) {
    BYTE_ARRAY; return &byte_array[index * vec->element_size];
}

void vector_free(vector* vec) {
    free(vec->elements);
}
