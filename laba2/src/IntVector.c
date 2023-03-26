#include <stdio.h>
#include <stdlib.h>

typedef struct {
    size_t size; // размер
    size_t capacity; // ёмкость
    int* data; // массив
} IntVector;

IntVector* int_vector_new(size_t initial_capacity)
{
    IntVector* vector = malloc(sizeof(IntVector));

    if (!vector) {
        free(vector);
        return NULL;
    }

    vector->data = malloc(initial_capacity * sizeof(int));

    if (!(vector->data)) {
        free(vector);
        return NULL;
    }

    vector->capacity = initial_capacity;
    vector->size = 0;
    
    return vector;
}

IntVector* int_vector_copy(const IntVector* v) 
{
    IntVector* vector_copy = malloc(sizeof(IntVector));

    if (!vector_copy) {
        free(vector_copy);
        return NULL;
    }

    vector_copy->data = malloc(v->capacity * sizeof(int));

    if (!(vector_copy->data)) {
        free(vector_copy);
        return NULL;
    }

    vector_copy->capacity = v->capacity;
    vector_copy->size = v->size;

    for (int i = 0; i < vector_copy->size; i++) {
        vector_copy->data[i] = v->data[i];
    }

    return vector_copy;
}

void int_vector_free(IntVector* v)
{
    free(v->data);
    free(v);
}

int int_vector_get_item(const IntVector* v, size_t index)
{
    return v->data[index];
}

void int_vector_set_item(IntVector* v, size_t index, int item)
{
    v->data[index] = item;

    if(index == v->size) {
        v->size = index + 1;
    }
}

size_t int_vector_get_size(const IntVector* v)
{
    return v->size;
}

size_t int_vector_get_capacity(const IntVector* v)
{
    return v->capacity;
}

int int_vector_push_back(IntVector* v, int item)
{
    // int* expance;

    if (v->size == v->capacity) {
        int* expance = realloc(v->data, v->capacity * sizeof(int) * 2);
        if (!expance) {
            return -1;
        }
        v->data = expance;
        v->capacity = v->capacity * 2;
    }

    v->data[v->size] = item;
    v->size++;

    return 0;
}

void int_vector_pop_back(IntVector* v)
{
    if (v->size > 0) {
        v->size--;
    }
}

int int_vector_shrink_to_fit(IntVector* v)
{
    if (v->size == 0) {
        return -1;
    }

    // int* expance;
    if (v->capacity > v->size) {
        int* expance = realloc(v->data, v->size * sizeof(int));
        if (!expance) {
            return -1;
        }
        v->data = expance;
        v->capacity = v->size;

        return 0;
    }
    
    return -1;
}

int int_vector_resize(IntVector* v, size_t new_size)
{
    if (new_size == v->size || new_size > v->capacity) {
        return -1;
    }
    
    if (new_size > v->size) {
        for (int i = v->size; i < new_size; i++) {
            v->data[i] = 0;
        }
        v->size = new_size;
    }

    if (new_size < v->size) {
        v->size = new_size;
        int_vector_shrink_to_fit(v);
    }
    return 0;
}

int int_vector_reserve(IntVector* v, size_t new_capacity)
{
    if (new_capacity <= v->capacity) {
        return -1;
    }

    // int* expance;
    int* expance = realloc(v->data, new_capacity * sizeof(int));

    if (!expance) {
        return -1;
    }
    v->data = expance;
    v->capacity = new_capacity;
    
    return 0;
}