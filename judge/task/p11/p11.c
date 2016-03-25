#include <stdio.h>

int main()
{
  int a, b, x, y;
  scanf("%d %d", &a, &b);
  x = a + b;
  y = b - a;
  if (x % 2 != 0 || y % 2 != 0) {
    printf("ERROR\n");
  } else {
    printf("%d %d\n", x / 2, y / 2);
  }
  return 0;
}
