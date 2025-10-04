#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

typedef int64_t (*clojureFn)(void *);

typedef struct {
  clojureFn fn;
  void *args;
  int64_t result;
  bool called;
} Clojure;

Clojure clojure(void *fn, void *args) {
  return (Clojure){
      .fn = (clojureFn)fn,
      .args = args,
      .called = false,
      .result = 0,
  };
}

int64_t call(Clojure *clojure) {
  if (!clojure->called) {
    clojure->result = clojure->fn(clojure->args);
    clojure->called = true;
  }
  return clojure->result;
}

typedef struct {
  int a;
  int b;
} Args;
int64_t function(Args *args) { return args->a + args->b; }

int main(void) {
  Clojure c = clojure(function, (Args[]){{.a = 399, .b = 21}}); // NOLINT
  printf("%" PRIu64 "\n", call(&c));
}
