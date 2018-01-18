#include <iostream>

int main(void)
{
  unsigned n;

  while (std::cin >> n)
  {
    unsigned row, n_copy = n;
    for (row = 1; row < n_copy; row++)
      n_copy -= row;

    if (row % 2 == 0)
      std::cout << "TERM " << n << " IS " << n_copy << "/" << row-n_copy+1 << '\n';
    else
      std::cout << "TERM " << n << " IS " << row-n_copy+1 << "/" << n_copy << '\n';
  }

  return 0;
}
