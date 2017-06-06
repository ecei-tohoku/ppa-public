
#include "stdio.h"
#include "string.h"

int max(int x, int y) { return x > y ? x : y; };
int min(int x, int y) { return x < y ? x : y; };

int min3(int a, int b, int c) {
  return min(a, min(b, c));
}

int ld(char *x, int m, char *y, int n) {
  if(m == 0 || n == 0)
    return max(m, n);

  return min3(
    ld(x, m-1, y, n-1) + (x[m-1] != y[n-1] ? 1 : 0),
    ld(x, m-1, y, n) + 1,
    ld(x, m, y, n-1) + 1
  );

}

int main() {
  char x[100], y[100];

  /* Wait for the user input. */
  scanf("%s", x);
  scanf("%s", y);

  printf("%d\n", ld(x, strlen(x), y, strlen(y)));

  return 0;
}
