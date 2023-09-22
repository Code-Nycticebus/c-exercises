#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

bool palindrome(size_t size, const char *s1) {
  for (size_t i = 0, j = size - 1; i < size; ++i, --j) {
    if (s1[i] != s1[j]) {
      return false;
    }
  }
  return true;
}

int main(void) {
#define MAX_INPUT 20
  char user_input[MAX_INPUT];
  fgets(user_input, MAX_INPUT, stdin);
  size_t len = strlen(user_input) - 1; // truncate the newline
  bool is_palindrome = palindrome(len, user_input);
  printf("\"%.*s\" %s a palindrome\n", len, user_input,
         is_palindrome ? "is" : "is not");
}