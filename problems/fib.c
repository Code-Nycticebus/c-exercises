#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define N 1000000000000000000UL

typedef struct {
    int cap;
    int len;
    uint64_t *data;
} BigInt;

void bi_push(BigInt *bi, uint64_t value) {
    if (bi->data == NULL) {
        bi->cap = 8;
        bi->data = malloc(sizeof(bi->data[0]) * bi->cap);
    } else if (bi->len >= bi->cap) {
        bi->cap *= 2;
        bi->data = realloc(bi->data, sizeof(bi->data[0]) * bi->cap);
    }
    bi->data[bi->len++] = value;
}

void bi_set(BigInt *bi, uint64_t value) {
}

void  bi_free(BigInt *bi) {
    free(bi->data);
    bi->data = NULL;
    bi->cap = 0;
    bi->len = 0;
}

BigInt *bi_add(BigInt *a, BigInt *b) {
    uint64_t carry = 0;
    for (int i = 0; i < b->len; ++i) {
        if (i < a->len) a->data[i] += b->data[i] + carry;
        else bi_push(a, b->data[i] + carry);
        uint64_t value = a->data[i] % N;
        carry = a->data[i] / N;
        a->data[i] = value;
    }
    if (carry > 0) {
        bi_push(a, carry);
    }
}

void bi_print(const BigInt *bi) {
    if (bi->len == 0) {
        printf("0\n");
        return;
    }

    for (int i = bi->len-1; i >= 0; --i) {
        if (i == bi->len-1) {
            printf("%lu", bi->data[i]);
        } else {
            printf("%018lu", bi->data[i]);
        }
    }
    printf("\n");
}

BigInt* bi_fib(uint64_t n, BigInt *a, BigInt *b) {
    a->len = 0;
    bi_push(a, 0);
    if (n == 0) return a;

    b->len = 0;
    bi_push(b, 1);

    BigInt *c = a;

    for (uint64_t i = 0; i < n; ++i) {
        bi_add(a, b);
        c = a;
        a = b;
        b = c;
    }

    return a;
}

int main(void) {
    BigInt a = {0};
    BigInt b = {0};

    BigInt *value = bi_fib(420, &a, &b);
    printf("fib: \t"); bi_print(value);

    bi_free(&a);
    bi_free(&b);
}
