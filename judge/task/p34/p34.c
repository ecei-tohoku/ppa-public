
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

int max(int x, int y) { return x > y ? x : y; };
int min(int x, int y) { return x < y ? x : y; };

int min3(int a, int b, int c) {
  return min(a, min(b, c));
}

int ld_dp(int d[100][100], char *x, int m, char *y, int n) {
  int i, j;

  /* Fill c_{0,i} and c_{j,0}. */
  for(i=0; i<m+1; i++) d[i][0] = i;
  for(j=0; j<n+1; j++) d[0][j] = j;

  for(i=1; i<m+1; i++) {
    for(j=1; j<n+1; j++) {
      d[i][j] = min3(
        d[i-1][j-1] + (x[i-1] != y[j-1] ? 1 : 0),
        d[i-1][j] + 1,
        d[i][j-1] + 1
      );
    }
  }

  return d[m][n];
}

void show_matrix(int d[100][100], char *x, int m, char *y, int n) {
  int i, j;

  // Put three spaces.
  printf("   ");

  // Print characters of Y.
  for(i=0; i<n; i++) {
    printf(" %c", y[i]);
  }

  printf("\n");

  // Print characters of X.
  for(i=0; i<m+1; i++) {
    printf("%c", i > 0 ? x[i-1] : ' ');

    for(j=0; j<n+1; j++) {
      printf(" %d", d[i][j]);
    }

    printf("\n");
  }
}

int main() {
  char x[100], y[100];
  int d[100][100];

  /* Wait for the user input. */
  scanf("%s", x);
  scanf("%s", y);

  ld_dp(d, x, strlen(x), y, strlen(y));
  show_matrix(d, x, strlen(x), y, strlen(y));

  return 0;
}
