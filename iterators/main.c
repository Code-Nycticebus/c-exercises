#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

typedef struct {
  size_t i;
  size_t end;
  uint32_t *data;
  uint32_t *element;
} Iterator;

Iterator iter(uint32_t *array, size_t size) {
  return (Iterator){
      .i = 0,
      .data = array,
      .end = size,
      .element = array,
  };
}

bool iter_end(Iterator *iterator) { return iterator->i < iterator->end; }

uint32_t *next(Iterator *iterator) {
  assert(iterator->i < iterator->end);
  iterator->element = &iterator->data[++iterator->i];
  return iterator->element;
}

int main(void) {
  uint32_t array[4] = {1, 2, 3, 4};
  for (Iterator it = iter(array, 4); iter_end(&it); next(&it)) {
    printf("%d\n", *it.element);
  }
}

