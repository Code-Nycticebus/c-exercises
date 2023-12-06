#include <stdint.h>
#include <stdio.h>

void swap(uint32_t *a, uint32_t *b) {
  uint32_t temp = *a;
  *a = *b;
  *b = temp;
}

void sort(uint32_t *array, size_t n) {
  const size_t highest_index = n - 1;
  for (size_t insert_index = 0; insert_index < highest_index; insert_index++) {
    size_t min_index = insert_index;
    for (size_t i = insert_index; i <= highest_index; ++i) {
      if (array[i] < array[min_index]) {
        min_index = i;
      }
    }
    swap(&array[min_index], &array[insert_index]);
  }
}

void print_array(uint32_t *array, size_t n) {
  printf("{");
  for (size_t i = 0; i < n; ++i) {
    if (i != 0) {
      printf(", ");
    }
    printf("%d", array[i]);
  }
  printf("}");
}

int main(void) {
  uint32_t array[] = {6, 5, 9, 7, 2}; // NOLINT
  const size_t array_size = sizeof(array) / sizeof(array[0]);
  sort(array, array_size);
  print_array(array, array_size);
}

