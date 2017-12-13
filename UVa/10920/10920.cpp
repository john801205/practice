#include <iostream>
#include <cmath>

int main(void)
{
  unsigned long long SZ, P;

  while (std::cin >> SZ >> P) {
    if (SZ == 0 && P == 0)
      break;

    unsigned circle, center, left;

    circle = (unsigned)(std::sqrt(P - 0.01) + 1) / 2;
    center = SZ / 2 + 1;
    left = P - (2*circle - 1) * (2*circle - 1);

    if (left <= circle*2) {
      std::cout << "Line = " << center + circle
                << ", column = " << center + circle - left << ".\n";
    } else if (left <= circle*4) {
      left -= circle * 2;
      std::cout << "Line = " << center + circle - left
                << ", column = " << center - circle << ".\n";
    } else if (left <= circle*6) {
      left -= circle * 4;
      std::cout << "Line = " << center - circle
                << ", column = " << center - circle + left << ".\n";
    } else {
      left -= circle * 6;
      std::cout << "Line = " << center - circle + left
                << ", column = " << center + circle << ".\n";
    }
  }

  return 0;
}
