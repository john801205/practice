#include <iostream>

int main(void)
{
  int n;

  while (std::cin >> n) {
    if (n == 0)
      break;

    int a = 0, count = 0;

    for (int i = 0, bit = 1; i < 31; i++, bit <<= 1) {
      if ((n & bit) == 0)
        continue;

      count++;
      if ((count & 1) == 1)
        a |= bit;
    }

    std::cout << a << ' ' << n - a << std::endl;
  }

  return 0;
}
