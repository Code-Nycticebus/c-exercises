#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef int64_t NodeValue;

typedef struct Node {
  NodeValue value;
  struct Node *last, *next;
} Node;

Node *node_create(NodeValue value) {
  Node *node = malloc(sizeof(Node));
  assert(node);
  node->last = NULL;
  node->next = NULL;
  node->value = value;
  return node;
}

typedef struct {
  Node *start;
  Node *end;
} LinkedList;

void ll_push(LinkedList *ll, NodeValue value) {
  Node *node = node_create(value);
  if (ll->start != NULL) {
    ll->start->last = node;
    node->next = ll->start;
  }

  if (ll->end == NULL) {
    ll->end = node;
  }

  ll->start = node;
}

void ll_push_back(LinkedList *ll, NodeValue value) {
  Node *node = node_create(value);
  if (ll->end != NULL) {
    ll->end->next = node;
    node->last = ll->end;
  }
  if (ll->start == NULL) {
    ll->start = node;
  }
  ll->end = node;
}

NodeValue ll_pop(LinkedList *ll) {
  assert(ll->start);
  NodeValue value = ll->start->value;
  ll->start = ll->start->next;
  ll->start->last = NULL;
  return value;
}

NodeValue ll_pop_back(LinkedList *ll) {
  assert(ll->end);
  NodeValue value = ll->end->value;
  ll->end = ll->end->last;
  ll->end->next = NULL;
  return value;
}

void ll_print(LinkedList *ll) {
  for (Node *next = ll->start; next != NULL; next = next->next) {
    printf("%lld\n", next->value);
  }
}

int main(void) {
  LinkedList ll = {0};
  ll_push(&ll, 1);
  ll_push(&ll, 2);
  ll_push(&ll, 3);

  ll_push_back(&ll, 120);

  printf("pop: %lld\n", ll_pop(&ll));
  printf("pop: %lld\n", ll_pop_back(&ll));

  ll_print(&ll);
}