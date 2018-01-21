#include <iostream>
#include <vector>

int main(void)
{
  unsigned n, k, m;

  while (std::cin >> n >> k >> m)
  {
    std::vector<std::vector<long>> tables (n+1, std::vector<long>(k+1));

    // initialize
    for (std::vector<std::vector<long>>::size_type i = 1;
         i <= m and i <= n;
         i++)
      tables[i][1] = 1;

    // dynamic programming
    for (std::vector<std::vector<long>>::size_type i = 2; i <= n; i++)
    {
      for (std::vector<long>::size_type j = 2; j <= k; j++)
      {
        for (unsigned len = 1; len <= m and len < i; len++)
          tables[i][j] += tables[i-len][j-1];
      }
    }

    std::cout << tables[n][k] << '\n';
  }

  return 0;
}
