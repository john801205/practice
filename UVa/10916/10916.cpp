#include <cmath>
#include <iostream>

int pow(int base, int exp)
{
  int result = 1;

  while (exp)
  {
    if (exp & 1)
      result *= base;

    exp >>= 1;
    base *= base;
  }

  return result;
}

int main(void)
{
  int year;

  while (std::cin >> year and year != 0)
  {
    int bits = 4 * pow(2, (year - 1960)/10);

    int i;
    double sum = 0;
    for (i = 1; sum < bits; i++)
      sum += std::log2(i);

    std::cout << i - 2 << '\n';
  }

  return 0;
}
