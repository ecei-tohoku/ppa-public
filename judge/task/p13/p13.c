#include <stdio.h>

int main()
{
  int i;
  double v, s = 0., min = 20., max = 0.;

  for (i = 0; i < 7; ++i) {
    scanf("%lf", &v);
    if (v < min) {
      min = v;
    }
    if (max < v) {
      max = v;
    }
    s += v;
  }

  printf("%.2f\n", (s - min - max) / 5.);
  return 0;
}
