#include <iostream>
#include <vector>

int main(void)
{
  int N, D;

  while (std::cin >> N >> D)
  {
    if (N == 0 and D == 0)
      break;

    std::vector<bool> students (N, true);

    for (int d = 0; d < D; d++)
    {
      for (int n = 0; n < N; n++)
      {
        int attend;
        std::cin >> attend;

        students[n] = students[n] && (attend == 1);
      }
    }

    bool one = false;
    for (int n = 0; n < N; n++)
      one = one || students[n];

    if (one)
      std::cout << "yes\n";
    else
      std::cout << "no\n";
  }

  return 0;
}
