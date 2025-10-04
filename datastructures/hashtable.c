#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASHBUCKET_KEY_MAX_LEN 20

typedef struct HashBucket {
  char key[HASHBUCKET_KEY_MAX_LEN];
  uint64_t value;
  struct HashBucket *next;
} HashBucket;

HashBucket *hashbucket(const char *key, uint64_t value) {
  HashBucket *hb = malloc(sizeof(HashBucket));
  assert(hb);
  strncpy(hb->key, key, HASHBUCKET_KEY_MAX_LEN);
  hb->value = value;
  hb->next = NULL;
  return hb;
}

#define HASHTABLE_TABLE_SIZE 32

typedef struct {
  size_t num_elements;
  size_t num_of_collisions;
  HashBucket *table[HASHTABLE_TABLE_SIZE];
} HashTable;

uint64_t hash(const char *key, size_t size) {
  uint64_t result = 1;
  for (size_t i = 0; i < size; i++) {
    result *= key[i] * 3 ^ 4;
  }
  return result;
}

HashTable *hashtable(void) {
  HashTable *hash_table = calloc(1, sizeof(HashTable));
  assert(hash_table);
  return hash_table;
}

void hashtable_insert(HashTable *hash_table, const char *key, uint64_t value) {
  uint64_t index = hash(key, strlen(key)) % HASHTABLE_TABLE_SIZE;

  if (hash_table->table[index] == NULL) {
    hash_table->table[index] = hashbucket(key, value);
    hash_table->num_elements++;
    return;
  }

  HashBucket *current = hash_table->table[index];
  HashBucket *prev;
  while (current) {
    if (strncmp(key, current->key, HASHBUCKET_KEY_MAX_LEN) == 0) {
      current->value = value;
      return;
    }
    prev = current;
    current = current->next;
  }

  prev->next = hashbucket(key, value);
  hash_table->num_of_collisions++;
  hash_table->num_elements++;
}

uint64_t hashtable_get(HashTable *hash_table, const char *key) {
  uint64_t index = hash(key, strlen(key)) % HASHTABLE_TABLE_SIZE;

  HashBucket *current = hash_table->table[index];
  while (current) {
    if (strncmp(key, current->key, HASHBUCKET_KEY_MAX_LEN) == 0) {
      return current->value;
    }
    current = current->next;
  }

  assert(false);
  return 0;
}

void hashtable_free(HashTable *hash_table) {
  for (size_t i = 0; i < HASHTABLE_TABLE_SIZE; i++) {
    HashBucket *next = hash_table->table[i];
    while (next) {
      HashBucket *tmp = next;
      next = next->next;
      free(tmp);
    }
  }
  free(hash_table);
}

void hashtable_dump(HashTable *hash_table) {
  printf("%ld/%ld\n", hash_table->num_of_collisions, hash_table->num_elements);
  for (size_t i = 0; i < HASHTABLE_TABLE_SIZE; i++) {
    HashBucket *next = hash_table->table[i];
    while (next) {
      printf("%s -> %ld", next->key, next->value);
      next = next->next;
      printf("%s", next ? " | " : "");
    }
    printf("%s", hash_table->table[i] ? "\n" : "");
  }
}

int main(void) {
  HashTable *hash_table = hashtable();

  hashtable_insert(hash_table, "Loris", 4);
  hashtable_insert(hash_table, "Jose", 3);
  hashtable_insert(hash_table, "Michi", 2);
  hashtable_insert(hash_table, "Laven", 2);
  hashtable_insert(hash_table, "Loris", 1);

  printf("%ld\n", hashtable_get(hash_table, "Loris"));
  printf("%ld\n", hashtable_get(hash_table, "Jose"));
  printf("%ld\n", hashtable_get(hash_table, "Laven"));

  hashtable_dump(hash_table);
  hashtable_free(hash_table);
}
