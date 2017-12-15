#include <iostream>

int main(void)
{
  int n;

  while (std::cin >> n) {
    if (n == 0)
      break;

    int a = 0, b = 0;
    bool odd = true;

    while (n & (-n)) {
      if (odd)
        a |= n & (-n);
      else
        b |= n & (-n);

      n -= n & (-n);
      odd = !odd;
    }

    std::cout << a << ' ' << b << std::endl;
  }

  return 0;
}
