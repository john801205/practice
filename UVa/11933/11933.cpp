#include <iostream>

int main(void)
{
  int n;

  while (std::cin >> n) {
    if (n == 0)
      break;

    int a = 0, b = 0, i = 0;

    while (i < 31) {
      while (i < 31 && ((n >> i) & 1) == 0)
        i++;

      if (i < 31)
        a |= 1 << i;
      i++;

      while (i < 31 && ((n >> i) & 1) == 0)
        i++;

      if (i < 31)
        b |= 1 << i;
      i++;
    }

    std::cout << a << ' ' << b << std::endl;
  }

  return 0;
}
