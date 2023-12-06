#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE 10

void sort(int *array, size_t size) {
  for (size_t i = 0; i < size; i++) {
    for (size_t j = 1; j < size; j++) {
      if (array[j - 1] > array[j]) {
        int temp = array[j - 1];
        array[j - 1] = array[j];
        array[j] = temp;
      }
    }
  }
}

int main(void) {
  srand(time(NULL));
  int array[ARRAY_SIZE] = {0};
  for (size_t i = 0; i < ARRAY_SIZE; i++) {
    array[i] = rand();
  }

  sort(array, ARRAY_SIZE);

  for (size_t i = 0; i < ARRAY_SIZE; i++) {
    printf("%ld: %d\n", i, array[i]);
  }
}
