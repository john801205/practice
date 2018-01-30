#include <iostream>

int main(void)
{
  unsigned n, m, c;

  while (std::cin >> n >> m >> c)
  {
    if (n == 0 and m == 0 and c == 0)
      break;

    // if the bottom right corner is black
    // we add one bogus row to make it white
    if (c == 0)
      n += 1;

    // n, n-2, n-4, ... x m, m-2, m-4, ...
    int col_shifts = n >= 8 ? (n - 8) / 2 + 1: 0,
        row_shifts = m >= 8 ? (m - 8) / 2 + 1: 0;

    // n-1, n-3, n-5, ... x m-1, m-3, m-5, ...
    int col_shifts_inner = n-1 >= 8 ? (n - 9) / 2 + 1: 0,
        row_shifts_inner = m-1 >= 8 ? (m - 9) / 2 + 1: 0;

    // one shift is impossible because of the bogus row
    if (c == 0)
      col_shifts -= 1;

    std::cout << col_shifts*row_shifts + col_shifts_inner*row_shifts_inner << '\n';
  }

  return 0;
}
