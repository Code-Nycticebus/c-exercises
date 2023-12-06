#include <stdint.h>
#include <stdio.h>

const uint8_t *binary_search_r(size_t size, const uint8_t array[size],
                               uint8_t search_value) {
  if (size == 0) {
    return NULL;
  }
  size_t middle_idx = (size % 2 ? size + 1 : size) / 2;
  return array[middle_idx] == search_value ? &array[middle_idx]
         : array[middle_idx] < search_value
             ? binary_search_r(middle_idx, &array[middle_idx], search_value)
             : binary_search_r(middle_idx, &array[0], search_value);
}

int binary_search(size_t size, const uint8_t array[size],
                  uint8_t search_value) {
  const uint8_t *ptr = binary_search_r(size, array, search_value);
  return ptr ? ptr - array : -1;
}

int main(void) {
  const uint8_t array[] = {
      1,  2,  7,  8,  9,   10,  22,  23,  38,  55,
      56, 67, 70, 98, 101, 160, 199, 200, 250, 255,
  };
  const size_t size = sizeof(array) / sizeof(array[0]);
  const uint8_t search_value = 55;

  const int searchindex = binary_search(size, array, search_value);
  if (searchindex != -1) {
    printf("element with value %u is at index %d\n", search_value, searchindex);
  } else {
    printf("element with value %u not found!\n", search_value);
  }
  return 0;
}
