#include <algorithm>
#include <iostream>
#include <set>
#include <string>
#include <vector>

int main(void)
{
  bool first = true;
  std::string a, b;

  while (std::cin >> a >> b)
  {
    if (!first)
      std::cout << '\n';

    std::vector<std::vector<int>> table (a.length() + 1,
                                         std::vector<int> (b.length() + 1, 0));

    std::set<std::string> longest_common_seqs;
    int length = 0;

    for (std::string::size_type i = 0; i < a.length(); i++)
    {
      for (std::string::size_type j = 0; j < b.length(); j++)
      {
        if (a[i] == b[j])
          table[i+1][j+1] = table[i][j] + 1;
        else
          table[i+1][j+1] = 0;

        if (table[i+1][j+1] >= length && table[i+1][j+1] != 0)
        {
          if (table[i+1][j+1] > length)
          {
            length = table[i+1][j+1];
            longest_common_seqs.clear();
          }

          std::string lcs (&a[i-table[i+1][j+1]+1], table[i+1][j+1]);
          longest_common_seqs.insert(lcs);
        }
      }
    }

    if (longest_common_seqs.empty())
      std::cout << "No common sequence.\n";
    else
      for (const auto &lcs: longest_common_seqs)
        std::cout << lcs << '\n';

    first = false;
  }

  return 0;
}
