#include <cassert>
#include <iostream>
#include <string>
#include <vector>

class Solution
{
  public:
    int numDistinct(const std::string s, const std::string t)
    {
      std::vector<int> dp (s.size()+1, 0);

      // empty s and empty t
      dp[0] = 1;

      // non-empty s and empty t
      for (std::string::size_type j = 0; j < s.size(); j++)
      {
        dp[j+1] = 1;
      }

      // dynamic programming
      for (std::string::size_type i = 0; i < t.size(); i++)
      {
        int prev = dp[0];
        dp[0] = 0;

        for (std::string::size_type j = 0; j < s.size(); j++)
        {
          int temp = dp[j+1];

          if (t[i] == s[j])
          {
            dp[j+1] = dp[j] + prev;
          }
          else
          {
            dp[j+1] = dp[j];
          }

          prev = temp;
        }
      }

      return dp.back();
    }
};

int main(void)
{
  Solution s;
  assert(s.numDistinct("rabbbit", "rabbit") == 3);
  assert(s.numDistinct("raabbbit", "rabb") == 6);
  assert(s.numDistinct("raabbbit", "rabbbb") == 0);
  assert(s.numDistinct("rabbit", "") == 1);
  assert(s.numDistinct("", "") == 1);
  return 0;
}
