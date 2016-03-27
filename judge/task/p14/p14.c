#include <stdio.h>

int main()
{
  int i, j;
  double v[1246];

  for (i = 1; i <= 1245; ++i) {
    scanf("%lf", &v[i]);
  }

  for (i = 20; i <= 1245; ++i) {
    double sma5 = 0., sma20 = 0.;
    for (j = 0; j < 5; ++j) {
      sma5 += v[i-j];
    }
    for (j = 0; j < 20; ++j) {
      sma20 += v[i-j];
    }
    printf("%d %.2f %.2f %.2f\n", i, v[i], sma5 / 5, sma20 / 20);
  }

  return 0;
}
