#include <cmath>
#include <cstdio>

int main(void)
{
  int p, q, r, s, t, u;

  while (scanf("%d%d%d%d%d%d", &p, &q, &r, &s, &t, &u) != EOF) {
    double left = 0, right = 1;
    double x, y;

    while (true) {
      // to make sure the output after rounding is correct up to
      // four digits, we should make sure five digits are the same.
      if (floor(left*100000) == floor(right*100000))
        break;

      x = (left + right) / 2;
      y = exp(-x)*p + sin(x)*q + cos(x)*r + tan(x)*s + x*x*t + u;

      if (y == 0)
        break;
      else if (y > 0)
        left = x;
      else
        right = x;
    }

    // the result is correct up to four digits
    if (y >= 0.001 || y <= -0.001)
      printf("No solution\n");
    else
      printf("%.4f\n", x);
  }

  return 0;
}
