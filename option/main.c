#define T int
#include "option.h"

#define T char
#include "option.h" // NOLINT

#include <stdio.h>

#define MAX_VALUE 20

Option(int) validate(int i) { return i < MAX_VALUE ? Some(int, i) : None(int); }

int main(void) {
  const int input = 10;
  Option(int) o = validate(input);
  int i = Unwrap(int, o);

  OptionPtr(char) o2 = SomePtr(char, "Fuck");

  printf("%d\n", i);
  printf("%s\n", UnwrapPtr(char, o2));
}
