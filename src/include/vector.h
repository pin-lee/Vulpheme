#include <stddef.h>
#include <stdlib.h>
#include <string.h>

/* vector.h usage
 * To implement
*/

// growth factor
#define GR_F 1.5

typedef struct vector {
    size_t element_size;
    size_t size;
    size_t length;
    void* elements;
} vector;

#define vector_create(type) _vector_create(sizeof (type))

vector _vector_create(size_t type_size) {
    vector v = {
        .element_size = type_size,
        .size = 0,
        .length = 0,
        .elements = 0 
    };
    return v;
}

void vector_add(vector* vec, void* element) {
    if (vec->element_size * (vec->length+1) >= vec->size) {
        vec = (vector*) realloc(vec->elements, vec->size * GR_F);
        vec->size *= GR_F;
    }
    char* sized_ptr = (char*) vec->elements; // vec->elements as byte array
    size_t cursor = vec->length * vec->element_size;
    memcpy(&sized_ptr[cursor], element, vec->element_size);
}

void vector_pop(vector* vec) {}
void vector_get(vector* vec) {}
void vector_delete(vector* vec) {}
void vector_free(vector* vec) {}