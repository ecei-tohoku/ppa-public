
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

int max(int x, int y) { return x > y ? x : y; };
int min(int x, int y) { return x < y ? x : y; };

int min3(int a, int b, int c) {
  return min(a, min(b, c));
}

int ld(char *x, int m, char *y, int n, int *c, int memo[100][100]) {
  int ret;

  (*c)++;

  if(m == 0 || n == 0)
    return max(m, n);

  if(memo != NULL) {
    if(memo[m][n] == -1) {
      ret = min3(
        ld(x, m-1, y, n-1, c, memo) + (x[m-1] != y[n-1] ? 1 : 0),
        ld(x, m-1, y, n, c, memo) + 1,
        ld(x, m, y, n-1, c, memo) + 1
      );

      memo[m][n] = ret;

    } else {
      ret = memo[m][n];

    }

  } else {
    ret = min3(
      ld(x, m-1, y, n-1, c, memo) + (x[m-1] != y[n-1] ? 1 : 0),
      ld(x, m-1, y, n, c, memo) + 1,
      ld(x, m, y, n-1, c, memo) + 1
    );

  }

  return ret;
}

int main() {
  char x[100], y[100];

  /* Wait for the user input. */
  while(scanf("%s %s", x, y) != EOF) {
    int c_withmemo = 0, c_withoutmemo = 0;
    int memo[100][100];
    int m, n, ret1, ret2;

    memset(memo, -1, sizeof(int)*100*100);

    m = strlen(x);
    n = strlen(y);

    ret1 = ld(x, m, y, n, &c_withoutmemo, NULL);
    ret2 = ld(x, m, y, n, &c_withmemo, memo);

    printf("%d\n", ret1);
    fprintf(stderr, "%d,%d,%d,%d,%d\n",
      m, n, m*n,
      c_withoutmemo,
      c_withmemo);

  }

  return 0;
}
