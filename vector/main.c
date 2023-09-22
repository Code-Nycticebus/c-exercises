#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef int32_t DynamicArrayType;
typedef struct {
  size_t _capacity;
  size_t size;
  DynamicArrayType *data;
} DynamicArray;

DynamicArray dynamic_array(size_t size) {
  DynamicArray array;
  array.data = malloc(size * sizeof(DynamicArrayType));
  array._capacity = size;
  array.size = 0;
  return array;
}

void _dynamic_array_resize(DynamicArray *array, size_t new_size) {
  array->data = realloc(array->data, new_size * sizeof(DynamicArrayType));
  array->_capacity = new_size;
}

void dynamic_array_push(DynamicArray *array, DynamicArrayType value) {
  if (!(array->size < array->_capacity)) {
    _dynamic_array_resize(array, array->_capacity * 2);
  }
  array->data[array->size] = value;
  array->size++;
}

DynamicArrayType dynamic_array_pop(DynamicArray *array) {
  array->size--;
  DynamicArrayType value = array->data[array->size];
  if (array->size < array->_capacity / 2) {
    _dynamic_array_resize(array, array->_capacity / 2);
  }
  return value;
}

int main(void) {
  DynamicArray array = dynamic_array(10);

  for (int j = 0; j < 5; ++j) {
    for (int i = 0; i < 20; ++i) {
      dynamic_array_push(&array, i);
    }

    size_t len = array.size;
    for (int i = 0; i < len; ++i) {
      printf("%d\n", dynamic_array_pop(&array));
    }
  }
}