#include <stdio.h>
#include <assert.h>

#define MEMORY_MAX 1024
unsigned char memory[MEMORY_MAX];
unsigned long top = 0;

void reset(void) {
    top = 0;
}

void *allocate(unsigned long size) {
    assert(top + size < MEMORY_MAX && "out of memory. reset the buffer");
    void *ptr = &memory[top];
    top += size;
    return ptr;
}

int main(void) {
    const char *greeting = "Hello";
    const char *farewell = "Goodbye";

    {
        unsigned long size = 16;
        char *buffer = allocate(size);
        snprintf(buffer, size, "%s, World", greeting);
        printf("%s\n", buffer);
    }

    reset();

    {
        unsigned long size = 16;
        char *buffer = allocate(size);
        snprintf(buffer, size, "%s, World", farewell);
        printf("%s\n", buffer);
    }
}
