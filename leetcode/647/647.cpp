#include <cassert>
#include <iostream>
#include <string>
#include <vector>

class Solution
{
  public:
    int countSubstrings(const std::string s)
    {
      std::vector<std::vector<bool>> dp (s.size(), std::vector<bool> (s.size(), false));
      std::string::size_type count = 0;

      for (std::string::size_type len = 0; len < s.size(); len++)
      {
        for (std::string::size_type i = 0; i+len < s.size(); i++)
        {
          std::string::size_type j = i + len;

          if (s[i] == s[j])
          {
            if (i+2 <= j && i+1 < s.size())
            {
              dp[i][j] = dp[i+1][j-1];
            }
            else
            {
              dp[i][j] = true;
            }
          }

          if (dp[i][j])
          {
            count++;
          }
        }
      }

      return count;
    }
};

int main(void)
{
  Solution s;
  assert(s.countSubstrings("") == 0);
  assert(s.countSubstrings("abc") == 3);
  assert(s.countSubstrings("aaa") == 6);
  assert(s.countSubstrings("abcdedcba") == 13);
  return 0;
}
