#include <algorithm>
#include <iostream>
#include <vector>

int gcd(int a, int b)
{
  while (b != 0)
  {
    int r = a % b;
    a = b;
    b = r;
  }

  return a;
}

int main(void)
{
  int N;

  while (std::cin >> N and N != 0)
  {
    std::vector<int> numbers ({N});

    while (std::cin >> N and N != 0)
      numbers.emplace_back(N);

    int min_element = *std::min_element(std::begin(numbers), std::end(numbers));

    for (auto &number: numbers)
      number -= min_element;

    int divisor = numbers.front();
    for (const auto &number: numbers)
    {
      if (number != 0)
      {
        divisor = gcd(divisor, number);
      }
    }

    std::cout << divisor << '\n';
  }

  return 0;
}
