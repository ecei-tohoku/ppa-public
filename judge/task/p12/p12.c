#include <stdio.h>

int main()
{
  int i, x;

  scanf("%d", &x);
  for (i = 0; i < 100; ++i) {
    printf("%d\n", x);
    if (x % 2 == 0) {
      x /= 2;
    } else {
      x *= 3;
      ++x;
    }
    if (x == 1) {
      printf("%d\n", x);
      printf("OK\n");
      break;
    }
  }
  return 0;
}
