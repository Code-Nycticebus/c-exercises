#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  size_t ref_count;
  void *data;
} _SharedPtr;

#define SharedPtr(...) _SharedPtr

SharedPtr(T) make_shared(void *data) {
  return (SharedPtr(T)){
      .ref_count = 1,
      .data = data,
  };
}

SharedPtr(T) * shared_inc_ref(SharedPtr(T) * shared) {
  shared->ref_count++;
  return shared;
}

void shared_dec_ref(SharedPtr(T) * shared) {
  shared->ref_count--;
  if (shared->ref_count == 0) {
    free(shared->data);
  }
}

#define shared_get(T) (T *)_shared_get
void *_shared_get(SharedPtr(T) * ptr) {
  assert(ptr->ref_count);
  return ptr->data;
}

typedef struct {
  SharedPtr(int) * ptr;
} IsUsingShared;

void do_things(IsUsingShared *s) { printf("%d\n", *shared_get(int)(s->ptr)); }
void free_thing(IsUsingShared *s) { shared_dec_ref(s->ptr); }

int main(void) {
  int *i = malloc(sizeof(int));
  *i = 2;
  SharedPtr(int) shared_int = make_shared(i);

  IsUsingShared s = {.ptr = shared_inc_ref(&shared_int)};
  shared_dec_ref(&shared_int);

  do_things(&s);
  free_thing(&s);
}
