#include <stdio.h>

int main()
{
  int i, x, d[3];

  scanf("%d", &x);
  do {
    // Extract three digits d[2]d[1]d[0] from x.
    for (i = 0; i < 3; ++i) {
      d[i] = x % 10;
      x /= 10;
    }

    // Find the maximum and minimum of the digits.
    int max = -1, min = 11;
    for (i = 0; i < 3; ++i) {
      if (max < d[i]) max = d[i];
      if (d[i] < min) min = d[i];
    }

    // Find the middle of the digits.
    int mid = d[0] + d[1] + d[2] - max - min;

    // Compute high - low.
    int high = 100*max + 10*mid + min;
    int low = 100*min + 10*mid + max;
    x = high - low;
    printf("%3d - %3d = %3d\n", high, low, x);
  } while (x != 495);

  return 0;
}
