#define T int
#include "option.h"

#define T char
#include "option.h"

#include <stdio.h>

Option(int) validate(int i) { return i < 20 ? Some(int, i) : None(int); }

int main(void) {
  Option(int) o = validate(10);
  int i = Unwrap(int, o);

  OptionPtr(char) o2 = SomePtr(char, "Fuck");

  printf("%d\n", i);
}
