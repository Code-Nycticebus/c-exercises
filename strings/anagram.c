#include <stdbool.h>
#include <stdio.h>
#include <string.h>

bool anagram(const char *s1, const char *s2) {
  const size_t len = strlen(s2);
  char buffer[len + 1];
  buffer[len] = '\0';
  strcpy(buffer, s2);
  size_t count = 0;

  for (size_t i = 0; s1[i] != '\0'; i++) {
    for (size_t j = 0; buffer[j] != '\0'; j++) {
      if (s1[i] == buffer[j]) {
        buffer[j] = -1;
        count++;
      }
    }
  }

  return count == len;
}

int main(void) {
  if (anagram("nana", "anna")) {
    printf("is anagram\n");
  } else {
    printf("is not anagram\n");
  }
}
