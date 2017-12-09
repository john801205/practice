#include <iostream>
#include <algorithm>

int main(void)
{
  int N;

  while (std::cin >> N) {
    if (N == 0)
      break;

    int *ages = new int[N];

    for (int i = 0; i < N; ++i)
      std::cin >> ages[i];

    std::sort(ages, ages + N);

    std::cout << ages[0];
    for (int i = 1; i < N; ++i)
      std::cout << ' ' << ages[i];
    std::cout << std::endl;

    delete ages;
  }

  return 0;
}
