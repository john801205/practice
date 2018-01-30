#include <cmath>

#include <iostream>

int main(void)
{
  int N;

  while (std::cin >> N and N != 0)
  {
    int x, y;

    int root = static_cast<int>(std::floor(std::sqrt(N)));
    int remainder = N - root*root;

    x = 1;
    y = root;

    if (remainder > 0)
    {
      y += 1;
      remainder -= 1;
    }

    if (remainder > 0)
    {
      x += std::min(root, remainder);
      remainder -= std::min(root, remainder);
    }

    if (remainder > 0)
    {
      y -= std::min(root, remainder);
    }

    if ((root & 1) == 0)
      std::swap(x, y);

    std::cout << x << ' ' << y << '\n';
  }

  return 0;
}
