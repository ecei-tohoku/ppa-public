
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

int main() {
  char w[100];
  int  i;
  int  size_vocab;
  int  dm[100][100];
  char dict[5000][100];
  int  edist[5000];

  // Read a dictionary.
  scanf("%d", &size_vocab);

  for(i=0; i<size_vocab; i++) {
    scanf("%s", dict[i]);
  }

  // Wait for the user input.
  while(scanf("%s", w) != EOF) {
    int min_w = 0, out_w = 0;

    // Calculate edit distance between the input word and candidates.
    for(i=0; i<size_vocab; i++) {
      edist[i] = ld_dp(dm, dict[i], strlen(dict[i]), w, strlen(w));

      if(edist[min_w] > edist[i]) {
        min_w = i;
      }
    }

    // Output minimum edit distance words.
    for(i=0; i<size_vocab; i++) {
      if(edist[i] == edist[min_w]) {
        if(out_w > 0)
          printf(" ");

        printf("%s", dict[i]);
        out_w++;
      }
    }

    printf("\n");
  }

  return 0;
}
