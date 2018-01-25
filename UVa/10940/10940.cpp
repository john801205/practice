#include <array>
#include <iostream>

#define MAX 500000

int main(void)
{
  std::array<int, MAX+1> table = {0, 1};

  for (std::array<int, MAX+1>::size_type i = 2; i < table.size(); i++)
  {
    if (i & 1)
    {
      // if i is odd
      table[i] = table[i/2+1] == 0 ? i : (table[i/2+1]-1) * 2;
    }
    else
    {
      // if i is even
      table[i] = table[i/2] * 2;
    }
  }

  unsigned n;

  while (std::cin >> n and n != 0)
  {
    std::cout << table[n] << '\n';
  }

  return 0;
}
