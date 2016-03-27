#include <ctype.h>
#include <stdio.h>

int main()
{
  int i, j, x;
  int states[9] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
  int patterns[8][3] = {
    {0, 1, 2}, {3, 4, 5}, {6, 7, 8},
    {0, 3, 6}, {1, 4, 7}, {2, 5, 8},
    {0, 4, 8}, {2, 4, 6}
  };

  for (i = 0; i < 10; ++i) {
    // The mark of this turn.
    int m = (i % 2 == 0) ? 'o' : 'x';

    // Show the current state.
    printf("%c|%c|%c\n", states[6], states[7], states[8]);
    printf("-+-+-\n");
    printf("%c|%c|%c\n", states[3], states[4], states[5]);
    printf("-+-+-\n");
    printf("%c|%c|%c\n", states[0], states[1], states[2]);

    // Judge the state.
    for (j = 0; j < 8; ++j) {
      int a = patterns[j][0];
      int b = patterns[j][1];
      int c = patterns[j][2];
      if (states[a] == 'o' && states[b] == 'o' && states[c] == 'o') {
        printf("o win!\n");
        return 0;
      }
      if (states[a] == 'x' && states[b] == 'x' && states[c] == 'x') {
        printf("x win!\n");
        return 0;
      }
    }

    // Terminate the game if necessary.
    if (i == 9) {
      printf("even.\n");
      break;
    }

    // Print the prompt and read the number.
    do {
      printf("%c> ", m);
      scanf("%d", &x);
      if (x < 1 || 9 < x || !isdigit(states[x-1])) {
        printf("ERROR!\n");
        x = 0;
      }
    } while (x == 0);
    printf("\n");

    // Mark the position #x with c.
    states[x-1] = m;
  }

  return 0;
}
