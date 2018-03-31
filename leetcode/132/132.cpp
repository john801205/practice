#include <cassert>
#include <climits>

#include <iostream>
#include <string>
#include <vector>

class Solution
{
  public:
    int minCut(const std::string s)
    {
      if (s.size() == 0)
      {
        return 0;
      }

      std::vector<std::vector<bool>> is_palindrome (s.size(), std::vector<bool> (s.size(), false));

      for (std::string::size_type len = 0; len < s.size(); len++)
      {
        for (std::string::size_type i = 0; i+len < s.size(); i++)
        {
          std::string::size_type j = i+len;

          if (s[i] == s[j] && (i+2 >= j || is_palindrome[i+1][j-1]))
          {
            is_palindrome[i][j] = true;
          }
        }
      }

      std::vector<int> dp (s.size()+1, INT_MAX);

      dp[0] = -1;
      for (std::string::size_type i = 0; i < s.size(); i++)
      {
        for (std::string::size_type j = 0; j <= i; j++)
        {
          if (dp[j] != INT_MAX && is_palindrome[j][i])
          {
            dp[i+1] = std::min(dp[i+1], dp[j]+1);
          }
        }
      }

      return dp.back();
    }
};

int main(void)
{
  Solution s;
  assert(s.minCut("aab") == 1);
  assert(s.minCut("aacbbcaa") == 0);
  assert(s.minCut("aacbbcaabcaacbcdeaedf") == 4);
  assert(s.minCut("cacbcdcacbcacd") == 3);
  assert(s.minCut("") == 0);
  return 0;
}
