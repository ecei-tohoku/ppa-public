#include <stdio.h>
#include <string.h>

int main()
{
  int i, s = 0;
  char digits[101];
  int table[10] = {0, 2, 4, 6, 8, 1, 3, 5, 7, 9};

  scanf("%s", digits);

  for (i = 1; i <= strlen(digits); ++i) {
    int v = digits[strlen(digits)-i] - '0';
    if (i % 2 == 1) {
      s += v;
    } else {
      s += table[v];
    }
  }

  if (s % 10 == 0) {
    printf("true\n");
  } else {
    printf("false\n");
  }

  return 0;
}
