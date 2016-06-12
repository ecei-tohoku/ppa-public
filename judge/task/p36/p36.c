
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

int get_operations(char *pout_seq_x, char *pout_seq_y, char *pout_opr, int d[100][100], char *x, int m, char *y, int n) {
  int i, min, opr_ptr = 0;
  char operations[100], seq_x[100], seq_y[100];

  // Zero-fill.
  memset(operations, '\0', sizeof(char) * 100);
  memset(seq_x, '\0', sizeof(char) * 100);
  memset(seq_y, '\0', sizeof(char) * 100);

  // For null character.
  opr_ptr++;

  // Traverse the DP matrix.
  while(m != 0 || n != 0) {
    char opr_type = -1;

    if(m == 0 || n == 0) {
      if(m == 0) opr_type = 'I';
      if(n == 0) opr_type = 'D';

    } else {
      // Need to decide which way to go.
      min = min3(d[m-1][n-1], d[m][n-1], d[m-1][n]);

      if(min == d[m-1][n-1])
        opr_type = x[m-1] == y[n-1] ? '=' : 'R';
      else if(min == d[m-1][n])
        opr_type = 'D';
      else
        opr_type = 'I';

    }

    if(opr_type == '=' || opr_type == 'R') {
      operations[opr_ptr] = opr_type;
      seq_x[opr_ptr]    = x[m-1];
      seq_y[opr_ptr]    = y[n-1];

      opr_ptr++;
      m--;
      n--;

    } else if(opr_type == 'D') {
      operations[opr_ptr] = 'D';
      seq_x[opr_ptr]    = x[m-1];
      seq_y[opr_ptr]    = ' ';

      opr_ptr++;
      m--;

    } else if(opr_type == 'I') {
      operations[opr_ptr] = 'I';
      seq_x[opr_ptr]    = ' ';
      seq_y[opr_ptr]    = y[n-1];

      opr_ptr++;
      n--;

    }
  }

  // Copy the operations (do not forget to copy the null character!).
  for(i=0; i<opr_ptr; i++) {
    pout_opr[i] = operations[(opr_ptr-1) - i];
    pout_seq_x[i] = seq_x[(opr_ptr-1) - i];
    pout_seq_y[i] = seq_y[(opr_ptr-1) - i];
  }

  return opr_ptr;
}

void trim(char *s) {
  int i;

  for(i=strlen(s)-1; s[i]==' '; i--)
    s[i] = '\0';
}

int main() {
  char x[100], y[100];
  char operations[100], seq_x[100], seq_y[100];
  int d[100][100];

  /* Wait for the user input. */
  scanf("%s", x);
  scanf("%s", y);

  ld_dp(d, x, strlen(x), y, strlen(y));
  get_operations(seq_x, seq_y, operations, d, x, strlen(x), y, strlen(y));

  // Trimming.
  trim(operations);
  trim(seq_x);
  trim(seq_y);

  printf("%s\n%s\n%s\n", seq_x, seq_y, operations);

  return 0;
}
