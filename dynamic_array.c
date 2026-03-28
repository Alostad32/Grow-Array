#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int   *data;      // heap-allocated array
    int    size;      // current number of elements
    int    capacity;  // total allocated slots
} DynArray;

// Set up the array with an initial capacity of 4
void da_init(DynArray *arr) {
    arr->capacity = 4;
    arr->size     = 0;
    arr->data     = (int *)malloc(arr->capacity * sizeof(int));
    if (arr->data==NULL) { fprintf(stderr, "malloc failed\n"); exit(1); }
}

// Add a value doubles capacity if full
void da_push(DynArray *arr, int val) {
    if (arr->size == arr->capacity) {
        arr->capacity *= 2;
        arr->data = (int *)realloc(arr->data, arr->capacity * sizeof(int));
        if (!arr->data) { fprintf(stderr, "realloc failed\n"); exit(1); }
        printf("  [resized → capacity now %d]\n", arr->capacity);
    }
    arr->data[arr->size++] = val;
}

// Remove and return the last element
int da_pop(DynArray *arr) {
    if (arr->size == 0) { fprintf(stderr, "pop on empty array\n"); exit(1); }
    return arr->data[--arr->size];
}

// Get element at index using pointer arithmetic
int da_get(DynArray *arr, int i) {
    if (i < 0 || i >= arr->size) { fprintf(stderr, "index out of bounds\n"); exit(1); }
    return *(arr->data + i);
}

// Set element at index
void da_set(DynArray *arr, int i, int val) {
    if (i < 0 || i >= arr->size) { fprintf(stderr, "index out of bounds\n"); exit(1); }
    *(arr->data + i) = val;
}

// Print all elements
void da_print(DynArray *arr) {
    printf("  Array (size=%d, cap=%d): [", arr->size, arr->capacity);
    for (int i = 0; i < arr->size; i++)
        printf(" %d", arr->data[i]);
    printf(" ]\n");
}

// Free heap memory
void da_free(DynArray *arr) {
    free(arr->data);
    arr->data     = NULL;
    arr->size     = arr->capacity = 0;
}

int main(void) {
    DynArray arr;
    da_init(&arr);

    printf("\n=== Pushing 10 elements (starts at capacity 4) ===\n");
    for (int i = 1; i <= 10; i++) {
        printf("  push(%d)\n", i * 10);
        da_push(&arr, i * 10);
    }
    da_print(&arr);

    printf("\n=== Accessing via pointer arithmetic ===\n");
    printf("  da_get(0) = %d\n", da_get(&arr, 0));
    printf("  da_get(4) = %d\n", da_get(&arr, 4));
    printf("  da_get(9) = %d\n", da_get(&arr, 9));

    printf("\n=== Modifying element at index 2 ===\n");
    da_set(&arr, 2, 999);
    da_print(&arr);

    printf("\n=== Popping 3 elements ===\n");
    printf("  popped: %d\n", da_pop(&arr));
    printf("  popped: %d\n", da_pop(&arr));
    printf("  popped: %d\n", da_pop(&arr));
    da_print(&arr);

    printf("\n=== Freeing memory ===\n");
    da_free(&arr);
    printf("  data ptr = %p (NULL after free)\n", (void *)arr.data);

    printf("\nDone.\n\n");
    return 0;
}
