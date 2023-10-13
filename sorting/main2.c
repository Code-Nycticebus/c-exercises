#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE 100000

int main(void) {
  int arr[ARRAY_SIZE];
  for (size_t i = 0; i < ARRAY_SIZE; i++) {
    arr[i] = rand() % ARRAY_SIZE;
  }

  bool switched = true;
  while (switched == true) {
    switched = false;
    for (int i = 0; ARRAY_SIZE - 1 > i; i++) {
      if (arr[i] < arr[i + 1]) {
        int x;
        x = arr[i];
        arr[i] = arr[i + 1];
        arr[i + 1] = x;
        switched = true;
      }
    }
  }
  // for (unsigned int i = 0; i < sizeof(arr) / sizeof(int); i++) {
  //   printf("Sorted List = %d\n", arr[i]);
  // }
  printf("Done!\n");
  return 0;
}
