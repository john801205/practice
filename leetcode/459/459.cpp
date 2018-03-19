#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

class Solution {
  public:
    bool repeatedSubstringPattern(std::string s)
    {
      std::vector<std::string::size_type> dp (s.size(), 0);

      for (std::string::size_type i = 1, j = 0; i < s.size(); )
      {
        if (s[i] == s[j])
        {
          j++;
          dp[i] = j;
          i++;
        }
        else if (j > 0)
        {
          j = dp[j-1];
        }
        else
        {
          i++;
        }
      }

      return dp.back() != 0 && dp.back() % (s.size() - dp.back()) == 0;
    }
};

int main(void)
{
  Solution s;
  std::string str;

  while (std::cin >> str)
  {
    std::cout << s.repeatedSubstringPattern(str) << '\n';
  }

  return 0;
}
