#include <stdio.h>
#include <stdlib.h>

typedef enum {
  UNIQUE_OK,
  UNIQUE_FREE,
  UNIQUE_MOVED,
  UNIQUE_USED,
} UniqueState;

typedef struct {
  UniqueState state;
  void *data;
  const char *file;
  int line;
} UniquePtr;

UniquePtr make_unique(void *data) {
  return (UniquePtr){
      .data = data,
      .state = UNIQUE_OK,
      .file = NULL,
      .line = 0,
  };
}

#define ASSERT(cond, msg, ptr, file, line, action)                             \
  {                                                                            \
    if (!(cond)) {                                                             \
      fprintf(stderr, "%s:%d: '%s' failed: %s: %s:%d\n", file, line, action,   \
              msg, ptr->file, ptr->line);                                      \
      abort();                                                                 \
    }                                                                          \
  }

static void _unique_check(UniquePtr *ptr, const char *action, const char *file,
                          int line) {
  ASSERT(ptr->state != UNIQUE_USED, "Pointer in use", ptr, file, line, action);
  ASSERT(ptr->state != UNIQUE_MOVED, "UniquePtr was moved", ptr, file, line,
         action);
  ASSERT(ptr->state != UNIQUE_FREE, "UniquePtr was moved!", ptr, file, line,
         action);
  ASSERT(ptr->state == UNIQUE_OK, "Something went wrong!", ptr, file, line,
         action);
}

#define unique_free(ptr) _unique_free(ptr, __FILE__, __LINE__)
#define unique_move(ptr) _unique_move(ptr, __FILE__, __LINE__)
#define unique_get(ptr) _unique_get(ptr, __FILE__, __LINE__)

void _unique_free(UniquePtr *ptr, const char *file, int line) {
  _unique_check(ptr, "free", file, line);
  ptr->file = file;
  ptr->line = line;
  ptr->state = UNIQUE_FREE;
  free(ptr->data);
}

void *_unique_get(UniquePtr *ptr, const char *file, int line) {
  _unique_check(ptr, "get", file, line);
  ptr->state = UNIQUE_USED;
  ptr->line = line;
  ptr->file = file;
  return ptr->data;
}

void unique_release(UniquePtr *ptr) { ptr->state = UNIQUE_OK; }

UniquePtr _unique_move(UniquePtr *ptr, const char *file, int line) {
  _unique_check(ptr, "move", file, line);
  UniquePtr new_ptr = *ptr;
  ptr->state = UNIQUE_MOVED;
  ptr->line = line;
  ptr->file = file;
  new_ptr.state = UNIQUE_OK;
  return new_ptr;
}

int *make_int(int value) {
  int *i = malloc(sizeof(int));
  *i = value;
  return i;
}

int add(UniquePtr ptr, int value) {
  int result = *(int *)unique_get(&ptr) + value;
  unique_release(&ptr);
  unique_free(&ptr);
  return result;
}

int add_ip(const int *ptr, int value) { return *ptr + value; }

int main(void) {
  const int my_val = 420;
  UniquePtr my_int = make_unique(make_int(my_val));

  printf("%d\n", *(int *)unique_get(&my_int));
  unique_release(&my_int);

  // printf("%d\n", add(unique_move(&my_int), 1));
  printf("%d\n", add_ip(unique_get(&my_int), 2));
  unique_release(&my_int);

  unique_free(&my_int);
}
