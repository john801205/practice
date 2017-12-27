#include <climits>
#include <cstdio>

int main(void)
{
  int N;

  while (scanf("%d", &N) != EOF) {
    if (N == 0)
      break;

    int number, current_max, total_max;

    scanf("%d", &number);
    current_max = number;
    total_max = number;

    for (int i = 1; i < N; i++) {
      scanf("%d", &number);
      if (current_max > 0)
        current_max = current_max + number;
      else
        current_max = number;

      if (current_max > total_max)
        total_max = current_max;
    }

    if (total_max > 0)
      printf("The maximum winning streak is %d.\n", total_max);
    else
      printf("Losing streak.\n");
  }

  return 0;
}
