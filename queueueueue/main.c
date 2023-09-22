#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#define QUEUE_MAX 10

typedef struct {
  uint64_t items[QUEUE_MAX];
  size_t items_count;
  size_t front, back;
} Queue;

void queue_init(Queue *queue) {
  queue->front = 0;
  queue->back = 0;
  queue->items_count = 0;
}

bool queue_empty(Queue *queue) { return queue->items_count == 0; }

bool queue_full(Queue *queue) { return queue->items_count == QUEUE_MAX; }

void enqueue(Queue *queue, uint64_t item) {
  // If queue is at end a start over
  if (!(queue->back < QUEUE_MAX)) {
    queue->back = 0;
  }

  if (!(queue->items_count < QUEUE_MAX)) {
    fprintf(stderr, "Queue is full!\n");
    return;
  }

  queue->items[queue->back] = item;
  queue->back++;
  queue->items_count++;
}

uint64_t dequeue(Queue *queue) {
  if (queue->items_count == 0) {
    fprintf(stderr, "Queue is empty!\n");
    return 0;
  }

  // If queue is at end start over
  if (QUEUE_MAX <= queue->front) {
    queue->front = 0;
  }

  uint64_t ret = queue->items[queue->front];
  queue->front++;
  queue->items_count--;
  return ret;
}

int main(void) {
  Queue queue;
  queue_init(&queue);

  printf("First:\n");
  const size_t first_step = QUEUE_MAX;
  for (size_t i = 0; i < first_step; ++i) {
    enqueue(&queue, i + 1);
  }

  for (size_t i = 0; i < first_step; ++i) {
    printf("  %d: %lld\n", i, dequeue(&queue));
  }

  printf("Second:\n");
  const size_t second_step = first_step + QUEUE_MAX;
  for (size_t i = first_step; i < second_step; ++i) {
    enqueue(&queue, i + 1);
  }

  for (size_t i = 0; i < second_step - first_step; ++i) {
    printf("  %d: %lld\n", i, dequeue(&queue));
  }

  printf("Empty:\n");
  (void)dequeue(&queue);

  printf("Full:\n");
  for (size_t i = 0; i < QUEUE_MAX; ++i) {
    enqueue(&queue, 0);
  }
  enqueue(&queue, 0);
}