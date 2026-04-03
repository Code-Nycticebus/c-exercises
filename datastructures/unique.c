#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Unique pointers are there to signal ownership. Movement of Unique pointers is movement of
// ownership. The taker is now responsible for calling free...

#define _unique_check(ptr, action)                                                                 \
    ((ptr).moved == true                                                                           \
         ? (printf("%s:%d: '%s' but already moved!\n", __FILE__, __LINE__, action), abort())       \
         : (void)0)

#define Unique(T) struct { bool moved; T* data; }

#define unique_alloc(T)  {.data = calloc(1, sizeof(T)), .moved = false}
#define unique_free(ptr)                                                                           \
    do {                                                                                           \
        _unique_check(ptr, "unique_free");                                                         \
        free((ptr).data);                                                                          \
        (ptr).data = NULL;                                                                         \
        (ptr).moved = true;                                                                        \
    } while (0)

#define unique_get(ptr) (_unique_check(ptr, "unique_get"), (ptr).data)
#define unique_move(ptr) {.data = (_unique_check(ptr, "unique_move"), (ptr).moved = true, (ptr).data)}

// USER CODE

typedef Unique(int) UniqueInt;

// a function that creates an object
UniqueInt make_int(int value) {
    UniqueInt i = unique_alloc(int);
    *unique_get(i) = value;
    return (UniqueInt)unique_move(i);
}

// a function that will take ownership
void take_int(UniqueInt ptr) {
    printf("%d\n", *unique_get(ptr));
    unique_free(ptr);
}

int main(void) {
    // create unique pointer
    UniqueInt my_uptr = make_int(420);

    // move unique pointer
    take_int((UniqueInt)unique_move(my_uptr));

    // all these errors get catched!
    // *unique_get(my_uptr) = 420;                // use after free
    // take_int((UniqueInt)unique_move(my_uptr)); // multiple moves
    // unique_free(my_uptr);                      // double free
}
