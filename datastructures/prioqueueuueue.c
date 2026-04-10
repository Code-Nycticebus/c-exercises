// Sorted Queue / Priority Queue using linked list

#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

#define NODE_MAX 100
Node _memory[NODE_MAX] = {0};
unsigned int _memory_top = 0;

Node *memory_allocate(void) {
    assert(_memory_count < NODE_MAX && "Memory overflow");
    return &_memory[_memory_top++];
}

void memory_reset(void) {
    _memory_top = 0;
}

typedef Node *Heap;

static Node *_heap_create_node(int value, Node *next) {
    Node *new = memory_allocate();
    new->value = value;
    new->next = next;
    return new;
}

void heap_insert(Heap *heap, int value) {
    assert(heap);
    if (*heap == NULL) {
        *heap = _heap_create_node(value, NULL);
        return;
    }
    if ((*heap)->value == value) return;
    if ((*heap)->value > value) {
        *heap = _heap_create_node(value, *heap);;
        return;

    }

    for (Node *node = *heap; node != NULL; node = node->next) {
        if (node->next && node->next->value < value) continue;
        if (node->next && node->next->value == value) return; 
        node->next = _heap_create_node(value, node->next);
        return;
    }

    assert(0 && "Unreachable: heap_insert()");
}

bool heap_pop(Heap *heap, int *out) {
    assert(heap);
    if (*heap == NULL) return false;
    *out = (*heap)->value;
    *heap = (*heap)->next;
    return true;
}


int main(void) {
    Node *root = NULL;

    heap_insert(&root, 420);
    heap_insert(&root, 213);
    heap_insert(&root, 179);
    heap_insert(&root, 123);
    heap_insert(&root, 313);

    for (int i = 0; i < 3; ++i) {
        int n = 0;
        if (!heap_pop(&root, &n)) assert(0 && "empty !");
        printf("%d\n", n);
    }
}
