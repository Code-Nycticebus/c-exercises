#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>


#define ARENA_DEFAULT_SIZE (1024*8)

typedef struct Chunk Chunk;

typedef struct {
    Chunk *begin, *end;
} Arena;

struct Chunk {
    Chunk *next;
    size_t cap;
    size_t top;
    uint8_t data[];
};

Chunk *arena_chunk_alloc(size_t size) {
    Chunk *chunk = NULL;

    size = ARENA_DEFAULT_SIZE < size ? size : ARENA_DEFAULT_SIZE;
    chunk = malloc(size + sizeof(Chunk));
    assert(chunk);
    chunk->next = NULL;
    chunk->cap  = size;
    chunk->top  = chunk->cap;

    return chunk;
}

void *arena_chunk_ptr(Chunk *chunk, size_t size) {
    assert(chunk->top >= size);
    chunk->top -= size;
    return &chunk->data[chunk->top];
}

void *arena_alloc(Arena *arena, size_t size) {
    if (arena->begin == NULL) {
        arena->begin = arena_chunk_alloc(size);
        arena->end = arena->begin;
    }

    for (Chunk *current = arena->begin; current; current = current->next) {
        if (size <= current->top) {
            return arena_chunk_ptr(current, size);
        }
    }

    Chunk *end = arena->end;
    arena->end = arena_chunk_alloc(size);
    end->next = arena->end;

    return arena_chunk_ptr(arena->end, size);
}

void arena_free(Arena *arena) {
    Chunk *current = arena->begin;
    Chunk *next = NULL;
    while (current) {
        next = current->next;
        free(current);
        current = next;
    }
}

int main(void) {
    Arena arena = {0};

    int *a = arena_alloc(&arena, sizeof(int));
    int *b = arena_alloc(&arena, sizeof(int));
    int *c = arena_alloc(&arena, sizeof(int));

    *a = 69;
    *b = 23;
    *c = 42;

    printf("%d %d %d\n", *a, *b, *c);

    arena_free(&arena);
}
