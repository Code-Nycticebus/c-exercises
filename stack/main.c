#include <assert.h>
#include <inttypes.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#define STACK_CAP 100

typedef uint64_t StackItem;

typedef struct {
  size_t top;
  StackItem data[STACK_CAP];
} Stack;

void stack_init(Stack *stack) { stack->top = 0; }

void stack_push(Stack *stack, StackItem item) {
  assert(stack->top < STACK_CAP);
  stack->data[stack->top++] = item;
}

StackItem stack_pop(Stack *stack) {
  assert(0 < stack->top);
  return stack->data[--stack->top];
}

int main(void) {
  Stack stack;
  stack_init(&stack);

  stack_push(&stack, 123);
  stack_push(&stack, 321);

  StackItem item;
  item = stack_pop(&stack);
  assert(item == 321);

  item = stack_pop(&stack);
  assert(item == 123);

  const size_t first_step = 10;
  for (size_t i = 0; i < first_step; ++i) {
    stack_push(&stack, i + 1);
  }

  for (size_t i = 0; i < first_step; ++i) {
    StackItem item = stack_pop(&stack);
    assert(item == first_step - i);
  }
}