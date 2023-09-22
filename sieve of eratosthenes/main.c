#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int32_t input(const char *msg) {
#define MAX_INPUT 11
  if (msg) {
    printf("%s", msg);
  }
  char user_input_str[MAX_INPUT];
  fgets(user_input_str, MAX_INPUT, stdin);
  return strtol(user_input_str, NULL, 10);
#undef MAX_INPUT
}

int main(void) {
  uint32_t N = input("Input Limit: ");
  bool *array = calloc(N, sizeof(bool));

  for (size_t i = 2; i < N; ++i) {
    if (array[i] == false) {
      uint32_t composite = i + i;
      while (composite < N) {
        array[composite] = true;
        composite += i;
      }
    }
  }

  for (size_t i = 2; i < N; ++i) {
    if (array[i] == false) {
      printf("%d\n", i);
    }
  }

  free(array);
}