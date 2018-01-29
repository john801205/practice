#include <iostream>

int main(void)
{
  int N;

  while (std::cin >> N)
  {
    for (int i = 0; i < N; i++)
    {
      int x, y;

      std::cin >> x >> y;

      if (x == y)
      {
        if (x & 1)
          std::cout << x*2-1 << '\n';
        else
          std::cout << x*2   << '\n';
      }
      else if (x == y+2)
      {
        if (x & 1)
          std::cout << x+y-1 << '\n';
        else
          std::cout << x+y << '\n';
      }
      else
      {
        std::cout << "No Number\n";
      }
    }
  }

  return 0;
}
